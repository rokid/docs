## 局域网对接

局域网对接，即通过简单服务发现协议（SSDP），实现同一局域网内智能家居网桥设备和 Rokid 设备的对接。

### 基本组成

![](https://s.rokidcdn.com/homebase/upload/r1H-Qt-wM.jpg)

对接步骤：

1. 自动发现：基于 SSDP 协议实现自动发现服务；
2. 远程驱动：基于 HTTP 或 TCP 协议实现服务，提供设备列表和设备控制接口；

### 相关文档

- 自动发现基于 SSDP 协议：[SSDP Auto Discovery](./ssdp-auto-discovery.md)

通过自动发现，我们可以发现网桥和网桥提供的接口。接口通过（HTTP 或 TCP) 两种协议给出。

- HTTP 协议地址：[HTTP Remote Driver](./http-remote-driver.md)
- TCP 协议地址：[JSON RPC over TCP](./json-rpc-over-tcp.md)

### 可以参考我们的示例程序

https://github.com/Rokid/homebase-ssdp-tcp-driver-sample
