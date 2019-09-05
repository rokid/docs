### Rokid云云对接服务网关文档

### 概述

本文档目的是描述Rokid云云对接网关开放API，支持长连接WebSocket方式以及短链接HTTP方式，
包含语音识别(ASR)、语音合成(TTS)等功能，面向想要了解语音交互细节，并具有一定开发能力的开发者或用户。

暂不支持语义理解（NLP）功能。



#### 语音识别(ASR)
 - [WebSocket接口文档](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-ws-asr-api.html)
 - [HTTP接口文档](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-http-asr-api.html)



#### 语音合成(TTS)
 - [WebSocket接口文档](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-ws-tts-api.html)
 - [HTTP接口文档](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-http-tts-api.html)

#### 背景音乐取得(TTS)
 - [HTTP接口文档](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-http-tts-bgm-api.html)

#### 数据统计和收费模式
  TODO


#### WebSocket 接入
- [语音识别（ASR）WebSocket 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer/blob/master/src/main/java/com/rokid/open/mapi/demo/demo/WebSocketAsrDemo.java)
- [ 语音合成（TTS）WebSocket 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer/blob/master/src/main/java/com/rokid/open/mapi/demo/demo/WebSocketTtsDemo.java)

#### HTTP 接入
- [ 语音识别（ASR） HTTP 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer/blob/master/src/main/java/com/rokid/open/mapi/demo/demo/HttpAsrDemo.java)
- [ 语音合成（TTS） HTTP 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer/blob/master/src/main/java/com/rokid/open/mapi/demo/demo/HttpTtsDemo.java)
