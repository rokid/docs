## TTS(语音合成) HTTP接口文档

### 概述

本文档目的是描述Rokid云TTS(语音合成)HTTP接口协议，面向想要了解TTS细节，并具有一定开发能力的开发者或用户。


### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | https://mapi.open.rokid.com/rest/tts/requestid     | 对外提供的正式稳定环境 |


### 协议详解

- 请求认证：在建立http连接时，通过http header authorization 进行权限认证
- TTS语音合成

#### HTTP API 接入参考Demo
- [HTTP 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer)


### 协议概述

此协议遵循http协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 https 连接，注意是 **https**，在此基础上进行[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
* service 设置为 tts，此连接后续可进行一次语音合成


#### 语音合成

##### 请求

1. 需要带包含认证信息的 **authorization** 的 http header [请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
2. 使用 **HTTP POST** 方式
3. 其中 Content-Type 为 **Content-Type:application/json**
4. 请求url中的requestid需要自增或者唯一，两个并发请求的requestid相同时可能引发并发错误
5. http body里面的请求是json格式的，字段如下：
 字段说明：
 
| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| text   | string    | 需要转换的text文本（或为唱歌歌词）          | 空   |
| declaimer | string | 发音人，目前支持 中文成人 "zh" 与 中文儿童 "c1" 两种 | 空 |
| codec     | string | 语音流的编码，目前支持PCM、OPU、OPU2、opus、mp3。   | 空 |
| content_type | string | 1、raw: 返回是二进制语音数据  2、url: 返回是对应语音数据CDN的url  3、sing: 使用midi或者score合成歌曲保存到cdn 4、mix 与背景音乐混音（需要配合options字段使用，切codec仅支持mp3）| raw  |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| midi      | bytes  | 用于歌曲合成使用，二进制midi文件   | 空    |
| score  | string | 歌词信息，用于歌曲合成使用  | 空    |
| options  | string | 可选json字段，配合各种需求使用详见下表  | 空    |


######  options里面的请求是json格式的，字段描述如下：
| 参数     | 类型        | 描述               | 默认值  |
| ------ | --------- | -------------------- | ---- | 
| mixbgurl | string | 当content_type为mix时使用，混音背景音url，格式为遵循此规则的wav(https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/ssml-document.html#audio) | 空 | 
| mixtype | string | 当content_type为mix时使用，可分为"mixtts"和"mixmusic") | 空 | 
###### 示例使用mix混音tts和背景音乐则需要填写参数
```
		options:     `{"mixbgurl":"https://s.rokidcdn.com/temp/rokid-ring.wav","mixtype":"mixmusic"}`,
		declaimer:   "zh",
		codec:       "mp3",
		contentType: "mix",
		text:        "",
		score:       "header\t93\t4\t4\tC4\t1\n1\tM\t0.5\t相\n1\tM\t0.5\t逢\n3\tM\t0.5\t在\n4\tM\t0.5\t我\n3\tM\t0.5\t的\n7\tL\t1.5\t梦，\n1\tM\t0.5\t快\n2\tM\t0.5\t乐\n3\tM\t0.5\t是\n3\tM\t0.5\t我\n2\tM\t0.5\t的\n1\tM\t1.0\t家，\n0\tM\t0.5\t\n2\tM\t0.5\t幸\n3\tM\t0.5\t福\n4\tM\t0.5\t的\n4\tM\t0.5\t眼\n4\tM\t0.5\t神\n3\tM\t1.0\t里，\n0\tM\t0.5\t\n1\tM\t0.5\t想\n2\tM\t0.5\t跟\n2\tM\t0.5\t你\n4\tM\t0.5\t在\n5\tM\t0.5\t一\n1\tM\t1\t起，\n0\tM\t4.5\t\n4\tM\t0.5\t我\n6\tM\t0.5\t有\n1\tM\t0.5\t我\n4\tM\t0.5\t的\n1\tM\t0.5\t欢\n4\tM\t1.5\t喜，\n5\tM\t0.5\t青\n6\tM\t0.5\t春\n7\tL\t0.5\t的\n5\tM\t0.5\t故\n4\tM\t0.5\t事\n3\tM\t1.0\t里，\n0\tM\t0.5\n4\tM\t0.5\t你\n4\tM\t0.5\t不\n6\tL\t0.5\t会\n3\tM\t0.5\t再\n2\tM\t0.5\t哭\n5\tL\t0.5\t泣，\n0\tM\t1\t\n1\tM\t0.5\t愿\n2\tM\t0.5\t意\n1\tM\t0.5\t为\n3\tM\t0.5\t我\n3\tM\t0.5\t的\n1\tM\t0.5\t心，\n0\tM\t1\t\n4\tM\t0.5\t留\n6\tM\t0.5\t下\n1\tM\t0.5\t我\n4\tM\t0.5\t一\n1\tM\t0.5\t生\n4\tM\t1.5\t的，\n5\tM\t0.5\t全\n6\tM\t0.5\t世\n7\tL\t0.5\t界\n5\tM\t0.5\t的\n4\tM\t0.5\t人\n3\tM\t1.0\t啊，\n0\tM\t0.5\t\n4\tM\t0.5\t身\n4\tM\t0.5\t边\n6\tL\t0.5\t有\n3\tM\t0.5\t一\n2\tM\t0.5\t个\n5\tL\t0.5\t梦，\n0\tM\t1.0\t\n1\tM\t0.5\t向\n2\tM\t0.5\t往\n1\tM\t0.5\t梦\n3\tM\t0.5\t中\n3\tM\t0.5\t的\n1\tM\t1\t你。\n",
```

##### 响应

1.响应是json格式的，字段如下：

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| text  | string | voice语音中包含的文字，如果request的content_type=url，则返回的是保存了文字的url |
| voice | bytes  | 合成的voice语音，如果request的content_type=url，则返回的是语音数据CDN的url    |
| finish   | bool | 是否是此次合成请求的最后一个语音包 |
| result  | string | 结果信息  SUCCESS/ERROR等 |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   |

1. http code 除了200以外，还有部分非200的code，取值如下：

| code 值         | 涵义           |
| ----------------- | -------------- |
| 400           | Bad Request ：url格式不对，requestId不对或者为空 |
| 405           | 非post方法不可行       |
| 413           | 请求体过大，HTTP BODY 最大支持655350；如果超过这个大小，建议用websocket方式进行流式传输|
| 500           | http协议层错误     |


3. http code 为200时，所有请求成功与否由 result 决定：SUCCESS 为成功，其余的为失败,返回值如下：
  - SUCCESS 成功
  - BUSY 云端繁忙/调用受限/欠费
  - UNAUTHENTICATED 验证未通过
  - UNINITIALIZED 没有发START或者ONESHOT包导致SESSION顺序错误
  - INTERNAL 云端内部错误
  - BADREQUEST 网络或者协议导致的错误


