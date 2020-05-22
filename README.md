# 加密通信基础架构
- WARN：目前只支持英文
- 查看接收方结果：http://code.douge.net.cn/

## 文件说明
### client.py
- 通信客户端
- 打开即开始与服务器进行通信

### code_server.py
- 服务程序
- 使用Flask架构，运行在Linux系统，由Apache2提供HTTP服务
- 一方面，处理来自客户端的Post请求，转发给解密程序
- 另一方面，响应浏览器Get请求，返回解密结果

### decryptor.py
- 解密程序样例
- 使用混合解码方法
- 处理来自服务程序的信息，并返回解码结果

### encryptor.py
- 加密程序样例
- 使用混合编码方法
- 获取人工输入的信息，发送给通信客户端

### Mixcode.py
- 混合编码类
- 对称加密样例，提供加密方法和解密方法

## 样例使用方法
- 建立工作空间，将client.py和encryptor.py放在工作空间中
- 运行client.py
- 运行encryptor.py，输入待传输信息

## ToDo
- 目前只支持英文！试图发送中文会使系统崩溃；
- 文件支持
- UI界面
- 更多的加密方法