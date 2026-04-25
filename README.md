# OJ 在线判题系统

## 项目概述

OJ（Online Judge）是一个在线编程判题系统，用于支持编程竞赛和练习。本项目包含多个模块，提供完整的在线判题功能，包括用户管理、题目管理、代码评测、讨论区和排行榜等功能。

## 项目结构

```
OJ/
├── common/           # 公共模块，提供基础功能
├── datas/            # 数据相关文件，包括数据库脚本和登录功能
├── discussion/       # 讨论区模块
├── judge/            # 评测模块，负责代码编译和执行
├── management/       # 题目管理模块，基于Spring Boot
├── rank/             # 排行榜模块
├── 模块使用文档/     # 各模块的使用文档
└── README.md         # 项目说明文档
```

## 模块说明

### 1. common 模块

公共模块，提供基础功能，包括：
- 配置管理
- 日志处理
- 数据库连接池
- Redis缓存
- 错误处理

### 2. datas 模块

数据相关文件，包括：
- 数据库初始化脚本
- 登录功能（基于Spring Boot）

### 3. discussion 模块

讨论区模块，提供题目讨论功能。

### 4. judge 模块

评测模块，负责代码的编译和执行，支持多种编程语言。

### 5. management 模块

题目管理模块，基于Spring Boot，提供题目CRUD操作和管理功能。

### 6. rank 模块

排行榜模块，记录用户的解题情况和排名。

## 技术栈

- **后端**：C++17, Java 8, Spring Boot 2.7
- **数据库**：MySQL
- **缓存**：Redis
- **构建工具**：CMake, Maven

## 安装和运行

### 前提条件

- CMake 3.14+
- Maven 3.6+
- JDK 8+
- MySQL 5.7+
- Redis 5.0+

### 构建步骤

1. **编译C++模块**

```bash
# 在OJ根目录执行
mkdir build && cd build
cmake .. -DOJ_ENABLE_MYSQL=ON -DOJ_ENABLE_REDIS=ON
cmake --build .
```

2. **编译Java模块**

```bash
# 在management目录执行
mvn clean package
```

### 运行步骤

1. **初始化数据库**

执行 `datas/database/test.sql` 和 `management/main/resources/schema.sql` 脚本初始化数据库。

2. **启动各模块**

- **管理模块**：
  ```bash
  cd management
  java -jar target/problem-management-1.0.0.jar
  ```

- **评测模块**：
  ```bash
  cd build/judge
  ./judge
  ```

- **讨论区模块**：
  ```bash
  cd build/discussion
  ./discussion
  ```

- **排行榜模块**：
  ```bash
  cd build/rank
  ./rank
  ```

## 配置说明

各模块的配置可以通过环境变量或配置文件进行设置。具体配置项请参考各模块的说明文档。

## 模块使用文档

详细的模块使用文档请参考 `模块使用文档` 目录下的相关文件。

## 开发指南

### 代码风格

- C++代码：遵循Google C++风格指南
- Java代码：遵循Java编码规范

### 提交规范

- 提交信息应清晰明了，描述本次提交的内容
- 提交前应确保代码编译通过
- 提交前应运行相关测试

## 贡献

欢迎提交Issue和Pull Request，共同改进OJ系统。

## 许可证

本项目采用MIT许可证。