# rokid-openvoice-websocket
## 开放平台接口定义文档(websocket版)

> 文档版本:V0.1

Rokid openvoice开放服务(websocket版)包含以下四部分功能，

- 设备认证
- 语音转文字（ASR）
- 自然语言合成（TTS）
- 完整语音交互(SPCH)

## 文档简介

此文档用于定义开放平台上云端应用接口开发协议，协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。

## Speech 接口

### protobuf 定义

```
syntax = "proto2";

package rokid.open;

enum SpeechErrorCode {
  SUCCESS           = 0;
  AUTH_FAILED       = 1;
  UNAUTHENTICATED   = 2;
  CONNECTION_EXCEED = 3;
  RESOURCE_EXHASTED = 4;
  BUSY              = 5;
  INTERNAL          = 6;
}

enum ReqType {
  START             = 0;
  VOICE             = 1;
  END               = 2;
  // used for SpeechRequest
  TEXT              = 3;
}

message AuthRequest {
  required string key            = 1;
  required string device_type_id = 2;
  required string device_id      = 3;
  required string service        = 4;
  required string version        = 5;
  required string timestamp      = 6;
  required string sign           = 7;
}

message AuthResponse {
  // 0: success
  // -1: failed
  required SpeechErrorCode result = 1;
}

message AsrRequest {
  required int32 id     = 1;
  // 0: start
  // 1: voice data
  // 2: end
  required ReqType type = 2;
  optional bytes voice  = 3;
  optional string lang  = 4;
  optional string codec = 5;
  // vt = voice trigger
  optional string vt    = 6;
}

message AsrResponse {
  required int32 id               = 1;
  required SpeechErrorCode result = 2;
  optional string asr             = 3;
  optional bool finish            = 4;
}

message TtsRequest {
  required int32 id         = 1;
  required string text      = 2;
  optional string declaimer = 3;
  optional string codec     = 4;
}

message TtsResponse {
  required int32 id               = 1;
  required SpeechErrorCode result = 2;
  optional string text            = 3;
  optional bytes voice            = 4;
  optional bool finish            = 5;
}

message SpeechRequest {
  required int32 id      = 1;

  // 0: start
  // 1: voice data
  // 2: end
  // 3: text
  required ReqType type  = 2;

  optional bytes voice   = 3;

  optional string asr    = 4;

  // zh
  // en
  optional string lang   = 5;

  // pcm
  // opu
  // opu2
  optional string codec  = 6;

  // vt = voice trigger
  optional string vt     = 7;

  // stack of current domains
  optional string stack  = 8;

  // json format
  optional string device = 9;
}

message SpeechResponse {
  required int32 id               = 1;
  required SpeechErrorCode result = 2;
  optional string asr             = 3;
  optional string nlp             = 4;
  optional string action          = 5;
  optional bool finish            = 6;
}

```

### AuthRequest


| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key,在管理平台获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | asr,tts,spch            | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp           | string | unix时间戳                | 无，必填 |
| sign           | string | 由以上几项+secret按约定的加密方式生成 | 无，必填 |

sign的生成加密方式：

key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={timestamp}&secret={secret}

的utf8字符串的md5值

其中{xxx}由xxx的值替代

key及secret由开发方通过管理平台获取，并保管。

### AuthResponse

请求响应参数详见：[golang代码例子](https://github.com/Rokid/rokid-openvoice-websocket/blob/master/sample-code-golang/src/wstool/auth.go)

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

### AsrRequest

在同一条连接上第一个请求必须为AuthRequest。

一个请求一个AsrRequest{type = START}后跟多个AsrRequest{type = VOICE}，最后跟一个AsrRequest{type = END}。
PCM为RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 16000 Hz语音。

| 参数          | 类型     | 描述                                       | 默认值   |
| ----------- | ------ | ---------------------------------------- | ----- |
| id        | int32 | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。                  | 0 |
| type         | ReqType | START, VOICE, END              | 无 |
| voice        | bytes | 需要识别的voice语音流                  | 无 |
| lang        | string | 语音流的语言，目前支持zh-CN，en-US。                  | zh-CN |
| codec    | string | 语音流的编码，目前支持PCM，OPU，OPU2。 | PCM   |
| vt | string | 激活词，即用于唤醒设备的名字，如"若琪"。 | 空     |

### AsrResponse

请求响应参数详见：[golang代码例子](https://github.com/Rokid/rokid-openvoice-websocket/blob/master/sample-code-golang/src/wsasr/main.go)

| 参数   | 类型     | 描述         |
| ---- | ------ | ---------- |
| id   | int32 | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。                  |
| asr  | string | asr实时识别的结果 |
| finish   | bool | 语音是否结束 |

### TtsRequest

PCM格式为 RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 24000 Hz语音。
注意，这里的PCM与Asr的PCM格式不一致，因此不能将tts的输出直接作为asr的输入。

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| text   | string    | 需要转换的text文本          | 无    |
| declaimer | string | 发音者，如"zh","zhangsan","rose" | "zh" |
| codec     | string | 语音流的编码，目前支持PCM，OPU，OPU2。    | PCM  |

### TtsResponse

请求响应参数详见：[golang代码例子](https://github.com/Rokid/rokid-openvoice/blob/master/sample-code-golang/src/ttsclient/main.go)

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| text  | string | voice语音中包含的文字 |
| voice | bytes  | 合成的voice语音    |

### SpeechRequest

请求响应参数详见：
[文本请求的代码例子](https://github.com/Rokid/rokid-openvoice-websocket/blob/master/sample-code-golang/src/wsspeecht/main.go)
[语音请求的代码例子](https://github.com/Rokid/rokid-openvoice-websocket/blob/master/sample-code-golang/src/wsspeechv/main.go)

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 | 0     |
| voice  | bytes     | 需要识别的voice语音流        | 无    |
| lang    | string | 语音流的语言，目前支持zh-CN，en-US。   | zh-CN |
| codec   | string | 语音流的编码，目前支持PCM，OPU，OPU2。  | PCM   |
| vt      | string | 激活词，即用于唤醒设备的名字，如"若琪"。     | 空     |
| stack   | string | 设备当前的应用栈信息。              | 空     |
| device  | string | 设备上的状态信息，为json结构。         | 空     |

stack结构："applicationId1:applicationId2:application3"按照应用被调用的早晚逆序排列，当前应用在第一个。


### SpeechResponse

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| asr    | string | asr实时识别的结果     |
| nlp    | string | nlp识别的结果       |
| action | string | cloud app处理的结果 |
| finish   | bool | 语音是否结束 |

asr：标准字符串，返回实时识别结果。

nlp：json字符串，结构如下
```
"content": {
    "applicationId": "com.rokid.cloud.music",
    "intent": "play_random",
    "slots": {}
}
```

action：json字符串，结构详见 [action定义](https://github.com/Rokid/docs/blob/master/2-RokidDocument/1-SkillsKit/Cloud%20App%20Development%20Protocol_cn.md#32-action%E5%AE%9A%E4%B9%89)

