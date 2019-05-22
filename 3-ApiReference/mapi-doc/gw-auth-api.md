## 请求认证

### 认证方式

不管是WebSocket方式还是HTTP方式，都是在http request header里面加上Authorization Header，格式是：

```text
authorization: key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&sign={sign}
```

#### 各个参数含义

| 参数            | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID，开发者平台默认赠送10个sn，请选择任意一个                   | 无，必填 |
| service        | string | tts 或 asr         | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| time     | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项及 secret 按约定的加密方式生成 | 无，必填 |

##### 参数说明

1. 字段 sign 计算方法：
  - 拼成如下字符串 utf8 的字符串：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
     - {xxx} 由 xxx 的值替代
     - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取
  - 计算 str 字符串的 md5 值
2. 字段 version 有 1.0 或 2.0，目前支持的协议版本：
  - 语音识别： serivce(**asr**)， version(**2**)
  - 语音合成 ：serivce(**tts**)， version(**1**)



#### 响应说明
1. 当认证失败时，服务端会**主动断开**此连接。
2. 确保device_id是经过认证的sn，开发者平台里面默认赠送10个已认证sn，用于测试。


