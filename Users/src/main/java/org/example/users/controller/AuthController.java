package org.example.users.controller;

import jakarta.servlet.http.HttpSession;
import org.example.users.entity.User;
import org.example.users.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
public class AuthController {
    private final UserService userService;

    public AuthController(UserService userService) {
        this.userService = userService;
    }

    // 展示欢迎界面
    @GetMapping({"", "index", "index.html"})
    public String showIndex() {
        return "index";
    }

    // 展示用户登录界面
    @GetMapping("/login")
    public String showLogin(HttpSession session, Model model) {
        // 检查 session 中的提示信息
        String loginMsg = (String) session.getAttribute("loginMsg");
        String registerMsg = (String) session.getAttribute("registerMsg");

        // 出现错误
        if (loginMsg != null) {
            model.addAttribute("errorMsg", "无效的用户名或密码");
            session.removeAttribute("loginMsg");
        }
        // 注册成功
        if (registerMsg != null) {
            model.addAttribute("successMsg", "注册成功，请登录");
            session.removeAttribute("registerMsg");
        }

        return "login";
    }

    // 处理用户登录请求
    @PostMapping("/login")
    public String handleLogin(String username,
                            String password,
                            HttpSession session) {
        // 检验用户身份
        User user = userService.authenticate(username, password);
        if (user == null) {
            session.setAttribute("loginMsg", "invalid username or password");
            return "redirect:/login";
        }
        else {
            session.setAttribute("loginUser", username);
            return "redirect:/home";
        }
    }

    // 展示用户主页
    @GetMapping({"/home"})
    public String showHome(HttpSession session) {
        String username = (String) session.getAttribute("loginUser");
        // 无 Session 时重定向至登录界面
        if (username != null) {
            return "home";
        }
        return "redirect:/login";
    }

    // 处理用户登出
    @GetMapping({"/logout"})
    public String handleLogout(HttpSession session, RedirectAttributes redirectAttributes) {
        // 销毁当前 session
        session.invalidate();

        // 将注销成功写入 Flash 中
        redirectAttributes.addFlashAttribute("successMsg", "注销成功");

        return "redirect:/login";
    }

    // 展示用户注册界面
    @GetMapping("/register")
    public String showRegister(HttpSession session, Model model) {
        // 检查 session 中的提示信息
        String registerMsg = (String) session.getAttribute("registerMsg");

        // 用户名被占用
        if (registerMsg != null) {
            model.addAttribute("errorMsg", "用户名已被占用");
            session.removeAttribute("registerMsg");
        }

        return "register";
    }

    // 处理用户注册请求
    @PostMapping("/register")
    public String handleRegister(String username,
                                 String password,
                                 HttpSession session) {
        // 检验用户名是否可用
        boolean valid = userService.checkUsername(username);
        if (valid) {
            userService.insertUser(username, password);
            session.setAttribute("registerMsg", "successfully register");
            return "redirect:/login";
        }
        else {
            session.setAttribute("registerMsg", "invalid username");
            return "redirect:/register";
        }
    }
}