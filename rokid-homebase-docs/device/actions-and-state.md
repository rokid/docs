# 设备能力与状态

- 设备能力 `actions`: 指的是智能设备具备的能力，比如智能灯泡具有开关、调颜色、调亮度的能力。
- 设备状态 `state`: 指的是设备当前的状态，与定义的设备能力对应。
- 设备能力接受值与状态值详见 [设备能力](#actions)

Example:

actions:
```JSON
{
  "switch":["on","off"],
  "color":["num"],
  "brightness":["num"]
}
```

**actions** 数据定义参考: [jsonschemalint 在线校验工具](https://jsonschemalint.com/#/version/draft-04/markup/json?gist=a03c0a8cc249d2e69f63d74c4564cad3)

state:
```JSON
{
  "switch": "on",
  "color": 256,
  "brightness": 10
}
```

**state** 数据定义参考: [jsonschemalint 在线校验工具](https://jsonschemalint.com/#/version/draft-04/markup/json?gist=09e266c8fba04a88c117fe05e4ab41d6)

## <span id = "actions">设备能力 actions</span>

- 开关 [switch](#switch)
- 颜色 [color](#color)
- 亮度 [brightness](#brightness)
- 模式 [mode](#mode)
- 位置量 [position](#position)
- 风速 [fanspeed](#fanspeed)
- 转向模式 [swing_mode](#swing_mode)
- 音量 [volume](#volume)
- 频道 [channel](#channel)
- 湿度 [humidity](#humidity)
- 温度 [temperature](#temperature)
- 色温 [color_temperature](#color_temperature)
- 媒体播放控制 [playback](#playback) 未上线
- Ping [ping](#ping)

### <span id = "switch">开关 switch</span>

- actions 接受值 [ "on", "off", "stop"]
  - "on" : 开
  - "off" : 关
  - "stop" : 暂停，停止

Example:
```JSON
{ "switch": ["on", "off"] }
```

- state 值
  - {string}
  - actions 定义设备能力对应的状态
  - 可以为 null

Example:
```JSON
{ "property": "switch", "name":"on" }
```

### <span id = "color">颜色 color</span>

- actions 接受值 [ "random", "num" ]
  - "random": 颜色随机值
  - "num": 指定颜色RGB值，例如蓝色RGB值为 0x00FF00
  - 当设备同时支持调颜色和调亮度是，则亮度值将会整合在RGB中，因此RGB设备的调亮度能力不需要添加 brightness 的能力，只需添加 color 即可。如，RGB灯。

Example:
```JSON
{ "color": ["num"] }
```

- state 值
  - {number}
  - RGB 十六进制数值
  - 0x000000 - 0xFFFFFF
  - 可以为 null

Example:
```JSON
{ "property": "color", "name":"num", "value": 65280 }
```

### <span id = "brightness">亮度 brightness</span>

- actions 接受值 [ "up", "down", "max", "min", "num" ]
  - "up": 调亮
  - "down": 调暗
  - "max": 调到最亮
  - "min": 调到最暗
  - "num": 调到 0 到 100 之间指定数值，若设备亮度范围更大，则需要自行转换。
  - 当设备支持RGB调颜色和调亮度时，不需要添加此能力。当设备不支持RGB调色，但支持调亮度时，则添加此能力。如，白光灯。

Example:
```JSON
{ "brightness": ["up", "down", "num"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 可以为 null

Example:
```JSON
{ "property": "brightness", "name":"num", "value": 68 }
```

### <span id = "mode">模式 mode</span>

- actions 接受值 [ "auto", "manual", "cool", "heat", "dry", "fan", "silent", "energy", "sleep" ]
  - "auto": 自动模式
  - "manual": 手动模式
  - "cool": 制冷模式
  - "heat": 制热模式
  - "dry": 除湿模式
  - "fan": 送风模式
  - "silent": 静音模式
  - "energy": 省电模式
  - "sleep": 睡眠模式

Example:
```JSON
{ "mode": ["auto", "cool", "heat", "fan"] }
```

- state 值
  - {string}
  - actions 定义能力对应的一个状态
  - 可以为 null  

Example:
```JSON
{ "property": "mode", "name":"auto"}
```

### <del><span id = "position">位置量 position</span></del>  暂时不支持

- actions 接受值 [ "up","down","num" ]
  - "up": 如：窗帘打开一点
  - "down": 如：窗帘关闭一点
  - "num": 如：窗帘打开/关闭到百分之几

Example:
```JSON
{ "position": ["num"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "position", "name":"num", "value": 10}
```

### <span id = "fanspeed">风速 fanspeed</span>

- actions 接受值 [ "up", "down", "max", "min", "switch", "num" ]
  - "up": 调高，调大
  - "down": 调低，调小
  - "max": 调到最高，调到最大
  - "min": 调到最低， 调到最小
  - "switch": 切换不同档位
  - "num": 调到指定数值

Example:
```JSON
{ "fanspeed": ["up", "down", "num"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "fanspeed", "name":"num", "value": 10}
```

### <span id = "swing_mode">转向模式 swing_mode</span>

- actions 接受值 [ "auto", "on", "off", "horizon", "horizon.off","vertical", "vertical.off" ]
  - "auto": 自动模式
  - "on": 打开转向模式
  - "off": 关闭转向模式
  - "horizon": 水平转向，左右转向
  - "horizon.off": 关闭水平转向、关闭左右转向
  - "vertical": 垂直转向、上下转向
  - "vertical.off": 关闭垂直转向、上下转向

Example:
```JSON
{ "swing_mode": ["auto", "horizon", "vertical"] }
```

- state 值
  - {string}
  - actions 定义的能力对应的一个状态
  - 可以为 null

Example:
```JSON
{ "swing_mode": "auto" }
{ "property": "position", "name":"num", "value": 10}
```

### <span id = "volume">音量 volume</span>

- actions 接受值 [ "up", "down", "max", "min", "num" ]
  - "up": 调高，调大
  - "down": 调低，调小
  - "max": 调到最大
  - "min": 调到最小
  - "num": 调到指定数值

Example:
```JSON
{ "volume": ["up", "down", "mun"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "volume", "name":"num", "value": 100}
```

### <span id = "channel">频道 channel</span>

- actions 接受值 [ "next", "prev", "random", "num" ]
  - "next": 上一个频道
  - "prev": 下一个频道
  - "random": 随机频道
  - "num": 指定频道

Example:
```JSON
{ "channel": ["num"] }
```

- state 值
  - {number}
  - 正整数
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "channel", "name":"num", "value": 34}
```

### <span id = "humidity">湿度 humidity</span>

- actions 接受值 [ "up", "down", "max", "min", "num" ]
  - "up": 调高
  - "down": 调低
  - "max": 调到最大
  - "min": 调到最小
  - "num": 调到指定数值

Example:
```JSON
{ "humidity": ["up", "down", "max", "min", "num"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "humidity", "name":"num", "value": 100}
```

### <span id = "temperature">温度 temperature</span>

- actions 接受值 [ "up", "down", "max", "min", "num" ]
  - "up": 调高
  - "down": 调低
  - "max": 调到最大
  - "min": 调到最小
  - "num": 调到指定数值

Example:
```JSON
{ "temperature": ["up", "down"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "temperature", "name":"num", "value": 26}
```

### <span id = "color_temperature">色温 color_temperature</span>

- actions 接受值 [ "up", "down", "max", "min", "num" ]
  - "up": 调高
  - "down": 调低
  - "max": 调到最大
  - "min": 调到最小
  - "num": 调到指定数值

Example:
```JSON
{ "color_temperature": ["up", "down"] }
```

- state 值
  - {number}
  - 0 到 100 之间十进制数值
  - 如果不能明确获取到具体数值，可以为 null

Example:
```JSON
{ "property": "color_temperature", "name":"num", "value": 26}
```

### <span id = "ping">ping</span>

- actions 接受值 [ "trigger" ]
  - ping 是设备提示的功能。比如，智慧灯泡闪一下（打开关闭或者关闭打开，或者换颜色，改亮度），用来发现。如果设备没有该能力，又支持开关，那么默认开关一下，用以提示。
    - trigger 触发

Example:
```JSON
{ "property": "ping", "name":"trigger"}
```

- state 值
  - 为空，不需要提供state


### <span id = "playback">playback</span> 媒体播放控制， 草稿未上线

- actions
 - play
 - pause
 - stop
 - next
 - previous

Example:

```JSON
{ "property": "playback", "name":"play"}
```

- state 值