/**
 * @file submission_handler.cpp
 * @brief 提交处理器实现
 * @author OJ Team
 * @date 2024-01-01
 */
#include "submission_handler.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

/**
 * @brief 构造函数
 */
SubmissionHandler::SubmissionHandler() {
    judge_engine_ = std::make_unique<JudgeEngine>();
    app_ = std::make_unique<crow::SimpleApp>();
    
    // 注册路由
    CROW_ROUTE((*app_), "/api/submit").methods("POST"](const crow::request& req) {
        return handleSubmit(req);
    });
    
    CROW_ROUTE((*app_), "/api/submissions").methods("GET"](const crow::request& req) {
        return handleGetSubmissions(req);
    });
    
    CROW_ROUTE((*app_), "/api/submissions/<int>").methods("GET"](const crow::request& req, int id) {
        return handleGetSubmission(req, id);
    });
    
    CROW_ROUTE((*app_), "/api/submissions/<int>/status").methods("GET"](const crow::request& req, int id) {
        return handleSubmissionStatus(req, id);
    });
}

/**
 * @brief 验证提交
 * @param req HTTP请求
 * @return 是否验证通过
 */
bool SubmissionHandler::validateSubmission(const crow::request& req) {
    try {
        auto body = json::parse(req.body);
        if (!body.contains("code") || !body.contains("language") || !body.contains("problem_id")) {
            return false;
        }
        return true;
    } catch (...) {
        return false;
    }
}

/**
 * @brief 处理代码提交
 * @param req HTTP请求
 * @return HTTP响应
 */
crow::response SubmissionHandler::handleSubmit(const crow::request& req) {
    if (!validateSubmission(req)) {
        return crow::response(400, "Invalid submission format");
    }
    
    try {
        auto body = json::parse(req.body);
        std::string code = body["code"];
        std::string language = body["language"];
        int problem_id = body["problem_id"];
        
        // 模拟测试用例
        std::vector<TestCase> test_cases;
        TestCase test_case1;
        test_case1.id = 1;
        test_case1.input = "1 2";
        test_case1.expected_output = "3";
        test_case1.score = 50;
        test_cases.push_back(test_case1);
        
        TestCase test_case2;
        test_case2.id = 2;
        test_case2.input = "10 20";
        test_case2.expected_output = "30";
        test_case2.score = 50;
        test_cases.push_back(test_case2);
        
        // 评测代码
        JudgeResult result = judge_engine_->judge(code, language, test_cases, 1000, 128);
        
        // 构建响应
        json response_data;
        response_data["submission_id"] = 1; // 模拟ID
        response_data["problem_id"] = problem_id;
        response_data["language"] = language;
        response_data["status"] = static_cast<int>(result.overall_status);
        response_data["runtime"] = result.runtime_ms;
        response_data["memory"] = result.memory_kb;
        response_data["error_message"] = result.error_message;
        
        json test_case_results;
        for (const auto& tc_result : result.test_case_results) {
            json tc_data;
            tc_data["case_id"] = tc_result.case_id;
            tc_data["status"] = static_cast<int>(tc_result.status);
            tc_data["runtime"] = tc_result.runtime_ms;
            tc_data["memory"] = tc_result.memory_kb;
            tc_data["passed"] = tc_result.passed;
            test_case_results.push_back(tc_data);
        }
        response_data["test_cases"] = test_case_results;
        
        return crow::response(200, response_data.dump());
    } catch (const std::exception& e) {
        return crow::response(500, std::string("Internal error: ") + e.what());
    }
}

/**
 * @brief 获取提交列表
 * @param req HTTP请求
 * @return HTTP响应
 */
crow::response SubmissionHandler::handleGetSubmissions(const crow::request& req) {
    // 模拟返回提交列表
    json response_data = json::array();
    
    json submission1;
    submission1["id"] = 1;
    submission1["problem_id"] = 1;
    submission1["language"] = "cpp";
    submission1["status"] = 2; // ACCEPTED
    submission1["submit_time"] = "2024-01-01 12:00:00";
    response_data.push_back(submission1);
    
    json submission2;
    submission2["id"] = 2;
    submission2["problem_id"] = 2;
    submission2["language"] = "python";
    submission2["status"] = 3; // WRONG_ANSWER
    submission2["submit_time"] = "2024-01-01 12:30:00";
    response_data.push_back(submission2);
    
    return crow::response(200, response_data.dump());
}

/**
 * @brief 获取提交详情
 * @param req HTTP请求
 * @param id 提交ID
 * @return HTTP响应
 */
crow::response SubmissionHandler::handleGetSubmission(const crow::request& req, int64_t id) {
    // 模拟返回提交详情
    json response_data;
    response_data["id"] = id;
    response_data["problem_id"] = 1;
    response_data["language"] = "cpp";
    response_data["code"] = "#include <iostream>\nint main() { int a, b; std::cin >> a >> b; std::cout << a + b << std::endl; return 0; }";
    response_data["status"] = 2; // ACCEPTED
    response_data["runtime"] = 100;
    response_data["memory"] = 4096;
    response_data["submit_time"] = "2024-01-01 12:00:00";
    
    return crow::response(200, response_data.dump());
}

/**
 * @brief 获取评测状态（SSE）
 * @param req HTTP请求
 * @param id 提交ID
 * @return HTTP响应
 */
crow::response SubmissionHandler::handleSubmissionStatus(const crow::request& req, int64_t id) {
    // 模拟SSE响应
    std::string response = "event: status\ndata: {\"status\": 2, \"runtime\": 100, \"memory\": 4096}\n\n";
    return crow::response(200, response);
}

/**
 * @brief 启动服务器
 * @param port 端口号
 */
void SubmissionHandler::startServer(uint16_t port) {
    app_->port(port).multithreaded().run();
}