### 开放平台接口定义文档

### 概述

本文档目的是描述云端语音接口的 WebSocket 版本的开放协议，主要包含语音识别、语义理解、语音合成三大部分功能，主要面向想要了解语音交互细节，并具有一定开发能力的开发者或用户。

### 协议详解

协议可分为以下部分：

- [设备认证](#设备认证)
- [语音交互](#语音交互)（speech）

#### WebSocket API接入
[ 语音合成（TTS） WebSocket 接入文档](https://developer.rokid.com/docs/3-ApiReference/wstts-api.html)

[WebSocket 接入Demo（JAVA）](https://github.com/Rokid/rokid-speech)

[WebSocket  接入Demo（Python）](https://github.com/Rokid/speech-python-demo)

#### HTTP 接入
[ 语音合成（TTS） HTTP 接入文档](https://developer.rokid.com/docs/3-ApiReference/openvoice-api-http.html)

[ 语音识别（ASR） HTTP 接入文档](https://developer.rokid.com/docs/3-ApiReference/openvoice-http-api.html)

#### Android SDK 接入
[ Android SDK 接入文档](https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/fullLink/fulllink.html)

#### 技能开发
[Skill开发指南（相关技能开发）](https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/platform-introduction.html)

#### 索引
  - [服务地址](#服务地址)
  - [协议地址](#协议地址)
  - [协议概述](#协议概述)
  - [协议详解](#协议详解)
    - [设备认证](#设备认证)
    - [语音交互](#语音交互)
    - [语音合成](#语音合成)
  - [典型场景](#典型场景)
    - [本地vad](#本地vad)
    - [云端vad](#云端vad)
  - [speech异常](#speech异常)

### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | wss://apigwws.open.rokid.com/api       | 对外提供的正式稳定环境 |

### 协议地址

- [github](https://github.com/Rokid/rokid-openvoice-websocket/tree/master/protobuf)

### 协议概述

此文档用于定义开放平台上云端应用接口开发协议，协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 wss 连接，注意是 **websocket + ssl**
* 认证
* 如果认证中 service 为 speech，则此连接后续可进行一次或多次语音交互，直至连接断开
* 如果认证中 service 为 tts，则此连接后续可进行一次或多次语音合成，直至连接断开

* 如果需要同时使用语音识别与语音合成，则需要建立**两条** wss 连接，**每条连接需要分别作认证**

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

#### 语音交互

##### 流程

1. 需要先进行 service 为 speech 的 [设备认证](#%E8%AE%BE%E5%A4%87%E8%AE%A4%E8%AF%81)
2. 一次完整的语音识别的数据包以 id 来标识，称为一个 session
3. 设备端发送三种类型的数据
   - START 设置 session 的参数数据
   - VOICE 发送 session 的语音数据
   - END 表示 session 结束
4. 云端返回三种 RespType 的数据
   - INTERMEDIATE 返回 asr 的中间结果，典型的有 extra 中 activation
   - ASR_FINISH 返回 asr 识别结果
   - FINISH 返回 nlp 结果
5. 每个 session 以 FINISH 结束

##### SpeechRequest


| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 | 0     |
| type   | ReqType | START、VOICE、END 或 TEXT | 空  |
| voice  | bytes     | 需要识别的语音流      | 空   |
| asr    | bytes     | 需要理解的 asr 文本      | 空   |
| options    | SpeechOptions     | 辅助理解的选项，内容见下表       | 空   |

**options 字段的详细说明**

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| lang    | string | 语音流的语言，目前支持 zh-CN，en-US。  | zh-CN |
| codec | string | 语音流的编码，目前支持 PCM，OPU，OPU2，OPUS，AMRWB，AMRNB，PCM8K。<br />PCM，OPU，OPU2，OPUS，AMRWB 的语音数据格式为单通道，采样率16Khz，16bit；<br />AMRNB，PCM8K的语音数据格式为单通道，采样率8Khz，16bit； | PCM   |
| vad_mode   | VadMode | LOCAL、CLOUD | LOCAL |
| vend_timeout   | uint32 | 如果 vad_mode 为 CLOUD 时，指定 vad 时间，单位 ms，推荐设置为 500ms | 0  |
| no_nlp   | bool | 是否需要语义理解（nlp） | false   |
| no_intermediate_asr   | bool | 是否需要 asr 的实时识别结果 | false   |
| stack   | string | 设备当前的应用栈信息，"appid1:appid2"按照应用被调用的时间逆序排列          | 空   |
| voice_trigger      | string | 激活词，即用于唤醒设备的名字，如"若琪"；可用 "\|" 分隔指定多个，如 "若琪\|洛奇" | 空   |
| voice_power   | float | 语音流的音强，若设置则在多设备中作仲裁，同时只有音强最强的设备有响应 | 0      |
| trigger_start   | float | 语音流的激活词的开始位置。  | 0   |
| trigger_length   | float | 语音流的激活词的长度。  | 0   |
| skill_options  | string | 设备上的状态信息，为 json 结构，此结构会传给相应的 skill 的 cloud app   | 空   |
| voice_extra | string | asr 引擎 的参数，json 格式 | 空 |
| vad_begin | uint32 | vad begin 的窗口大小 :-( | 0 |
| no_trigger_confirm | bool | 是否需要云端激活词的二次确认功能 | false |

##### 说明

1. voice_trigger 激活词：设备的名字，当用户说这个词时，设备会被唤醒，并给出反应。
2. VAD：语音活性检测(Voice activity detection)，当用户说了一个指令后，停顿一定时间(可以由vad_timeout参数设定)，会被设备或云端认为已经说完
3. 仲裁：同一用户的多个设备同时收到语音指令时，由 voice_power 的强弱决定离说话人的远近，从而最近的设备有响应，而其它设备无响应
4. 声纹：由 trigger_start 及 trigger_length 来指明 激活词 在语音流中的位置，声纹服务用来作说话人识别
5. voice的编码格式如下：
   - 识别支持pcm语音流识别，单通道 数据位宽16bit 采样率16kHZ pcm
   - 识别支持opu语音流识别，单通道 数据位宽16bit 采样率16kHZ opu opu压缩每帧数据格式由1字节（数据长度）+ opus压缩320字节数据

##### SpeechResponse

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| result  | SpeechErrorCode | 错误信息 |
| type  | RespType | 结果类型：INTERMEDIATE、ASR_FINISH、FINISH |
| asr    | string | asr实时识别的结果     |
| nlp    | string | nlp识别的结果: {"appId": "技能id", "appName": "技能名称", "asr": "asr识别结果", "cloud": "是否为云端技能: true / fasle", "intent": "意图", "pattern": "设定的用户语句","slots": { "槽名称": { "type": "槽类型", "value": "槽的值" }}}|
| action | string | cloud app处理的结果，json字符串 |
| extra | string | 目前有：{"activation": "xxx"} |
| vpr | string | 声纹的结果，json字符串，目前为：{"id": "xxx"} |
| asr_phoneticisms | string | 每个字的拼音结果，json字符串，如“晓”字的拼音为{"phoneticism":"xiao3","word":"晓","type":"CHINESE"} |
| voice_trigger | string | 激活词的识别结果 |

##### 说明

1. 字段 extra 返回 激活词（由 SpeechRequest 中的 voice_trigger 指定）的二次确认、仲裁、声纹结果，为 json 格式，其中 activation 有如下取值：

    - none: 无激活词
    - accept: 有激活词，并且识别结果确认以激活词开头
    - fake: 有激活词，但识别结果不以激活词开头
    - reject: 有激活词，但语音能量 voice_power 不是仲裁设备中最大的
    - invalidate: 打开了声纹锁，但说话者并不是已录制的用户
2. 当语音指令为 "激活词xxx" 时，如 "若琪现在几点"，除返回上述的 activation 值外，字段 extra 还会返回 {"oneshot": false}
3. SpeechRequest 中的 no_trigger_confirm 指定是否返回字段 extra 中 activation 为 "fake" 的结果
4. SpeechRequest 中的 no_intermediate_asr 指定是否返回字段 asr 中间结果
5. SpeechRequest 中的 no_nlp 指定是否返回字段 nlp 结果
6. voice的编码格式如下：
   - 识别支持pcm语音流识别，单通道 数据位宽16bit 采样率16kHZ pcm
   - 识别支持opu语音流识别，单通道 数据位宽16bit 采样率16kHZ opu opu压缩每帧数据格式由1字节（数据长度）+ opus压缩320字节数据


### 典型场景

#### 本地vad

- 如果发送的 VOICE 中包含 "若琪今天天气怎么样"，需要发送 END
- 使用场景
  - 物理按键开始拾音（发送 START），发送 VOICE...，放开结束拾音（发送 END）
  - 用激活词唤醒（发送 START），发送 VOICE…，本地 vad 结束（发送 END）


#### 云端vad

如果发送的 VOICE 中包含 "若琪今天天气怎么样"，设置 vad_timeout 为 500ms，不需要发送 END


### speech异常

* 如果内部服务异常或不可用，则 SpeechResponse.result 会被设为 INTERNAL
* 语音开始前 3s 内不包含人声，则
  * 如果带激活词，并且 asr 已经识别出激活词打头，则返回 extra 为 {"activation": "fake"}
  * 否则 按正常流程继续
* SpeechRequest.id 为 session id，只要确保同一连接下唯一即可
* 同一 session 中，如果有 **2s** 内没有收到下一个语音，则中止 session，按当时 asr 识别出的结果走后续流程
* 任一 session 的语音不允许超过 **10s**，超过即中止，按当时 asr 识别出的结果走后续流程
* 任一 session 中 asr 返回最终结果为 空，则立即返回 {FINISH, SUCCESS, asr(""), nlp(""), action(""), ...}


### speech 特殊逻辑
1. 二次确认 逻辑
  1. 当 asr 中间识别的文本 以 某一激活词打头，则返回 extra {"activation":"**accept**"} 即 正常激活
  2. 当 asr 中间识别的文本 比 最长激活词 多 9 个字时，进行判断
  3. 或 asr 识别为最终结果时，进行判断
  4. 如果不以任一激活词打头，则返回 extra {"activation":"**fake**"} 即 误激活
2. 仲裁 逻辑
   1. 当 仲裁服务 返回拒绝
   2. 并且在 1s 的响应时间内
   3. 返回 extra {"activation":"**reject**"} 即 仲裁失败
   4. 超时 1s，则丢弃这次结果
3. 声纹锁 逻辑
   1. 当 声纹服务 返回用户已经打开声纹锁，但未识别出有效用户
   2. 并且在 1s 的响应时间内
   3. 返回 extra {"activation":"**invalidate**"} 即 仲裁失败
   4. 超时 1s，则丢弃这次结果
4. 如果设置 **no_trigger_confirm**，voice_trigger（"abc"）而 asr 识别出来 "xyz123456"，则返回 {ASR_FINISH，"xyz123456"}，但按 "abc" 字的个数**3**取 "xyz123456" 前3个 "xyz" 作为此次的激活词走后续 nlp 流程，此时会有多种可能：
   - 如果 asr 误将 "abc" 识别成 "xyz"，则 nlp 将得到去掉激活词后的文本 "12356"，语义理解正常
   - 如果 asr 误将 "abc" 识别成 "xy"，则 nlp 将得到去掉激活词后的文本 "z12356"，语义理解可能会不正常
   - 如果 asr 误将 "abc" 识别成 "xyz1"，则 nlp 将得到去掉激活词后的文本 "2356"，语义理解可能会不正常
5. 请求中 voice_trigger 为 "|" 分隔的多激活词，二次确定将按最先匹配的激活词，而交给 nlp 则为文本匹配上的那个：
   - 如 voice_trigger（"abc|abcde"），当 asr 识别结果为 "abc"时，即返回 extra {"activation":"**accept**"}，则最终 asr 识别出 "abcde123"，则交给 nlp 的激活词为 "abcde"
   - 如 voice_trigger（"abc|abcde"），当 asr 识别结果为 "abc"时，即返回 extra {"activation":"**accept**"}，则最终 asr 识别出 "xyz123"，则交给 nlp 的激活词为 "xyz12"


