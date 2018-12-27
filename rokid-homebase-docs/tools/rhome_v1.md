# rhome（旧版协议）

命令行接口检验工具

## 功能

- 调用 list|get|execute 接口。

- 使用 jsonshema 对返回的数据格式进行校验，并指出具体错误信息。

## 安装

**注意：**目前由于若琪智能家居协议已升级到 v2 版本，v1 协议接口调试，需要下载 v1.2.0 版本。

从 [Release v1.2.0](https://github.com/Rokid/rokid-homebase-cli/releases/tag/v1.2.0) 页面下载最新的适合你的操作系统的已打包的程序。

> 在项目 [GitHub](https://github.com/Rokid/rokid-homebase-cli) 页面了解更多

## 使用

```
$ rhome -h

Usage: rhome [options] [command]


  Commands:

    serve <path> [port]            transform local driver to server with default port 3000
    add                            add a remote driver's session
    del <name>                     delete a remote driver's session
    sessions                       list all added sessions
    use <name>                     user an added session
    list                           list a driver's all devices
    get <id>                       get one device's current state
    exec <id> <prop> <name> [val]  execute the device<id> with target action(e.g color num 256)
    *                              [object Object]
    help [cmd]                     display help for [cmd]

  show help

  Options:

    -h, --help     output usage information
    -V, --version  output the version number
    -b, --body     show response body of list/get/execute
    -l, --local    list local devices
```

* `rhome` 运行后，将在用户目录下新建 **rhome.json** 文件，保存 sessions、devices、currentSession 信息。如有必要，开发者可以进行修改。
* `add` 是交互式命令。 name 必须由 **字母**、**数字** 和 **下划线** 组成。例如: demo_1。 其余为命令行模式。
* `sessions` 命令显示已添加的所有 session，和显示当前使用的 session。默认使用第一个 session，或通过 `use` 指定。
* `-b` 显示 list | get | execute 的原始返回。
* `-l` 显示 **rhome.json** 文件中的当前 session 下的所有设备。

rhome demo:

```
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

## 数据校验

`rhome` 将对返回数据进行校验，并显示具体的错误信息。

* 数据格式正确

```
$ rhome list

id: 0
sessionName: demo
deviceId: "e12e2735-5e64-44d3-8ee2-46471f03d182"
name: light1
type: light
offline: false
```

* 数据格式错误

如有错误，将会显示具体的错误信息，以供参考。

```
$ rhome list

body checked by json schema:
instance does not match allOf schema [subschema 1] with 2 error[s]:
instance.data[0].actions.color[1] is not one of enum values: random,num
instance.data[0] requires property "type"
```
