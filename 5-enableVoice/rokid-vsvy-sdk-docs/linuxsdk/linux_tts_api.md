# 语音合成服务（TTS） 接口定义

## 1. SDK 初始化

**接口说明**

Rokid TTS 语音合成 SDK 初始化

| ~      | 名称    | 类型                  | 描述                                    |
| ------ | ------- | --------------------- | --------------------------------------- |
| 接口   | prepare |                       | tts sdk初始化                           |
| 参数   | options | PrepareOptions | 选项，详见PrepareOptions数据结构 |
| 返回值 |         | bool                  | true 成功 false 失败                    |

**示例代码**

```
PrepareOptions opts;
	opts.host = "apigwws.open.rokid.com";
	opts.port = 443;
	opts.branch = "/api";
	opts.key = "rokid_test_key";
	opts.device_type_id = "rokid_test_device_type_id";
	opts.device_id = "ming.qiwo";
	opts.secret = "rokid_test_secret";
```

## 2.SDK 关闭

**接口说明**

关闭 Rokid TTS 语音合成服务

| ~      | 名称    | 类型 | 描述        |
| ------ | ------- | ---- | ----------- |
| 接口   | release |      | tts sdk关闭 |
| 参数   | 无      |      |             |
| 返回值 | 无      |      |             |

**示例代码**

```
...
tts.release();
```

## 3. 文字转语音

**接口说明**

发起文字转语音请求

| ~      | 名称    | 类型        | 描述                                         |
| ------ | ------- | ----------- | -------------------------------------------- |
| 接口   | speak   |             | 发起文字转语音                               |
| 参数   | content | const char* | 文本                                         |
| 返回值 | int32   |             | 成功将文本加入待处理队列，返回id。失败返回-1 |

**示例代码**

```
...
int32_t id = tts->speak("我是会说话的机器人，我最爱吃的食物是机油，最喜欢的运动是聊天");
```

## 4. 取消文字转语音请求

**接口说明**

取消文字转语音请求

| ~      | 名称   | 类型  | 描述                       |
| ------ | ------ | ----- | -------------------------- |
| 接口   | cancel |       | 取消id指定的文字转语音请求 |
| 参数   | id     | int32 | 此前调用speak返回的id      |
| 返回值 | 无     |       |                            |

**示例代码**

```
...
tts.cancel(id) //此前调用speak返回的id
```

## 5. 修改 TTS 配置选项

**接口说明**

修改 TTS 配置选项

| ~      |    名称 | 类型              | 描述                                         |
| ------ | ------: | ----------------- | -------------------------------------------- |
| 接口   |  config |                   | 修改tts配置选项                              |
| 参数   | options | TtsOptions | tts的配置选项，详见TtsOptions数据结构 |
| 返回值 |      无 |                   |                                              |

**示例代码**

```
// 在prepare后任意时刻，都可以调用config修改配置

// 默认配置codec = PCM, declaimer = ZH, samplerate = 24000

// 下面的代码将codec修改为OPU2，declaimer、samplerate保持原状不变

shared_ptr<TtsOptions> topts = TtsOptions::new_instance();

topts->set_codec(Codec::OPU2);

tts->config(topts);
```

## 6. 获取 TTS 结果数据

**接口说明**

获取tts结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false

| ~      | 名称   | 类型             | 描述                                                         |
| ------ | ------ | ---------------- | ------------------------------------------------------------ |
| 接口   | poll   |                  | 获取tts结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false。 |
| 参数   | result | TtsResult | 成功时存放获取到的tts结果数据，详见TtsResult数据结构  |
| 返回值 |        | bool             | true 成功 false sdk已关闭                                    |

**示例代码**

```
TtsResult result;

while (true) {
	if (!tts->poll(result))
		break;
	// 处理result
	handle_tts_result(result);
}
```

# 数据结构

**PrepareOptions**

| 名称           | 类型   | 描述                      |
| -------------- | ------ | ------------------------- |
| host           | string | tts服务host               |
| port           | uint32 | tts服务port               |
| branch         | string | tts服务url path           |
| key            | string | tts服务认证key            |
| device_type_id | string | 设备类型，用于tts服务认证 |
| secret         | string | 用于tts服务认证           |



**TtsOptions**

使用set\_xxx接口设定选项值，未设定的值将不会更改旧有的设定值

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_codec | | 设定编码格式，默认PCM|
|参数 | codec | enum Codec | 限定值PCM, OPU2, MP3|

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_declaimer | | 设定语音朗读者，默认"zh"|
|参数 | declaimer | string | 限定值"zh"|

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_samplerate | | 设定语音采样率，默认24000|
|参数 | samplerate | uint32 | |

|接口 | set\_lang | | 设定文字语言。设定speech put\_text接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言|


**TtsResult**

| 名称  | 类型               | 描述                                                         |
| ----- | ------------------ | ------------------------------------------------------------ |
| type  | enum TtsResultType | 0: tts语音数据<br>1: tts语音开始<br>2: tts语音结束<br>3: tts请求取消<br>4: tts请求出错 |
| id    | int32              | tts请求id                                                    |
| err   | enum TtsError      | 详见[错误码](../common/err_code.md)                                       |
| voice | string             | 语音数据                                                     |

