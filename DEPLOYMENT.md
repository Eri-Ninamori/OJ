# OJ 系统部署和使用指南

## 1. 系统要求

### 硬件要求
- CPU: 至少2核
- 内存: 至少4GB
- 存储空间: 至少50GB

### 软件要求
- **操作系统**: Windows 10/11 或 Linux
- **JDK**: 8 或以上版本
- **Maven**: 3.6 或以上版本
- **CMake**: 3.14 或以上版本
- **MySQL**: 5.7 或以上版本
- **Redis**: 5.0 或以上版本（可选）

## 2. 安装步骤

### 2.1 克隆代码仓库

```bash
git clone <repository-url>
cd OJ
```

### 2.2 安装依赖

#### Windows 系统
1. 安装 JDK 8 或以上版本，并配置环境变量
2. 安装 Maven 3.6 或以上版本，并配置环境变量
3. 安装 CMake 3.14 或以上版本，并配置环境变量
4. 安装 MySQL 5.7 或以上版本，并启动服务
5. 安装 Redis 5.0 或以上版本（可选），并启动服务

#### Linux 系统
```bash
# 安装 JDK
sudo apt-get install openjdk-8-jdk

# 安装 Maven
sudo apt-get install maven

# 安装 CMake
sudo apt-get install cmake

# 安装 MySQL
sudo apt-get install mysql-server

# 安装 Redis（可选）
sudo apt-get install redis-server
```

### 2.3 配置数据库

1. 启动 MySQL 服务
2. 执行数据库初始化脚本：

```bash
mysql -u root -p < datas/database/test.sql
```

3. 创建数据库用户：

```sql
CREATE USER 'oj'@'localhost' IDENTIFIED BY 'your_mysql_password';
GRANT ALL PRIVILEGES ON oj.* TO 'oj'@'localhost';
FLUSH PRIVILEGES;
```

### 2.4 配置系统

1. 编辑 `config.json` 文件，修改以下配置：
   - 数据库连接信息
   - Redis 连接信息（如果使用）
   - 各模块的端口配置

## 3. 编译和构建

### 3.1 编译 C++ 模块

```bash
mkdir build
cd build
cmake .. -DOJ_ENABLE_MYSQL=ON -DOJ_ENABLE_REDIS=ON
cmake --build .
```

### 3.2 编译 Java 模块

```bash
cd management
mvn clean package
```

## 4. 启动和停止系统

### 4.1 启动系统

#### 使用启动脚本

```bash
# Windows 系统
start_oj.bat

# Linux 系统
chmod +x start_oj.sh
./start_oj.sh
```

#### 手动启动

1. 启动管理模块：
   ```bash
   cd management
   java -jar target/problem-management-1.0.0.jar
   ```

2. 启动评测模块：
   ```bash
   cd build/judge
   ./judge
   ```

3. 启动讨论区模块：
   ```bash
   cd build/discussion
   ./discussion
   ```

4. 启动排行榜模块：
   ```bash
   cd build/rank
   ./rank
   ```

5. 启动登录模块：
   ```bash
   cd datas/login
   mvn spring-boot:run
   ```

### 4.2 停止系统

#### 使用停止脚本

```bash
# Windows 系统
stop_oj.bat

# Linux 系统
chmod +x stop_oj.sh
./stop_oj.sh
```

#### 手动停止

- 停止 Java 进程：
  ```bash
  # Windows 系统
taskkill /f /im java.exe

  # Linux 系统
  pkill -f java
  ```

- 停止 C++ 进程：
  ```bash
  # Windows 系统
taskkill /f /im judge.exe
taskkill /f /im discussion.exe
taskkill /f /im rank.exe

  # Linux 系统
  pkill -f judge
  pkill -f discussion
  pkill -f rank
  ```

## 5. 访问系统

启动成功后，可以通过以下地址访问各个模块：

- **管理模块**: http://localhost:8083/api
- **评测模块**: http://localhost:8080
- **讨论区模块**: http://localhost:8081
- **排行榜模块**: http://localhost:8082
- **登录模块**: http://localhost:8084

## 6. 系统使用

### 6.1 管理员操作

1. **登录管理系统**：访问 http://localhost:8083/api，使用用户名 `admin` 和密码 `test123` 登录

2. **创建题目**：
   - 点击 "创建题目" 按钮
   - 填写题目信息，包括标题、描述、难度、时间限制和内存限制
   - 添加测试用例
   - 选择标签
   - 点击 "保存" 按钮

3. **管理题目**：
   - 查看题目列表
   - 编辑题目
   - 删除题目
   - 查看题目详情

### 6.2 用户操作

1. **注册账号**：访问 http://localhost:8084/register，填写用户名和密码

2. **登录系统**：访问 http://localhost:8084/login，使用注册的用户名和密码登录

3. **浏览题目**：
   - 查看题目列表
   - 查看题目详情
   - 提交代码

4. **查看排行榜**：访问 http://localhost:8082，查看用户排名

5. **参与讨论**：访问 http://localhost:8081，查看和发布讨论帖子

## 7. 系统配置

### 7.1 配置文件说明

系统配置文件为 `config.json`，位于项目根目录。主要配置项包括：

- **database**: 数据库配置
- **redis**: Redis 配置（可选）
- **log**: 日志配置
- **modules**: 各模块配置

### 7.2 环境变量

除了配置文件外，系统还支持通过环境变量覆盖配置：

- **OJ_MYSQL_HOST**: MySQL 主机地址
- **OJ_MYSQL_PORT**: MySQL 端口
- **OJ_MYSQL_USER**: MySQL 用户名
- **OJ_MYSQL_PASSWORD**: MySQL 密码
- **OJ_MYSQL_DATABASE**: MySQL 数据库名
- **OJ_REDIS_HOST**: Redis 主机地址
- **OJ_REDIS_PORT**: Redis 端口
- **OJ_REDIS_PASSWORD**: Redis 密码
- **OJ_REDIS_DB**: Redis 数据库编号
- **OJ_LOG_FILE**: 日志文件路径
- **OJ_LOG_LEVEL**: 日志级别

## 8. 故障排查

### 8.1 常见问题

1. **数据库连接失败**：
   - 检查 MySQL 服务是否启动
   - 检查数据库连接配置是否正确
   - 检查数据库用户权限是否正确

2. **编译失败**：
   - 检查 CMake 版本是否符合要求
   - 检查依赖项是否安装
   - 检查代码是否有语法错误

3. **模块启动失败**：
   - 检查端口是否被占用
   - 检查配置文件是否正确
   - 检查依赖服务是否启动

### 8.2 日志查看

各模块的日志信息：

- **管理模块**: 控制台输出
- **评测模块**: 控制台输出
- **讨论区模块**: 控制台输出
- **排行榜模块**: 控制台输出
- **登录模块**: 控制台输出

## 9. 系统维护

### 9.1 数据库备份

定期备份数据库，防止数据丢失：

```bash
# 备份数据库
mysqldump -u oj -p oj > oj_backup.sql

# 恢复数据库
mysql -u oj -p oj < oj_backup.sql
```

### 9.2 系统更新

1. 停止系统
2. 拉取最新代码
3. 重新编译和构建
4. 启动系统

## 10. 技术支持

如果遇到问题，请联系系统管理员或查看项目文档。