## 语音识别服务集成

用户需要在使用语音识别服务之前，调用以下代码来进行初始化

首先创建实例

```java
        Speech speech = new Speech();
```
传入之前获取的相关秘钥，以及相关配置信息

```java
        PrepareOptions prepareOptions = new PrepareOptions();
        prepareOptions.host = "apigwws.open.rokid.com";
        prepareOptions.port = 443;
        prepareOptions.branch = "/api";
        //key
        prepareOptions.key = "";
        //device_type_id
        prepareOptions.device_type_id = "";
        //secret
        prepareOptions.secret = "";
        // 设备名称，类似昵称，可自由选择，不影响认证结果
        prepareOptions.device_id = "";
        
        speech.prepare(prepareOptions);

```
在prepare后任意时刻，都可以调用config修改配置
```java
        // 修改音频编码格式及语言，其它选项不变
        SpeechOptions opts = new SpeechOptions();
        opts.set_codec("opu");
        opts.set_lang("zh");
        speech.config(opts);
```

以上为初始化步骤，初始化完成后，开发者可模拟发送语音识别请求来验证是否集成成功

```java
// 语音Speech请求
// 不设置VoiceOptions，全部使用默认值。
int id = speech.startVoice(new SpeechCallback() {
                ......
            });
speech.putVoice(id, your_voice_data);
speech.putVoice(id, more_voice_data);
speech.putVoice(id, ...);
...
speech.endVoice(id);
```

```java
// 文字Speech请求
speech.putText("你好若琪", new SpeechCallback() {
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
             
            }

            @Override
            public void onCancel(int i) {
                LogUtil.d("onCancel " + i);
            }

            @Override
            public void onError(int i, int i1) {
                LogUtil.d("onError " + i + " " + i1);
            }
        });
```


