### 开放平台接口定义文档(http版) - 语音识别

**Table of Contents** 

  - [前言](#%E5%89%8D%E8%A8%80)
  - [文档版本](#%E6%96%87%E6%A1%A3%E7%89%88%E6%9C%AC)
  - [服务地址](#%E6%9C%8D%E5%8A%A1%E5%9C%B0%E5%9D%80)
  - [协议地址](#%E5%8D%8F%E8%AE%AE%E5%9C%B0%E5%9D%80)
  - [协议概述](#%E5%8D%8F%E8%AE%AE%E6%A6%82%E8%BF%B0)
  - [认证](#%E8%AE%A4%E8%AF%81)
      - [说明](#%E8%AF%B4%E6%98%8E)
  - [语音识别](#%E8%AF%AD%E9%9F%B3%E8%AF%86%E5%88%AB)
      - [请求](#%E8%AF%B7%E6%B1%82)
      - [响应](#%E5%93%8D%E5%BA%94)
  - [示例](#%E7%A4%BA%E4%BE%8B)

### 前言

此文档正在开发中，后续可能会有变动，请参照使用。

### 文档版本

0.1

### 服务地址

https://apigwws.open.rokid.com/api/v2/asr/uid 其中 uid 是客户端指定的代表此次语音交互请求的唯一id

### 协议地址

- 外部 [github]()


### 协议概述

此文档用于定义开放平台上云端应用接口开发协议，协议遵循 http 协议。

### 认证

在 HTTP 头部中提供一个 **Authorization** 包含认证信息，格式如下：

```
time={time};sign={sign};key={key};device_type_id={device_type_id};device_id={device_id};
```
其中

- 各 key=value 之间由 分号 分隔
- 各 key 顺序随意
- 各参数说明如下

| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| secret         | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | 服务名：asr 或 tts | 无，必填 |
| version        | string | 服务版本号：2 或 1     | 无，必填 |
| time     | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项按以下方法计算生成 | 无，必填 |

##### 说明

- 字段 **sign** 计算方法：

1. 拼成如下字符串 utf8 的字符串 utf8str：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
    - {xxx} 由 xxx 的值替代
    - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取
2. 计算 str 字符串的 md5 值
3. **asr** 服务的 sign 的字符串为 utf8str：key={key}&device_type_id={device_type_id}&device_id={device_id}&service=**asr**&version=**2**&time={time}&secret={secret}
4. **tts** 服务的 sign 的字符串为 utf8str：key={key}&device_type_id={device_type_id}&device_id={device_id}&service=**tts**&version=**1**&time={time}&secret={secret}

#### 语音识别

##### 请求

1. 需要带包含认证信息的 **Authorization** 的 http header
2. 使用 **HTTP POST** 方式
3. 其中 Content-Type 为 **multipart/form-data**
4. 第一段 Content-Disposition: form-data; **name**="**voice-config**"，内容为 **json** 数据，格式如下：

| 参数     | 下级参数 | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- | ---- |
| id    |     | int | 客户端指定的代表此次语音交互请求中语音的序号，为0开始递增  | 无，必填 |
| type    |     | string | 表示语音的开始，中间，结束，取值为：START、VOICE、END、ONESHOT | 无，必填 |
| options    |     | string | 语音流的语言，目前支持 ZH。  | 无 |
|     | lang | string | 语音流的语言，目前支持 ZH。  | ZH |
|    | codec | string | 语音流的编码，目前支持 PCM，OPU，OPU2，OPUS，AMRWB，AMRNB，PCM8K。<br />PCM，OPU，OPU2，OPUS，AMRWB 的语音数据格式为单通道，采样率16Khz，16bit；<br />AMRNB，PCM8K的语音数据格式为单通道，采样率8Khz，16bit； | PCM   |
|      | voiceTrigger | string | 激活词，即用于唤醒设备的名字，如"若琪"；<br />可用 "&#0124;" 分隔指定多个，如 "若琪&#0124;洛奇"<br />若指定，则会提高对此词的识别 | 空     |
|     | noNlp | bool | 是否需要语义理解（nlp）。  | false |


5. 后续段的 Content-Disposition: form-data; **name**="xxx"，其中 name 可以任意，其Content-Type 应为 application/octet-stream，内容为语音内容
6. 语音段可以有多个，如将每 30ms 的语音组织成一段，云端会将所有段的数据组织到一起作识别
7. 一次完整的语音交互序列包含**多个**语音数据时，需要发送如下序列的多个 http post 请求：

   1. 第一个请求的 type 设置为 START，并设置好其它参数，此请求可带上语音数据
   2. 后面的多个请求设置 type  为 VOICE，并带上语音数据
   3. 最后一个请求设置 type 为 END 包表示交互结束，此请求可带上语音数据
   4. 以上请求需要使用相同的 url，即相同的 uid，id 为递增的数值
8. 一次完整的语音交互序列只包含**一个**语音数据时，只需发送一个 http post 请求，其中 type 设置为 ONESHOT，并带上语音数据

##### 响应

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id | int | 对应请求中的id    |
| result  | SpeechErrorCode | 错误信息：SUCCESS |
| type  | RespType | 结果类型：FINISH |
| asr    | string | asr识别的结果     |
| asrScores | float 数组 | asr识别的得分 |
| nlp    | string | nlp识别的结果: {"appId": "技能id", "appName": "技能名称", "asr": "asr识别结果", "cloud": "是否为云端技能: true / fasle", "intent": "意图", "pattern": "设定的用户语句","slots": { "槽名称": { "type": "槽类型", "value": "槽的值" }}}|
| action | string | cloud app处理的结果，json字符串 |
| extra | string | 目前有：{"activation": "xxx"} |
| vpr | string | 声纹的结果，json字符串，目前为：{"id": "xxx"} |

1. 包含**多个**语音数据的语音交互时，仅当是最后一个请求即 type 为 END 的包有以上响应
2. 只包含**一个**语音数据的语音交互时，即 type 为 ONESHOT 的请求同样也有以上响应
3. 其余请求返回为空
4. 所有请求成功与否由 result 决定：SUCCESS 为成功，其余的为失败

##### result 取值

| result 值         | 含义           |
| ----------------- | -------------- |
| SUCCESS           | 成功           |
| UNAUTHENTICATED   | 认证失败       |
| RESOURCE_EXHASTED | 请求量过大     |
| INTERNAL          | 内部错误       |
| UNINITIALIZED     | 未接收到 start |
| DUP_INITIALIZED   | 收到多个 start |
| BADREQUEST        | 请求格式错误   |


### 示例

- 可直接使用 curl 命令构造请求：

```bash
curl -X POST \
	-H 'Authorization:key=xxx;device_type_id=xxx;device_id=xxx;time=xxx;sign=xxx;' \
	-F 'voice-config=@voice-config.json' \
	-F 'voice=@test.pcm' \
	https://apigwws-pre.open.rokid.com/api/v2/asr
```

其中：
1. xxx 需要由实际值替代
2. voice-config.json内容为：
```
{"id": 1,"type": "START","options": {"lang": "ZH","codec": "PCM","voiceTrigger": "若琪"}}
```
3. test.pcm 为16k 16位 单通道 pcm 格式的语音文件

- 请求 http 内容：

```http
POST /api/v2/asr HTTP/1.1
Host: apigwws-pre.open.rokid.com
Accept: */*
Content-Length: 307
Content-Type: multipart/form-data; boundary=----------------------------77bb6bb36e97
Expect: 100-continue
User-Agent: curl/7.19.7 (x86_64-redhat-linux-gnu) libcurl/7.19.7 NSS/3.27.1 zlib/1.2.3 libidn/1.18 libssh2/1.4.2

------------------------------77bb6bb36e97
Content-Disposition: form-data; name="voice-config"

{}
------------------------------77bb6bb36e97
Content-Disposition: form-data; name="voice"; filename="test.pcm"
Content-Type: application/octet-stream

语音的二进制数据

------------------------------77bb6bb36e97--
```

- 返回 http 内容

```
HTTP/1.1 200 OK
Server: nginx/1.12.0
Date: Mon, 22 Oct 2018 08:56:56 GMT
Content-Type: text/plain; charset=utf-8
Content-Length: 85
Connection: keep-alive

{id":12345,"type":"FINISH","result":"SUCCESS","asr":"","asrScores":[0,-6.496677,-0]}
```

- 一个完整语音交互的示例

```
=>  {"id": 1,"type": "START","options": {"lang": "ZH","codec": "PCM","voiceTrigger": "若琪"}}
无内容返回

=>  {"id": 2,"type": "VOICE"}
无内容返回

=>  {"id": 3,"type": "END"}

{"id":1540952889,"asr":"若琪今天天气怎么样若琪今天天气怎么样","asrScores":[-0.0019035237,1.8807955,-0.93645704],"result":"SUCCESS","type":"FINISH"}
```
