# Node.js 开发者生态

RokidOS 提供了完整的 Node.js 语音应用接口及框架。

### 安装开发者工具

```shell
$ npm install rokidos-cli -g
```

### 语音应用框架介绍

RokidOS 内置了一套完整的语音应用框架，整个框架遵循基本的 Node.js 规则，只需在
根目录创建 `app.js` 及 `package.json` 即可。

##### `package.json`

```shell
$ npm init
```

可通过上述命令生成一个通用模版，然后更新文件的如下字段：

- `name`: 应用名，会作为安装后目录的名字
- `version`: 应用版本号，请开发者遵守语义化版本更新你的应用
- `metadata`: 应用安装所需的信息
  - `type`: 应用类型，可选：`scene`和`cut`
  - `skills`: 使用该字段配置应用需要处理的技能 ID

##### `app.js`

下面是一个示例的入口脚本：

```js
'use strict';

const app = require('@rokid/ams')();
const tts = require('@rokid/tts');
const player = require('@rokid/player');

app.on('create', function() {
  // the app is created
});

app.on('resume', function() {
  // the app is resume
});

app.on('pause', function() {
  // the app is pause
});

app.on('request', function(data, action, event) {
  // upstream voice data
});
app.start();
```

`app`对象支持如下事件：

| 事件名   | 描述                    |
|---------|-------------------------|
| create  | 在应用第一次被唤起时调用   |
| restart | 在应用再次被创建时调用     |
| resume  | 在应用被置为栈顶恢复时调用 |
| pause   | 在应用被其他应用占用时调用 |
| stop    | 在应用被停止时调用        |
| destroy | 在应用被销毁时调用        |

同时也支持下列 BlackSiren 下发的事件如下：

- `vad_start`
- `vad_data`
- `vad_end`
- `vad_cancel`
- `wake_cmd`
- `sleep`

更复杂的例子可以参考 `/opt/apps/` 目录下的内置应用。

### 安装应用

```sh
$ cd /path/to/app/directory
$ rokid install
```

如果你想单独构建出应用包，则使用 `rokid build` 即可。

### 调试应用

首先确保你已正确安装应用，并且已通过 USB 连接到你要调试的 RokidOS 设备：

```sh
$ rokid debug
```

### 语音应用测试

在项目目录下创建 `tests` 目录，然后在该目录下创建测试样例如下：

```js
test('test voice play', (t) => {
  t.send('asr', 'nlp', 'action');
  // t.assert([event], [value], [callback]);
});
```

在这里返回的对象 `t` 中，分别提供了两个方法：`send()` 和 `assert()`。

##### `send(asr, nlp, action)`

该方法用于向测试设备发送指定的 `asr`、`nlp` 对象和 `action` 对象。

##### `assert(event, val, callback)`

该方法用于在 `t.send()` 之后，捕获来自测试设备发送的探针事件，现支持的事件如下：

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
$ rokid test
```

