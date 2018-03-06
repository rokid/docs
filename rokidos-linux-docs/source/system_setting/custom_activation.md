# 自定义激活词配置

现在我们提供自定义激活词配置的方式来让您更亲切的唤醒您的设备。

RokidOS 会读取 /data/system/device.json 中的信息来初始化一些系统信息；在 /data/system/ 下创建 device.json ，自定义以下内容：

- `namePrefix` {String} 用于设备开启蓝牙时的名称前缀，如："Rokid-Pebble-" 等。
- `triggerWord` {Object} 自定义激活词配置：
   - `text` {String} 激活词的汉字。
   - `pinyin` {String} 激活词拼音字符，如："ruo4qi2"。

比如：我想用 “小琪小琪” 作为激活词，就在 device.json 里添加如下代码！
```
{
	"namePrefix" : "Rokid-ble",
	"triggerWord" :{
		"text" : "小琪小琪",
		"pinyin" : "xiao3qi2xiao3qi2"
	}	
}
```
**保存后重启生效。**
