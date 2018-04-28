## 1. 调用方式
```
client                   http                   InternalService(grpc)
-------------------------------------------------------------------------

http(带Authorization)      -->   根据Authorization进行设备认证或用户认证
                        A  <--   认证失败 500 body为失败原因的字符串
                           或
                           -->   按url推断出InternalService的域名
                                 将body解析成req
                                 填充AccountId, DeviceTypeId, DeviceId(设备认证)或ClientId, UserId(用户认证)
                                 调用resp = grpc(req)
                        B  <--   调用失败 500 body为失败原因的字符串
                           或
                        C  <--   返回200 body为resp
```

## 2. 认证方式
客户端向httpgw发起请求时，需要在HTTP头部中增加字段Authorization。

### 2.1. 设备认证

#### 2.1.1. Authorization
设备认证方式中的Authorization内容格式如下：

```
version={version};time={time};sign={sign};key={key};device_type_id={device_type_id};device_id={device_id};service={service}
```

#### 2.1.2. Signature
Authorization中的sign字段是签名串，是对下列组合的字符串（UTF-8编码）做MD5计算

```
key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}
```

#### 2.1.3. 字段说明

| 字段名称       | 意义                                                              |
| -------------- | ----------------------------------------------------------------- |
| version        | 版本，当前为1.0                                                   |
| time           | UNIX时间                                                          |
| sign           | 签名串，具体生成方式见下文                                        |
| key            | 授权KEY，从[开发者平台](https://developer.rokid.com/voice/#/)获取 |
| device_type_id | 设备类型ID，同样从开发者平台获取                                |
| device_id      | 设备ID，客户端自己维护                                           |
| service        | 服务类型，自定义，建议与请求的服务名保持一致                      |
| secret         | 密钥，从开发者平台获取                                            |

## 3. 接口
#### 3.1.1. 地址
```
https://apigwrest.open.rokid.com
```
#### 3.1.2. 绑定接口 （POST）
```
/v1/device/deviceManager/bindMaster
```
###### 参数说明：
| 参数名称       | 意义                                                              |
| -------------- | ----------------------------------------------------------------- |
| Authorization        | 认证信息，http请求时，放置在header中                                                   |
| body           | 传入json类型的字符串 例：{"userId":"xxxx"}   userId是rokid账户id                                                 |
| Content-Type          | application/json;charset=utf-8                                                 |

###### 返回结果：
```
{
    "resultCode": 0,
    "message": "success"
}
```
#### 3.1.3. 解绑接口 （POST）
```
/v1/device/deviceManager/unBindMaster
```
###### 参数说明：
| 参数名称       | 意义                                                              |
| -------------- | ----------------------------------------------------------------- |
| Authorization        | 认证信息，http请求时，放置在header中                                                   |
| body           | 传入json类型的字符串 例：{"userId":"xxxx"}   userId是rokid账户id                                                 |
| Content-Type          | application/json;charset=utf-8                                                 |

###### 返回结果：
```
{
    "resultCode": 0,
    "message": "success"
}
```
