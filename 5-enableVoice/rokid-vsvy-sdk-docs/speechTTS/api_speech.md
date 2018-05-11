### 语音识别服务
### API 参考

#### SDK 初始化
**接口说明**

Rokid Speech 语音合成 SDK 初始化

**方法预览**

返回类型|方法|备注|
---|---|---|
void|prepare(PrepareOptions options)|使用PrepareOption 初始化

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
options | PrepareOptions | 可选 |选项，详见PrepareOptions数据结构

**示例代码**

```java
//使用 PrepareOption 初始化
                Speech speech = new Speech();
                PrepareOptions prepareOptions = new PrepareOptions();
                prepareOptions.host = "apigwws.open.rokid.com";
                prepareOptions.port = 443;
                prepareOptions.branch = "/api";
                prepareOptions.key = Prepare.ROKID_KEY;
                prepareOptions.device_type_id = Prepare.ROKID_DEVICE_TYPE_ID;
                prepareOptions.secret = Prepare.ROKID_SECRET;
                prepareOptions.device_id = Prepare.ROKID_DEVICE_ID;
                speech.prepare(prepareOptions);
``` 
#### SDK 关闭

**接口说明**

关闭 Rokid Speech 语音识别服务

**方法预览**

返回类型|方法|备注|
---|---|---|
void|release()|Speech SDK关闭

**示例代码**

```java
	...
	speech.release();
```
#### 文本识别

**接口说明**

Rokid 语音识别服务允许用户直接发送文字，并根据用户发送的文本，返回对应的数据

**方法预览**

返回类型|方法|备注|
---|---|---|
int|putText|发起文本识别，返回值为当前发起的语音识别请求speech id

**参数说明**

返回类型|方法|备注|
---|---|---|
text | String | speech文本
cb | SpeechCallback | speech回调接口对象

**示例代码**

```java

        speech.putText(s, new SpeechCallback() {
            @Override
            public void onStart(int i) {
                LogUtil.d("onStart " + i);
            }

            @Override
            public void onIntermediateResult(int i, String s, String s1) {
                LogUtil.d("onIntermediateResult " + i + " " + s + " " + s1);
            }

            @Override
            public void onAsrComplete(int i, String s) {
                LogUtil.d("onAsrComplete " + i + " " + s);
            }

            @Override
            public void onComplete(int i, final String s, final String s1) {
                LogUtil.d("onComplete " + s + " " + s1);
                //需要在主线程更新ui
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        //自然语义解析结果
                        tvAsrResult.setText(s);
                        //Rokid Speech skill返回的结果
                        tvAsrBackResult.setText(s1);
                    }
                });
            }

            @Override
            public void onw/Cancel(int i) {
                LogUtil.d("onCancel " + i);
            }

            @Override
            public void onError(int i, int i1) {
                LogUtil.d("onError " + i + " " + i1);
            }
        });

```

#### 语音识别

返回类型|返回值|方法|备注|
---|---|---|---|
int|speech id|startVoice(SpeechCallback callback,VoiceOptions options)| 发起语音speech，返回
void||putVoice(int id ,byte[] data)| 发送语音数据, 一次speech的语音数据可分多次发送
void||endVoice(int id)|通知sdk语音数据发送完毕，结束speech

**startVoice**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
cb | SpeechCallback | 是|speech回调接口对象
options | VoiceOptions |否| 当前语音speech的选项，详见VoiceOptions。

**putVoice**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
id | int |是 |speech id
data | byte[]|是 | 语音数据,**输入的音频流必须为16bit 16kHz采样，单声道**

**endVoice**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
id | int |是 |speech id

**示例代码**

```java
int speechId = speech.startVoice(new SpeechCallback() {
            @Override
            public void onStart(int i) {
                
            }

            @Override
            public void onIntermediateResult(int i, String s, String s1) {

            }

            @Override
            public void onAsrComplete(int i, String s) {

            }

            @Override
            public void onComplete(int i, String s, String s1) {

            }

            @Override
            public void onCancel(int i) {

            }

            @Override
            public void onError(int i, int i1) {

            }
        });
        speech.putVoice(speechId,voiceByte);
        speech.endVoice(speechId);

```

#### 设置语音识别参数

**接口说明**

用户可以通过这种方式来手动录音，并发送给语音分析服务器，并返回识别结果

**方法预览**

返回类型|方法|备注|
---|---|---|
void|config(SpeechOptions options)| 语音识别Speech的配置选项

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
config | SpeechOptions | 是 | 

#### 取消语音识别请求

**接口说明**

当用户调用了startVoice请求之后，如果想取消语音识别，可调用此方法，而不是endVoice方法

**方法预览**

返回类型|方法|备注|
---|---|---|
void|cancel(int id)| 取消指定的speech请求

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
id | int | 是 | speech id

**示例代码**

```java
speech.cancel(speechId);
```

#### SpeechOptions

使用SpeechOptions设置语音识别相关参数

返回类型|方法|备注|
---|---|---|
void | set\_lang(String lang) | 设定文字语言。设定speech putText接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言
void | set\_codec(String codec)| 设定语音编码。指定putVoice接口发送的语音编码格式
void | set\_vad\_mode(String mode)|设定语音起始结束检查在云端还是本地
void | set\_no\_nlp(boolean v)|设定是否需要服务端给出nlp结果
void | set\_no\_intermediate\_asr(boolean v)| 设定是否需要服务端给出中间asr结果

**set\_lang**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
lang | String | 是 |限定值```zh```

**set\_codec**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
codec | String | 是 |编码格式，限定值```pcm```、```opu``` 

**set\_vad\_mode**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
mode | String | 是 |限定值```local```、 ```cloud```

**set\_no\_nlp**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
v | boolean | 是 |

**set\_no\_intermediate\_asr**

**参数说明**

字段| 类型 |必须？| 描述
---|---|---|---|
v | boolean | 是 |

#### 回调接口

##### SpeechCallback

**方法预览**

返回类型|方法|备注|
---|---|---|
void | onStart(int id) | speech结果开始返回
void | onIntermediateResult(int id,String asrResult，String extraResult)| 给出当前已经转成语音的文字
void | onAsrComplete(int id,String asrResult)|speech asr完整结果
void | onComplete(int id，String nlpResult,String intent)|speech最终结果
void | onCancel(int id)| speech被取消
void | onError(int id,int errCode)| speech出错

**onStart(int id)**

**方式说明**

通知开发者，语音识别的结果开始返回。

**参数说明**

字段| 类型 | 描述
---|---|---|---|---
id| int  | 当前Speech 请求的id

**onIntermediateResult(int id,String asrResult，String extraResult)**

**方法说明**

持续返回当前语音识别出的文字

**参数说明**

字段| 类型 | 描述
---|---|---|
id | int | speech id
asrResult | String | 语音转文字中间结果
extraResult | String | 激活结果

**onAsrComplete(int id,String asrResult)**

**方法说明**

语音识别技术后返回完整的语音识别结果

**参数说明**

字段| 类型 | 描述
---|---|---|
id | int | 当前Speech 请求的id
asrResult | String | 语音转文字完整结果

**onComplete(int id，String nlpResult,String intent)**

**方法说明**

根据识别结果返回Rokid 云平台上的skill信息

**参数说明**

字段| 类型 | 描述
---|---|---|
id | int |当前Speech 请求的id
nlpResult | String | 自然语义解析结果
intent | String | rokid speech skill返回的结果

**onCancel(int id)**

**方法说明**

语音是被取消

**参数说明**

字段| 类型 | 描述
---|---|---|
id | int | 当前Speech 请求的id
**onError(int id,int errCode)**

**方法说明**

语音识别发生错误，详情请看[错误码](../common/err_code.md)

**参数说明**

字段| 类型 | 描述
---|---|---|
id | int |当前Speech 请求的id
errCode | int | 错误码

#### 数据结构

#### PrepareOptions
名称 | 类型 | 描述
---|---|---
host | String | 语音识别服务host,一般为 ```apigwws.open.rokid.com```
port | int | 语音识别服务port ```443```
branch | String | 语音识别服务url path ```/api```
key | String | 语音识别服务认证key
device\_type\_id | String | 设备类型，用于语音识别服务认证
secret | String | 用于语音识别服务认证
device\_id | String | 设备id，用于语音识别服务认证

获取key、id等参数，请参考[创建设备流程](../rookie-guide/create-device.md)章节


