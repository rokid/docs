#### 设备认证

##### AuthRequest


| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | tts 或 speech         | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp      | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项及 secret 按约定的加密方式生成 | 无，必填 |

##### 说明

1. 字段 sign 计算方法：

  1. 拼成如下字符串 utf8 的字符串：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
     - {xxx} 由 xxx 的值替代
     - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取
  2. 计算 str 字符串的 md5 值

2. 字段 version 有 1.0 或 2.0，分别对应 [协议地址](#%E5%8D%8F%E8%AE%AE%E5%9C%B0%E5%9D%80) 中 v1 或 v2 目录，目前支持的协议版本：

  - 语音识别： serivce(**speech**)， version(**2**)

  - 语音合成 ：serivce(**tts**)， version(**1**)


##### AuthResponse

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

##### 说明

1. 当认证失败时，服务端会**主动断开**此连接。
