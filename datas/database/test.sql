-- 创建OJ数据库
CREATE DATABASE IF NOT EXISTS `oj`;
USE `oj`;

-- 用户表
CREATE TABLE IF NOT EXISTS `users` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(32) NOT NULL UNIQUE,
    password VARCHAR(60) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 题目表
CREATE TABLE IF NOT EXISTS `problems` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(100) NOT NULL,
    description TEXT NOT NULL,
    difficulty ENUM('EASY', 'MEDIUM', 'HARD') NOT NULL,
    time_limit INT NOT NULL,
    memory_limit INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- 标签表
CREATE TABLE IF NOT EXISTS `tags` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL UNIQUE
);

-- 题目标签关联表
CREATE TABLE IF NOT EXISTS `problem_tags` (
    problem_id INT NOT NULL,
    tag_id INT NOT NULL,
    PRIMARY KEY (problem_id, tag_id),
    FOREIGN KEY (problem_id) REFERENCES problems(id) ON DELETE CASCADE,
    FOREIGN KEY (tag_id) REFERENCES tags(id) ON DELETE CASCADE
);

-- 测试用例表
CREATE TABLE IF NOT EXISTS `test_cases` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    problem_id INT NOT NULL,
    input TEXT NOT NULL,
    output TEXT NOT NULL,
    is_sample BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (problem_id) REFERENCES problems(id) ON DELETE CASCADE
);

-- 提交表
CREATE TABLE IF NOT EXISTS `submissions` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    problem_id INT NOT NULL,
    code TEXT NOT NULL,
    language VARCHAR(20) NOT NULL,
    status ENUM('PENDING', 'ACCEPTED', 'WRONG_ANSWER', 'TIME_LIMIT_EXCEEDED', 'MEMORY_LIMIT_EXCEEDED', 'RUNTIME_ERROR', 'COMPILATION_ERROR') NOT NULL,
    execution_time INT,
    memory_used INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (problem_id) REFERENCES problems(id) ON DELETE CASCADE
);

-- 讨论帖子表
CREATE TABLE IF NOT EXISTS `discussion_posts` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    problem_id INT,
    title VARCHAR(200) NOT NULL,
    content TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (problem_id) REFERENCES problems(id) ON DELETE SET NULL
);

-- 讨论回复表
CREATE TABLE IF NOT EXISTS `discussion_replies` (
    id INT PRIMARY KEY AUTO_INCREMENT,
    post_id INT NOT NULL,
    user_id INT NOT NULL,
    content TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (post_id) REFERENCES discussion_posts(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- 排行榜表
CREATE TABLE IF NOT EXISTS `leaderboard` (
    user_id INT PRIMARY KEY,
    username VARCHAR(32) NOT NULL,
    solved_count INT DEFAULT 0,
    total_submissions INT DEFAULT 0,
    score INT DEFAULT 0,
    rating INT DEFAULT 1000,
    last_submission TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- 插入测试数据
INSERT INTO `users` (username, password) VALUES ("admin", "test123");
INSERT INTO `tags` (name) VALUES ("算法"), ("数据结构"), ("动态规划"), ("贪心"), ("图论");

-- 查看用户数据
SELECT * FROM `users`;