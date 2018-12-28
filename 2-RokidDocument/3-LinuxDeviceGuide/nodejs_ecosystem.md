# Node.js 开发者生态

- [本地开发者工具](#本地开发者工具)
- [技能框架介绍](#语音应用框架介绍)
  - [工程结构](#工程结构)
  - [安装](#安装)
  - [调试](#调试)
  - [测试](#测试)
- [系统接口](#系统接口)
  - [语音合成](#语音合成)
  - [媒体播放](#媒体播放)
  - [灯光控制](#灯光控制)

RokidOS 提供了完整的 Node.js 语音技能接口及框架。

### 本地开发者工具

RokidOS 为 Node.js 开发者提供了 `rokidos-cli` 包：

```shell
$ npm install rokidos-cli -g
```

### 语音技能框架介绍

RokidOS 内置了一套完整的语音技能框架，该框架遵循基本的 Node.js 规则，只需在根目录创建 `app.js` 及 `package.json` 即可。

#### 工程结构

RokidOS 本地技能的工程结构如下：

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
module.exports = require('@rokid/ams')({
  created() {
    // the app is created
  },
  resumed() {
    // the app is resume
  },
  paused() {
    // the app is pause
  },
  onrequest(context) {
    // upstream voice data
  },
  beforeDestroy() {
    // the app is to be destroyed
  },
  destroyed() {
    // the app is destroyed
  }
});
```

`app`对象支持如下生命周期函数：

| 生命周期        | 描述 |
|---------------|-------------------------|
| created       | 在应用第一次被唤起时调用 |
| resumed       | 在应用被置为栈顶恢复时调用 |
| paused        | 在应用被其他应用占用时调用 |
| beforeDestroy | 在应用被停止时调用 |
| destroyed     | 在应用被销毁时调用 |

另外，你可以在生命周期函数内调用如下接口：

- `.say(text)` 使用 RokidOS 说出制定的话；
- `.pickup()` 打开拾音并接受语音指令；
- `.exit()` 退出当前应用，并且关闭拾音；

更复杂的例子可以参考 `/opt/apps/` 目录下的内置应用。

#### 安装

```sh
$ cd /path/to/app/directory
$ rokid install
```

如果你想单独构建出应用包，则使用 `rokid build` 即可。

#### 调试

首先确保你已正确安装应用，并且已通过 USB 连接到你要调试的 RokidOS 设备：

```sh
$ rokid debug
```

#### 测试

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

### 系统接口

为了让开发者完成各种开放性的技能需求，RokidOS 为本地技能开发者提供了如下系统基础接口：

#### 语音合成

样例：

```js
const tts = require('@rokid/tts');
tts.play('text to speech');
```

该模块提供以下方法：

- `play(text, callback)` 让若琪说出指定的文字内容
  - {String} `text` 需要让若琪说的文字，支持 `SSML`
  - {Function} `callback` 当 `tts` 完成、取消或其他方式结束时，会通过这个回调函数通知用户
- `stop()` 停止播放当前内容

#### 媒体播放

样例：

```js
const player = require('@rokid/player');
player.play(url);
player.stop();
player.resume();
player.pause();
```

该模块提供以下方法：

- `play(url)` 播放某个 `url` 的媒体
  - {String} `url` 媒体地址
- `stop()` 停止当前应用中所有的媒体播放
- `pause()` 暂停当前应用中所有的媒体播放
- `resume()` 恢复当前应用中所有的媒体播放

#### 灯光控制

样例：

```js
const light = require('@rokid/lumen');
light.fill('red', 'all');
light.update({
  [1]: 'red',
  [2]: 'green',
});
```

该模块提供以下方法：

- `fill(color, sets)` 向指定的 LED 填充单个颜色
  - {String} `color` `RGB` 颜色值，支持的格式：#000000、red
  - {Array} `sets` 表示需要填充颜色的 LED 坐标，目前 LED 阵列为一维
- `update(dataWithSets)` 更底层的填充方法，一般用于更复杂的灯光渲染需求
  - {Object} `dataWithSets` 该对象是 `LED-Color` 的映射关系
- `gradients(dataWithSets, ms)` 提供灯光的渐变控制

