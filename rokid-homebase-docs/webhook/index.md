# Webhook 功能简介

目前若琪通过该接口开放了tts播报、播放音乐流媒体的能力。
开发者可以将新增的Webhook接口地址复制并添加至智能家居第三方平台，（如Abox，homeassistant...）

当第三方平台中的传感器事件触发该接口，若琪便会执行相应的操作。

`请开发者注意：最大调用限制：每分钟20次，每24小时1000次。`

# Webhook 使用详述

Webhook 是一个通过 HTTP 调用控制用户授权设备的服务，当某一个事件发生时，通过发起一个 HTTP Post 请求并使用期望的参数至指定的 Webhook URL 接口即可直接控制家庭里的设备。

## 触发 Webhook

创建一个 HTTP POST 请求至

```
https://homebase.rokid.com/trigger/with/{your_very_awesome_token}
```

与一个可选的 JSON 请求 Body，如：

```json
{
  "type": "tts",
  "devices": {
    "sn": "a_very_random_serial_number_of_rokid"
  },
  "data": {
    "text": "Vive l'amour"
  }
}
```

你可以在命令行使用 `curl` 来尝试：

```
curl -X "POST" "https://homebase.rokid.com/trigger/with/{your_very_awesome_token}" \
     -H 'Content-Type: application/json; charset=utf-8' \
     -d $'{
  "type": "tts",
  "devices": {
    "sn": "a_very_random_serial_number_of_rokid"
  },
  "data": {
    "text": "卧室若琪，你好呀"
  }
}'
```

## 触发 Body

Webhook 请求体的数据结构如下表所示，是一个 JSON 格式的 `object` 类型

字段名 | 类型 | 必需 | 描述
--- | --- | --- | ---
type | `string` | 必需 | 触发类型，只能是 `tts` 或者 `audio` 的其中一个
devices | `DeviceQuery` | 必需 | 设备筛选，详细格式见下面的 DeviceQuery
data | `object` | 必需 | 触发数据，根据触发类型见下方的文档

DeviceQuery 是筛选设备的 `object` 类型描述符，支持的筛选属性如下表所示，属性之间为“与”关系，具体筛选例子请看下方的“筛选设备”小节

DeviceQuery 字段名 | 类型 | 必需 | 描述
--- | --- | --- | ---
sn | `string` | 非必需 | 若琪序列号
roomName | `string` | 非必需 | 若琪所处的房间
tag | `string` | 非必需 | 设备标签
isAll | `boolean` | 非必需 | 选择所有设备，默认 `false`

### 当 `type` 为 `tts` 时

`data` 字段为包含以下字段的 `object`

字段名 | 类型 | 必需 | 描述
--- | --- | --- | ---
text | `string` | 必需 | 播报内容

### 当 `type` 为 `audio` 时

`data` 字段为包含以下字段的 `object`

字段名 | 类型 | 必需 | 描述
--- | --- | --- | ---
url | `string` | 必需 | 音频地址，必须符合 `^https?://` 的格式

### 筛选设备

`devices` 属性的 `sn`，`roomName`，`tag` 和 `isAll` 共同筛选目标若琪设备，我们设一个在厨房的若琪 SN 为 `a_very_random_serial_number_of_rokid`，并且有 `拿破仑`，`雪球` 两个标签，则我们可以用以下条件筛选：

```
{
  "sn": "a_very_random_serial_number_of_rokid"
}
```

```
{
  "sn": "a_very_random_serial_number_of_rokid",
  "roomName": "厨房"
}
```

```
{
  "tag": "雪球"
  "roomName": "厨房"
}
```

```
{
  "tag": "拿破仑"
}
```

## 常见问题

1. HTTP 状态码 422
  Webhook 的调用请求内容不符合约定，可以根据请求返回的错误消息修改请求内容。
2. HTTP 状态码 429
  在一定时间内 Webhook 接口被访问了过多次数，如果认为不是被授权的操作访问的话，需要用户在若琪应用中重新生成 Webhook Token 并更新访问的 url。
3. 如遇任何问题，均可发邮件至 homebase@rokid.com 向我们反馈。
