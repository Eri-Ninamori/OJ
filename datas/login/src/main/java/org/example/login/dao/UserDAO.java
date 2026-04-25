package org.example.login.dao;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public class UserDAO {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    public String findPasswordByUsername(String username) {
        String sql = "SELECT password FROM `users` WHERE username = ?";
        List<String> results = jdbcTemplate.queryForList(sql, new Object[]{username}, String.class);
        return results.isEmpty() ? "" : results.get(0);
    }

    public boolean findUsername(String username) {
        String sql = "SELECT EXISTS (SELECT 1 FROM `users` WHERE username = ?) AS isExist";
        Integer result = jdbcTemplate.queryForObject(sql, new Object[]{username}, Integer.class);
        return result != null && result == 1;
    }

    public int registerUser(String username, String password) {
        String sql = "INSERT INTO `users` (username, password) VALUES (?, ?)";
        return jdbcTemplate.update(sql, username, password);
    }
}
