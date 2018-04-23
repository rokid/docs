# 开放平台接口定义文档(websocket版)

> 文档版本:V0.2

Rokid openvoice开放服务(websocket版)包含以下功能，

- 设备认证
- 自然语言合成（TTS）
- 完整语音交互(SPCH)

## 文档简介

此文档用于定义开放平台上云端应用接口开发协议，协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。

## Speech 接口

### 服务地址

wss://apigwws.open.rokid.com/api

### protobuf 定义
详见[protobuf](https://github.com/Rokid/rokid-openvoice-websocket/tree/master/protobuf)

### AuthRequest


| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key,在管理平台获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | asr,tts,spch            | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp      | string | unix时间戳                | 无，必填 |
| sign           | string | 由以上几项+secret按约定的加密方式生成 | 无，必填 |

sign的生成加密方式：

key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={timestamp}&secret={secret}

的utf8字符串的md5值

其中{xxx}由xxx的值替代

key及secret由开发方通过管理平台获取，并保管。

此处version可有1.0或2.0，分别对应protobuf中v1或v2目录。

### AuthResponse

请求响应

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

### TtsRequest

PCM格式为 RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 24000 Hz语音。
注意，这里的PCM与Asr的PCM格式不一致，因此不能将tts的输出直接作为asr的输入。

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| text   | string    | 需要转换的text文本          | 无    |
| declaimer | string | 发音者，目前支持 中文成人"zh" 与 中文儿童"c1" 两种 | 无 |
| codec     | string | 语音流的编码，目前支持PCM，OPU，OPU2。    | 无  |

### TtsResponse

请求响应

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   |
| result  | SpeechErrorCode | 错误信息 |
| text  | string | voice语音中包含的文字 |
| voice | bytes  | 合成的voice语音    |
| finish   | bool | 语音是否结束 |

### SpeechRequest

说明：
1. 语音长度限制在 10s 以内。
2. vad_timeout 为 ms 级，一般设为 500ms 。
3. no_intermediate_asr 默认为 false，即是会实时返回 asr 识别结果，如果只需要最终结果，则设为 true 即可。


| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 | 0     |
| type   | ReqType | START/VOICE/END 或 TEXT | 无   |
| voice  | bytes     | 需要识别的voice语音流        | 无    |
| asr    | bytes     | 需要理解的asr文本        | 无    |
| options    | SpeechOptions     | 辅助理解的选项        | 无    |
| lang    | string | 语音流的语言，目前支持zh-CN，en-US。   | zh-CN |
| codec   | string | 语音流的编码，目前支持PCM，OPU，OPU2。  | PCM   |
| vad_mode   | VadMode | LOCAL/CLOUD  | 无   |
| vend_timeout   | uint32 | 如果vad_mode为CLOUD时，指定vad时间，单位ms  | 无   |
| no_nlp   | bool | 是否需要nlp  | false   |
| no_intermediate_asr   | bool | 是否需要asr的实时识别结果  | false   |
| stack   | string | 设备当前的应用栈信息,"appid1:appid2"按照应用被调用的早晚逆序排列。              | 空     |
| voice_trigger      | string | 激活词，即用于唤醒设备的名字，如"若琪"。     | 空     |
| voice_power   | float | 语音流的音强  | 如有进行多设备间的仲裁   |
| trigger_start   | float | 语音流的激活词的开始位置。  | 无   |
| trigger_length   | float | 语音流的激活词的长度。  | 无   |
| skill_options  | string | 设备上的状态信息，为json结构，此结构会传给相应的skill的cloud app中。         | 空     |

### SpeechResponse

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| result  | SpeechErrorCode | 错误信息 |
| type  | RespType | 结果类型INTERMEDIATE/ASR_FINISH/FINISH |
| asr    | string | asr实时识别的结果     |
| nlp    | string | nlp识别的结果: {"appId": "技能id", "appName": "技能名称", "asr": "asr识别结果", "cloud": "是否为云端技能: true / fasle", "intent": "意图", "pattern": "设定的用户语句","slots": { "槽名称": { "type": "槽类型", "value": "槽的值" }}}|
| action | string | cloud app处理的结果, json字符串 |
| extra | string | 目前有：{"activation": "fake(误激活), reject(仲裁失败), accept(激活确认) none(无激活词时)"} |
