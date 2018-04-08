# 局域网接入

局域网对接是接入 Rokid Homebase 最简单的方式：

## 基本组成
![](https://s.rokidcdn.com/homebase/upload/r1H-Qt-wM.jpg)

1. 自动发现：自动发现主机
2. 远程驱动：HTTP 或 TCP 协议接口， 提供设备列表， 和设备控制接口

## 相关文档

自动发现基于SSDP， 文档在 https://rokid.github.io/rokid-homebase-docs/connect/ssdp-auto-discovery.html

通过自动发现， 我们可以发现网桥和网桥提供的接口。 接口通过（HTTP 或 TCP) 两种协议给出。

HTTP 协议地址： https://rokid.github.io/rokid-homebase-docs/connect/http-remote-driver.html

TCP 协议地址： https://rokid.github.io/rokid-homebase-docs/connect/json-rpc-over-tcp.html



## 可以参考我们的示例程序

https://github.com/Rokid/homebase-ssdp-tcp-driver-sample



