# 向若琪发送消息

当 Skill 获取了由若琪颁发的 EventGateway Token 后，即可向若琪 EventGateway 推送用户终端的状态变化信息、异步消息等事件。

Rokid IoT EventGateway 使用 HTTP 状态码来表述本次事件请求结果，当状态码为 202 时（成功）回复体为空：

HTTP 状态码 |	场景
--- | ---
202 Accepted |	Rokid EventGateway 收到了请求，并且请求体合法；但是不代表已经处理了请求
401 Unauthorized |	Skill 启用，但是 Token 已经过期
403 Forbidden |	Skill 已经停用，或者 Token 无效
400 Bad Request |	请求体不符合预设格式
422 Unprocessible Entity |	请求体符合格式，但是请求内容无法处理

## ChangeReport

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "ChangeReport",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-rokid"
    }
  },
  "endpoint": {
    "endpointId": "device:an-id-unique-to-user",
    "states": [
      {
        "interface": "Switch",
        "value": "On",
        "timeOfSample": "2018-03-15T18:00:00.000Z"
      },
      {
        "interface": "Color",
        "value": 12345,
        "timeOfSample": "2018-03-15T18:00:00.000Z"
      }
    ]
  },
  "payload": {
    "change": {
      "cause": "PHYSICAL_INTERACTION"
    }
  }
}
```

### ChangeReport Payload

字段名 | 类型 | 描述
--- | --- | ---
change.cause | `enum` | 本次状态推送的状态变更因素

ChangeCause | 描述
--- | ---
PHYSICAL_INTERACTION | 终端物理开关等造成状态变更
