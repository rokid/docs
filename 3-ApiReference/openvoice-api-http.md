# API文档

## 认证方式

客户端发起 HTTP 请求时，需要在 HTTP 头部中增加字段 Authorization，支持设备验证方式。

### 设备认证

#### Authorization

设备认证方式中的Authorization内容格式如下：

```text
version={version};time={time};sign={sign};key={key};device_type_id={device_type_id};device_id={device_id};service={service}
```

#### Signature

Authorization中的sign字段是签名串，是对下列组合的字符串（UTF-8编码）做MD5计算

```text
key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}
```

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
| secret         | 密钥，从开发者平台获取                                            |

#### 设备验证示例代码

```go

func generateAuthorization(version, secret, key, deviceTypeID, deviceID, service string) string {
    now := strconv.FormatInt(time.Now().Unix(), 10)
    return fmt.Sprintf("version=%s;time=%s;sign=%s;key=%s;device_type_id=%s;device_id=%s;service=%s",
        version, now, generateSign(now, version, secret, key, deviceTypeID, deviceID, service),
        key, deviceTypeID, deviceID, service)
}

func generateSign(now, version, secret, key, deviceTypeID, deviceID, service string) string {
    src := "key=" + key + "&device_type_id=" + deviceTypeID + "&device_id=" + deviceID + "&service=" + service + "&version=" + version + "&time=" + now + "&secret=" + secret
    fmt.Println("sign source:", src)
    sign := strings.ToUpper(makeMD5(src))
    fmt.Println("sign:", sign)
    return sign
}

func makeMD5(data string) string {
    h := md5.New()
    h.Write([]byte(data))
    return hex.EncodeToString(h.Sum(nil))
}

```
## 编码格式

通过HTTP头部的Content-Type字段支持不同的编码格式，目前支持JSON和Protobuf2，默认为Protobuf2。如果客户端需要JSON格式，可以在HTTP头部设置`Content-Type为application/json;charset=utf-8`
JSON 中 bytes 数据以 base64 编码的字符串表示

## 语音识别API

### 请求URL


线上：<https://apigwrest.open.rokid.com/api/v1/asr/AsrProxy/Asr>

### proto 文件

[proto](https://github.com/Rokid/rokid-openvoice-http/blob/master/protobuf/asr.proto)

### 请求和回复数据

``` protobuf
syntax = "proto2";

package rokid.open.v1.asr.AsrProxy;

message AsrRequest {
    required bytes voice         = 1;
    optional string lang         = 2;
    optional string codec        = 3;
}

message AsrResponse {
    required string asr          = 1;
}

```

### AsrRequest 字段说明

| 参数    | 类型    | 描述                                   | 默认值  |
| --------| ------ | -------------------------------       | ---- |
| voice   | bytes  | 语音二进制数据 | 无，必填 |
| lang    | string | 语言，可选范围：zh                      | zh，可选 |
| codec   | string | 编码格式，可选范围：pcm, opu, opu2       | pcm，可选 |

### AsrResponse 字段说明

| 参数             | 类型     | 描述                         | 默认值  |
| -------------- | ------ | ------------------------------- | ---- |
| asr            | string  | 语音文本结果                    | 无 |

## 语音合成API

### 请求URL

线上：<https://apigwrest.open.rokid.com/api/v1/tts/TtsProxy/Tts>

### proto 文件

[proto](https://github.com/Rokid/rokid-openvoice-http/blob/master/protobuf/tts.proto)

### 请求和回复数据

``` protobuf
syntax = "proto2";

package rokid.open.v1.tts.TtsProxy;

message TtsRequest {
    required string text             = 1;
    optional string declaimer        = 2;
    optional string codec            = 3;
}

message TtsResponse {
    required bytes voice             = 1;
}

```

### TtsRequest 字段说明

| 参数    | 类型    | 描述                                   | 默认值  |
| --------| ------ | -------------------------------       | ---- |
| text   | string  | 文字 | 无，必填 |
| declaimer    | string | 朗读者，可选范围：zh(成人),c1(儿童)                      | zh，可选 |
| codec   | string | 语音格式，可选范围：mp3, pcm, opu, opu2       | mp3，可选 |

### TtsResponse 字段说明

| 参数             | 类型     | 描述                         | 默认值  |
| -------------- | ------ | ------------------------------- | ---- |
| voice            | bytes  | 语音二进制数据                    | 无 |
