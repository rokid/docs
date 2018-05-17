## 云云对接

云云对接，即厂商自建设备云服务与 Homebase 云服务的对接，厂商智能家居设备连接自建云服务后，适配若琪智能家居协议，实现与 Homebase 云服务的接驳。

### 简介

![云云对接示意图](https://s.rokidcdn.com/homebase/upload/BygMjQZwM.jpg)

智能家居设备云云对接遵循 [若琪智能家居协议](../v2/message-reference.md)

对接步骤：

1. 完成用户授权，授权用户；
2. 开发云端驱动, 提供设备搜索接口和设备控制接口；
3. 完成测试；
4. 提交云端驱动信息给我们；

### 相关文档

- 用户授权基于标准的 OAuth 2.0 协议：[符合 RFC6749 的 OAuth2.0](./rfc6749.md)

通过用户授权，我们能够将厂商设备控制权交给若琪。另外，在开发和调试环节：

- 开发云端驱动参考：[若琪智能家居协议](../v2/message-reference.md) 
- 调试可以使用：[rhome 命令行工具](../tools/rhome.md) 或 [自定义接入](../tools/developer-driver.md)

### 可以参考我们的示例程序

- [homebase-ssdp-tcp-driver-sample](https://github.com/Rokid/homebase-ssdp-tcp-driver-sample)
