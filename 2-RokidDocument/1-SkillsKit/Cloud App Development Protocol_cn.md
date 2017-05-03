## Cloud App 开发协议
### Rokid 开放平台
版本：1.0.0-alpha

语言：简体中文（[Change to English](https://github.com/Rokid/docs/blob/master/2-RokidDocument/1-SkillsKit/Cloud%20App%20Development%20Protocol_en.md)）

### 大纲
* [简介](#1-简介)
	* [一些概念](#11-一些概念)
* [Request](#2-request)
	* [协议概览](#21-协议概览)
	* [Session定义](#22-session定义)
	* [Context定义](#23-context定义)
	* [Request定义](#24-request定义)
* [Response](#3-response)
	* [协议概览](#31-协议概览)
	* [Action定义](#32-action定义)

### 1. 简介

本文是对在*[Rokid开放平台][developer_website_link]*上开发CloudApp的协议的详细描述。

[developer_website_link]: https://developer.rokid.com

#### 1.1 一些概念

在了解本文所描述协议之前，需要对一下概念作如下说明：

* **CloudApp** - 在*[Rokid开放平台][developer_website_link]*上接入的云端应用，可以理解为遵循本文所描述的协议开发的某种云端服务或小应用。
* **CloudDispatcher** - 用于向CloudApp传递请求和分发CloudApp返回结果的模块。
* **CloudAppClient** - 用于处理CloudApp返回结果的设备端的执行容器。
* **RokidMobileSDK** - 与*[Rokid开放平台][developer_website_link]*向关联的手机端SDK，用于对CloudApp的信息扩展展示或第三方授权。
* **TTS** - **T**ext **T**o **S**peech的缩写，这是机器人的语音表达方式。

### 2. Request

*Request* is used to fetch response from *CloudApps*, which is sent by *CloudDispatcher*. Currently **IntentRequest** and **EventRequest** are available. **IntentRequest** is created according an *NLP* intent. And **EventRequest** is created when an event occurs.

*Request* 是*CloudDispatcher*产生的用于向*CloudApp*获取对应返回结果的请求。目前有两种类型的请求：一种是**IntentRequest**，一种是**EventRequest**。**IntentRequest** 是根据语音识别和语义理解（*NLP*）的结果创建的，其中会带有（*NLP*）的信息。**EventRequest**是在当有某种事件发生是产生的，并通过*CloudDispatcher*转发给当前*CloudApp*，比如当某个TTS播放结束的时候会产生一个TTS结束的事件，当前*CloudApp*可以选择处理或者不处理。

#### 2.1 协议概览

*Request* 的整体协议定义如下所示：

```
{

    "version": "2.0.0",

    "session": {

        "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6", 

        "newSession": true, 

        "applicationId": "application id for requested CloudApp",

        "attributes": {
            "key1": "value1",
	    "key2": "value2"
        }
	
    },

    "context": {

        "application": {
	    "applicationId": "application id for requested CloudApp"
        },

        "device": {  
	    
	    "basic":{
                "vendor":"vendor id",
                "deviceType":"device type",
                "deviceId": "010116000100",
                "locale": "zh-cn",
                "timestamp": 1478009510909
	    },

            "screen":{
		"x":"640",
		"y":"480"
            },

            "media": {
                "state": "PLAYING / PAUSED"
            },

            "location": {
                "latitude": "30.213322455923485",
                "longitude": "120.01190010997654"
            }
	    
        },

        "user": {
            "userId": "user id string"
        }
	
    },

    "request": {

        "reqType": "intent / event",

        "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a",

	"content": {
            "applicationId": "com.rokid.cloud.music",
            "intent": "play_random",
            "slots": {
            }
        }
	
    }
    
}
```

* **request** - 协议中真正代表此次*Request*的实体，会明确给出请求的类型**RequestType**和请求的内容**RequestContent**。

#### 2.2 Session定义

*Session* 向所请求的*CloudApp*表明了会话的信息，每一次对*CloudApp*的请求都会产生会话信息，会话的信息和状态由开放平台的系统更新。*Session*也提供了*attributes*字段留给*CloudApp*来保存一些上下文信息。具体阐述如下：

```
"session": {
    "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6", 
    "newSession": true, 
    "applicationId": "application id for requested CloudApp",
    "domain": "domain for requested CloudApp",
    "attributes": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| sessionId              | string          | *每次会话的唯一ID，由系统填充*  |
| newSession  | boolean         | *true / false (由系统填充)*   |
| applicationId          | string          | *当前会话的CloudApp的ID*  |
| domain       | string    | *所请求的CloudApp的domain*         |
| attributes             | key-value map          | *一个string-string map*         |

* **sessionId** - 每次会话的唯一ID，由系统填充
* **newSession** - 向CloudApp表明此次会话是新的会话还是已经存在的会话
* **applicationId** - 表明当前会话的CloudApp的ID，由开放平台在申请应用时自动生成
* **domain** - 表明当前会话的CloudApp的*domain*，由开放平台在申请应用时自动生成
* **attributes** - 为*CloudApp*提供*attributes*字段留保存上下文信息的字段

#### 2.3 Context定义

*Context* 向所请求的CloudApp提供了当前的设备信息，用户信息和应用状态，用以帮助CloudApp更好的去管理逻辑，状态以及对应的返回结果。

```
"context": {
    "application": {},
    "device": {},
    "user": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| application              | ApplicationInfo object          | *ApplicationInfo对象，目前只有应用ID*  |
| device  | DeviceInfo object         | *DeviceInfo对象*   |
| user          | UserInfo object          | *UserInfo对象*  |

##### 2.3.1 ApplicationInfo

*ApplicationInfo* 包含了当前的应用信息，目前只有**applicationId**可用。

```
"application": {
    "applicationId": "application id for requested CloudApp"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| applicationId     | string         | *应用ID字符串*  |

* **applicationId** - *CloudApp*在*Rokid开放平台*上的唯一ID.

##### 2.3.2 DeviceInfo

*DeviceInfo* 是对此次请求发生时当前设备信息的描述。

```
"device": {
    "basic":{},
    "screen":{},
    "media": {},
    "location": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| basic    | BasicInfo object          | *BasicInfo对象*  |
| screen    | ScreenInfo object          | *ScreenInfo对象*  |
| media     | MeidaStatus object          | *当前设备上CloudAppClient的MediaPlayer状态*  |
| location  | LocationInfo object          | *当前设备的地理位置信息*  |

* **basic** - 展示了当前设备的基础信息，主要包含设备制造信息、时间信息、国家文字信息。
* **screen** - 展示了当前设备的屏幕信息，主要包含屏幕的分辨率信息。
* **meida** - 向CloudApp表明当前设备上CloudAppClient中的MediaPlayer的状态信息。
* **location** - 向CloudApp提供当前设备的地理位置信息。

###### 2.3.2.1 BasicInfo

```
"basic":{
    "vendor":"vendor id",
    "deviceType":"device type",
    "deviceId": "010116000100",
    "locale": "zh-cn",
    "timestamp": 1478009510909
}
```
| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| vendor  | string         | *注册生产商ID*  |
| deviceType    | string         | *该生产商设定的设备型号*  |
| deviceId    | string         | *该型号下的设备ID*  |
| locale    | string         | *国家及语言，标准locale格式*  |
| timestamp    | long         | *当前时间，unix timestamp*  |


* **vendor** - 生产商ID，通过在网站注册生产商生成，保证全局唯一
* **deviceType** - 设备型号ID，通过在网站注册设备型号生成，保证生产商内部唯一
* **deviceId** - 设备ID，由生产商自行生成，保证设备型号内部唯一
* **locale** - 国家及语言，采用标准locale格式，language-country
* **timestamp** - 当前时间，使用设备当前的时间戳，unix timestamp

###### 2.3.2.2 ScreenInfo

当前设备的显示设备信息：

```
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

当前设备上CloudAppClient中MediaPlayer的状态：

```
"media": {
    "state": "PLAYING / PAUSED"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| state  | string         | *PLAYING / PAUSED*  |


* **state** - 表明当前播放状态. 当前**有且仅有 PLAYING** 和 **PAUSED** 两种状态可用.

###### 2.3.2.4 LocationInfo

```
"location": {
    "latitude": "30.213322455923485",
    "longitude": "120.01190010997654"
}
```

当当前设备存在地理位置信息时会通过*location*提供给CloudApp。基于地理位置的CloudApp可以根据此信息来处理逻辑。*location* 信息目前包括 ***纬度(latitude)*** 和 ***经度(longtitude)***。

##### 2.3.3 UserInfo

UserInfo 展示了与当前设备绑定的用户信息，通常是设备对应手机应用的账号。

```
"user": {
    "userId": "user id string"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| userId  | string         | *用户ID*  |


#### 2.4 Request定义

*Request* 是当前请求的真正内容：

```
"request": {
    "reqType": "INTENT / EVENT",
    "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a",
    "content": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| reqType  | string         | *INTENT / EVENT*  |
| reqId    | string         | *当前请求的唯一ID*  |
| content  | request content object         | *IntentRequest 或 EventRequest的对象*  |

* **reqType** - 表明请求的类型： **INTENT** 和 **EVENT** 分别对应 *IntentRequest* 和 *EventRequest*。
* **reqId** - 每次请求都会对应一个唯一ID用以区分每一次的请求。请求ID将会与返回ID一一对应。
* **content** - **IntentRequest** 和 **EventRequest** 对应的具体内容，下面会具体介绍。

##### 2.4.1 IntentRequest

IntentRequest 是基于 *NLP* 的结果产生的请求，其中包括了 *NLP* 的所有信息：**ApplicationId**， **Intent** 和 **Slots**。IntentRequest将会发给对应的 *CloudApp* 根据 *intent* 和 *slots* 进行相应的逻辑处理。

```
"content": {
    "applicationId": "com.rokid.cloud.music",
    "intent": "play_random",
    "slots": {}
}
```

| 字段               | 类型            | 可能值 |
|:-------:       |:--------------:|:-------------------------------|
| applicationId  | string         | *CloudApp 对应的 applicationId*  |
| intent         | string         | *CloudApp 对应的 nlp intent*     |
| slots          | string         | *CloudApp 对应的 nlp slots*      |

* **applicationId**, **intent** 和 **slots** 均为 **NLP** 结果的基本元素。分别表明了一句话所代表的领域，意图和完成这个意图所需要的参数。

##### 2.4.2 EventRequest

当CloudAppClient在执行中发生了一个事件，则会产生一个EventRequest。*CloudApp* 可以根据自己的需要选择处理或者不处理当前收到的事件。

```
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
	* **Voice.STARTED** - 当Voice开始播放时发生
	* **Voice.FINISHED** - 当Voice停止是发生，此处停止可能是被打断，可能是播放完成，也可能是播放失败，但都作为统一的事件抛出。
	* **Media.START_PLAYING** - 当MediaPlayer开始播放时发生。
	* **Media.PAUSED** - 当MediaPlayer中途停止时发生。
	* **Media.NEAR_FINISH** - 当播放内容结束前15秒时发生，当总时长不足15秒时，会在 *Media.START_PLAYING** 后发生。
	* **Media.FINISHED** - 当播放内容结束时发生。
	* *更多的事件会在未来的版本更迭中给出*

* **extra** - 预留扩展字段，暂无定义。

### 3. Response

根据之前的描述，Response是 *CloudApp* 向客户端的返回结果。

#### 3.1 协议概览

整体协议示例如下：

```
{
    "version": "2.0.0",
    "session": {
        "attributes": {
    	    "key1": "value1",
    	    "key2": "value2"
        }
    },
    "response": {
        "action": { // for Rokid device

            "version":"2.0.0",

	    "type": "NORMAL / EXIT", 
            
            "shoudEndSession": true, 
            
            "voice": {
                "needEventCallback": true,
                "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
                "item": {
                    "tts": "tts content"
                }
            },

            "media": {
                "needEventCallback": true,
                "action": "PLAY/PAUSE/RESUME",
                "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
                "item": {
                    "token": "xxxx",
                    "type": "AUDIO/VIDEO",
                    "url": "media streaming url",
                    "offsetInMilliseconds": 0
                }
            },
	    
	    "display": {
	    	// TBD
	    },

	    "confirm": {
		"confirmIntent": "nlp intent to confirm",
		"confirmSlot": "nlp slot to confirm",
		"optionWords": ["word1","word2"],
	    }
        }
    }
}
```

* **version** - 表明了Response协议的版本，必须由 *CloudApp* 填充。当前协议版本是 `2.0.0`.
* **session** - 表示当前应用的session，与Request中的信息一致，*CloudApp* 可以在 *attributes* 里填充自己需要的上下文信息用于后面的请求。
* **response** - 返回给 *CloudAppClient* 的Response内容。包括了 `card` 和 `action` 两个部分。`card` 会在之后的协议更新中作详细说明。

#### 3.2 Action定义

Action 目前包括两种类型：`voice` 和 `media`。`voice` 表示了语音交互的返回。`media` 是对媒体播放的返回。

```
"action": {
    "version": "2.0.0",
    "type": "NORMAL/EXIT", 
    "shoudEndSession": true, 
    "voice": {},
    "media": {},
    "display": {},
    "confirm": {}
}
```


| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| version           | string          | *action 协议的版本，当前为 2.0.0*  |
| type              | string          | *NORMAL / EXIT*  |
| shouldEndSession  | boolean         | *true / false*   |
| voice       | voice object    | *Voice对象*         |
| media             | media object          | *Media对象*         |

* **version** - 表明 action 协议版本，当前版本为: 2.0.0.
* **type** - 当前action的类型：`NORMAL` 或 `EXIT`。 当 `type` 是 `NORMAL` 时，`voice` 和 `media` 会同时执行；当 `type` 是 `EXIT` 时，action会立即退出，并且在这种情况下，`voice` 和 `media` 将会被会被忽略。
* **shouldEndSession** - 表明当此次返回的action执行完后 *CloudAppClient* 是否要退出，同时，当 `shouldEndSession` 为 `true` 时，*CloudAppClient* 将会忽略 *EventRequests*，即在action执行过程中不会产生 *EventRequest*。

##### 3.2.1 Voice

*Voice* 定义了 *CloudApp* 返回的语音交互内容。具体定义如下：

```
"voice": {
    "needEventCallback": true,
    "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
    "item": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| needEventCallback              | boolean          | *true / false*  |
| behaviour          | string          | *APPEND / REPLACE\_ALL / REPLACE\_APPEND / CLEAR*  |
| item       | item object    | *voice 的 item 对象*         |

* **needEventCallback** - 表示 *CloudAppClient* 是否需要等待所有 *EventRequest* 的返回结果。如果 *needEventCallback* 为 *true*， *CloudAppClient* 在action执行完后不会立即退出，会一直等待 *EventRequest* 的返回；当 *needEventCallback* 为 *false*， *CloudAppClient* 在action执行完后（包括队列中所有的action)，会立即退出，不会等待 *EventRequest* 的返回。 
* **behaviour** - 表示 `voice` 的队列执行策略。目前有如下四种 `behaviours`。默认情况下，如果 *behaviour* 在返回中没有提供，**REPLACE_ALL** 将会作为默认策略执行。
	* **APPEND** - 仅将当前voice加入队列，对当前正在执行的voice和队列已有的voice没有任何影响。
	* **REPLACE_ALL** - 会将当前正在执行的voice停止，将队列中已有的voice清除，再将当前新的voice加入队列并立即执行。
	* **REPLACE_APPEND** - 会将当前正在执行的voice停止，但不会清除队列中已有的voice，将新的voice加入队列，并执行队列。
	* **CLEAR** - 会立即停止当前所有的voice任务，此策略等同于退出voice，此时voice中的item内容将会被忽略。

* **item** - 定义了voice的具体内容，将会在 *3.2.1.1* 中详细描述.

###### 3.2.1.1 Item

Item定义了voice的具体内容。

```
"item": {
    "tts": "tts content"
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| tts              | string          | *tts 内容*  |

* **tts** - 定义了需要播报的TTS内容。

##### 3.2.2 Media

Media 用来播放CloudApp返回的流媒体内容。有 *audio* 和 *video* 两种类型，目前第一版暂时只对 *audio* 作了支持，后续会支持 *video*。

```
"media": {
    "needEventCallback": true,
    "action": "PLAY/PAUSE/RESUME",
    "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
    "item": {}
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| needEventCallback              | boolean          | *true / false*  |
| action              | string          | *PLAY / PAUSE / RESUME*  |
| behaviour          | string          | *APPEND / REPLACE\_ALL / REPLACE\_APPEND / CLEAR* |
| item  | media item object        | *media的具体内容*  |

* **needEventCallback** - 与 *Voice* 中的定义相同。
* **action** - 定义了对MediaPlayer的操作，目前只支持 **3** 种操作：**PLAY**， **PAUSE** 和 **RESUME**。
* **behaviour** -与 *Voice* 中的定义相同。
* **item** - 定义了具体的播放内容，如下：

###### 3.2.2.1 Item

```
"item": {
    "token": "xxxx",
    "type": "AUDIO/VIDEO",
    "url": "media streaming url",
    "offsetInMilliseconds": 0
}
```

| 字段               | 类型            | 可能值 |
|:-----------------:|:---------------:|:---------------|
| token              | string          | *用于鉴权的token，由CloudApp填充和判断*  |
| type          | string          | *AUDIO / VIDEO* |
| url  | string        | *可用的流媒体播放链接*  |
| offsetInMilliseconds  | long        | *毫秒数值，表明从哪里开始播放*  |

* **token** - 用于鉴权的token，由CloudApp填充和判断。
* **type** - 表明了当前媒体类型：**AUDIO** 或 **VIDEO**，有且只能取其一。
* **url** - 为MediaPlayer指明可用的流媒体播放链接。
* **offsetInMilliseconds** - 毫秒数值，告诉MediaPlayer开始播放的位置。有效范围从0到歌曲整体播放时长。

###### Copyright © 2017 Rokid Corporation Ltd. All rights reserved.




