## 智能家居设备接入流程

智能家居设备接入流程可以分为 4 个步骤：

![](https://s.rokidcdn.com/homebase/upload/ByGeJ4PTG.jpg)

### Step 1：注册开发者

申请成为智能家居开发者需要准备：

- 向商务申请一台测试的若琪设备；
- 先将测试若琪的 sn 码发给我们，我们会将其加入到开发者环境中；

**注意：**

有些厂商希望在自有 APP 中进行设备管理，并希望通过自有 APP 账号登录来自动绑定 Rokid 账号，这种情况您需要联系我们申请 appId，并在自有 APP 中集成 Rokid SDK。

您可以参考以下文档集成 Rokid SDK：

- [Rokid Mobile SDK IOS 开发指南](https://rokid.github.io/mobile-sdk-ios-docs)
- [Rokid Mobile SDK Android 开发指南](https://rokid.github.io/mobile-sdk-android-docs)

### Step 2：开发

不管是云云对接，还是局域网对接，您都需要遵循[智能家居协议](v2/message-reference.html)，提供设备列表查询接口、设备控制接口、设备状态查询接口（可选）。

**云云对接**

对于云云对接，我们遵循 OAuth 2.0 协议接入三方用户授权。因此，设备云服务端还需要实现一套标准的 OAuth 2.0 授权机制。

您可以参考以下文档完成云云对接：

- [OAuth 2.0 协议](connect/rfc6749.html)
- [云云对接](connect/cloud-to-cloud.md)

**局域网对接**

对于局域网对接，我们遵循 SSDP 协议实现局域网内的设备自动发现。

您可以参考以下文档完成局域网对接：

- [局域网自动发现](connect/ssdp-auto-discovery.html)
- [局域网对接](connect/via-lan.md)

### Step 3：调试

我们提供两种测试方式：

**命令行接口校验工具 - rhome**

使用 rhome 工具通过 json schema 来验证 discover|control|report-state 接口的返回值来验证接入 Rokid Homebase 协议。

您可以参考 [命令行接口检验工具](tools/rhome.html) 文档完成调试。

**远程调试驱动**

使用远程调试驱动可以很方便的调试开发中的远程驱动，目前支持 HTTP 远程驱动，TCP 远程驱动的调试。

您可以参考 [远程调试驱动](tools/developer-driver.html) 文档完成调试。

**注意：**

自测通过之后，请下载测试用例并按模板填写：[测试用例下载](https://s.rokidcdn.com/homebase/upload/HkOw4tzcf.xlsx)

### Step 4：发布上线

申请发布上线智能家居品牌需要准备：

* 图标 1024*1024 jpg 格式 方形无圆角
* 厂商名称
* 厂商 app 下载地址 (可选)
* 品牌介绍
    * 支持设备列表
    * 服务联系方式
    * 安装配置说明
* 测试报告

可以将以上信息通过邮箱：[smarthomeconnect@rokid.com](mailto:smarthomeconnect@rokid.com) 发给我们。

### 获得帮助

想要获得更多帮助，可以发邮件到如下商务邮箱：

[smarthomeconnect@rokid.com](mailto:smarthomeconnect@rokid.com)