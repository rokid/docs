### API参考

VoiceRecognize.jar中包含```VoiceRecognize```和```VoiceRecognizeBuilder```两个比较重要的类。
使用```VoiceRecognizeBuilder```设置Rokid账号信息就能得到一个```VoiceRecognize```对象，账号获取方式见[创建设备流程](../rookie-guide/create-device.md)。
下面详细介绍```VoiceRecognize```内部类和接口定义。


#### VoiceRecognize

**方法预览**

返回类型|返回值|方法|备注|
---|---|---|---|
int|成功返回0；失败返回-1|control(Action action)| 控制语音激活
int|成功返回0；失败返回-1|addVtWord(VtWord vtWord)| 添加激活词
int|成功返回0；失败返回-1|remoteVtWord(String content)|删除激活词
ArrayList|成功返回激活词集合；失败返回一个空的集合|getVtWords()|获取激活词
int|成功返回0；失败返回-1|setSkillOption(String skillOption)|同步客户端信息到云端
int|成功返回0；失败返回-1|updateStack(String currAppId,String prevAppId)|更新云端NLP栈信息

**control(Action action)**

**方法说明**

控制语音激活

**参数说明**

字段| 类型 | 描述
---|---|---|
action|Action|控制意图

**返回说明**

类型|  描述
---|---|
int|成功返回0；失败返回-1

**addVtWord(VtWord vtWord)**

**方法说明**

添加激活词

**参数说明**

字段| 类型 | 描述
---|---|---|
vtWord|VtWord|激活词信息

**返回说明**

类型|  描述
---|---|
int|成功返回0；失败返回-1

**remoteVtWord(String content)**

**方法说明**

删除激活词

**参数说明**

字段| 类型 | 描述
---|---|---|
content|String|需要删除的激活词utf-8字符串

**返回说明**

类型|  描述
---|---|
int|成功返回0；失败返回-1

**getVtWords()**

**方法说明**

获取激活词

**返回说明**

类型|  描述
---|---|
ArrayList|成功返回激活词集合；失败返回一个空的集合

**setSkillOption(String skillOption)**

**方法说明**

同步客户端信息到云端

**参数说明**

字段| 类型 | 描述
---|---|---|
skillOption|String|当前skill运行状态信息

**返回说明**

类型|  描述
---|---|
int|成功返回0；失败返回-1

**updateStack(String currAppId,String prevAppId)**

**方法说明**

更新云端NLP栈信息

**参数说明**

字段| 类型 | 描述
---|---|---|
currAppId|String|执行当前语音命令的应用AppId
prevAppId|String|执行上一条语音命令的应用AppId

**返回说明**

类型|  描述
---|---|
int|成功返回0；失败返回-1

#### 内部类
|类型|名称|描述|
|:--:|:--|:--|
|enum|Action|语音控制意图枚举定义：<br> `ACTION_SET_STATE_AWAKE` 设置当前从休眠状态进入激活状态，此时不用说激活词直接语音命令即可，也可以通过说休眠词进入休眠状态<br>`ACTION_SET_STATE_SLEEP` 设置当前从激活状态进入休眠状态，此时可以通过唤醒词再次进入激活状态<br>`ACTION_OPEN_MIC` 打开麦克风，此时可以通过唤醒词进入激活状态<br>`ACTION_CLOSE_MIC` 关闭麦克风，需要打开麦克风才能通过唤醒词唤醒|
|enum|Event|语音唤醒事件枚举定义：<br>`EVENT_VOICE_COMING` 激活即将开始<br>`EVENT_VOICE_LOCAL_WAKE` 本地已经激活<br>`EVENT_VOICE_START` 开始上传VAD<br>`EVENT_VOICE_NONE` 二次确认结果为空，只出于已经在激活状态下，直接说语音命令<br>`EVENT_VOICE_ACCEPT` 云端二次确认通过<br>`EVENT_VOICE_REJECT` 云端二次确认不通过<br>`EVENT_VOICE_CANCEL` 取消当前上传VAD<br>`EVENT_VOICE_LOCAL_SLEEP` 通过休眠词从激活状态进入休眠状态|
|enum|ExceptionCode|异常状态定义：<br>`EXCEPTION_SERVICE_INTERNAL` 语音内部错误 <br> `EXCEPTION_ASR_TIMEOUT` ASR识别超时
|class|VtWord|激活词信息：`type` 激活词类型，`word`激活词中文字符表示形式，`pinyin`激活词拼音字符+音调表示形式(例：若琪 ruo4qi2，ruo为四声，qi为二声)|
|enum|Type|激活词类型枚举定义：`AWAKE`唤醒词，`SLEEP`休眠词，`HOTWORD`热词，`OTHER`保留|
|interface|Callback|接收识别结果的回调接口定义，详细介绍见第3节Callback接口说明|


#### 回调接口
#####  VoiceRecognize.Callback

返回类型|方法|备注|
---|---|---|
void | onVoiceEvent(Event event,float sl,float energy) | 语音事件回调接口
void | onIntermediateResult(String asr，boolean isFinal)| 语音识别中间结果，可能回调多次
void | onRecognizeResult(String nlp,String action)|最终语音识别回调接口
void | onException(ExceptionCode code)|语音识别出错

**onVoiceEvent(Event event,float sl,float energy))**

**方法说明**

语音事件回调接口

**参数说明**

字段| 类型 | 描述
---|---|---|
event| Event  | 语音事件
sl|float|当前唤醒角度(0到360度之间)
energy|float|当前说话能量值(0到1之间的浮点数)

**onIntermediateResult(String asr，boolean isFinal)**

**方法说明**

语音识别中间结果，可能回调多次

**参数说明**

字段| 类型 | 描述
---|---|---|
asr|String|语音转文字结果
isFinal|boolean|是否是最终完整的语音转文字结果

**onRecognizeResult(String nlp,String action)**

**方法说明**

最终语音识别回调接口

**参数说明**

字段| 类型 | 描述
---|---|---|
nlp|String|自然语义解析结果
action|String|云端skill结果

**onException(ExceptionCode code)**

**方法说明**

语音识别出错

**参数说明**

字段| 类型 | 描述
---|---|---|
code|ExceptionCode|错误码
   
#### 示例代码

```java
import android.util.Log;
    
    import com.rokid.voicerec.VoiceRecognize;
    import com.rokid.voicerec.VoiceRecognizeBuilder;
    
    public class MainService extends android.app.Service implements VoiceRecognize.Callback{
    
        private String TAG = getClass().getSimpleName();
        private VoiceRecognize mVoiceRecognize = null;
    
        @Override
        public void onCreate(){
            VoiceRecognizeBuilder builder = new VoiceRecognizeBuilder();
            mVoiceRecognize = builder.setHost("apigwws.open.rokid.com")
                .setPort(443)
                .setBranch("/api")
                .setKey("your key")
                .setSecret("your secret")
                .setDeviceTypeId("your device_type_id")
                .setDeviceId("your device_id")
                .setCallback(this)
                .build();
    
            //mVoiceRecognize.control(VoiceRecognize.Action.ACTION_OPEN_MIC);
        }   
    
        @Override
        public void onVoiceEvent(VoiceRecognize.Event event, float sl, float energy) {
            Log.d(TAG, "onVoiceEvent    event " + event + ", sl " + sl + ", energy " + energy);
        }   
        
        @Override
        public void onIntermediateResult(String asr, boolean isFinal) {
            Log.d(TAG, "onIntermediateResult    asr " + asr);
        }   
        
        @Override
        public void onRecognizeResult(String nlp, String action) {
            Log.d(TAG, "onRecognizeResult   nlp " + nlp + ", action " + action);
        }   
        
        @Override
        public void onException(int errCode) {
            Log.d(TAG, "onException     errCode " + errCode);
        }   
    
        @Override
        public android.os.IBinder onBind(android.content.Intent intent) {
            return null;
        }   
    }
    
```



