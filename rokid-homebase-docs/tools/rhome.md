### 目录

-   [命令行接口检验工具 - rhome](#命令行接口检验工具---rhome)
-   [功能](#功能)
-   [安装](#安装)
-   [使用](#使用)

### 命令行接口检验工具 - rhome

使用 rhome 工具通过 json schema 来验证 discover\|control\|report-state 接口的返回值来验证接入 Rokid Homebase 协议。

### 功能

-   调用 discover\|control\|report-state 接口。

-   使用 jsonschema 对返回的数据格式进行校验，并指出具体错误信息。

-   使用 jsonschema 对 ChangeReport 事件进行校验，并指出具体错误信息。

### 安装

从 [Release](https://github.com/Rokid/rokid-homebase-cli/releases)页面下载最新的适合你的操作系统的已打包的程序。

### 使用

``` {.bash}
$ rhome -h

  Usage: rhome [options] [command]

  Options:

    -V, --version                               output the version number
    -v, --verbose                               show raw response body
    -h, --help                                  output usage information

  Commands:

    add                                         add a session of remote driver
    del <name>                                  delete the session of remote driver
    sessions                                    list all added sessions
    use <name>                                  user an added session

    discover [options]                          list all devices of a driver
    control [options] <endpointId> <directive> [value]  execute the device<id> with target action(e.g `Media.TVChannel.Set '{ "tvChannel": { "code": "123" } }'`)
    report-state [options] <id>                 get current state of a driver

    await-event [options]                       serve an event gateway to await change reports
```

#### 步骤 1: 添加 Skill 配置

-   `rhome` 运行后，将在用户目录下新建 **rhome.json** 文件，保存 sessions、devices、currentSession信息。如有必要，开发者可以进行修改。
-   `add` 是交互式命令。 name 必须由 **字母**、**数字** 和 **下划线**组成。例如: demo\_1。 其余为命令行模式。
-   `sessions` 命令显示已添加的所有 session，和显示当前使用的session。默认使用第一个 session，或通过 `use` 指定。

如：

``` {.bash}
$ rhome add

? remote driver's name demo
? remote driver's endpoint http://127.0.0.1:3000
? userId in userAuth. If null, skip
? userToken in userAuth. If null, skip
{
  "name": "demo",
  "endpoint": "http://127.0.0.1:3000",
  "userId": "",
  "userToken": ""
}
```

#### 步骤 2: 搜索设备

在控制设备之前，我们需要先获取 Skill 能控制的设备

``` {.bash}
$ rhome discover

id: 0
sessionName: mimic
endpointId: device-1
displayName: 大米台灯
displayType: light
offline: false
```

#### 步骤 3: 控制设备

使用 `control <endpointId> <directive> [payload]` 命令来控制设备，其中`payload` 为序列化的 JSON 字符串，如 `'{"value": 123}'`

``` {.bash}
$ rhome control device-1 Switch.On

id: 0
sessionName: mimic
endpointId: device-1
displayName: 大米台灯
displayType: light
offline: false
```

##### 数据校验

`rhome` 将对返回数据进行校验，并显示具体的错误信息。

-   数据格式正确

``` {.bash}
$ rhome discover

id: 0
sessionName: demo
deviceId: "e12e2735-5e64-44d3-8ee2-46471f03d182"
name: light1
type: light
offline: false
```

-   数据格式错误

如有错误，将会显示具体的错误信息，以供参考。

    $ rhome discover
    
    body checked by json schema:
    instance does not match allOf schema [subschema 1] with 2 error[s]:
    instance.data[0].actions.color[1] is not one of enum values: random,num
    instance.data[0] requires property "type"

#### 步骤 4: 发送终端状态变化事件

使用 `await-event` 命令来启动一个本地接收事件的测试服务器，可以使用如`-p 7001` 的选项来指定服务器端口。

``` {.bash}
$ rhome await-event -p 9999

rhome listening on port 9999
Received a change report: {
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
    "endpointId": "0",
    "states": [
      {
        "interface": "Switch",
        "value": "On",
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
Caused by: PHYSICAL_INTERACTION
sessionName: mimic
endpointId: 0
displayName: 台灯
displayType: light
offline: false
states:
  Switch: "On"
```
