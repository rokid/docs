# 消息


## 请求消息类型

### 命令 Directives
由若琪主动向 Skill 发起的请求，可以是 Skill 开放的 HTTP 服务，或者是 JSON RPC over TCP 等

- Rokid.Discovery: 搜索终端
- Rokid.Control: 终端控制，如“帮我打开客厅灯”
- Rokid.Query: 终端状态查询，如“现在家里门锁了吗“

Skill 对于若琪命令的回复需要使用 Responses 所定义的消息类型，否则若琪会认为本次消息发送失败；

> Beta 版尚不支持向若琪问询终端状态
>

### 事件 Events
由 Skill 主动向若琪发起的请求，只能通过 Rokid EventGateway 开放的 HTTP 服务使用

- Rokid.AsyncResponse: 当 Skill 认为终端控制、终端发现可能需要超过 3 秒的时间来完成时，可以推迟回复
- Rokid.ChangeReport: 终端状态变更，如灯被手动打开了

> Beta 版尚不支持事件推送
>

## 回复消息类型

### 回复 Responses
 Skill 回复若琪发起的命令

所有回复应该在 3 秒内返回，如果 Skill 认为本次操作需要更长的时间，应该考虑使用 DeferredResponse 来向若琪告知会在一定时间内使用 AsyncResponse 回复若琪

- Response: 普通的命令回复，包含终端的最新状态
- DiscoveryResponse: 终端发现命名空间的回复，需要包含终端所有应有的信息
- ErrorResponse: 发生错误时的回复，包含一个错误码和一条描述错误的消息
- DeferredResponse: 表示这个操作会超过2秒，需要在指定时间内使用 AsyncResponse 事件通知 Rokid EventGateway

## 消息体

### Header Object
通用的必需字段

字段名 | 类型 | 描述
--- | --- | ---
messageId | `string` | 若琪或 Skill 如果认为之前的消息发送失败了，可以尝试使用相同的 messageId 再次发送
namespace | `string` | 本消息的命名空间，如 Rokid.Discovery，Rokid.Control，Rokid.Query
name | `string` | 本次消息的名称，如在 Rokid.Control 的命名空间下 Switch.On，Rokid.Discovery 命名空间下的 Discover，Rokid.Query 命名空间下的 ReportState
payloadVersion | `enum` | 本消息的 Payload 定义版本，当前只支持 `v1`
authentication | Authentication Object | 本消息的认证信息，只有请求消息才需要这个字段，回复消息不需要

#### Authentication Object

字段名 | 类型 | 描述
--- | --- | ---
type | `string` | 通常为 BearerToken
token | `string` | 从若琪获取的 Token 或者若琪从 Skill 方获取的 Token

### Endpoint Object
本次消息的目标终端描述信息如 endpointId 和 additionalInfo

### Payload Object
根据消息类型决定内容，像控制请求的期望值等

# 示例

## 一个控制请求
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Color.Set",
    "payloadVersion": "v1",
    "authentication": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "unique-id-for-user",
    "additionalInfo": {
      "key1": "value1"
    },
    "states": [
      {
        "interface": "Color",
        "value": 12345,
        "timeOfSample": "20180320T00:00:00.000Z"
      }
    ]
  },
  "payload": {
    "value": 65280
  }
}
```


## 一个控制成功的返回
```json
{
  "header": {
    "messageId": "123-456",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "v1",
  },
  "endpoint": {
    "endpointId": "unique-id-for-user",
    "states": [
      {
        "interface": "Color",
        "value": 12345,
        "timeOfSample": "20180320T00:00:00.000Z"
      }
    ]
  },
  "payload": {}
}
```


## 当发生了错误时的一个返回

若琪会使用 Skill 的错误消息告知用户发生了什么错误，并如何解决该错误；如果 Skill 没有返回标准的错误格式，若琪将无法告知用户如何解决问题。

```json
{
  "header": {
    "messageId": "789-123",
    "namespace": "Rokid",
    "name": "ErrorResponse",
    "payloadVersion": "v1",
  },
  "payload": {
    "name": "E_DRIVER_ERROR",
    "message": "发生了一些不可告人的错误"
  }
}
```

关于错误的更多信息请查阅 [当发生了错误](./error-response.md)。
