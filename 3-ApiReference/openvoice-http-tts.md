### 开放平台接口定义文档(http版) - 语音合成
### 简介
 - Rokid语音合成服务，基于HTTP请求将文本转换为可以播放的音频文件。

### 编解码
- 目前支持的格式有 opu2（非标）、opu（非标）、pcm、mp3。采样率目前支持24000和16000，默认为24000、16位深、单声道

- pcm：24000，16bit，mono

- mp3：mp3编码，保存成文件可以直接用播放器播放

- opu：由数据帧组成，每帧由 1字节（后面数据长度）与 用opus压缩320字节后的数据

- opu2：与 opu 区别是没有表示数据长度的1字节
- 
- opus：标准的opus编码 4字节长度+4字节校验总共8字节头（非OGG封装）

### 认证方式

客户端发起 HTTP 请求时，需要在 HTTP 头部中增加字段 Authorization，支持设备验证方式。

#### 字段说明

| 字段名称       | 意义                                                              |
| -------------- | ----------------------------------------------------------------- |
| version        | 版本，当前为1.0                                                   |
| time           | UNIX时间                                                          |
| sign           | 签名串，具体生成方式见下文                                        |
| key            | 授权KEY，从[开发者平台](https://developer.rokid.com/voice/#/)获取 |
| device_type_id | 设备类型ID，同样从开发者平台获取                                |
| device_id      | 设备ID，客户端自己维护                                           |
| service        | 服务类型，自定义，建议与请求的服务名保持一致                      |
| secret         | 密钥，从开发者平台获取        
| text         | 需要合成的文字            
| declaimer         | 合成模型参数    若琪：zh 儿童：c1   
| codec         | 返回音频编码格式 可选参数为 pcm 、mp3 、opu opu2  
                                  

### Curl示例

- 可直接使用 curl 命令构造请求测试：

```bash
curl -X POST --header "Content-Type:application/json" \
--header "Authorization:key=xxx;device_type_id=xxx;device_id=xxx;service=rest;version=1;time=xxx;sign=xxx;" \
--data '{"text": "xxx", "declaimer":"zh", "codec":"mp3"}' \
https://apigwrest.open.rokid.com/api/v1/tts/TtsProxy/Tts
```
### 设备认证
- 详见[认证设备](https://developer.rokid.com/docs/3-ApiReference/openvoice-auth-api.html)

## 语音合成API

### 请求URL

线上：<https://apigwrest.open.rokid.com/api/v1/tts/TtsProxy/Tts>

### proto 文件

[proto](https://github.com/Rokid/rokid-openvoice-http/blob/master/protobuf/tts.proto)


### 请求和回复数据
#### 回复消息示例
```bash
{"voice":"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","text":"[{\"Score\":0.07,\"Phone\":\"sil\"},{\"Score\":0.095,\"Phone\":\"EH\"},{\"Score\":0.065,\"Phone\":\"K\"},{\"Score\":0.12,\"Phone\":\"S\"},{\"Score\":0.21,\"Phone\":\"EH\"},{\"Score\":0.085,\"Phone\":\"K\"},{\"Score\":0.175,\"Phone\":\"S\"},{\"Score\":0.006,\"Phone\":\"sil\"}]"}
```


#### TTSResponse 字段说明

| 参数             | 类型     | 描述                         | 默认值  |
| -------------- | ------ | ------------------------------- | ---- |
| voice            | bytes  | 语音二进制数据                    | 无 |
| text            |  string | 语音返回信息详细字段请见下表（可忽略）|无 | 

##### TTSResponse text字段说明

| 参数             | 类型     | 描述                         | 默认值  |
| -------------- | ------ | ------------------------------- | ---- |
| Phone            | string  | 音素                   | 无 |
| Score            |  float | 音素时间戳          | 无 | 


