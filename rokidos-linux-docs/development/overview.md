## 应用开发

应用开发包括如下介绍：

- [应用概述](#应用概述)
- [工程结构](#工程结构)
- [开发者工具](#开发者工具)
- [教程](#教程)

## 应用概述

RokidOS 的本地技能分为两类：

- 轻应用(LightApp)
- 本地应用(NativeApp)

**轻应用**，直接通过语音交互的守护进程(vui-daemon)通过 JavaScript 引擎直接加载，适合于快速反馈的技能，
如天气、聊天等。轻应用不需要管理复杂的状态，可以理解为在本地的轻量级技能。

**本地应用**，是一个独立运行的进程，用于需要管理复杂状态的语音技能，比如闹钟、提醒等。

## 工程结构

无论是轻应用还是本地应用，工程结构都是统一的：

**`package.json`**

```shell
$ npm init
```

可通过上述命令生成一个通用模版，然后更新文件的如下字段：

- `name`: 应用名，会作为安装后目录的名字；
- `main`: 启动应用的入口程序；
- `version`: 应用版本号，请开发者遵守语义化版本更新你的应用；
- `metadata`: 应用安装所需的信息；
  - `type`: 应用类型，可选：`scene`和`cut`；
  - `skills`: 使用该字段配置应用需要处理的技能`ID`；
  - `native`: `true`或`false`，轻应用或本地应用；

## 开发者工具

首先，通过 npm 下载开发者工具：

> 不熟悉 npm 的开发者可以通过 https://npmjs.org 了解。

```shell
$ npm install rokidos-cli -g
```

该命令行工具支持：

- 设备配网
- 应用安装
- 查看设备日志
- 连接设备

### 安装

```sh
$ cd /path/to/app/directory
$ ro install
```

如果你想单独构建出应用包，则使用 `rokid build` 即可。

### 调试

首先确保你已正确安装应用，并且已通过 USB 连接到你要调试的 RokidOS 设备：

```sh
$ ro debug
```

更多详情请查看：[Rokid/rokidos-cli](https://github.com/Rokid/rokidos-cli)。

### 测试

在项目目录下创建 `tests` 目录，然后在该目录下创建测试样例如下：

```js
test('test voice play', (t) => {
  t.send('asr', 'nlp', 'action');
  // t.assert([event], [value], [callback]);
});
```

在这里返回的对象 `t` 中，分别提供了两个方法：`send()` 和 `assert()`。

**`send(asr, nlp, action)`**

> 该方法用于向测试设备发送指定的 `asr`、`nlp` 对象和 `action` 对象。

**`assert(event, val, callback)`**

> 该方法用于在 `t.send()` 之后，捕获来自测试设备发送的探针事件，现支持的事件如下：

- `voice`
- `media.start`
- `media.stop`

`callback` 在事件发生后被调用，因此你可以在 `media.stop` 的回调中，继续执行一些链式用例。例如：

```js
test('chainable case example', (t) => {
  t.send(asr, nlp, action);
  t.assert('media.stop', true, () => {
    t.send(asr2, nlp2, action2);
    t.assert('voice', 'some text to speak');
  });
});
```

当你写完测试用例后，使用下面的命令来执行测试：

```sh
$ ro test
```

## 教程

RokidOS 提供了如下开发接口：

- [Node.js入门](tutorial-nodejs.md)
- [C/C++入门](tutorial-cplusplus.md)
