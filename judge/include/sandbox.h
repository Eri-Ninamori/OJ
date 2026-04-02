/**
 * @file sandbox.h
 * @brief 沙箱环境管理
 * @author OJ Team
 * @date 2024-01-01
 */
#ifndef SANDBOX_H
#define SANDBOX_H

#include <string>

/**
 * @struct SandboxConfig
 * @brief 沙箱配置结构体
 */
struct SandboxConfig {
    int time_limit_ms;       ///< 时间限制（毫秒）
    int memory_limit_mb;     ///< 内存限制（MB）
    int output_limit_mb;     ///< 输出限制（MB）
    bool enable_network;     ///< 是否启用网络
    bool enable_file_system; ///< 是否启用文件系统
};

/**
 * @struct SandboxResult
 * @brief 沙箱执行结果结构体
 */
struct SandboxResult {
    int exit_code;         ///< 退出码
    int runtime_ms;        ///< 运行时间（毫秒）
    int memory_kb;         ///< 内存使用（KB）
    std::string output;    ///< 标准输出
    std::string error;     ///< 错误输出
    bool timeout;          ///< 是否超时
    bool memory_exceeded;  ///< 是否内存超限
};

/**
 * @class Sandbox
 * @brief 沙箱环境类
 */
class Sandbox {
public:
    /**
     * @brief 构造函数
     * @param config 沙箱配置
     */
    Sandbox(const SandboxConfig& config);
    
    /**
     * @brief 执行命令
     * @param command 命令字符串
     * @param input 输入数据
     * @return 执行结果
     */
    SandboxResult execute(const std::string& command, 
                       const std::string& input);
    
private:
    SandboxConfig config_; ///< 沙箱配置
    
    /**
     * @brief 设置资源限制
     * @return 是否设置成功
     */
    bool setupResourceLimits();
    
    /**
     * @brief 创建隔离环境
     * @return 是否创建成功
     */
    bool createIsolatedEnvironment();
};

#endif // SANDBOX_H