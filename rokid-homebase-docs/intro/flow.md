## 智能家居设备接入流程

智能家居设备接入流程可以分为 4 个步骤：

![](https://s.rokidcdn.com/homebase/upload/ByGeJ4PTG.jpg)

### Step 1：注册开发者

申请成为智能家居开发者需要准备：

- 向商务申请一台测试的若琪设备；
- 将测试若琪的 SN 码发给我们，我们会将其加入到开发者环境中；

**注意：**

有些厂商希望在自有 APP 中集成若琪手机 SDK，通过若琪手机 SDK 登录为厂商 APP 用户自动绑定若琪账号，从而实现通过若琪语音控制自有设备的功能。这种情况您需要先在[开放平台](https://developer.rokid.com/)注册一个帐号，并联系我们申请 AppId 和 AppSecrect。

您可以参考以下文档集成若琪手机 SDK：

- [Rokid Mobile SDK IOS 开发指南](https://rokid.github.io/mobile-sdk-ios-docs)
- [Rokid Mobile SDK Android 开发指南](https://rokid.github.io/mobile-sdk-android-docs)

### Step 2：开发

不管是云云对接，还是局域网对接，都需要遵循若琪智能家居协议，提供设备搜索接口、设备控制接口、设备状态查询接口（可选）。

我们推荐使用 v2 版本协议完成接入：[若琪智能家居协议](../v2/message-reference.md)

**云云对接**

对于云云对接，我们遵循 OAuth 2.0 协议接入三方用户授权。因此，设备云服务端还需要实现一套标准的 OAuth 2.0 授权机制。

您需要将以下信息提供给我们：

- 账号授权 URL（适配手机端访问的 OAuth 2.0 授权 H5 页面地址）
- Client ID（为若琪注册生成的客户端 ID）
- Client Secret（为若琪注册生成的客户端秘钥）
- Access Token URL（用于获取 access_token 的地址）
- 设备指令接受 URL（用于接受若琪设备控制指令的地址）

您可以参考以下文档完成云云对接：

- [OAuth 2.0 协议](../connect/rfc6749.md)
- [云云对接](../connect/cloud-to-cloud.md)

**局域网对接**

对于局域网对接，我们遵循 SSDP 协议实现局域网内的设备自动发现。

您可以参考以下文档完成局域网对接：

- [局域网自动发现](../connect/ssdp-auto-discovery.md)
- [局域网对接](../connect/via-lan.md)

### Step 3：调试

我们提供两种测试方式：

**命令行接口校验工具 - rhome**

使用 rhome 工具通过 json schema 来验证 discover|control|report-state 接口的返回值来验证接入 Rokid Homebase 协议。

您可以参考 [RHOME 桌面版调试工具](../tools/rhome-desktop.md) 文档完成调试。

**自定义接入**

使用自定义接入可以很方便的调试开发中的远程驱动，目前支持 HTTP 远程驱动，TCP 远程驱动的调试。

您可以参考 [自定义接入](../tools/developer-driver.md) 文档完成调试。

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
