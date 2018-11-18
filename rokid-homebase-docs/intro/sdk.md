# 智能家居隐身接入

在完成「**智能家居设备接入**」后，有些厂商还希望在自有 APP 中集成若琪手机 SDK，通过若琪手机 SDK 登录为厂商 APP 用户自动绑定若琪账号，从而实现通过若琪语音控制自有设备的功能。

集成这部分能力，需要以下 4 个步骤：

## 一、为若琪智能家居分配 appId 和 appSecret，实现基于 JWT 签名的服务端授权

在实现「**智能家居设备接入流程**」时，授权遵循的是 OAuth 2.0 协议。这是因为用户在若琪智能家居页面添加设备时，会选择某个厂商品牌，若琪账号绑定厂商账号的流程必须由用户主动发起。

而在「**语音控制引擎接入**」流程中，若琪账号由调用 SDK 登录接口时自动创建，对授权过程是无感知的。为了实现这种无感知的授权过程，我们会使用厂商分配的 appSecret 对 appId、厂商用户 ID 进行签名，厂商在接收到该签名时解码和验权。

因此，您需要预先准备：

* 分配 appId 和 appSecret 给我们；
* 实现基于 JWT 签名的服务端授权，具体参考文档：[基于 JWT 签名的服务端授权](../connect/rfc7519.md)；

## 二、向若琪申请 clientId 和 clientSecret

你需要先在[开放平台](https://developer.rokid.com/)注册一个帐号，把帐号、联系邮箱、步骤一中分配好的 appId 和 appSecret，连同申请说明通过邮箱：<smarthomeconnect@rokid.com> 发给我们，申请 clientId 和 clientSecret。

## 三、接入若琪手机 SDK

拿到了 clientId 和 clientSecret 后，配置并创建 SDK Client。

您可以参考以下文档集成若琪手机 SDK：

- [Rokid Mobile SDK IOS 开发指南](https://rokid.github.io/mobile-sdk-ios-docs)
- [Rokid Mobile SDK Android 开发指南](https://rokid.github.io/mobile-sdk-android-docs)

## 四、接入智能家居 Homebase Open API

在若琪 SDK 中，您可以通过 SDK 提供的方法获取用户登录的 Token，具体参考以下文档：

- [iOS SDK 获取用户登录 Token](https://rokid.github.io/mobile-sdk-ios-docs/resource/31_token_login.html)
- [Android SDK 获取用户登录 Token](https://rokid.github.io/mobile-sdk-android-docs/resource/31_login.html)

接着，通过 Authorization HTTP 请求头携带用户 Token 来进行 Homebase Open API 鉴权。

例如：

**发起设备搜索**

调用这个接口， 我们会发一次用户设备同步：

接口地址： `GET https://homebase-openapi.rokid.com/api/trigger-discovery`

```
GET /api/trigger-discovery HTTP/1.1
Host: homebase-openapi.rokid.com
Authorization: <your-user-token-here-这里填写通过SDK获取的用户Token>
Cache-Control: no-cache
```

用户 Token 会过期， 发起设备搜索同步接口推荐放在 App 内执行。

## 五、获得帮助

想要获得更多帮助，可以发邮件到如下商务邮箱：<smarthomeconnect@rokid.com>