## Homebase TCP 通讯协议 [草稿]

通讯基于 JSON-RPC 2.0，使用 TCP 短连接

## 连接过程

- Homebase 获取到 TCP 驱动服务 ip 与 端口
- Homebase 建立与该端口的连接
- Homebase 发送 TCP json-rpc call
- TCP 驱动返回结果
- 本次连接断开

## 指令

### method: `list`

获取设备列表

输入参数

- params
  - {Object} userAuth
    - userId
    - userToken


返回设备列表， 标准设备接口参考 [Homebase 设备][device]

- {Array} result
  - {String} deviceId
  - {Object} deviceInfo
  - {String} state
  - actions

```
--> {"jsonrpc": "2.0", "method": "list", "params": {"userAuth":{ "userId": "hello1234" }}, "id": 1}
<-- {"jsonrpc": "2.0", "result": [{"deviceId": "1", }], "id": 1}
```

### method: `get`

获取单个设备最新状态


输入参数

- params
  - userAuth， 可选
    - userId
    - userToken
  - device
    - deviceId
    - deviceInfo

返回设备， 标准设备接口参考 [Homebase 设备][device]

- result
  - deviceId
  - deviceInfo
  - name
  - type
  - offline
  - parent



```
--> {"jsonrpc": "2.0", "method": "get", "params": {"userAuth":{ "userId": "hello1234", "userToken": "" }, "device": {"deviceId": "", deviceInfo: {}}}, "id": 1}
<-- {"jsonrpc": "2.0", "result": {"deviceId": "abc", "deviceInfo":{}, "name": "灯", "type": "light", "offline": false}, "id": 1}
```

### method: `execute`

- params
  - userAuth， 可选
    - userId
    - userToken
  - device
    - deviceId
    - deviceInfo
    - state
  - action
    - property  eg: 'color'
    - name  eg: 'num'
    - value eg: 0xff0000

方法返回

- 可以返回设备最新 state
- 返回 null 会触发一次 get 请求来更新最新设备状态

- result

```
--> { "jsonrpc": "2.0", "method": "list", "params": {"userAuth":{ "userId": "hello1234" }, "device": {"deviceId": "abc"}, "action": {"property": "switch", "name": "on"}}, "id": "1" }


// 返回 null 会触发一次 get 请求来更新最新设备状态
<-- { "jsonrpc": "2.0", "result": null, "id": "1"}  

// 返回设备最新 state, 可以更新设备状态
<-- { "jsonrpc": "2.0", "result": {"switch": "on"}, "id": "1"}
```

### method: `command`

- params
  - method {String}
  - params {Object}


[device]: ../device/device.md
