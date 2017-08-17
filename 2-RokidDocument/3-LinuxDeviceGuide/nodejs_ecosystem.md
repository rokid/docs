# Node.js 开发者生态

Rokid Linux 提供了完整的 Node.js 语音应用接口及框架。

### 安装开发者工具

```shell
$ npm install rokid-linux-cli
```

### 语音应用框架介绍

Rokid Linux 内置了一套完整的语音应用框架，整个框架遵循基本的 Node.js 规则，只需在
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
const player = require('@rokid/rplay');

app.on('tts', function(data, action, event) {
  tts.say(data.tts);
});

app.on('media', function(data, action, event) {
  player.play(data.url);
});
app.start();
```

更复杂的例子可以参考 `/opt/apps/` 目录下的内置应用。
