### SDK生成产物目录结构

#### config

* speech_config.json ---- sdk需要与厂商相关的key/secret等信息,在语音识别以及tts合成时,需要用这些配置信息进行认证,会作为参数传递进SDK,可以点击[语音接入](https://developer.rokid.com/voice/#/product/create/list)创建产品，在下载 SDk 处查看key/secret。

#### java-libraries  文件列表

* jdk1.7  若编译器javac版本为java 1.7.x版本
 * rokid_speech.jar
* jdk1.8  若编译器javac版本为java 1.8.x版本
  * rokid_speech.jar

**说明**
* rokid_speech.jar    ---- 语音识别以及合成服务(speech/tts) 输入输出的java api接口封装

#### shared-libraries 文件列表

* arm64-v8a
  * libc++_shared.so
  * librkcodec.so
  * librokid_opus_jni.so
  * librokid_speech_jni.so
  * libspeech.so
  * libuWS.so
*  armeabi-v7a
   * libc++_shared.so
   * librkcodec.so
   * librokid_opus_jni.so
   * librokid_speech_jni.so
   * libspeech.so
   * libuWS.so



