### 快速集成

### 集成步骤

#### 下载SDK

 * 请通过 [Rokid SDK下载网站](https://developer-dev.rokid.com/tob) , 根据网站提示进行配置,生成 SDK 后下载
 
#### 集成SDK

  * 将下载的SDK进行解压,解压后的目录结构说明请参照 [SDK目录结构](sdk_dir.md)
  * 需要将对应的```so/jar/exe```以及配置文件预置到系统指定位置,可参考方法如下:将解压后的目录放到系统源码中,比如```/vendor/rokid/sdk_v2/``` 目录下,然后在此文件夹下添加如下 [sdk_v2.mk](../extra/sdk_v2.mk) ,同时按照以下步骤使sdk能够被系统编译到
   * 在系统源码的```device/{platform}/{product}/*.mk``` 最后(此mk文件可以在编译时被编译到) 中添加如下
   ```
      $(call inherit-product,vendor/rokid/sdk_v2/sdk_v2.mk) 
   ```
   * 在 config 文件夹加下 添加 [Android.mk](../extra/android_config.mk) 
   * 在 executable 文件夹 添加 [Android.mk](../extra/android_executable.mk)
   * 在 shared-libraries 文件夹下添加 [Android.mk](../extra/android_libs.mk)
   * 将预置到```system/bin/turenproc``` 可执行进程加入到工程的```init.*.rc```中,使之能够以 root 权限在开机启动,示例如下:
   ```
     service turenproc /system/bin/turenproc <port> <deviceName>
     class main
     user root
     group root root
  ```
  其中 port 为启动 turenproc 进程启动时所依赖的运行端口号,比如: ```30000```, ```deviceName``` 为在网站上下载sdk时选择前端麦克风时的 ```deviceName``` ,与生成的``` workdir_asr_cn ``` 文件加中 ```ctc.{deviceName}.cfg```文件中的```deviceName```必须保持一致.假如在网站上 ```deviceName``` 取名为 pebble ,则需要如下方式启动
  ```
     service turenproc /system/bin/turenproc 30000 pebble
     class main
     user root
     group root root
  ```

   * 将 java-libraries 下的静态jar包集成到一个系统应用中,来接收前端语音事件以及ASR/NLP,以提供的 example 中的 SpeechExecutor [模块说明](introduce_speechexecutor.md)为例,集成编译后会在```system/app/SpeechExecutor```下生成 SpeechExecutor.apk, 在系统开机配置好网络后,通过```adb shell am startservice com.rokid.voicerec/.SpeechExecutor``` 来启动Demo的service,然后通过Log查看是否有前端语音事件以及asr/nlp相关的log信息,如果有则证明集成OK.如果没有,请参考下边的集成注意事项或者联系我们.

#### 集成注意事项

 * 目前Android全链路前端语音识别部分仅支持32位armeabi-v7a so文件输出,64位支持正在开发中,敬请期待.
 * 由于前端拾音模块需要读取Mic数据,因此各个客户/集成开发者需要在hal层实现mic设备的open以及read等接口,并以```"mic_array"```为```HAL_MODULE_INFO_SYM``` 的 id.具体接口为 android 标准的硬件设备hal层实现,具体可参考 [mic_array.c](../extra/mic_array.c) & [mic_array.h](../extra/mic_array.h) 的实现.目前支持的 mic 阵列数据采集格式至少为```16K/16bit/单通道``` 的数据格式.

#### 接口调用说明
* 请参考[Android全链路接口调用说明](api_voicerecognize.md)
