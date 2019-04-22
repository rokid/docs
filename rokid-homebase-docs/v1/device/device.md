### 标准化设备

#### 数据类型 {Object}

- {String} [deviceId](#deviceId) 设备ID
- {String} [name](#name) 设备名
- {String} [type](#type) 设备类型
- {Object} [actions](#actions) 设备支持的能力
- {Object} [state](#state) 设备状态
- {Boolean} [offline](#offline) 是否离线
- {Object} [deviceInfo](#deviceInfo) (Optional) 附加信息
- {Object} [execDelay](#execDelay) (Optional) 控制延迟
- {String} [roomName](#roomName) (Optional) 房间名称
- {String} [homeName](#homeName) (Optional) 家庭名称

**标准化设备** 数据定义参考： [jsonschemalint 在线检查工具](https://jsonschemalint.com/#/version/draft-04/markup/json?gist=f9b8fcb4b8e9e2761978fb9cbde48392)

##### <span id = "deviceId">deviceId</span>

- {String}
- 设备唯一Id，用来标识一个设备，要具备唯一性

Example: uuid 等
```
"06d0dfe0-1123-11e7-93ae-92361f002671"
```

##### <span id = "name">name</span>

- {String}
- 设备名称

Example:
```
"智能灯泡"
```

##### <span id = "type">type</span>

- {String}
- 设备类型
- [支持的设备类型](type.md)

Example:
```
"light"
```

##### <span id = "actions">actions</span>

- {Object}
- 一个智能设备具备的能力，如下面 example 所示，智能灯泡具备开关，调颜色，调亮度三个能力。
- [设备能力定义](actions-and-state.md)

Example:
```JSON
{
  "switch":["on","off"],
  "color":["num"],
  "brightness":["num"]
}
```

##### <span id = "state">state</span>

- {Object}
- 设备当前状态
- 与 [actions](#actions) 对应， actions 定义的设备能力对应的当前状态

Example:

state:
```JSON
{
  "switch": "on",
  "color": 256,
  "brightness": 10
}
```
actions:
```JSON
{
  "switch":["on","off"],
  "color":["num"],
  "brightness":["num"]
}
```

##### <span id = "offline">offline</span>

- {Boolean}
- 设备离线状态
  - true: 离线
  - false: 在线

##### <span id = "deviceInfo">deviceInfo</span>

- {Object}
- Option
- 与设备有关的信息，允许自由定义和储存查询、控制设备等必需的信息

Example:

```JSON
{
  "hostname":"http://127.0.0.1",
  "port":"3000"
}
```

##### <span id = "execDelay">execDelay</span>

- {Number} Option 该设备控制指令发出后与下一个控制指令的延迟， 默认 150ms

Example:
```JSON
{
  "name": "电视",
  "deviceId": "123",
  "type": "tv",
  "actions": {
    "switch": ["on", "off"]
  },
  "execDelay": 1000,
}
```

##### <span id = "roomName">roomName</span>

- {String}
- 可选
- 设备所属房间名称

Example:

```json
{
  "deviceId": "qwert",
  "name": "落地灯",
  "roomName": "卧室",
}
```


##### <span id = "homeName">homeName</span>

- {String}
- 可选
- 设备所属家庭名称

Example:

```json
{
  "deviceId": "qwert",
  "name": "落地灯",
  "homeNmae": "客房218"
}
```