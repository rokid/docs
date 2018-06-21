# 当发生了错误

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
    "name": "E_INTERNAL_ERROR",
    "vendorCode": "origin-error-code",
    "message": "发生了一些不可告人的错误",
    "debugInfo": "something for debug",
  }
}
```

### Error Payload

字段名 | 类型 | 描述
--- | --- | ---
name | string | 若琪提供的枚举错误码
vendorCode | string | 厂家自有错误码
message | string | Skill 对发生的错误的详细描述，若琪不会将这个消息展现给用户
debugInfo | string | 用于调试的必要信息，用于协助问题定位

### Error Codes 错误码

ErrorCode | 描述
--- | ---
E_AUTHORIZATION_EXPIRED | 授权过期，应该尽快刷新
E_INVALID_AUTHORIZATION | 授权非法，并且不应该继续使用、刷新
E_NO_SUCH_ENDPOINT | 终端不存在
E_NOT_SUPPORTED_DIRECTIVE | Skill 不支持当前命令请求
E_VALUE_OUT_OF_RANGE | 命令的值超出了阈值
E_ENDPOINT_BUSY | 终端正在处理请求（不一定是来自若琪的命令请求），无法处理当前命令请求
E_CHANNEL_NOT_FOUND | 没有对应的频道
E_INTERNAL_ERROR | 通用错误，当错误不是上述任一错误时，使用该错误码
E_ENDPOINT_UNBOUND | 设备被解绑，无法控制。建议用户：重新对该设备配网
E_ENDPOINT_NEEDS_UPGRADE | 设备固件需要升级
E_ENDPOINT_UNREACHABLE | 无法访问到终端
E_ENDPOINT_INITIATING | 终端正在初始化
E_GATEWAY_UNREACHABLE | 无法访问到终端网关
E_SERVER_UNREACHABLE | 无法访问到终端服务器

MediaErrorCode | 描述
--- | ---
E_MEDIA_RESOURCE_NOT_FOUND | 找不到相关歌曲
E_MEDIA_FAVORITE_NOT_FOUND | 未找到收藏歌曲
E_MEDIA_NO_PREV | 已经是第一首了
E_MEDIA_NO_NEXT | 已经是最后一首了
