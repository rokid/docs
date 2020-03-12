# 酒店领域开放API

## 权限申请

资源使用方：用户可在若琪酒店后台申请应用，在应用配置时可勾选需要的权限，配置好后可将授权链接发送给资源提供方。

![创建应用](https://s.rokidcdn.com/homebase/upload/9yJs80xQ.png)

资源提供方：点击授权链接后，根据应用详情，用户可将名下酒店资源授权给对应的应用。

![授权应用](https://s.rokidcdn.com/homebase/upload/4DGJfTix.png)

## 调用方式

用户可以以应用的身份（见上文）调用酒店领域开放API，操作有权限的酒店资源。

### 鉴权

若琪酒店API使用JWT方式鉴权。

1. **token生成说明**
    使用应用信息secret，将应用中的accessKey、需要操作的酒店id，合并签名。

  ``` javascript
  token = jwt.sign({accessKey: 'sdffwerdfcccx', hotel: 'q3fffetv'}, secret)
  ```

2. **header 设置**
    设置 Authorization。
   `Authorization: ROKID_HOTEL_JWT token`

### API 调用

若琪酒店领域API使用标准graphql，可以注册若琪账号在控制台中开发测试，地址：https://hotelbase.rokid.com/graphql
配置文件确保如下配置项设置正确：

```json
{
  "request.credentials": "include"
}
```

具体API描述请参阅graphql控制台中文档。

> ***注意：***
>
> *在web控制台中调用任意方法，操作的都为此若琪账号下资源，请先确保当前若琪账号下有酒店、房间、设备等资源，以供调试使用。*

