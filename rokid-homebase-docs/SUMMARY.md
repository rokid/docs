# Summary

* [介绍 Homebase](README.md)

## 接入方式

* [云云对接](connect/cloud-to-cloud.md)
* [局域网对接](connect/via-lan.md)

## 智能家居技能接入协议 V2

* [消息格式参考](protocol/message-reference.md)
* [当发生了错误](protocol/error-response.md)
* [终端](protocol/endpoint.md)
* [主动推送终端状态](protocol/event-gateway.md)
* [能力接口](protocol/rokid-interface.md)
  * [推送授权 Authorization](protocol/authorization.md)
  * [搜索发现 Discovery](protocol/discovery.md)
  * [终端控制 Control](protocol/control.md)
  * [终端查询 Query](protocol/query.md)

## 智能家居技能接入协议 V1

* 接口协议
  * [HTTP 远程驱动](connect/http-remote-driver.md)
  * [TCP 远程驱动](connect/json-rpc-over-tcp.md)
  * [局域网自动发现](connect/ssdp-auto-discovery.md)
* 授权方式
  * [Homebase OAuth 授权](connect/oauth.md)
  * [Homebase OAuth2.0 授权](connect/oauth2.0.md)
* [设备描述](device/README.md)
  * [设备](device/device.md)
  * [设备类型](device/type.md)
  * [设备能力与状态](device/actions-and-state.md)
  * [设备房间](device/room-name.md)
  * [标准错误](connect/errors.md)

## [调试工具](tools/README.md)

* [命令行接口校验工具](tools/rhome.md)
* [远程驱动调试工具](tools/developer-driver.md)
* [如何测试 OAuth|OAuth2.0 接口](tools/oauth-test.md)

## 其它

* [Webhook](webhook/index.md)
