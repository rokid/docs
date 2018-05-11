## 语音合成服务集成

用户需要在使用语音合成服务之前，调用以下代码来进行初始化

首先创建实例

```java
        Tts tts = new Tts();
```
传入之前获取的相关秘钥，以及相关配置信息

```java
        PrepareOptions popts = new PrepareOptions();
        popts.host = "apigwws.open.rokid.com";
        popts.port = 443;
        popts.branch = "/api";
        // 认证信息，需要申请
        popts.key = "";
        popts.device_type_id = "";
        popts.secret = "";
        // 设备名称，类似昵称，可自由选择，不影响认证结果
        popts.device_id = "";
        tts.prepare(popts);

```
在prepare后任意时刻，都可以调用config修改配置
```java
        // 默认配置codec = "pcm", declaimer = "zh", samplerate = 24000
        // 下面的代码将codec修改为"opu2"，declaimer、samplerate保持原状不变
        TtsOptions topts = new TtsOptions();
        topts.set_codec("opu2");
        tts.config(topts);
```

以上为初始化步骤，初始化完成后，开发者可以调用语音合成接口来验证是否集成成功

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
        tts.speak(s,
                new TtsCallback() {
                    // 在这里实现回调接口 onStart, onVoice等
                    // 在onVoice中得到语音数据，调用播放器播放
                    @Override
                    public void onStart(int i) {

                    }

                    @Override
                    public void onText(int i, String s) {

                    }

                    public void onVoice(int id, byte[] data) {
                        OpusPlayer opusPlayer = new OpusPlayer();
                        opusPlayer.play(data);
                    }

                    @Override
                    public void onCancel(int i) {

                    }

                    @Override
                    public void onComplete(int i) {

                    }

                    @Override
                    public void onError(int i, int i1) {

                    }
                });
```


