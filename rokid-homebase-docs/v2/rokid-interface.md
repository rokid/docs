### 目录

-   [终端能力](#终端能力)
  - [Switch 开关状态](#switch-开关状态)
  - [MotionSwitch 行为状态](#motionswitch-行为状态)
  - [Position 位置百分比状态](#position-位置百分比状态)
  - [Color 颜色状态](#color-颜色状态)
  - [ColorTemperature 色温状态](#colortemperature-色温状态)
  - [Brightness 亮度状态](#brightness-亮度状态)
  - [Mode 模式状态](#mode-模式状态)
  - [SwingMode 转向状态](#swingmode-转向状态)
  - [Humidity 湿度状态](#humidity-湿度状态)
  - [Temperature 温度状态](#temperature-温度状态)
  - [FanSpeed 风速状态](#fanspeed-风速状态)
  - [Volume 音量状态](#volume-音量状态)
  - [Media.TVChannel 频道状态](#mediatvchannel-频道状态)
  - [Media.Music 音乐控制](#mediamusic-音乐控制)
  - [PlaybackControl 媒体播放状态](#playbackcontrol-媒体播放状态)
  - [PlaybackMode 媒体播放模式状态](#playbackmode-媒体播放模式状态)


### 终端能力

终端能力 Interface 代表终端具备的变化状态值。

当这个能力可以问询时（`isRetrievable`）,除了可以通过向若琪控制:"帮我把灯调为红色",将 `Color` 设置为红色,还可以通向若琪问询:"这个现在是什么颜色",若琪播报"这个灯现在是红色"。当这个能力会主动推送状态时（`isProactivelyReported`）,那么就可以将这个终端状态作为一个自动化操作的触发器, 如一个自动化操作是"当在早上家门关闭时, 关闭家里所有灯",那么就需要有一个家门的开关（`Switch` ）可以主动推送状态（ `isProactivelyReported`）,当在早上它的值设为`Switch.Off`时, 该自动化操作就会被触发。类似的，如果我们有一个温度传感器，而且他的温度（ `Temperature`）能够主动推送（ `isProactivelyReported`）我们就可以设置一个自动化场景:"当室内高于25摄氏度时，开启电风扇"。

终端能力的状态值可以是 number 与 enum 或者特殊描述符类型；

 - Number类型接口: 可以具有 Set 和 Adjust 控制命令；Set 为设为绝对期望值, Adjust为 delta 如 +1, -1 等相对值
    - Percentage: 取值 0 到 100, Adjust 默认步长为 10 
    - RGB: 取值 0 到 0xFFFFFF
- Enum 类型接口: 具体的 Enum 值即为命令（相当于 Set 但是枚举了所有值） 
- 描述符类型接口:是值的说法无法枚举、也不是 Number 类型的类型, 如歌曲、电视频道, 具有 Set控制命令

> Beta 版尚不支持向若琪问询终端状态

#### Switch 开关状态

类型: Enum

可对应说法: 若琪, 开灯；若琪, 关灯

命令 | 描述
--- | ---
Switch.On | 打开终端
Switch.Off | 关闭终端

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Switch.On",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

#### MotionSwitch 行为状态

类型: Enum

可对应说法: 若琪, 开灯；若琪, 关灯

可以与 Switch 组合成：若琪，开窗；*(窗户正在打开，3秒后)* 若琪，停下

命令 | 描述
--- | ---
MotionSwitch.On | 终端开始运动
MotionSwitch.Off | 终端停止运动

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "MotionSwitch.On",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

#### Position 位置百分比状态

类型: percentage

可对应说法: 若琪, 把窗户开到一半

命令 | 描述
--- | ---
Position.Set | 设置为指定值
Position.Adjust | 通过相对值调整

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Position.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Position.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Color 颜色状态

类型: Number

可对应说法: 若琪, 把灯调为红色

命令 | 描述
--- | ---
Color.Set | 设置为指定值
Color.SetRandom | 由 Skill 设置一个随机色值

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 颜色 RGB Hex 值

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Color.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 255
  }
}
```

##### SetRandom Payload

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Color.SetRandom",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

#### ColorTemperature 色温状态

类型: percentage

可对应说法: 若琪, 把灯颜色调暖点；若琪, 把灯调为冷色

命令 | 描述
--- | ---
ColorTemperature.Set |
ColorTemperature.SetMax |
ColorTemperature.SetMin |
ColorTemperature.Adjust |

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "ColorTemperature.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "ColorTemperature.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "ColorTemperature.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "ColorTemperature.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Brightness 亮度状态

类型: percentage

可对应说法: 若琪, 把灯调亮点；若琪, 把灯亮度设到百分之五十

命令 | 描述
--- | ---
Brightness.Set  |
Brightness.SetMax |
Brightness.SetMin |
Brightness.Adjust |

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Brightness.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Brightness.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Brightness.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Brightness.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Mode 模式状态

类型: enum

可对应说法: 若琪, 把空调设为制冷模式

命令 | 描述
--- | ---
Mode.Auto | 自动模式
Mode.Manual | 手动模式
Mode.Cool | 制冷模式
Mode.Heat | 制热模式
Mode.Dry | 除湿模式
Mode.Fan | 送风模式
Mode.Silent | 静音模式
Mode.Energy | 省电模式
Mode.Sleep | 睡眠模式

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Mode.Auto",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

#### SwingMode 转向状态

类型: enum

可对应说法: 若琪, 打开风扇转向

命令 | 描述
--- | ---
SwingMode.Auto |
SwingMode.On |
SwingMode.Off |
SwingMode.Horizon |
SwingMode.HorizonOff |
SwingMode.Vertical |
SwingMode.VerticalOff |

命令示例：
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "SwingMode.Auto",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

<!--
## CustomMode 可自定义的模式状态
类型: 模式描述符

可对应说法: 若琪, 打开舞台灯的跑马灯模式；

命令 | 描述
--- | ---
CustomMode.Set |

CustomMode 描述符

字段名 | 类型 | 描述
--- | --- | ---
mode.type | custom, preset |
mode.name | `string` | -->
#### Humidity 湿度状态

类型: percentage, unit: relative humidity

可对应说法: 若琪, 加湿器调大点；若琪, 加湿器设到五十

命令 | 描述
--- | ---
Humidity.Set |
Humidity.SetMax |
Humidity.SetMin |
Humidity.Adjust |

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Humidity.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Humidity.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Humidity.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Humidity.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Temperature 温度状态

类型: number, Unit: Celsius

可对应说法: 若琪, 空调调高点

命令 | 描述
--- | ---
Temperature.Set |
Temperature.SetMax |
Temperature.SetMin |
Temperature.Adjust |


##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Temperature.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Temperature.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Temperature.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Temperature.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### FanSpeed 风速状态

类型: percentage

可对应说法: 若琪, 空调风大点

命令 | 描述
--- | ---
FanSpeed.Set |
FanSpeed.SetMax |
FanSpeed.SetMin |
FanSpeed.Adjust |


##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "FanSpeed.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "FanSpeed.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "FanSpeed.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "FanSpeed.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Volume 音量状态

类型: percentage

可对应说法: 若琪, 电视音量大点

命令 | 描述
--- | ---
Volume.Set |
Volume.SetMax |
Volume.SetMin |
Volume.Adjust |

##### Set Payload

字段 | 类型 | 描述
--- | --- | ---
value | `number` | 百分比

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Volume.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "value": 20
  }
}
```

##### SetMax Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Volume.SetMax",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### SetMin Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Volume.SetMin",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Adjust Payload

字段 | 类型 | 描述
--- | --- | ---
delta | `number` | 相对值

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Volume.Adjust",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "delta": -1
  }
}
```

#### Media.TVChannel 频道状态

类型: channel descriptor

可对应说法: 若琪, 湖南卫视

当前的播放频道, 可以预置一系列的频道码, 如 CCTV第一频道 为 CCTV1

命令 | 描述
--- | ---
Media.TVChannel.Next |
Media.TVChannel.Previous |
Media.TVChannel.Set |


字段名 | 类型 | 描述
--- | --- | ---
tvChannel.name | `string` |
tvChannel.code | `string` |


##### Set Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Media.TVChannel.Set",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {
    "tvChannel": {
      "name": "芒果台",
      "code": "123"
    }
  }
}
```

##### Previous Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Media.TVChannel.Previous",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

##### Next Payload

命令示例：

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Media.TVChannel.Next",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key": "value"
    },
    "states": []
  },
  "payload": {}
}
```

#### Media.Music 音乐控制

类型: song descriptor
型: song descriptor

可对应说法: 若琪, 想听Don't You Worry Child

当前播放的媒体信息, 或者没有在播放

命令 | 描述
--- | ---
Media.Music.Next |
Media.Music.Previous |
Media.Music.Stop |
Media.Music.Set |

字段名 | 类型 | 描述
--- | --- | ---
music.name | `string` |
music.artist | `string` |
music.album | `string` |
music.genre | `string` |
music.source | `string` |

#### PlaybackControl 媒体播放状态

类型: enum

可对应说法: 若琪, 暂停音乐

当前播放状态, 如暂停, 正在播放

命令 | 描述
--- | ---
PlaybackControl.Play |
PlaybackControl.Pause |

#### PlaybackMode 媒体播放模式状态

类型: enum

可对应说法: 若琪, 单曲循环

当前播放模式, 如列表循环, 随机, 重复单曲, 顺序播放

命令 | 描述
--- | ---
PlaybackMode.RepeatAll |
PlaybackMode.RepeatOne |
PlaybackMode.Shuffle |
PlaybackMode.Order |
