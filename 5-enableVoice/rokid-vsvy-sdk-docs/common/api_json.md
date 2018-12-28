key | 描述
--- | ---
host | 服务器主机名 一般使用apigwws.open.rokid.com
port | 服务器端口 目前为443
branch | 服务器功能选择分支 固定为/api
key | 用于服务登录认证　
device\_type\_id | 用于服务登录认证
secret | 用于服务登录认证
device\_id | 设备名，用于服务登录
codec | 语音编码格式:<br>speech服务可选项"pcm" "opu"<br>tts服务可选项 "pcm" "opu2" "mp3"
speech服务专有配置 | ...
lang | 语音语言: "zh"或"en"
vad\_mode | 判断语音结束算法部署位置:<br>"cloud" 云端运行算法，准备确率高<br>"local" 本地运行算法
vend\_timeout | 用于判断语音结束的参数，一般不需设置，使用默认值
no\_nlp | true或false: 是否接收nlp/action结果
no\_intermediate\_asr | true或false: 是否接收asr中间识别结果
tts服务专有配置 | ...
declaimer | 语音播报员设置<br>目前只有一个播报员，默认名"zh"。未来将扩展多个播报员。

上面列出的key值在配置字串中都是可选项，如不配置则使用缺省值

配置字串示例

```json
{
	"host": "apigwws.open.rokid.com",
	"port": 443,
	"branch": "/api",
	"key": "用于服务认证的key",
	"device_type_id": "用于服务认证的device_type_id",
	"secret": "用于服务认证的secret",
	"device_id": "设备id 一般使用设备sn"
}
```