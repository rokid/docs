### 开放平台接口定义文档

### 概述

本文档目的是描述云端语音接口的开放协议，支持长连接WebSocket方式以及短链接HTTP方式，
主要包含语音识别、语义理解、语音合成等功能，面向想要了解语音交互细节，并具有一定开发能力的开发者或用户。

注意：语音识别、语义理解、语音合成的接口地址是同一个，通过不同的service参数来区分，详见各接入文档
#### [设备认证](https://developer.rokid.com/docs/3-ApiReference/openvoice-auth-api.html)

#### WebSocket 接入
- [ 语音识别（ASR） WebSocket 接入文档](https://developer.rokid.com/docs/3-ApiReference/wsasr-api.html)
- [ 语音合成（TTS） WebSocket 接入文档](https://developer.rokid.com/docs/3-ApiReference/wstts-api.html)
- [WebSocket 接入Demo（JAVA）](https://github.com/Rokid/rokid-speech)
- [WebSocket 接入Demo（Python）](https://github.com/Rokid/speech-python-demo)

#### HTTP 接入
- [ 语音识别（ASR） HTTP 接入文档](https://developer.rokid.com/docs/3-ApiReference/openvoice-http-asr.html)
- [ 语音合成（TTS） HTTP 接入文档](https://developer.rokid.com/docs/3-ApiReference/openvoice-http-tts.html)

#### Android SDK 接入
- [ Android SDK 接入文档](https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/fullLink/fulllink.html)

#### 技能开发
- [Skill开发指南（相关技能开发）](https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/platform-introduction.html)
