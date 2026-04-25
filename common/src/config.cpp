#include "oj/config.h"

#include <cstdlib>
#include <fstream>
#include <stdexcept>

// 包含nlohmann/json库
#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace oj {

static std::string getenvOr(const char* key, const std::string& def) {
#if defined(_WIN32)
    char* buf = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, key) == 0 && buf) {
        std::string v(buf);
        std::free(buf);
        return v;
    }
    return def;
#else
    const char* v = std::getenv(key);
    return v ? std::string(v) : def;
#endif
}

static unsigned getenvUInt(const char* key, unsigned def) {
    std::string s = getenvOr(key, "");
    if (s.empty()) {
        return def;
    }
    return static_cast<unsigned>(std::stoul(s));
}

AppConfig loadConfigFromEnv() {
    AppConfig c;
    c.mysql_host = getenvOr("OJ_MYSQL_HOST", c.mysql_host);
    c.mysql_port = getenvUInt("OJ_MYSQL_PORT", c.mysql_port);
    c.mysql_user = getenvOr("OJ_MYSQL_USER", c.mysql_user);
    c.mysql_password = getenvOr("OJ_MYSQL_PASSWORD", c.mysql_password);
    c.mysql_database = getenvOr("OJ_MYSQL_DATABASE", c.mysql_database);
    c.mysql_pool_min = getenvUInt("OJ_MYSQL_POOL_MIN", c.mysql_pool_min);
    c.mysql_pool_max = getenvUInt("OJ_MYSQL_POOL_MAX", c.mysql_pool_max);

    c.redis_host = getenvOr("OJ_REDIS_HOST", c.redis_host);
    c.redis_port = getenvUInt("OJ_REDIS_PORT", c.redis_port);
    c.redis_password = getenvOr("OJ_REDIS_PASSWORD", c.redis_password);
    c.redis_db = static_cast<int>(getenvUInt("OJ_REDIS_DB", static_cast<unsigned>(c.redis_db)));

    c.log_file = getenvOr("OJ_LOG_FILE", c.log_file);
    c.log_level = getenvOr("OJ_LOG_LEVEL", c.log_level);
    return c;
}

AppConfig loadConfigFromJson(const std::string& configFile) {
    AppConfig c;
    
    // 读取配置文件
    std::ifstream ifs(configFile);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open config file: " + configFile);
    }
    
    json j;
    ifs >> j;
    
    // 读取数据库配置
    if (j.contains("database") && j["database"].contains("mysql")) {
        const auto& mysql = j["database"]["mysql"];
        if (mysql.contains("host")) c.mysql_host = mysql["host"];
        if (mysql.contains("port")) c.mysql_port = mysql["port"];
        if (mysql.contains("user")) c.mysql_user = mysql["user"];
        if (mysql.contains("password")) c.mysql_password = mysql["password"];
        if (mysql.contains("database")) c.mysql_database = mysql["database"];
        if (mysql.contains("pool_min")) c.mysql_pool_min = mysql["pool_min"];
        if (mysql.contains("pool_max")) c.mysql_pool_max = mysql["pool_max"];
    }
    
    // 读取Redis配置
    if (j.contains("redis")) {
        const auto& redis = j["redis"];
        if (redis.contains("host")) c.redis_host = redis["host"];
        if (redis.contains("port")) c.redis_port = redis["port"];
        if (redis.contains("password")) c.redis_password = redis["password"];
        if (redis.contains("db")) c.redis_db = redis["db"];
    }
    
    // 读取日志配置
    if (j.contains("log")) {
        const auto& log = j["log"];
        if (log.contains("file")) c.log_file = log["file"];
        if (log.contains("level")) c.log_level = log["level"];
    }
    
    return c;
}

}  // namespace oj
