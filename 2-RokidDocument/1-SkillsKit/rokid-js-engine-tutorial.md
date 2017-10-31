# Rokid JS Engine 使用指南V2.0

> 欢迎使用Rokid-JS-Engine，很高兴大家可以通过编辑JS脚本来搭建技能服务。
> Tips：为对老版本(V1.0)技能的过渡性支持，本次Js Engine V1.0 也进行了同步更新（[点此查看文档v1.0文档](./rokid-js-engine-tutorial-v1.0.md)），但在下个版本起V1.0视情况更新，或滞后于V2.0，推荐开发者使用V2.0进行开发。

## 使用JS脚本更快速的开发技能

> 使用JS脚本，我们的目标是帮助您更快速地构建技能，同时可以让您避免不必要的复杂性。使用JS脚本的方式有以下优势：
> - **无需服务器** ：开发者不需要服务器去提供服务。
> - **无需https服务**：开发者不需要自己搭建复杂的https服务。

### 目录

*  [1.本期更新（2017.09）](#1-本期更新-201709)
*  [2.JS脚本基本内容](#2-js脚本基本内容)
 *  [2.1固定写法部分](#21-固定写法部分)
 *  [2.2开发者编写基本内容handlers](#22-开发者编写基本内容handlers)
 *  [2.3语音交互中对应配置](#23-语音交互中对应配置)
* [3.response配置项](#3-response配置项)
 * [3.1setBaseInfo相关配置](#31-setbaseinfo配置基础信息)
 * [3.2setSession相关配置](#32-setsession配置session信息)
 * [3.3setTts相关配置](#33-settts配置tts信息)
 * [3.4setMedia相关配置](#34-setmedia配置media信息)
 * [3.5setConfirm相关配置](#35-setconfirm配置confirm信息)
 * [3.6setCard相关配置](#36-setcard配置card信息)
 * [3.7setPickup相关配置](#37-setpickup配置pickup信息)
* [4.在Rokid对象中封装的工具](#4-在rokid对象中封装的工具)
* [5.关于调试](#5-关于调试)
* [6.关于日志](#6-关于日志)
* [7.Sample](#7-sample)
* [8.Q&A](#8-qa) 

### 1. 本期更新-2017.09
- request（异步请求）原本需要严格按照npm提供的方式，参数放在options.qs里，现兼容请求参数全放在url上如http://xxx.com/xxx?key=xxx&league=xxx。
- 考虑到sync_request与request的功能重叠，且存在兼容性问题，因此取消了sync_request。
- session改为key:object类型。

### 2. JS脚本基本内容
开发者可以利用编写JS脚本实现各自所需的技能意图函数实现不同的功能。

### 2.1 固定写法部分
这部分如没有特别需求，所有开发者都可以通用如下代码：

``` javascript
exports.handler = function(event, context, callback) {
    var rokid = Rokid.handler(event, context,callback);
    rokid.registerHandlers(handlers);
    rokid.execute();
};
```

我们通过Rokid对象封装了一些工具供大家使用。

 - 首先，通过Rokid.handler(event, context, callback)来使用Rokid-sdk。
 - 接下来，我们需要处理我们技能意图（intent），通过rokid.registerHandlers()以简单来注册您所需的技能意图。
 - 最后，通过rokid.execute()触发技能意图。
 
以上三步是必须的。

#### 2.2 开发者编写基本内容handlers

其中handlers，为大家所要写的意图技能处理函数，在“配置”编写js脚本，最基本写法比如：

``` javascript
var handlers = {
    'ttsSample': function () {
        try {
            this.setTts({
                tts: 'Hello World!'
            });
            //正常完成意图函数时emit(':done')
            this.emit(':done');
        } catch (error) {
            //报错时调用emit(':error', error)
            this.emit(':error', error);
        }
    },
    'mediaSample': function () {
        try {
            this.setMedia({
                type: 'AUDIO',
                url: 's.rokidcdn.com/temp/rokid-ring.mp3'
            });
            //正常完成意图函数时emit(':done')
            this.emit(':done');
        } catch (error) {
            //报错时调用emit(':error', error)
            this.emit(':error', error);
        }
    },
    'confirmSample': function () {
        try {
            this.setTts({
                tts: 'Hello World!'
            });
            this.setConfirm({
                confirmIntent: 'confirmIntent',
                confirmSlot: 'confirmSlot'
            });
            //正常完成意图函数时emit(':done')
            this.emit(':done');
        } catch (error) {
            //报错时调用emit(':error', error)
            this.emit(":error", error);
        }
    }
};
```

this.emit(':done'):表示信息配置完成，即返回response。
this.emit(':error', error):表示程序中出错，返回错误信息。
与1.0版本中的callback左右相似，拆分为更容易理解的以上两种结束语句。
**依然要着重注意this的指向问题。**

#### 2.3 语音交互中对应配置
"ttsSample"与"mediaSample"对应于"语音交互"中的intent如下：

``` javascript
{
    "intents": [
        {
            "intent": "ttsSample",
            "slots": [],
            "user_says": [
                "你好"
            ]
        },

        {
            "intent": "mediaSample",
            "slots": [],
            "user_says": [
                "播放"
            ]
        },
        {
            "intent": "confirmSample",
            "slots": [],
            "user_says": [
                "询问"
            ]
        }
    ]
}
```

"语音交互"的intent，slot等request信息可在Rokid.param（下文有介绍）中获取。

### 3. response配置项
2.0.0版本
开发者response配置方式更新，可根据需求分步骤set。
目前支持：setBaseInfo, setSession, setTts, setMedia, setConfirm, setCard, setPickup

| 配置方式  |   意图 |
| :-------- | :--: |
| setBaseInfo | 配置response的基础信息，如执行类型，任务插入方式等 |
| setSession | 配置session，可在下一次request时携带上的session信息 |
| setTts | 配置要播放的语句的相关信息（tts） |
| setMedia | 配置要播放的媒体流的相关信息（media） |
| setConfirm | 配置询问，多轮交互的相关信息（confirm） |
| setCard | 配置授权相关信息（card） |

#### 3.1 setBaseInfo配置基础信息

```javascript
this.setBaseInfo({
	type: 'NORMAL',
	form: 'cut',
	shouldEndSession: true
});
```

##### 开发者相关字段（setBaseInfo）
 
无必填字段。

| 字段       |   类型 | 必要性 | 默认值 | 可选值 |
| :-------- |--------:| ---:| --: | :--: |
| type | string | 选填 | NORMAL | NORMAL/EXIT |
| form | string | 选填 | cut| scene/cut/service |
| shouldEndSession | boolean | 选填 | true | true/false |

#### 3.2 setSession配置session信息

```javascript
this.setSession({
	sessionKey: {
		key: value
	}
});
```

##### 开发者相关字段（setSession）

setSession时完全自定义，可根据开发者需求自定义key-object键值对。

#### 3.3 setTts配置tts信息

```javascript
this.setTts({
	action: 'PLAY',
	disableEvent: false,
	itemId: 'xxx',
	tts: 'xxx'
});
```

##### 开发者相关字段（setTts）

setTts时"tts"属性必填且为string或number类型,可为空字符串。

| 字段       |   类型 | 必要性 | 默认值 | 可选值 |
| :-------- |--------:| ---:| --: | :--: |
| action | string | 选填 | PLAY | PLAY/PAUSE/RESUME/STOP |
| disableEvent | boolean | 选填 | false| true/false |
| itemId | string | 选填 | 无 | 不限 |
| tts | string/number | 必填 | 无 | 不限(值可为空字符串) |

#### 3.4 setMedia配置media信息

```javascript
this.setMedia({
	action: 'PLAY',
	disableEvent: false,
	itemId: 'xxx',
	token: 'xxx',
	type: 'AUDIO',
	url: 'media streaming url',
	offsetInMilliseconds: 0
});
```

##### 开发者相关字段（setMedia）

setMedia时"type"和"url"均必填且为string类型。
 
| 字段       |   类型 | 必要性 | 默认值 | 可选值 |
| :-------- |--------:| ---:| --: | :--: |
| action | string | 选填 | PLAY | PLAY/PAUSE/RESUME/STOP |
| disableEvent | boolean | 选填 | false| true/false |
| itemId | string | 选填 | 无 | 不限 |
| token | string | 选填 | 无 | 不限 |
| type | string | 必填 | 无 | AUDIO/VIDEO |
| url | string | 必填 | 无 | 不限 |
| offsetInMilliseconds | number | 0 | 毫秒数值 |

#### 3.5 setConfirm配置confirm信息

```javascript
this.setConfirm({
	confirmIntent: 'xxx',
	confirmSlot:'xxx',
	optionWords: []
});
```


##### 开发者相关字段（setConfirm）

setConfirm时"confirmIntent"和"confirmSlot"均必填且为string类型。
 
| 字段       |   类型 | 必要性 | 默认值 | 可选值 |
| :-------- |--------:| ---:| --: | :--: |
| confirmIntent | string | 必填 | 无 | 对应于相关语音交互 |
| confirmSlot | string | 必填 | 无 | 对应于相关语音交互 |
| optionWords | array | 选填 | 无 | 不限 |

#### 3.6 setCard配置card信息

```javascript
this.setCard('ACCOUNT_LINK');
```


##### 开发者相关字段（setCard）

setCard的参数为string类型，目前仅支持ACCOUNT_LINK。

#### 3.7 setPickup配置pickup信息

```javascript
this.setCard({
	enable: true,
	durationInMilliseconds: 1000
});
```

##### 开发者相关字段（setPickup）

setPickup时。

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| enable | boolean | 无（必填）| true/false |
| durationInMilliseconds | number | 6000（选填）| 0至6000 |

具体字段定义可参见：<https://rokid.github.io/docs/3-ApiReference/cloud-app-development-protocol_cn.html#3-response>

### 4. 在Rokid对象中封装的工具

##### 开发者可直接调用封装在Rokid对象中的所有工具方法，现有如下：
- Rokid.handler(event,contxt,callback):用于调用Rokid-sdk。
- Rokid.request(options,callback):异步请求，具体使用方法参见<https://www.npmjs.com/package/request>。
- Rokid.param:可根据“集成测试”中服务请求的数据结构获取一些数据。如：
	- slots：Rokid.param.request.content.slots
	- intent: Rokid.param.request.content.intent
	- session: Rokid.param.session.attributes
	- userId: Rokid.param.context.user.userId（只有在设备上测试才能获取，集成测试中获取不到）
- Rokid.dbServer:开发者可用此对象中的get，set，delete方法进行数据增删改查。
	- get:Rokid.dbServer.get(key, callback); key必须为string类型
	- set:Rokid.dbServer.set(key, value, callback); key,value必须为string类型。key值开发者可自定义（若每个用户都可能存取数据，则推荐使用userId）。
	- delete:Rokid.dbServer.delete(key,callback); key必须为string类型

数据存取基本操作如下：

``` javascript
var handlers = {
    'set':function() {
        var data = JSON.stringify([0,1,2,3,4]);//字符串存入数据库
        Rokid.dbServer.set('user001',data, (error, result) => {
            if(error) {
            		//错误处理
            		this.emit(':error', error);
            }else{
            		this.setTts({tts: result});
	          		this.emit(':done');
            }
        });
    },
    'get':function() {
        Rokid.dbServer.get('user001', (error, result) => {
            if(error) {
            		//错误处理
            		this.emit(':error', error);
            }else{
            		result = JSON.parse(result);//根据取出的数据进行处理
            		this.setTts({tts: result});
            		this.emit(':done');
            }
        });
    },
    'delete':function() {
        Rokid.dbServer.delete('user001', (error, result) => {
            if(error) {
            		//错误处理
            		this.emit(':error', error);
            }else{
            		this.setTts({tts: result});
	          		this.emit(':done');
            }
        });
    }
};
```

### 5. 关于调试
在“配置”页里，目前已支持单点测试，仅测试js应用脚本正确性。

 * 配置测试用例，其中的intent和slot是需要开发者在默认用例基础上对应于“语音交互”中作相应调整。
 * 调试结果中将测试用例作为request，response和log日志则是根据应用脚本产出的真实结果。

确保js应用脚本的正确性情况下，可在“集成测试”页中进行全链路集成测试。
脚本需要第三方请求时，可先通过Postman进行请求模拟，严格按照Postman的nodejs-request的code进行请求。

### 6. 关于日志
- 在应用脚本中可调用console.log()输出你想要看的日志。
- 须保证在“命中语音指令”的情况下才可查看日志。
- 此日志仅是应用脚本执行的日志，不包括其他链路的日志。
- 尽量在脚本中采用try-catch中调用callback传回状态，详细参见本文sample。

### 7. Sample

```javascript
var data = [
    "床前明月光，疑是地上霜，举头望明月，低头思故乡。",
    "白日依山尽，黄河入海流，欲穷千里目，更上一层楼。",
    "千山鸟飞绝，万径人踪灭，孤舟蓑笠翁，独钓寒江雪。",
    "松下问童子，言师采药去，只在此山中，云深不知处。",
    "向晚意不适，驱车登古原，夕阳无限好，只是近黄昏。"
];


exports.handler = function(event, context, callback) {
    var rokid = Rokid.handler(event, context,callback);
    rokid.registerHandlers(handlers);
    rokid.execute();
};

var handlers = {
    'LaunchRequest': function () {
	    //这里不是意图函数完成的地方，因此不是this.emit(":done"),而是触发另一个函数
        this.emit('GetNewFactIntent');
    },
    'GetNewFactIntent': function () {
	    try{
	        var factIndex = Math.floor(Math.random() * data.length);
	        var speechOutput = factArr[factIndex];
	        //配置tts信息
	        this.setTts({tts:speechOutput});
	        this.emit(':done');
		}catch(error){
			this.emit(':error', error);
		}
    },
    'NewsRequest': function () {
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
                self.emit(':error', error);
            }
            JSON.parse(body).forEach(function (item) {
            //根据返回结果进行不同处理。在此返回的一个数组，因此forEach处理。
                ttsRes += item + ',';
            });
            self.setTts({ tts: ttsRes });
            self.emit(':done');
        });
    },
    'MediaRequest': function () {
	    try{
			this.setMedia({ type: 'AUDIO', url: 's.rokidcdn.com/temp/rokid-ring.mp3' });
			this.emit(':done');
		}catch(error){
			this.emit(':error', error);
		}
    },
    'confirmRequest': function () {
        try {
	        //可任意组合任意set方法，此意图为tts和confirm组合
            this.setTts({tts: '欢迎成为Rokid开发者' });
            this.setConfirm({
                confirmIntent: 'question_one',
                confirmSlot: 'question_one_slot',
                optionWords: ['xxx', 'xxx']
            })
            this.emit(':done');
        } catch (error) {
            this.emit(':error', error);
        }
    }
};
```

### 8. Q&A

#### Q：为什么我有时候结果输出的会包含[Object,Object]？
A：需要注意在emit的时候写入{tts:xxx}对象时，xxx必须为string类型，如果object+string就可能出现以上现象。想要输出object的内容须用JSON.stringify()将其转换为string。

#### Q：为什么我的脚本一直超时？
A：1、脚本允许运行时间为2s，如在2s内未完成则会超时。
2、需要在emit之后立即调用callback。
3、在调用emit及callback时请注意“上下文this”的指向。

#### Q：同步请求处理总是报Unexpected token < in JSON at position 0；？
A：开发者使用的请求地址，其返回体必须是json格式的。比如“http://xx.com/xx.html”这类地址是不可用的。

#### Q：为什么的set和emit没有起效？
A：由于上下文this会在一定情况下改变指向，不再指向window对象，所以失去了set和emit等方法。须注意this的指向是否正确，请使用剪头函数或在函数外定义一个变量保存this即可。

#### Q：为什么request请求总是不成功？
A：首先确保request的所有参数均正确。其次，可用postman进行请求模拟，需要严格按照postman提供的nodejs-request的请求。

### 9. 1.0版本补充说明
为保证以往技能正常运行，1.0版本将继续维护，但可能会滞后于2.0版本的更新。
SDK-V1.0说明文档：<https://rokid.github.io/docs/2-RokidDocument/1-SkillsKit/rokid-js-engine-tutorial-v1.0.html>


