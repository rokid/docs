# Rokid.Control

执行指定的操作，并返回终端最新状态

### Endpint Object


字段名 | 类型 | 描述
--- | --- | ---
endpointId | `string` | Skill 提供的终端 Id
additionalInfo | key-value pairs | Skill 提供的终端附加信息
states | `InterfaceState[]` | 终端能力状态，具体信息请参考 [终端描述](./endpoint.md)


### Request Payload

根据各个控制命令，Payload 会有所变化，具体信息请参考 [终端能力](./rokid-interface.md)

#### Example Request
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Color.Adjust",
    "payloadVersion": "v1",
    "authentication": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "device:an-id-unique-to-user",
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
#### Example Response
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "v1"
  },
  "endpoint": {
    "endpointId": "device:an-id-unique-to-user",
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
