# 智能家居 OAuth 授权

![](https://s.rokidcdn.com/homebase/upload/rJsJRvPCl.jpg)

## 交互过程

- 用户添加驱动， 发起授权过程
- Homebase 向驱动调用 OAuth Command 接口， 参数为登陆回调页面地址
- HTTP 驱动 OAuth Command 返回 Oauth 登陆地址 `OAuth URL`
- Homebase 打开浏览器， 跳转到转到 `OAuth URL`
- 用户输入用户名和密码， 点击授权
- OAuth 服务授权完成， 跳转回 回调页面 `Callback URL`， 添加URL参数 （userId, userToken, expiredTime, refreshToken）
- Homebase 保存授权信息， 下次用户调用 搜索设备和控制设备的时候会带上。


## 字段说明

为了接入现有 OAuth 登录体系， 字段名称可以自定义， 默认字段名称如下：

- userId {可选}
- userToken 新的用户Token
- expiredTime 更新过期时间， 秒为单位， UTC 时间戳, 与 expiresIn 选择一个即可
- expiresIn Token 过期时间，相对现在的时间， 秒为单位, 与 expiredTime 选择一个即可
- refreshToken  可选， 更新 refreshToken



## 刷新 Token

- Homebase 检测到Token即将过期， 将现有的用户授权信息（userId, userToken, expiredTime, refreshToken）发送给驱动的 `refreshToken` command
- 驱动返回新的用户授权信息
- Homebase 保存用户的授权信息
