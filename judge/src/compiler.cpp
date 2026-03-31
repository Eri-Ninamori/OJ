/**
 * @file compiler.cpp
 * @brief 编译器实现
 * @author OJ Team
 * @date 2024-01-01
 */
#include "compiler.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>

/**
 * @brief 执行命令并获取输出
 * @param command 命令字符串
 * @return 执行结果
 */
CompileResult executeCommand(const std::string& command) {
    CompileResult result;
    result.success = false;
    result.exit_code = -1;
    
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        result.error = "Failed to open pipe";
        return result;
    }
    
    char buffer[1024];
    std::string output;
    
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }
    
    result.exit_code = pclose(pipe);
    result.success = (result.exit_code == 0);
    result.output = output;
    
    return result;
}

/**
 * @brief 保存代码到临时文件
 * @param code 代码内容
 * @param extension 文件扩展名
 * @return 临时文件路径
 */
std::string saveToTempFile(const std::string& code, const std::string& extension) {
    char temp_name[L_tmpnam_s + extension.size() + 1];
    tmpnam_s(temp_name, L_tmpnam_s);
    std::string temp_file = std::string(temp_name) + extension;
    
    std::ofstream file(temp_file);
    if (file.is_open()) {
        file << code;
        file.close();
    }
    
    return temp_file;
}

/**
 * @brief 编译C代码
 * @param source_code C源代码
 * @param output_path 输出文件路径
 * @return 编译结果
 */
CompileResult CCompiler::compile(const std::string& source_code, const std::string& output_path) {
    std::string temp_file = saveToTempFile(source_code, ".c");
    std::string command = "gcc -std=c11 -O2 -o " + output_path + " " + temp_file;
    
    CompileResult result = executeCommand(command);
    
    // 清理临时文件
    remove(temp_file.c_str());
    
    return result;
}

/**
 * @brief 编译C++代码
 * @param source_code C++源代码
 * @param output_path 输出文件路径
 * @return 编译结果
 */
CompileResult CppCompiler::compile(const std::string& source_code, const std::string& output_path) {
    std::string temp_file = saveToTempFile(source_code, ".cpp");
    std::string command = "g++ -std=c++17 -O2 -o " + output_path + " " + temp_file;
    
    CompileResult result = executeCommand(command);
    
    // 清理临时文件
    remove(temp_file.c_str());
    
    return result;
}

/**
 * @brief 编译Java代码
 * @param source_code Java源代码
 * @param output_path 输出文件路径
 * @return 编译结果
 */
CompileResult JavaCompiler::compile(const std::string& source_code, const std::string& output_path) {
    std::string temp_file = saveToTempFile(source_code, ".java");
    std::string command = "javac " + temp_file;
    
    CompileResult result = executeCommand(command);
    
    // 清理临时文件
    remove(temp_file.c_str());
    
    return result;
}

/**
 * @brief 编译Python代码
 * @param source_code Python源代码
 * @param output_path 输出文件路径
 * @return 编译结果
 */
CompileResult PythonCompiler::compile(const std::string& source_code, const std::string& output_path) {
    // Python 是解释型语言，不需要编译
    CompileResult result;
    result.success = true;
    result.exit_code = 0;
    result.output = "Python code does not require compilation";
    
    // 保存代码到文件
    std::ofstream file(output_path);
    if (file.is_open()) {
        file << source_code;
        file.close();
    }
    
    return result;
}