## Cloud App 开发协议
### Rokid 开放平台
版本：1.0.1-alpha

### 大纲


* [简介](#1-简介)
	* [一些概念](#11-一些概念)
* [Request](#2-request)
	* [协议概览](#21-协议概览)
	* [Session 定义](#22-session定义)
	* [Context 定义](#23-context定义)
	* [Request 定义](#24-request定义)
* [Response](#3-response)
	* [协议概览](#31-协议概览)
	* [Action 定义](#32-action定义)

### 1. 简介

本文是对在 *[Rokid 开发者社区][developer_website_link]* 上开发 CloudApp 的协议的详细描述。

[developer_website_link]: https://developer.rokid.com

#### 1.1 一些概念

在了解本文所描述协议之前，需要对以下概念作如下说明：

* **CloudApp** - 在 *[Rokid 开发者社区][developer_website_link]* 上接入的云端应用，可以理解为遵循本文所描述的协议开发的某种云端服务或小应用。
* **CloudDispatcher** - 用于向 CloudApp 传递请求和分发 CloudApp 返回结果的模块。
* **CloudAppClient** - 用于处理 CloudApp 返回结果的设备端的执行容器。
* **RokidMobileSDK** - 与 *[Rokid 开发者社区][developer_website_link]* 相关联的手机端 SDK，用于对 CloudApp 的信息扩展展示或第三方授权。
* **TTS** - **T**ext **T**o **S**peech 的缩写，这是机器人的语音表达方式。

### 2. Request

*Request* 是 *CloudDispatcher* 产生的用于向 *CloudApp* 获取对应返回结果的请求。目前有两种类型的请求：一种是 **IntentRequest**，一种是 **EventRequest**。**IntentRequest** 是根据语音识别和语义理解（*NLP*）的结果创建的，其中会带有（*NLP*）的信息。**EventRequest** 是在当有某种事件发生时产生的，并通过 *CloudDispatcher* 转发给当前 *CloudApp*，比如当某个TTS播放结束的时候会产生一个 TTS 结束的事件，当前 *CloudApp* 可以选择处理或者不处理。

#### 2.1 Request 协议预览

##### 2.1.1 Request Header
为了保证 Https 链接访问的安全性，在 http 请求的 hearder 中增加了 Singature 来校验请求是否来源于 Rokid。

Http Hearder 中相关内容的示例如下：

	Content-Type: application/json;charset=utf-8
	Signature: DAF1E1062C21E3BB80A55BA32F41D935

您可以在「技能开发的-配置」中，填写您自定义的认证 key（支持大小写英文和数字，最长不超过36位）。

**认证 key 的生成规则为：**
`Signature = MD5(Secret + MD5(Body))`

##### 2.1.2 Request Body

*Request* 的整体协议定义如下所示：

```json
{
  "version": "2.0.0",
  "session": {
    "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6",
    "newSession": true,
    "attributes": {
       "key1": {"type":"","value":""}
    }
  },
  "context": {
    "application": {
      "applicationId": "skill 本身的 Id",
      "media": {
        "state": "PLAYING/PAUSED/IDLE",
        "itemId": "Skill 响应的 MediaId",
        "token": "Skill 响应的 MediaToken",
        "progress": "当前的播放进度单位毫秒",
        "duration": "当前 Media 的总长度单位毫秒"
        },
     "voice": {
        "state": "PLAYING/PAUSED/IDLE",
        "itemId": "Skill 响应的 VoiceId"
        }
    },
    "device": {
      "basic": {
        "vendor": "注册生产商 ID",
        "deviceType": "该生产商设定的设备型号",
        "deviceId": "该型号下的设备 ID",
        "masterId": "设备主人 ID",
        "voicetrigger": "设备当前的激活词",
        "locale": "zh-cn",
        "timestamp": 1478009510909
      },
      "screen": {
        "x": "640",
        "y": "480"
      },
      "media": {
        "state": "PLAYING / PAUSED / IDLE"
      },
      "voice": {
        "state": "PLAYING / PAUSED / IDLE"
      },
      "location": {
        "latitude": "30.213322455923485",
        "longitude": "120.01190010997654",
        "country": "国家",
        "state": "州/省份",
        "city": "城市",
        "area": "区县",
        "district": "地区，行政",
        "street": "街道",
        "timeZone": "时区"
      }
    },
    "user": {
      "userId": "当前用户的ID"
    }
  },
  "request": {
    "reqType": "INTENT / EVENT",
    "reqId": "当前请求的 Id",
    "content": {
      "intent": "play_random",
      "sentence": "用户语句",
      "slots": {
        "key1":{"type":"","value":""},
        "key2":{"type":"","value":""}
      }
    }
  }
}
```

* **request** - 协议中真正代表此次 *Request* 的实体，会明确给出请求的类型 **RequestType** 和请求的内容 **RequestContent**。
* **request** - 注意获取用户语句时候，不要获取 **sentence**，建议使用 **slot**

#### 2.2 Session定义

*Session* 向所请求的 *CloudApp* 表明了会话的信息，每一次对 *CloudApp* 的请求都会产生会话信息，会话的信息和状态由开放平台的系统更新。*Session* 也提供了 *attributes* 字段留给 *CloudApp* 来保存一些上下文信息。具体阐述如下：

```json
"session": {
    "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6",
    "newSession": true,
    "attributes": {
      "key1": {"type":"","value":""}
    }
  }
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| sessionId              | string          | *每次会话的唯一ID，由系统填充*  |
| newSession  | boolean         | *true / false (由系统填充)*   |
| attributes             | key-object map          | *一个string-object map*         |

* **sessionId** - 每次会话的唯一 ID，由系统填充
* **newSession** - 向 CloudApp 表明此次会话是新的会话还是已经存在的会话，true 为新会话，false 为老会话
* **attributes** - 为 *CloudApp* 提供 *attributes* 字段留保存上下文信息的字段，开发者目前只能通过 INTENT 类型的 Request 拿到 attributes 信息，EVENT 类型的 Reuqest 还不能拿到，后续我们会做修改，attributes 是一个 key-object map 类型数据开发者可以自定义传 key 和 object，上述 json 只是一个样例，并不代表完全限制只能传递 type 和 value。

#### 2.3 Context定义

*Context* 向所请求的 CloudApp 提供了当前的设备信息，用户信息和应用状态，用以帮助 CloudApp 更好的去管理逻辑状态以及对应的返回结果。

```json
"context": {
    "application": {},
    "device": {},
    "user": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| application              | ApplicationInfo object          | *ApplicationInfo 对象*  |
| device  | DeviceInfo object         | *DeviceInfo 对象*   |
| user          | UserInfo object          | *UserInfo 对象*  |

##### 2.3.1 ApplicationInfo

*ApplicationInfo* 包含了当前的应用信息，目前有 **applicationId**、**media**、**voice** 可用。

```json
"application": {
    "applicationId": "application id for requested CloudApp",
    "media": {},
    "voice": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| applicationId     | string         | *应用 ID 字符串*  |
|media|object|*mediaInfo 对象*|
|voice|object|*voiceInfo 对象*|

* **applicationId** - *CloudApp* 在 *Rokid 开放平台* 上的唯一ID.
* **media** - 当前与您 Skill 相关的 media 状态。包括当前的播放状态、媒体 itemId、媒体 token、媒体播放进度、媒体总长度。
* **voice** - 当前与您 Skill 相关的 voice 状态。包括当前的播放状态、音频流 itemId。

##### 2.3.2 DeviceInfo

*DeviceInfo* 是对此次请求发生时当前设备信息的描述。

```json
"device": {
    "basic":{},
    "screen":{},
    "media": {},
    "voice": {},
    "location": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| basic    | BasicInfo object          | *BasicInfo 对象*  |
| screen    | ScreenInfo object          | *ScreenInfo 对象*  |
| media     | MediaStatus object          | *当前设备上 CloudAppClient 的 MediaPlayer 状态*  |
| location  | LocationInfo object          | *当前设备的地理位置信息*  |

* **basic** - 展示了当前设备的基础信息，主要包含设备制造信息、时间信息、国家文字信息。
* **screen** - 展示了当前设备的屏幕信息，主要包含屏幕的分辨率信息。
* **media** - 向 CloudApp 表明当前设备上 CloudAppClient 中的 MediaPlayer 的状态信息。
* **location** - 向 CloudApp 提供当前设备的地理位置信息。

###### 2.3.2.1 BasicInfo

```json
"basic":{
    "vendor":"vendor id",
    "deviceType":"device type",
    "deviceId": "010116000100",
    "masterId": "设备主人ID",
    "voicetrigger": "设备当前的激活词",
    "locale": "zh-cn",
    "timestamp": 1478009510909
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| vendor  | string         | *注册生产商 ID*  |
| deviceType    | string         | *该生产商设定的设备型号*  |
| deviceId    | string         | *该型号下的设备 ID*  |
| masterId    | string         | *对应设备的主人 ID*  |
|voicetrigger|string|*对应设备当前的激活词*|
| locale    | string         | *国家及语言，标准 locale 格式*  |
| timestamp    | long         | *当前时间，unix timestamp*  |


* **vendor** - 生产商 ID，通过在网站注册生产商生成，保证全局唯一
* **deviceType** - 设备型号 ID，通过在网站注册设备型号生成，保证生产商内部唯一
* **deviceId** - 设备ID，由生产商自行生成，保证设备型号内部唯一
* **locale** - 国家及语言，采用标准 locale 格式，language-country
* **timestamp** - 当前时间，使用设备当前的时间戳，unix timestamp

###### 2.3.2.2 ScreenInfo

当前设备显示的设备信息：

```json
"screen":{
    "x":"640",
    "y":"480"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| x  | string         | *X 方向上的像素大小*  |
| y    | string         | *Y 方向上的像素大小*   |


* **x** - X 方向上的像素大小
* **y** - Y 方向上的像素大小
* 根据给出的屏幕分辨率信息，通常来讲，如果 **x** 比 **y** 大，那么该屏幕会被认为是横屏 **landscape**，反过来则是竖屏 **protrait**.

###### 2.3.2.3 MediaStatus

当前设备上 CloudAppClient 中 MediaPlayer 的状态：

```json
"media": {
    "state": "PLAYING / PAUSED / IDLE"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| state  | string         | *PLAYING / PAUSED / IDLE*  |


* **state** - 表明当前播放状态. 当前有 **PLAYING** 、**PAUSED** 和 **IDLE** 三种状态可用。
    * **PLAYING**：代表当前有媒体正在播放；
    * **PAUSED**：代表当前媒体被暂停，可以执行继续播放（RESUME）操作；
    * **IDLE**：代表当前媒体播放器为空闲状态，没有任何媒体数据。


###### 2.3.2.4 VoiceStatus
参见上述[2.3.2.3 MediaStatus](#2323-mediastatus)

###### 2.3.2.5 LocationInfo

```json
"location": {
    "latitude": "30.213322455923485",
    "longitude": "120.01190010997654",
    "country": "国家",
    "state": "州/省份",
    "city": "城市",
    "area": "区县",
    "district": "地区，行政",
    "street": "街道",
    "timeZone": "时区"
}
```

当当前设备存在地理位置信息时会通过 *location* 提供给 CloudApp。基于地理位置的 CloudApp 可以根据此信息来处理逻辑。*location* 信息包括 **纬度(latitude)** 和 **经度(longtitude)** 等。

##### 2.3.3 UserInfo

UserInfo 展示了与当前的用户信息，通常是设备对应手机应用的账号。

```json
"user": {
    "userId": "user id string"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| userId  | string         | *用户 ID*  |

*注意：该用户 id 和 MasterId 的区别在于，用户 Id 为当前使用者的 Id，MasterId 为机器主人的 ID，机器主人不一定是当前使用的用户，目前 UserId 和 MasterId 是一致的，但后期上了声纹以后该两者会不一致。*

#### 2.4 Request定义

*Request* 是当前请求的真正内容：

```json
"request": {
    "reqType": "INTENT / EVENT",
    "reqId": "string",
    "content": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| reqType  | string         | *INTENT / EVENT*  |
| reqId    | string         | *当前请求的唯一 ID*  |
| content  | request content object         | *IntentRequest 或 EventRequest 的对象*  |

* **reqType** - 表明请求的类型： **INTENT** 和 **EVENT** 分别对应 *IntentRequest* 和 *EventRequest*。
* **reqId** - 每次请求都会对应一个唯一ID用以区分每一次的请求。
* **content** - **IntentRequest** 和 **EventRequest** 对应的具体内容，下面会具体介绍。

##### 2.4.1 IntentRequest

IntentRequest 是基于 *NLP* 的结果产生的请求，其中包括了 *NLP* 的所有信息：**ApplicationId**， **Intent** 和 **Slots**。IntentRequest 将会发给对应的 *CloudApp* 根据 *intent* 和 *slots* 进行相应的逻辑处理。

```json
"content": {
    "applicationId": "com.rokid.cloud.music",
    "intent": "play_random",
    "slots": {
        "key1":{"type":"","value":""},
        "key2":{"type":"","value":""}
    }
}
```

| 字段               | 类型            | 可能值 |
|:-------:       |:--------------:|:-------------------------------|
| intent         | string         | *CloudApp 对应的 nlp intent*     |
| slots          | object         | *CloudApp 对应的 nlp slots 对象*      |
| sentence         | string         | *CloudApp 对应的 用户说的话*     |

* **intent** 和 **slots** 均为 **NLP** 结果的基本元素。分别表明了一句话所代表意图和完成这个意图所需要的参数。

**intent** - 表明了当前具体的意图，目前我们有三个系统级的 Intent 请求具体如下。

* **ROKID.INTENT.WELCOME** - 当用户通过入口词打开该 Skill 时，会发送该 Intent 请求，请求内容如下：

```json
	"content": {
      "slots": {
        "domain": {
          "type": "app",
          "value": "domainid"
        },
        "openaction": {
          "type": "openaction",
          "value": "打开"
        }
      },
      "intent": "ROKID.INTENT.WELCOME",
      "sentence": "打开XXX"
    }
```
**开发者可以在这个 Intent 中给用户做欢迎引导语句也可以执行对应的操作**

* **ROKID.INTENT.EXIT** - 当用户需要退出该 Skill 时，会发送该 Intent 请求，请求内容如下：

```json
	"content": {
      "intent": "ROKID.INTENT.EXIT",
      "sentence": "退出XXX",
      "slots": {
        "closeaction": {
          "type": "closeaction",
          "value": "退出"
        },
        "domain": {
          "type": "app",
          "value": "domainid"
        }
      }
    }
```
**开发者不能对该 Request 做响应，但是开发者可以通过该 Request 记录服务的业务日志**

* **ROKID.INTENT.UNKNOWN** - 当 Skill 发起 Confirm 或者 Pickup 时，用户说了三次都没有命中该 Skill 需要的内容，这时候会发送该 Intent 请求，请求内容如下：

```json
	"content": {
      "intent": "ROKID.INTENT.UNKNOWN",
      "sentence": "用户说的话",
      "slots": {
        "asrvalue": {
          "type": "asrvalue",
          "value": "用户说的话"
        },
        "unknowtype": {
          "type": "unkonwtype",
          "value": "pickup"
        }
      }
    }
```
**开发者可以在该 Request 请求时响应自定义的响应内容，比如游戏类的技能，可以换一个题目等操作，然后开发者也可以直接退出该技能，unknowtype 有两种一个是 pickup，一个是 confirm**

###### 2.4.1.1 slots
slots 是对象类型，含有如下两个字段：

|字段  |类型  | 说明 |
| :------ | :------ | :-------- |
| type | String | slot类型    |
|  value| String | slot值    |

*注意：Slots 对象其实对应的是一个 HashMap<String,Slot>,其实 Slot 目前有 type 和 value 两个字段。其中 HashMap的key 是当前 NLP 那边配置的 slot 名称，Slot 里面的 Type 值分为两种情况：
1、有引用系统词表，则该 type 为系统词表的名称；
2、如果没有引用系统词表，则和 key 一致为用户自定义名称，Slot 里面的 value 为用户真正需要的业务值，该值是一个 String 类型，但是需要注意的是该 String 有可能是一个 Json 的 String，开发者需要根据 Type 去进行数据的解析。如下 number 这个 slot 的定义响应*

```json
"slots": {
  "number": {
    "type": "ROKID.NUMBER_ZH",
    "value": "{\"number\":\"3.000000\",\"text\":\"三\"}"
  }
```


##### 2.4.2 EventRequest

当 CloudAppClient 在执行中发生了一个事件，则会产生一 个 EventRequest。*CloudApp* 可以根据自己的需要选择处理或者不处理当前收到的事件。

```json
"content": {
    "event": "Media.NEAR_FINISH",
    "extra": {
    	"key1": "value1",
    	"key2": "value2"
    }
}
```

| 字段               | 类型            | 可能值 |
|:-------:|:--------------:|:-------------------------------|
| event  | string         | *事件类型*   |
| extra  | string-string map         | *自定义字段，目前暂无定义，作扩展用*   |

* **event** - 表明了是具体的事件类型.
	* **Voice.STARTED** - 当 Voice 开始播放时发生。
	* **Voice.FINISHED** - 当 Voice 停止时发生，此处停止可能是被打断，可能是播放完成，也可能是播放失败，但都作为统一的事件抛出。
	* **Voice.FAILED** - 当 Voice 播放失败时发生。
	* **Media.STARTED** - 当 MediaPlayer 开始播放时发生。
	* **Media.PAUSED** - 当 MediaPlayer 暂停时发生。
	* **Media.FINISHED** - 当播放内容结束时发生。
	* **Media.TIMEOUT** - 在媒体播放过程中因为网络慢等原因导致的卡顿持续5s后发生。
	* **Media.FAILED** - 当播放器加载音频资源失败时发生。
	* **Session.ENDED** - 当切换 Domain 时候，可以用于关闭资源，不能进行任何响应。
	
	**特别注意：***为防止开发者在我们后续增加 Event 事件的时候出现服务异常，建议开发者对于不在自己 Skill 范围之内的 Event 做忽略处理，忽略响应的内容如下：*

```json
{
  "version": "2.0.0",
  "session": {
  },
  "response": {
    "action": {
      "version": "2.0.0",
      "type": "NORMAL",
      "shouldEndSession": false,
      "directives": [
       ]
    }
  }
}
```

* **extra** - 针对 media 类型的 eventrequest 支持如下扩展字段：

```json
"content": {
  "event": "Media.PAUSED",
  "extra": {
    "media": {
      "itemId":"MediaItem 里面的 ItemId",
      "token": "MediaItem 里面的 token",
      "progress": "当前进度",
      "duration": "音频文件的总长度"
    }
  }
}
```
* **extra** - 针对 voice 类型的 eventrequest 支持如下扩展字段：

```json
"content": {
  "event": "Voice.STARTED",
  "extra": {
    "voice": {
      "itemId":"voiceItem 里面的 ItemId"
    }
  }
}
```


### 3. Response

根据之前的描述，Response 是 *CloudApp* 向客户端的返回结果。

#### 3.1 协议概览

整体协议示例如下：

```json
{
  "version": "2.0.0",
  "session": {
    "attributes": {
      "key1": {"type":"","value":""}
    }
  },
  "response": {
    "card": {
          "type": "ACCOUNT_LINK"
          },
    "action": {
      "version": "2.0.0",
      "type": "NORMAL / EXIT",
      "form": "scene/cut/service",
      "shouldEndSession": true,
      "directives": [
          {
            "type":"voice",
            "action": "PLAY/PAUSE/RESUME/STOP",
            "disableEvent":false,
            "item": {
              "itemId":"string of itemid",
              "tts": "tts content"
            }
          },
          {
            "type":"media",
            "action": "PLAY/PAUSE/RESUME/STOP",
            "disableEvent":false,
            "item": {
              "itemId":"string of itemid",
              "token": "xxxx",
              "type": "AUDIO/VIDEO",
              "url": "media streaming url",
              "offsetInMilliseconds": 0
            }
          },
          {
            "type":"display",
          },
          {
            "type":"confirm",
            "confirmIntent": "nlp intent to confirm",
            "confirmSlot": "nlp slot to confirm",
            "optionWords": [
                "word1",
                "word2"
            ]
         },
          {
            "type":"pickup",
            "enable": true,
            "durationInMilliseconds": 1000
          }
       ]
    }
  }
}
```

* **version** - 表明了 Response 协议的版本，必须由 *CloudApp* 填充。当前协议版本是 `2.0.0`.
* **session** - 表示当前应用的 session，与 Request 中的信息一致，*CloudApp* 可以在 *attributes* 里填充自己需要的上下文信息用于后面的请求。
* **response** - 返回给 *CloudAppClient* 的 Response 内容。包括了 `card` 和 `action` 两个部分。

#### 3.2 Card定义
Card 用于向 Rokid App 推送 push 消息。目前支持两种卡片类型：

- 用于第三方应用授权的 `ACCOUNT_LINK` 类型
- 用于展示若琪向用户发出对话内容的 `chat` 类型

更多card功能类型将在后续更新。

##### 3.2.1 Account_link
Account_link 类型将会向 Rokid App 发送一张账户授权的卡片，用于用户使用 Rokid 账号进行 Oauth 登录。如下：

```json
{
    "response": {
        "card" : {
          "type" : "ACCOUNT_LINK",
        },
        "action": {···},
        ···
    }
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| type           | string          | *ACCOUNT_LINK*  |


##### 3.2.2 Chat
Chat 类型将会向 Rokid App 发送一张无标题的纯文本卡片，用于展示若琪向用户说出的 TTS 内容。如下：

```json
{
    "response": {
        "card" : {
          "type" : "chat",
          "content" : "自定义词汇"
        },
        "action": {···},
        ···
    }
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| type           | string          | *chat*  |
| content           | string          | *需要在手机 APP 收到的卡片中展示的 TTS 语句*  |


#### 3.3 Action定义

Action 中最关键的部分是 `directives`，其中包含：

- `voice` 表示了语音交互的返回；
- `media` 是对媒体播放的返回；
- `confirm` 表示对特定语句进行确认时的返回；
- `pickup` 表示需要设备继续拾音时的返回。


```json
"action": {
      "version": "2.0.0",
      "type": "NORMAL / EXIT",
      "form": "scene/cut/service",
      "shouldEndSession": true,
      "directives": [
          {
            "type":"voice",
          },
          {
            "type":"media",
          },
          {
            "type":"display",
            //todo
          },
          {
            "type":"confirm",
          },
          {
            "type":"pickup",
          }
       ]
    }
}
```


| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| version           | string          | *action 协议的版本，当前为 2.0.0*  |
| type              | string          | *NORMAL / EXIT*  |
| form              | string          | *scene / cut / service*  |
| shouldEndSession  | boolean         | *true / false*   |
|directives|array|*directives 对象*|


* **version** - 表明 action 协议版本，当前版本为: 2.0.0.
* **type** - 当前action的类型：`NORMAL` 或 `EXIT`。 当 `type` 是 `NORMAL` 时，`voice` 和 `media` 会同时执行；当 `type` 是 `EXIT` 时，action 会立即退出，**清除系统端的应用 session**，并且在这种情况下，`voice` 和 `media` 将会被忽略。
* **form** - 当前 action 的展现形式：scene、cut、service。scene 的 action 会在被打断后压栈，cut 的 action 会在被打断后直接结束，service 会在后台执行，但没有任何界面。该字段在技能创建时被确定，无法由 cloud app 更改。
* **shouldEndSession** - 表明当此次返回的 action 执行完后 *CloudAppClient* 是否要退出,并且是否需要 **清除系统端的应用 session**，同时，当 `shouldEndSession` 为 `true` 时，*CloudAppClient* 将会忽略 *EventRequests*，即在 action 执行过程中不会产生 *EventRequest*。
* **directives** - 表明此次返回中需要让设备执行的指令。当前包含 `voice`, `media`, `confirm`, `pickup` 四种类型。


##### 3.3.1 Voice

*Voice* 定义了 *CloudApp* 返回的语音交互内容。具体定义如下：

```json
{
    "type":"voice",
    "action": "PLAY/PAUSE/RESUME/STOP",
    "disableEvent":false,
    "item": {
      "itemId":"string of itemid",
      "tts": "tts content"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| action              | string          | *PLAY / PAUSE / RESUME / STOP*  |
| disableEvent       | boolean    | *是否需要关闭 Event 事件的接收*        |
| item       | item object    | *voice 的 item 对象*         |

* **action** - 表示对当前 voice 的操作，可以播放（PLAY)、暂停（PAUSE）、继续播放（RESUME）和停止（STOP）（具体 Action 行为参照 Media 的 Action 行为，但是目前暂未实现，**PAUSE** 以及 **RESUME** 操作）;
* **disableEvent**-表示当前这个 Voice 执行过程中是否需要关闭 Event 事件，可以不传，默认 **false** 表示接收 Voice 的 EventRequest；
* **item** - 定义了 voice 的具体内容，将会在 *3.3.1.1* 中详细描述。

###### 3.3.1.1 Item

Item 定义了 voice 的具体内容。

```json
"item": {
    "itemId":"string of itemid",
    "tts": "tts content"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| itemId           | string          | *tts 内容的 ID*  |
| tts              | string          | *tts 内容*  |

* **itemId** - 定义了播报内容的 ID，当 disableEvent=false 时，VoiceEvent 会在拓展字段中带上 itemId。
* **tts** - 定义了需要播报的 TTS 内容。

##### 3.3.2 Media

Media 用来播放 CloudApp 返回的流媒体内容。有 *audio* 和 *video* 两种类型，目前第一版暂时只对 *audio* 作了支持，后续会支持 *video*。

```json
{
    "type":"media",
    "action": "PLAY/PAUSE/RESUME/STOP",
    "disableEvent":false,
    "item": {
      "itemId":"string of itemid",
      "token": "xxxx",
      "type": "AUDIO/VIDEO",
      "url": "media streaming url",
      "offsetInMilliseconds": 0
            }
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| action              | string          | *PLAY / PAUSE / RESUME / STOP*  |
| disableEvent       | boolean    | *是否需要关闭 Event 事件的接收*        |
| item  | media item object        | *media 的具体内容*  |

* **action** - 定义了对 MediaPlayer 的操作，目前只支持 **4** 种操作：**PLAY**， **PAUSE** ， **RESUME** 和 **STOP**。其中，只有 **PLAY** 接受 **item** 数据。
    * **PLAY**：如果有 **item** 数据，则按照最新的 **item** 从头开始播放，如果没有 **item** 数据，且原来有在播放的内容，则从原来播放的内容开始播放
    * **PAUSE**：暂停当前播放的内容，播放的进度等数据不会丢失（可以直接通过 **RESUME** 指令直接恢复原来的播放状态）
    * **RESUME**：继续播放（从原来的播放进度播放）
    * **STOP**：停止播放，并且清空当前的播放进度，但是播放内容不清
* **disableEvent**-表示当前这个 Media 执行过程中是否需要关闭 Event 事件，可以不传，默认 **false** 表示接收 Media 的 EventRequest
* **item** - 定义了具体的播放内容，如下：

###### 3.3.2.1 Item

```json
"item": {
    "itemId":"string of itemid",
    "token": "xxxx",
    "type": "AUDIO/VIDEO",
    "url": "media streaming url",
    "offsetInMilliseconds": 0
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| itemId           | string          | *Media 内容的 ID*  |
| token              | string          | *用于鉴权的 token，由 CloudApp 填充和判断*  |
| type          | string          | *AUDIO / VIDEO* |
| url  | string        | *可用的流媒体播放链接*  |
| offsetInMilliseconds  | long        | *毫秒数值，表明从哪里开始播放*  |

* **token** - 用于鉴权的 token，由 CloudApp 填充和判断，且该 Token 的值会在该 Media 执行的 EventRequest 的拓展信息中原样带回。
* **itemId**定义了播报内容的 ID，当 disableEvent=false 时，MediaEvent 会在拓展字段中带上 itemId。
* **type** - 表明了当前媒体类型：**AUDIO** 或 **VIDEO**，有且只能取其一。
* **url** - 为 MediaPlayer 指明可用的流媒体播放链接。
* **offsetInMilliseconds** - 毫秒数值，告诉 MediaPlayer 开始播放的位置。有效范围从0到歌曲整体播放时长。

##### 3.3.3 Confirm
表明此次返回中，是否存在需要 confirm 的内容。[了解用法指南](/2-RokidDocument/1-SkillsKit/important-concept/confirm)。

```json
{
    "type":"confirm",
    "confirmIntent": "nlp intent to confirm",
    "confirmSlot": "nlp slot to confirm",
    "optionWords": [
      "word1",
      "word2"
    ]
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| confirmIntent           | string          | *需要进行 confirm 的 intent 内容*  |
| confirmSlot           | string          | *需要进行 confirm 的 slot 内容*  |
| optionWords           | array          | *动态新增的 confirm 内容*  |

* **confirmIntent**：表明此次返回对哪一个 intent 进行 confirm。
* **confirmSlot**：表明此次返回对哪一个 slot 进行 confirm。
* **optionWords**：可选项。表明此次返回中在 confirmSlot 之上需要新增的 confirm 选项，用于需要动态新增 confirm 内容的场景。


##### 3.3.4 Pickup

Pickup 用来控制拾音状态（可以理解为手机app上的对话框）。当 CloudApp 没有可执行的内容时，会执行 Pickup，如果 Pickup 为空，则按照 Pickup.enable=false 执行。

```json
{
    "type":"pickup",
    "enable": true,
    "durationInMilliseconds": 1000,
    "retryTts":"自定义语句"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| enable              | boolean         | *true / false*  |
| durationInMilliseconds  | int        | *在没有用户说话时拾音状态持续多久，单位毫秒*  |
|retryTts|string|*定义在 pickup 未命中或超时后将会提示的语句*|

* **enable** - 定义了对拾音状态的开关操作：**true**，**false** ，其中，只有 **true** 接受 **durationInMilliseconds** 数据。
    * **true**：当 CloudApp 没有可执行的内容（**Voice播报**，**Media播报**，**EventRequest发送**）时，会把拾音打开。
    * **false**：不打开

* **durationInMilliseconds** - 当 **enable=true** 时，表示在用户不说话的情况下，拾音打开持续时间，单位**毫秒**。最长持续时间为6000ms。
