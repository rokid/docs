## Cloud App Development Protocol
### Rokid Open Platform
Version: 1.0.0-alpha

### Outline

* [Introduction](#1-introduction)
	* [Concepts](#11-concepts)
* [Request](#2-request)
	* [Protocol](#21-protocol)
	* [Session](#22-session)
	* [Context](#23-context)
	* [Request](#24-request)
* [Response](#3-response)
	* [Protocol](#31-protocol)
	* [Action](#32-action)

### 1. Introduction

This document is the detailed description for the protocols that used when developing a cloud app on *[Rokid Open Platform][developer_website_link]*

[developer_website_link]: https://developer.rokid.com

#### 1.1 Concepts

First of all, there are several significant concepts should be introduced. 

* **CloudApp** - apps developed on Rokid Open Platform. It's kind of servelet on the server side. 
* **CloudDispatcher** - dispatcher for request and response.
* **CloudAppClient** - the client side execution container and engine for *CloudApps*. The execution is completely based on the response protocol which is replied by *CloudApps*.
* **RokidMobileSDK** - the mobile SDK in Rokid Open Platform. *SpeechSDK* and *TTSSDK* are all included.
* **TTS** - abbreviation for **T**ext **T**o **S**peech, which is the way that a Robot expresses its feedback.

### 2. Request

*Request* is used to fetch response from *CloudApps*, which is sent by *CloudDispatcher*. Currently **IntentRequest** and **EventRequest** are available. **IntentRequest** is created according an *NLP* intent. And **EventRequest** is created when an event occurs.

#### 2.1 Protocol

The full protocol of *Request* is as follows:

```
{
    "version": "2.0.0",
    
    // session information
    "session": {
        // unique id for each new session
        "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6", 
        
        // indicates whether it is a new session
        "newSession": true, 
        
        "applicationId": "application id for requested CloudApp",
        
        "domain": "domain for requested CloudApp",
        
        "attributes": {
            // session attributes set by CloudApp in Response
        }
    },
    
    // usefull context information for handling the Request
    "context": {
        // application related information
        "application": {
            "applicationId": "application id for requested CloudApp"
        },
        
        // device status and information
        "device": {
            // current device id sending the request, autofill by system
            "deviceId": "010116000100",
            
            // current device type, autofill by system
            "deviceType":"device type"
            
            // vendor id of current device, autofill by system
            "vendor":"vendor id",
            
            // screen info of current device
            "screen":{
                "x":"640",
                "y":"480"
            },
            
            // locale of current device
            "locale": "zh_cn",
            
            // timestamp when sending the request
            "timestamp": 1478009510909,
            
            // media status on current device
            "media": {
                "state": "PLAYING / PAUSED"
            },
            
            // location config of current device
            "location": {
                "latitude": "30.213322455923485",
                "longitude": "120.01190010997654"
            }
        },
        
        // user info that binded to current device
        "user": {
            "userId": "user id string"
        }
    },
    
    // request info
    "request": {
        // distinguish the request type: IntentRequest or EventRequest
        "reqType": "intent / event",
        
        // unique id for each request
        "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a",
        
        "currentReqId":"",
        
        // request content - structure may be different for different reqType. 
        // Here is an example for IntentRequest
        "content": {
            "domain": "com.rokid.cloud.music",
            "intent": "play_random",
            "slots": {
            }
        }
    }
}
```


* **request** - indicates the real purpose of the request. **RequestType** and **RequestContent** are declared.

#### 2.2 Session

*Session* indicates the session for the *CloudApp* that currently be requested. Whenever a request is created, the session information will be updated by system.

```
"session": {
    "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6", 
    "newSession": true, 
    "applicationId": "application id for requested CloudApp",
    "domain": "domain for requested CloudApp",
    "attributes": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| sessionId              | string          | *unique id for each session (filled by system)*  |
| newSession  | boolean         | *true / false (filled by system)*   |
| applicationId          | string          | *the application id*  |
| domain       | string    | *domain for the application*         |
| attributes             | key-value map          | *string-string map*         |

* **sessionId** - unique id for each session.
* **newSession** - indicates whether the session is new or not.
* **applicationId** - indicates the application id in current session.
* **domain** - indicates the domain for the application in current session.
* **attributes** - indicates the attributes which are set in last session from last response.


#### 2.3 Context

*Context* indicates the main status of current device, the user binded and the application. Information in *Context* may help *CloudApps* to determin further actions and to choose proper version of response.

```
"context": {
    "application": {},
    "device": {},
    "user": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| application              | ApplicationInfo object          | *the application info object*  |
| device  | DeviceInfo object         | *device info object*   |
| user          | UserInfo object          | *user info object*  |

##### 2.3.1 ApplicationInfo

*ApplicationInfo* in the reqeust notifies the application information which is currently being requested. Right now, there is only one property: **applicationId**.

```
"application": {
    "applicationId": "application id for requested CloudApp"
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| applicationId     | string         | *the application id*  |

* **applicationId** - the unique id for *CloudApps* on *Rokid Open Platform*.


##### 2.3.2 DeviceInfo

*DeviceInfo* presents the main status of the device that created current request. 

```
"device": {
    "deviceId": "010116000100",
    "deviceType":"device type",
    "vendor":"vendor id",
    "screen":{},
    "locale": "zh_cn",
    "timestamp": 1478009510909,
    "media": {},
    "location": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| deviceId  | string         | *the id for device*  |
| deviceType  | string         | *the type for device*  |
| vendor    | string         | *the id for a specific vendor*   |
| screen    | ScreenInfo object          | *screen info object*  |
| locale    | string          | *language and region info. zh_cn for example*  |
| timestamp | long         | *timestamp in milliseconds when creating the request*  |
| media     | MeidaStatus object          | *media status object*  |
| location  | LocationInfo object          | *location info object*  |

* **deviceId** - indicates a standalone device who created the request.
* **deviceType** - distinguishes different deivces types. *CloudApps* may response differently according to different device types.
* **vendor** - distinguishes different vendors. *CloudApps* may response differently according to different vendors.
* **screen** - indicates the screen parameters such as **resolution**. *CloudApps* may choose different display *templates* for different screens.
* **locale** - notifies *CloudApps* what language and region configuration that the device are using.
* **timestamp** - timestamp in millisecond making the request.
* **meida** - indicates the current media player status.
* **location** - indicates the location configuration for the devices.

###### 2.3.2.1 ScreenInfo

Screen information for current devices:

```
"screen":{
    "x":"640",
    "y":"480"
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| x  | string         | *the x resolution in pixel*  |
| y    | string         | *the y resolution in pixel*   |


* **x** - the resolution in pixel for **x-axis** orientation.
* **y** - the resolution in pixel for **y-axis** orientation.
* As per the screen orientation, by default, if **x** is larger than **y**, the *orientation* will be resolved as **landscape** and vice versa.

###### 2.3.2.2 MediaStatus

Current media player status is offered by MediaStatus.

```
"media": {
    "state": "PLAYING / PAUSED"
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| state  | string         | *PLAYING / PAUSED*  |


* **state** - indicates current media player state. **ONLY** state **PLAYING** and **PAUSED** are available currently. Other status and information will be updated in the future.

###### 2.3.2.3 LocationInfo

```
"location": {
    "latitude": "30.213322455923485",
    "longitude": "120.01190010997654"
}
```

The location of a device can be generated in several ways. The `location` shows the location or the device and also indicates how the information be generated. *LBS* based *CloudApps* can fetch location information. *latitude* and *longitude* are provided.

##### 2.3.3 UserInfo

UserInfo contains the information of the user binded to the device.

```
"user": {
    "userId": "user id string"
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| userId  | string         | *id of user binded to the device*  |


#### 2.4 Request

In *Request* section, the real request action will be illustrated including the *request type* and *content*.

```
"request": {
    "reqType": "INTENT / EVENT",
    "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a",
    "currentReqId":"010116000100-cd1a462f4f0946ccb24e9248362c630b",
    "content": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| reqType  | string         | *INTENT / EVENT*  |
| reqId    | string         | *unique id for each request*  |
| content  | request content object         | *intent or event request content object*  |

* **reqType** - indicates the request type: **INTENT** or **EVENT**.
* **reqId** - unique id generated by system when creating the request to verify a specific request.
* **currentReqId** - indicates the last corresponding response id for the request. It is **ONLY* in effect when the *reqType* is *EVENT*.
* **content** - object may be one of the two kinds of requests: **IntentRequest** and **EventRequest**.

##### 2.4.1 IntentRequest

IntentRequest is based on the result of *NLP* result. **Domain**, **Intent** and **Slots** are indicated. *CloudApps* with the same *domain* should handle the *intent* with *slots* to make a response.

```
"content": {
    "domain": "com.rokid.cloud.music",
    "intent": "play_random",
    "slots": {}
}
```

| key     | type           | value available                |
|:-------:|:--------------:|:-------------------------------|
| domain  | string         | *nlp domain for the CloudApp*  |
| intent  | string         | *nlp intent for the CloudApp*  |
| slots   | string         | *nlp slots for the CloudApp*   |

* **domain**, **intent** and **slots** are basic concept of **NLP**. You can find detailed description from here.


##### 2.4.2 EventRequest

EventRequest is event based. Event handling is an optional request for *CloudApps*. *CloudApps* can make related response on demand.

```
"content": {
    "event": "Media.NEAR_FINISH",
    "extra": "extra info"
}
```

| key     | type           | value available                |
|:-------:|:--------------:|:-------------------------------|
| event  | string         | *events*   |
| extra  | string map         | *extra info may use in <MAP> form*   |

* **event** - indicates what event occured.
	* **Voice.STARTED** - sent when a voice interaction execution has been started.
	* **Voice.FINISHED** - sent when a voice interaction execution finished.
	* **Media.START_PLAYING** - sent when media player starts playing.
	* **Media.PAUSED** - sent when media player stops playing.
	* **Media.NEAR_FINISH** - sent when media player near the end. Typically, this event will be sent in 15 seconds before the end.
	* **Media.FINISHED** - sent when media player completes playing the current media item.
	* *More events will be updated in the future*

* **extra** - illustrates extra information and data that may be useful for *CloudApps*.

### 3. Response

As described before, the response should be replied by *CloudApps* for client side execution. 

#### 3.1 Protocol

The full protocol for cloud app response is as follows:

```
{
    "version": "2.0.0",
    "session": {
        "attributes": {
            // attributes that will be used for session 
            // which are filled by the app itself
        }
    },
    "response": {
        "action": { // for Rokid device
            // action protocol version
            "version":"2.0.0",
        
            // action type 
            // if type is EXIT, the cloud app will exit immediately
            "type": "NORMAL / EXIT", 
            
            // notifies that session should be cleard then action is done
            "shoudEndSession": true, 
            
            // voice section
            "voice": {
                "needEventCallback": true,
                "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
                "item": {
                    "tts": "tts content",
                    "confirm": {
                        "tts": "tts content for confirmation",
                        "confirmIntent": "nlp intent to confirm",
                        "confirmSlot": "nlp slot to confirm",
                        "confirmAttributes": {
                            // attributes that will used in the confirmation result 
                            // which are filled by the app
                            "isConfirm": "true"
                        }
                    }
                }
            },
            
            // media section
            "media": {
                "needEventCallback": true,
                "action": "PLAY/PAUSE",
                "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
                "item": {
                    "token": "xxxx",
                    "type": "AUDIO/VIDEO",
                    "url": "media streaming url",
                    "offsetInMilliseconds": 0
                }
            }
        }
    }
}
```
The **whole** protocol above **should** be returned by cloud apps including `version` and `session` sections.

* **version** - represents the protocol version. Current version is `2.0.0`.
* **session** - represents the session information.
* **response** - represents the response that will be transfered to the *CloudAppClient*. There are two sections in `response`. And `action` is for *CloudAppClient*.

#### 3.2 Action

There are three kinds of action, `voice` and `media`. `voice` is for voice interaction including *TTS* and *confirm*. `media` is for media streaming. Besides, `action` includes following properties.

```
"action": {
    "version": "2.0.0",
    "type": "NORMAL/EXIT", 
    "shoudEndSession": true, 
    "voice": {},
    "media": {}
}
```


| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| version           | string          | *action protocol version, current is 2.0.0*  |
| type              | string          | *NORMAL / EXIT*  |
| shouldEndSession  | boolean         | *true / false*   |
| voice       | voice object    | *object*         |
| media             | media object          | *object*         |

* **version** - indicates the current action protocol version: 2.0.0.
* **type** - indicates the type of current action. The values is one of `NORMAL` and `EXIT`. When `type` is `NORMAL`, `voice` and `media` will be executed concurrently. On the other side, when `type` is `EXIT`, the action will be shut down immediately. In this case, `voice` and `media` will be ignored.
* **shouldEndSession** - notifies *CloudDispatcher* and *CloudAppClient* to clear session for current *CloudApp*. In addition, when `shouldEndSession` is true, *EventRequests* will be ignored.

##### 3.2.1 Voice

*Voice* defines the voice interaction of *CloudApps*, including **TTS** and **Confirmation**. The properties are as follows.

```
"voice": {
    "needEventCallback": true,
    "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
    "item": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| needEventCallback              | boolean          | *true / false*  |
| behaviour          | string          | *APPEND / REPLACE\_ALL / REPLACE\_APPEND / CLEAR*  |
| item       | item object    | *object*         |

* **needEventCallback** - indicates whether the *CloudAppClient* should wait for event callbacks when all actions are finished. If *needEventCallback* is *true*, the *CloudAppClient* will wait for the callback until the callback is back. However, if *needEventCallback* is *false*, the *CloudAppClient* will finish immediately when all actions finishes execution. 
* **behaviour** - indicates the enqueue behaviour of current `voice`. Action for available `behaviours` are as follows. **REPLACE_ALL** will be set by **default** if behaviour is not offered by the response.
	* **APPEND** - current voice interaction will be appended to the end of the execution queue. And the voice interaction will not be executed until all of the previous voice interactions finish execution.
	* **REPLACE_ALL** - current voice interaction will be executed immediately. Currently executing voice interaction will be shut down and all of the previous voice interactions in queue will be cleared.
	* **REPLACE_APPEND** - current voice interaction will be appended to the end of the execution queue. And currently executing voice interaction will be shut down immediately.
	* **CLEAR** - Currently executing voice interaction will be shut down immediately. And meanwhile, the execution queue will be cleared. In addition, current voice interaction in response will **NOT** be executed and `duraton` and `item` will **NOT** be in effect as well.

* **item** - defines the detailed voice interaction content which will be illustrated in section *3.2.1.1*.

###### 3.2.1.1 Item

Item indicates the voice interaction content detail including **TTS** and **Confirm**.

```
"item": {
    "tts": "tts content",
    "confirm": {},
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| tts              | string          | *tts content*  |
| confirm          | confirm object          | *object* |

* **tts** - defines the **TTS** content for the current voice interaction.
* **confirm** - defines the **Confirm** content for confirm request. 

```
"confirm": {
    "tts": "tts content for confirmation",
    "confirmIntent": "nlp intent to confirm",
    "confirmSlot": "nlp slot to confirm",
    "confirmAttributes": {}
}
```

| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| tts              | string          | *tts content for confirm (mutually exclusive to `tts` in `item`)*  |
| confirmIntent         | string          | *nlp intent to confirm* |
| confirmSlot  | string        | *nlp slot to confirm related to confirmIntent*  |
| confirmAttributes  | key-value map        | *any necessary key-value attributes for further use (only string-string is supported)*  |

**Attention**, `tts in item` and `tts in confirm` are mutually exclusive. `tts in confirm` has higher priority than `tts in item`.

##### 3.2.2 Media

Meida is used to play streaming media. Both *audio* and *video* are supported. *Action*, *behaviour* and *media item* are defined in **media** section.

```
"media": {
    "needEventCallback": true,
    "action": "PLAY/PAUSE",
    "behaviour": "APPEND/REPLACE_ALL/REPLACE_APPEND/CLEAR",
    "item": {}
}
```
| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| needEventCallback              | boolean          | *true / false*  |
| action              | string          | *PLAY / PAUSE*  |
| behaviour          | string          | *APPEND / REPLACE\_ALL / REPLACE\_APPEND / CLEAR* |
| item  | media item object        | *media object that defines the media information*  |

* **needEventCallback** - as the same as the definition in *Voice* section.
* **action** - defines the action of the media player. **ONLY TWO** actions are supported, which are **PLAY** and **PAUSE**.
* **behaviour** - as same as the `behaviour` for *Voice* section.
* **item** - defines the media item information which is required by the media player. Here comes the definition.

###### 3.2.2.1 Item

```
"item": {
    "token": "xxxx",
    "type": "AUDIO/VIDEO",
    "url": "media streaming url",
    "offsetInMilliseconds": 0
}
```
| key               | type            | value available |
|:-----------------:|:---------------:|:---------------|
| token              | string          | *token string*  |
| type          | string          | *AUDIO / VIDEO* |
| url  | string        | *valid media streaming url*  |
| offsetInMilliseconds  | long        | *start playing offset in milliseconds*  |

* **token** - indicates the verification token for related apps.
* **type** - indicates the media type, which are **AUDIO** and **VIDEO**. **ONLY ONE** type is available for each media action.
* **url** - indicates the valid media streaming url for the media player.
* **offsetInMilliseconds** - indicates the start point to play in milliseconds.

###### Copyright © 2017 Rokid Corporation Ltd. All rights reserved.




