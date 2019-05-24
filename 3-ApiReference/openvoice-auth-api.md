# 设备认证

### WebSocket方式
#### AuthRequest

| 参数            | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/voiceParam.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID，开发者平台默认赠送10个sn，请选择任意一个                   | 无，必填 |
| service        | string | tts 或 speech         | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp      | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项及 secret 按约定的加密方式生成 | 无，必填 |

##### 说明

1. 字段 sign 计算方法：
  1. 拼成如下字符串 utf8 的字符串：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
     - {xxx} 由 xxx 的值替代
     - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/voiceParam.html)获取
  2. 计算 str 字符串的 md5 值

2. 字段 version 有 1.0 或 2.0，分别对应 [协议地址](#%E5%8D%8F%E8%AE%AE%E5%9C%B0%E5%9D%80) 中 v1 或 v2 目录，目前支持的协议版本：
  - 语音识别： serivce(**speech**)， version(**2**)
  - 语音合成 ：serivce(**tts**)， version(**1**)


#### AuthResponse

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

##### 说明
1. 当认证失败时，服务端会**主动断开**此连接。
2. 确保device_id是经过认证的sn，开发者平台里面默认赠送10个认证sn，用于测试。


### HTTP方式

#### Authorization

设备认证方式中的Authorization Header内容格式如下：

```text
version={version};time={time};sign={sign};key={key};device_type_id={device_type_id};device_id={device_id};service={service}
```

#### Signature

需要根据time字段实时计算，Authorization中的sign字段是签名串，是对下列组合的字符串（UTF-8编码）做MD5计算

```text
key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}
```

#### 生成sign示例代码（golang）

```go

func generateAuthorization(version, secret, key, deviceTypeID, deviceID, service string) string {
    now := strconv.FormatInt(time.Now().Unix(), 10)
    return fmt.Sprintf("version=%s;time=%s;sign=%s;key=%s;device_type_id=%s;device_id=%s;service=%s",
        version, now, generateSign(now, version, secret, key, deviceTypeID, deviceID, service),
        key, deviceTypeID, deviceID, service)
}

func generateSign(now, version, secret, key, deviceTypeID, deviceID, service string) string {
    src := "key=" + key + "&device_type_id=" + deviceTypeID + "&device_id=" + deviceID + "&service=" + service + "&version=" + version + "&time=" + now + "&secret=" + secret
    fmt.Println("sign source:", src)
    sign := strings.ToUpper(makeMD5(src))
    fmt.Println("sign:", sign)
    return sign
}

func makeMD5(data string) string {
    h := md5.New()
    h.Write([]byte(data))
    return hex.EncodeToString(h.Sum(nil))
}

```
