# 测试 OAuth|OAuth2.0 接口

在驱动发布上先之前， 我们需要先测试 OAuth|OAuth2.0 授权接口, 假设驱动已经部署到如下地址  `https://awesome-iot-brand.com/driver`

我们需要做以下 4 个测试，测试通过， 就可以提交你的驱动了！

## 测试1. 获取 OAuth 授权接口地址

OAuth 接口

```bash
POST /driver/command HTTP/1.1
Host: awesome-iot-brand.com
Content-Type: application/json
Cache-Control: no-cache
Postman-Token: 1d89f10f-b14d-e37e-fa9e-8deb3fce02e7

{
  "command": "OAuth",
  "params": {
    "callbackURL": "https://s.rokidcdn.com/path?u=1&v=2"
  }
}
```

期望返回结果

```
{
    "status": 0,
    "data": "http://awesome-iot-brand.com/oauth/authorize?callbackURL=https%3A%2F%2Fs.rokidcdn.com%2Fpath%3Fu%3D1%26v%3D2"
}
```

## 测试2. 授权逻辑

拿到结果的， 在浏览器打开， url `http://awesome-iot-brand.com/oauth/authorize?callbackURL=https%3A%2F%2Fs.rokidcdn.com%2Fpath%3Fu%3D1%26v%3D2`

授权成功后

1. 如果是 OAuth 授权:  需要重定向到 callbackURL， 并带上userAuth信息： `https://s.rokidcdn.com/path?u=1&v=2&userId=foo&userToken=xxxx&expiresIn=1200`
2. 如果是 **OAuth2.0** 授权:
授权成功，会重定向到callbackURL, 并带上 code  `https://s.rokidcdn.com/path?u=1&v=2&code=abcd1234`

检查项：

1. URL 里面包含 CallbackURL 所有信息， 路径，参数
2. OAuth 不同结果判断
  1. 如果是 OAuth2.0 需要 URL 返回 code 参数
  2. 如果 是 OAuth， 需要 URL 返回 userAuth 相关参数
3. [OAuth2.0] 通过 code 调用 OAuthGetToken command 接口

## 测试3. 检查通过 code 获取 userAuth『OAuth2.0』

通过 code 调用 `OAuthGetToken` command接口

```bash
POST /driver/command HTTP/1.1
Host: awesome-iot-brand.com
Content-Type: application/json
Cache-Control: no-cache

{
  "command": "OAuthGetToken",
  "params": {
    "code": "xxxx"
  }
}
```

期望返回结果

```json
{
  "status": 0,
  "data":  {
    "userId": "xxx",
    "userToken": "yyyy",
    "expiresIn": 3600,
    "refreshToken": 3600
  }
}
```


## 测试4. 检查 token 刷新

调用 `OAuthRefresh` command接口, 完成token的刷新

```bash
POST /driver/command HTTP/1.1
Host: awesome-iot-brand.com
Content-Type: application/json
Cache-Control: no-cache

{
  "command": "OAuthRefresh",
  "params": {
    "userId": "xxx",
    "userToken": "yyyy",
    "expiresIn": 3600,
    "refreshToken": 3600
  }
}
```

这个接口期望返回最新的 userAuth 信息

```json
{
  "status": 0,
  "data":  {
    "userId": "xxx",
    "userToken": "yyyy",
    "expiresIn": 3600,
    "refreshToken": 3600
  }
}
```
