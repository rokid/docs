# Rokid JS Engine 使用指南

> 欢迎使用Rokid-JS-Engine，很高兴大家可以通过编辑JS脚本来搭建技能服务。

## 使用JS脚本更快速的开发技能

> 使用JS脚本，我们的目标是帮助您更快速地构建技能，同时可以让您避免不必要的复杂性。使用JS脚本的方式有以下优势：
- **无需服务器** ：开发者不需要服务器去提供服务。
- **无需https服务**：开发者不需要自己搭建复杂的https服务。

### JS脚本

``` javascript
exports.handler = function(event, context, callback) {
    var rokid = Rokid.handler(event, context,callback);
    rokid.registerHandlers(handlers);
    rokid.execute();
};
```

我们通过Rokid对象封装了一些工具供大家使用。

 - 首先，通过Rokid.handler(event, context, callback)来使用Rokid-sdk。
 - 接下来，我们需要处理我们技能意图（intent），通过rokid.registerHandlers( )以简单来注册您所需的技能意图。
 - 最后，通过rokid.execute( )触发技能意图。
 
以上三步是必须的。

其中handlers，为大家所要写的意图技能处理函数，在“配置”编写js脚本，比如：

``` javascript
var handlers = {
	'HelloWorldSample':function() {
		try{
			this.emit(':tts',{tts:'Hello World!'},{sessionKey:sessionValue});
			//正常完成意图函数时callback
			this.callback(null);
		}catch(error){
			//报错时callback错误
			this.callback(error);
		}
	},
	'MediaSample': function () {
		try{
			//正常完成意图函数时callback
			this.emit(':media', { itemType: 'AUDIO', url:'s.rokidcdn.com/temp/rokid-ring.mp3' },{sessionKey:sessionValue});
		}catch(error){
			//报错时callback错误
			this.callback(error)
		}
    }
};
```
### 关于调用callback
**上述中this.callback是在意图函数运行完成后必须调用的，且需注意this的指向。如不调用，则jsEngine将会误认为脚本未执行完毕而导致无法输出结果。**

其中"HelloWorldSample"与"MediaSample"对应于"语音交互"中的intent如下：

``` javascript
{
    "intents": [
        {
            "intent": "HelloWorldSample",
            "slots": [],
            "user_says": [
                "你好"
            ]
        },
        {
			"intent": "MediaSample",
			"slots": [],
			"user_says": [
				"播放"
			]
		}
    ]
}
```

"语音交互"的intent，slot等request信息可在Rokid.param（下文有介绍）中获取。

```javascript
this.emit(':tts',{tts:'Hello World!'},{sessionKey:sessionValue})
```

- 上述语法是rokid-sdk用于同步响应对象的“tts”响应方法。注：传入":tts"方法的参数对象中tts属性是必须的，且其类型须为string或number！session根据需求选择。


### 开发者相关字段（tts）
 - this.emit(":tts",{},{})第二个参数如下：

 
| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| type | string |  NORMAL  |
| form | string |  cut  |
| shouldEndSession | boolean | true |
| action | string | PLAY |
| tts | string | 无（必填）|

 - this.emit(":tts",{},{})第三个参数如下：

| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| sessionKey | string | 无（自定义选填）|
| seesionValue | string | 无（自定义选填）|

```javascript
this.emit(':media', { itemType: 'AUDIO', url:'s.rokidcdn.com/temp/rokid-ring.mp3' },{sessionKey:sessionValue})
```

上述 语法是rokid-sdk用于同步响应对象的"media"响应方法。注：传入":media"方法的参数对象中"url"和属性"itemType"是必须的！session根据需求选择。

### 开发者相关字段（media）
 - this.emit(":media",{},{})第三个参数如下：

| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| type | string |  NORMAL  |
| form | string |  cut  |
| shouldEndSession | boolean | true |
| action | string | PLAY |
| token | string | 无 |
| itemType(对应文档item里的type) | string | 无（必填）|
| url | string | 无（必填）|
| offsetInMilliseconds | number | 0 |

 - this.emit(":media",{},{})第三个参数如下：

 
| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| sessionKey | string | 无（自定义选填）|
| seesionValue | string | 无（自定义选填）|

具体字段定义可参见：<https://rokid.github.io/docs/3-ApiReference/cloud-app-development-protocol_cn.html#3-response>

### 在Rokid对象中封装的工具
- Rokid.handler(event,contxt,callback):用于调用Rokid-sdk。
- Rokid.resHandler(content):buffer处理函数，如通过Rokid.sync_request请求必须通过此函数处理，再提交":tts"或":media"。
- Rokid.sync_request(method,url,options):同步请求，需把返回的数据通过Rokid.resHandler( )进行buffer处理。
- Rokid.request(options,callback):异步请求。
- Rokid.param:可根据“集成测试”中服务请求的数据结构获取一些数据。如：
	- slots：Rokid.param.request.content.slots
	- intent: Rokid.param.request.content.intent
	- session: Rokid.param.session.attributes

### 关于调试
在“配置”页里，目前已支持单点测试，仅测试js应用脚本正确性。

 *  配置测试用例，其中的intent和slot是需要开发者在默认用例基础上对应于“语音交互”中作相应调整。
 * 调试结果中将测试用例作为request，response和log日志则是根据应用脚本产出的真实结果。

确保js应用脚本的正确性情况下，可在“集成测试”页中进行全链路集成测试。

### 关于日志
- 在应用脚本中可调用console.log( )输出你想要看的日志。
- 须保证在“命中语音指令”的情况下才可查看日志。
- 此日志仅是应用脚本执行的日志，不包括其他链路的日志。
- 尽量在脚本中采用try-catch中调用callback传回状态，详细参见本文sample。

### Sample

```javascript
var data = [
    "床前明月光，疑是地上霜，举头望明月，低头思故乡。",
    "白日依山尽，黄河入海流，欲穷千里目，更上一层楼。",
    "千山鸟飞绝，万径人踪灭，孤舟蓑笠翁，独钓寒江雪。",
    "松下问童子，言师采药去，只在此山中，云深不知处。",
    "向晚意不适，驱车登古原，夕阳无限好，只是近黄昏"
];


exports.handler = function(event, context, callback) {
    var rokid = Rokid.handler(event, context,callback);
    rokid.registerHandlers(handlers);
    rokid.execute();
};

var handlers = {
    'LaunchRequest': function () {
	    //这里不是意图函数完成的地方，因此不需要callback
        this.emit('GetNewFactIntent');
    },
    'GetNewFactIntent': function () {
	    try{
			var factArr = data;
	        var factIndex = Math.floor(Math.random() * factArr.length);
	        var randomFact = factArr[factIndex];
	        var speechOutput = randomFact;
	        this.emit(':tts', {tts:speechOutput});
	        this.callback(null);
		}catch(error){
			this.callback(error);
		}
    },
    'sync_NewsRequest': function () {
	    //同步请求
	    try{
			result = Rokid.sync_request('GET', 'https://www.toutiao.com/hot_words/');
	        //buffer处理
	        result = Rokid.resHandler(result); 
	        var resStr = '';
	        result.forEach(function(item){
	            resStr += item + ','
	        })
	        this.emit(':tts', { tts: resStr });
	        this.callback(null);
		}catch(error){
			this.callback(error);
		}
    },
    'ansync_NewsRequest': function () {
	    //异步请求，注意this指向问题
        var ttsRes = '', self = this;
        Rokid.request({
		    method: 'GET',
		    url: 'https://www.toutiao.com/hot_words/',
		    headers:{
		        'User-Agent': 'request'
		    }
		}, function (error, response, body) {
            if (error) {
                self.callback(error);
            }
            JSON.parse(body).forEach(function (item) {
                ttsRes += item + ',';
            });
            self.emit(':tts', { tts: ttsRes });
            self.callback(null);
        });
    },
    'MediaRequest': function () {
	    try{
			this.emit(':media', { itemType: 'AUDIO', url: 's.rokidcdn.com/temp/rokid-ring.mp3' });
			this.callback(null);
		}catch(error){
			this.callback(error);
		}
    }
};
```

### Q&A
#### Q：为什么我有时候结果输出的会包含[Object,Object]？
A：需要注意在emit的时候写入{tts:xxx}对象时，xxx必须为string类型，如果object+string就可能出现以上现象。想要输出object的内容须用JSON.stringify()将其转换为string。
#### Q：为什么我的脚本一直超时？
A：1、脚本允许运行时间为2s，如在2s内未完成则会超时。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2、需要在emit之后立即调用callback。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3、在调用emit及callback时请注意“上下文this”的指向。

