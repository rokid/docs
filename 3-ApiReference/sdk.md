## Tts接口定义

### 调用接口
```
bool prepare(const char* config_file);

void release();

bool prepared();

int speak(const char* content, TtsCallback* cb);

void stop(int id);

// 'key': declaimer        'value':
//        codec            'value': opu2  (default)
//                                  opu
//                                  pcm
void config(const char* key, const char* value);
```
### 回调接口
```
virtual void onStart(int id) = 0;

virtual void onText(int id, const char* text) = 0;

virtual void onVoice(int id, const unsigned char* data, int length) = 0;

virtual void onStop(int id) = 0;

virtual void onComplete(int id) = 0;

virtual void onError(int id, int err) = 0;
```

### 示例
```
class DemoCallback : public TtsCallback {
public:
	void onStart(int32_t id) {
		...
	}

	void onData(int32_t id, const uint8_t* data, uint32_t length) {
		...
	}

	...
};

Tts tts;
DemoCallback cb;
// 配置服务器地址
tts.config("server_address", "apigw.open.rokid.com:443");
// 配置ssl cert文件路径(sdk源码中提供了roots.pem)
tts.config("ssl_roots_pem", "/system/etc/roots.pem");
// 配置语音服务认证信息
// key, secret, device_type_id需要申请
// device_id即设备序列号，由用户自定，用户可用它区分自己的设备
tts.config("key", "your_rokid_key");
tts.config("device_type_id", "your_device_type_id");
tts.config("secret", "your_secret");
tts.config("device_id", "your_device_id");
// api版本号
tts.config("api_version", "1");
if (!tts.prepare()) {
	log("tts prepare failed");
	return;
}
// 'cb' 回调会在另一个单独线程进行
int32_t id = tts.speak("你好", cb);
...
...
// quit tts
// 'release' 阻塞，直至所有tts创建的线程退出
tts.release();
```

## speech接口定义
```
struct SpeechResult {
	int32_t id;
	uint32_t err;
	std::string asr;
	std::string nlp;
	std::string action;
};

class Speech {
public:
	virtual bool prepare(const char* config_file = NULL) = 0;

	virtual void release() = 0;

	virtual int32_t put_text(const char* text) = 0;

	virtual int32_t start_voice() = 0;

	virtual void put_voice(int32_t id, const uint8_t* data, uint32_t length) = 0;

	virtual void end_voice(int32_t id) = 0;

	virtual void cancel(int32_t id) = 0;

	// poll speech results
	// block current thread if no result available
	// if Speech.release() invoked, poll() will return -1
	//
	// return value: 0  speech result
	//               1  stream result start
	//               2  stream result end
	//               3  speech cancelled
	//               4  speech occurs error, see SpeechResult.err
	//               -1  speech sdk released
	virtual int32_t poll(SpeechResult& res) = 0;

	virtual void config(const char* key, const char* value) = 0;
};

Speech* new_speech();

void delete_speech(Speech* speech);
```

示例
```
Speech* speech = rokid::speech::new_speech();
// 配置信息同tts示例，这里不再列出
// speech->config(......);
if (!speech->prepare()) {
	log("speech prepare failed");
	rokid::speech::delete_speech(speech);
	return;
}

... create callback thread and run ...


int32_t id1 = speech->put_text("你好");
int32_t id2 = speech->start_voice();
speech->put_voice(id2, voice_data, data_length);
speech->put_voice(id2, more_voice_data, data_length);
...
speech->end_voice();
...
...
speech->release();
callback_thread.join();
rokid::open::delete_speech(speech);


// callback thread
SpeechResult result;
int32_t r;
while (true) {
	r = speech->poll(result);
	// speech quit
	if (r < 0)
		break;
	... handler speech result ...
}
```

## asr接口定义

### 调用接口
```
bool prepare();

bool prepared();

void release();

int start(AsrCallback* cb);

void voice(int id, const unsigned char* data, int length);

void end(int id);

void cancel(int id);

void config(const char* key, const char* value);
```

### 回调接口
```
virtual void onStart(int id) = 0;

virtual void onData(int id, const char* text) = 0;

virtual void onStop(int id) = 0;

virtual void onComplete(int id) = 0;

virtual void onError(int id, int err) = 0;
```
### 示例
与tts接口用法相似

## nlp接口定义

### 调用接口
```
bool prepare();

bool prepared();

void release();

int request(const char* asr, NlpCallback* cb);

void cancel(int32_t id);

void config(const char* key, const char* value);
```

### 回调接口
```
virtual void onNlp(int id, const char* nlp) = 0;

virtual void onStop(int id) = 0;

virtual void onError(int id, int err) = 0;
```
### 示例
与tts接口用法相似
