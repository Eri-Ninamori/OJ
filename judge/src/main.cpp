#include "submission_handler.h"
#include <iostream>

int main() {
    try {
        // 创建提交处理器
        SubmissionHandler handler;
        
        // 启动服务器
        std::cout << "Judge server starting on port 8080..." << std::endl;
        handler.startServer(8080);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}