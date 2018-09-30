### 开放平台接口定义文档(websocket版)

  - [服务地址](#服务地址)
  - [协议地址](#协议地址)
  - [协议概述](#协议概述)
  - [协议详解](#协议详解)
    - [设备认证](#%E8%AE%BE%E5%A4%87%E8%AE%A4%E8%AF%81)
    - [语音交互](#%E8%AF%AD%E9%9F%B3%E4%BA%A4%E4%BA%92)
    - [语音合成](#%E8%AF%AD%E9%9F%B3%E5%90%88%E6%88%90)
  - [典型场景](#%E5%85%B8%E5%9E%8B%E5%9C%BA%E6%99%AF)
    - [本地 vad](#%E6%9C%AC%E5%9C%B0-vad)
    - [云端 vad](#%E4%BA%91%E7%AB%AF-vad)
  - [speech 异常](#speech-%E5%BC%82%E5%B8%B8)

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

### 协议详解

协议可分为以下三部分：

- [设备认证](#设备认证)
- [语音交互](#语音交互)（speech）
- [语音合成](#语音合成)（tts）

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
| type   | ReqType | START、VOICE、END 或 TEXT | 无   |
| voice  | bytes     | 需要识别的语音流      | 无    |
| asr    | bytes     | 需要理解的 asr 文本      | 无    |
| options    | SpeechOptions     | 辅助理解的选项        | 无    |
| lang    | string | 语音流的语言，目前支持 zh-CN，en-US。  | zh-CN |
| codec   | string | 语音流的编码，目前支持 pcm，opu，OPU2。 | PCM   |
| vad_mode   | VadMode | LOCAL、CLOUD | LOCAL |
| vend_timeout   | uint32 | 如果 vad_mode 为 CLOUD 时，指定 vad 时间，单位 ms，推荐设置为 500ms | 无   |
| no_nlp   | bool | 是否需要语义理解（nlp） | false   |
| no_intermediate_asr   | bool | 是否需要 asr 的实时识别结果 | false   |
| stack   | string | 设备当前的应用栈信息，"appid1:appid2"按照应用被调用的时间逆序排列          | 空     |
| voice_trigger      | string | 激活词，即用于唤醒设备的名字，如"若琪"；可用 "\|"分隔指定多个 | 空    |
| voice_power   | float | 语音流的音强，若设置则在多设备中作仲裁，同时只有音强最强的设备有响应 | 0      |
| trigger_start   | float | 语音流的激活词的开始位置。  | 无   |
| trigger_length   | float | 语音流的激活词的长度。  | 无   |
| skill_options  | string | 设备上的状态信息，为 json 结构，此结构会传给相应的 skill 的 cloud app   | 空     |
| voice_extra | string | asr 引擎 的参数，json 格式 | 空 |
| vad_begin | uint32 |  | 0 |
| no_trigger_confirm | bool | 是否需要云端激活词的二次确认功能 | false |

##### 说明

1. voice_trigger 激活词：设备的名字，当用户说这个词时，设备会被唤醒，并给出反应。
2. VAD：语音活性检测(Voice activity detection)，当用户说了一个指令后，停顿一定时间(可以由vad_timeout参数设定)，会被设备或云端认为已经说完
3. 仲裁：同一用户的多个设备同时收到语音指令时，由 voice_power 的强弱决定离说话人的远近，从而最近的设备有响应，而其它设备无响应
4. 声纹：由 trigger_start 及 trigger_length 来指明 激活词 在语音流中的位置，声纹服务用来作说话人识别

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

#### 语音合成

##### 流程
1. 需要先进行 service 为 tts 的 [设备认证](#%E8%AE%BE%E5%A4%87%E8%AE%A4%E8%AF%81)
2. 一次完整的语音合成的数据包以 id 来标识，称为一个 session
3. 语音数据以流的形式返回
4. 中间数据块 finish = false
5. 以 finish = true 的数据块结束

##### TtsRequest

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| text   | string    | 需要转换的text文本          | 无    |
| declaimer | string | 发音人，目前支持 中文成人 "zh" 与 中文儿童 "c1" 两种 | 无 |
| codec     | string | 语音流的编码，目前支持pcm、opu、OPU2、mp3。   | 无  |
| sample_rate | uint32 | 语音流的码率，目前支持 16000 与 24000 | 24000 |

##### 说明

1. declaimer 发音人
   - zh: 成人，会读中文与英文
   - c1: 儿童，会读中文与英文(完善中)
2. text 中的文本中可以设置 SSML 标签，详见[SSML文档](https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/ssml-document.html)
3. codec 编码格式：
   - pcm：24000，16bit，mono
   - opu：由数据帧组成，每帧由 1字节（后面数据长度）与 用opus压缩320字节后的数据
   - opu2：与 opu 区别是没有表示数据长度的1字节
   - mp3：mp3编码，保存成文件可以直接用播放器播放
4. 需要注意：这里的 pcm 与 [语音交互](#%E8%AF%AD%E9%9F%B3%E4%BA%A4%E4%BA%92) 的 pcm 格式语音的码率，如果不一致，则**不能**作为 [语音交互](#%E8%AF%AD%E9%9F%B3%E4%BA%A4%E4%BA%92) 的输入，否则会有识别问题。
5. sample_rate 可设置为 16000 或 24000，16000 语音数据较少，所需带宽较小，效果较差


##### TtsResponse

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   |
| result  | SpeechErrorCode | 错误信息 |
| text  | string | voice语音中包含的文字 |
| voice | bytes  | 合成的voice语音    |
| finish   | bool | 是否是此次合成请求的最后一个语音包 |

##### 说明

1. 接收到第一个数据块就可以开始播放，以加快响应速度

### 典型场景

#### 本地 vad

- 如果发送的 VOICE 中包含 "若琪今天天气怎么样"，需要发送 END
- 使用场景
  - 物理按键开始拾音（发送 START），发送 VOICE...，放开结束拾音（发送 END）
  - 用激活词唤醒（发送 START），发送 VOICE…，本地 vad 结束（发送 END）


#### 云端 vad

如果发送的 VOICE 中包含 "若琪今天天气怎么样"，设置 vad_timeout 为 500ms，不需要发送 END


### speech 异常

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


