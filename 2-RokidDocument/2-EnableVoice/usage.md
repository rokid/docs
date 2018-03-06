## 1 使用方法
### 1.1 直接调用API时的配置方法
直接通过API调用Rokid语音服务时，按照[Rokid开发者社区接口文档](/3-ApiReference/openvoice-api.md)中的要求，填入相应的参数即可。
其中提到的`key` `secret` `account_id` `device_type_id`均通过上一步中的创建认证文件获得。

但需要注意，`device_id`**需要由开发者自行指定**，由6~15位的字母和数字组成，不能含有空格和特殊符号。此ID每个设备唯一。

### 1.2 使用C++ SDK时的配置方法
通过调用SDK中的config方法来配置认证信息：

```c++
void config(String key, String value)
```

同样的，`device_id`需要开发者自行指定，用以区分每个不同的设备。

具体请查看[Rokid客户端SDK文档中的示例](/3-ApiReference/rokid-client-sdk-doc.md)。

### 1.3 在Android设备上使用TTS、Speech SDK时的配置方法

#### TTS SDK
SDK解包后`etc`目录下文件最终需要放到安卓设备的`/system/etc`目录下。
其中`tts_sdk.json`提供TTS SDK需要的配置信息，包括连接服务器的认证信息。

首先需要将创建认证文件中获得的认证信息填入到此文件中，具体需要修改如下几项：
`key` `secret` `device_type_id` `device_id`

再将`tts_sdk.json`文件push到设备中：

```text
cd etc
adb push . /system/etc/
```