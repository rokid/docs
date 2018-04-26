# Rokid.Authorization

为了能够授权 Skill 发送异步消息与终端状态推送，我们使用 `Rokid.Authorization` 来进行授权操作。

## 命令

### AcceptGrant

`AcceptGrant` 是为了 Rokid 能够验证 Skill 的消息推送请求是为了哪一个用户发起。为了能够在用户授权 Skill 推送状态的能力后 Skill 能够接收到由 Rokid 颁发的事件推送 Token，Skill 必须实现这个命令以能够发送事件到 Rokid IoT EventGateway。

详细 Payload

字段名 | 类型 | 描述
--- | --- | ---
grant.type | `string` | Token 类型
grant.token | `string` | Token

#### Example Request
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Authorization",
    "name": "AcceptGrant",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "payload": {
    "grant": {
      "type": "BearerToken",
      "token": "a-token-from-rokid"
    }
  }
}
```
#### Example Response
```json
{
  "header": {
    "messageId": "123-456",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "v1"
  },
  "payload": {}
}
```
