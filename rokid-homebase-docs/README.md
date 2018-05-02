## 智能家居设备接入平台简介

智能家居设备接入平台为智能家居厂商，提供了语音控制智能设备或智能网关的整套解决方案。

### Homebase 框架

Rokid Homebase，是面向智能家居的设备接入框架，通过适配接入 Homebase 协议，即可实现用户与设备或服务的智能语音交互。使用 Homebase 框架接入 Rokid 语音体系有如下特色：

- **极致体验**： 经过打磨的语音交互体验；
- **全屋控制**： 分区域， 分房间控制；
- **快速接入**： 两周完成智能语音接入；
- **开放协议**： 基于开放协议，跨生态互联；

![Homebase](https://s.rokidcdn.com/homebase/upload/S1mEU8c6e.jpg)

### 接入方案

目前我们提供云云对接、局域网对接两种接入方案。主推云云对接，通过 OAuth 协议接入用户授权。

#### 1. 云云对接

云云对接，即厂商自建设备云服务与 Homebase 云服务的对接，厂商智能家居设备连接自建云服务后，遵循 Homebase 协议进行接口适配，实现与 Homebase 云服务的接驳。

您可以参考 [云云对接](connect/cloud-to-cloud.md) 文档来完成对接。

#### 2. 局域网对接

局域网对接，即通过简单服务发现协议（SSDP），实现同一局域网内智能家居网桥设备和 Rokid 设备的对接，同样需要遵循 Homebase 协议。

您可以参考 [局域网对接](connect/via-lan.md) 文档来完成对接。

### 链接

- [智能家居开发者论坛](https://developer-forum.rokid.com/c/smart-home)
- [Rokid 官网](https://www.rokid.com/)
- [Rokid 开放平台](http://developer.rokid.com/)
