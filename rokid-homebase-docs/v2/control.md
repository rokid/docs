### Rokid.Control

执行指定的操作，并返回终端最新状态

#### Endpint Object

字段名 | 类型 | 描述
--- | --- | ---
endpointId | `string` | Skill 提供的终端 Id 
additionalInfo | key-value pairs | Skill 提供的终端附加信息
states | `InterfaceState[]` | 终端能力状态，具体信息请参考 [终端](./endpoint.md)


#### Request Payload

根据各个控制命令，Payload 会有所变化，具体信息请参考 [终端能力](./rokid-interface.md)。

`注意：对于无 payload/value 的能力，如 Temperature.SetMax，Request 中 payload 字段缺失。`

##### Example Request
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
    "states": [
      {
        "interface": "Color",
        "value": 12345
      }
    ]
  },
  "payload": {
    "delta": -1,
  }
}
```
##### Example Response
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "v1"
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "states": [
      {
        "interface": "Color",
        "value": 12344
      }
    ]
  },
  "payload": {}
}
```
