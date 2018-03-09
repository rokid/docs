## Rokid-Force-JS 使用指南V1.0

> 欢迎使用Rokid-Force-JS，很高兴大家可以通过编辑JS脚本来搭建技能服务。
> 您现在阅读的是老版本的文档，我们推荐您使用Rokid-Force-JS v2.0版本进行开发，（[点此查看文档v2.0文档](./rokid-force-js-tutorial.md)）

### 使用JS脚本更快速的开发技能

> 使用JS脚本，我们的目标是帮助您更快速地构建技能，同时可以让您避免不必要的复杂性。使用JS脚本的方式有以下优势：
> - **无需服务器** ：开发者不需要服务器去提供服务。
> - **无需https服务**：开发者不需要自己搭建复杂的https服务。

## 目录

*  [1.JS脚本基本内容](#2-js脚本基本内容)
 *  [1.1固定写法部分](#21-固定写法部分)
 *  [1.2开发者编写基本内容handlers](#22-开发者编写基本内容handlers)
 *  [1.3关于调用callback](#23-关于调用callback)
 *  [1.4语音交互中对应配置](#24-语音交互中对应配置)
* [2.response配置项](#3-response配置项)
 * [2.1tts相关配置](#31-tts相关配置)
 * [2.2ttsWithConfirm相关配置](#32-ttswithconfirm相关配置)
 * [2.3ttsWithCard相关配置](#33-ttswithcard相关配置)
 * [2.4ttsWithPickup相关配置](#34-ttswithpickup相关配置)
 * [2.5media相关配置](#35-media相关配置)
 * [2.6mediaWithConfirm相关配置](#36-mediawithconfirm相关配置)
 * [2.7mediaWithCard相关配置](#37-mediawithcard相关配置)
 * [2.8mediaWithPickup相关配置](#38-mediawithpickup相关配置)
* [3.在Rokid对象中封装的工具](#4-在rokid对象中封装的工具)
* [4.关于调试](#5-关于调试)
* [5.关于日志](#6-关于日志)
* [6.Sample](#7-sample)
* [7.Q&A](#8-qa) 

## 1. JS脚本基本内容
开发者可以利用编写JS脚本实现各自所需的技能意图函数实现不同的功能。

### 1.1 固定写法部分
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
 - 接下来，我们需要处理我们技能意图（intent），通过rokid.registerHandlers( )以简单来注册您所需的技能意图。
 - 最后，通过rokid.execute( )触发技能意图。
 
以上三步是必须的。

### 1.2 开发者编写基本内容handlers

其中handlers，为大家所要写的意图技能处理函数，在“配置”编写js脚本，比如：

``` javascript
var handlers = {
    'ttsSample': function () {
        try {
            this.emit(':tts', {
                tts: 'Hello World!'
            }, {
                    sessionKey: {
                    	key: 'xxx'
                    }
                });
            //正常完成意图函数时callback
            this.callback();
        } catch (error) {
            //报错时callback错误
            this.callback(error);
        }
    },
    'mediaSample': function () {
        try {
            //正常完成意图函数时callback
            this.emit(':media', {
                itemType: 'AUDIO',
                url: 's.rokidcdn.com/temp/rokid-ring.mp3'
            }, {
                    sessionKey: {
                    	key: 'xxx'
                    }
                });
        } catch (error) {
            //报错时callback错误
            this.callback(error)
        }
    },
    'confirmSample': function () {
        try {
            this.emit(':ttsWithConfirm', {
                tts: 'Hello World!',
                confirm: {
                    confirmIntent: 'confirmIntent',
                    confirmSlot: 'confirmSlot'
                }
            }, {
                    sessionKey: {
                    	key: 'xxx'
                    }
                });
            //正常完成意图函数时callback
            this.callback();
        } catch (error) {
            //报错时callback错误
            this.callback(error);
        }
    }
}
```

### 1.3 关于调用callback

**上述中this.callback是在意图函数运行完成后必须调用的，且须注意this的指向。如不调用，则jsEngine将会误认为脚本未执行完毕而导致无法输出结果。**

### 2.4 语音交互中对应配置
"HelloWorldSample"与"MediaSample"对应于"语音交互"中的intent如下：

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

## 2. response配置项
本节讲述开发者在意图函数中最终需要emit最终结果。

### 2.1 tts相关配置

```javascript
this.emit(':tts', {
	tts: 'Hello World!'
}, {
	sessionKey: {
			key: 'xxx'
		}
})
```

上述语法是rokid-sdk用于同步响应对象的“tts”响应方法。注：传入":tts"法的参数对象中tts属性是必须的，且其类型须为string或number！session根据需求选择。

##### 开发者相关字段（tts）

 this.emit(":tts",{},{})第二个参数如下（tts相关信息配置项）：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: |
| type | string |  NORMAL  | NORMAL/EXIT |
| form | string |  cut  | scene/cut/service |
| shouldEndSession | boolean | true | true/false |
| disableEvent | boolean | false | true/false |
| action | string | PLAY | PLAY/PAUSE/RESUME/STOP |
| itemId | string | 无（选填）| 不限 |
| tts | string/number | 无（必填）| 不限 |

 this.emit(":tts",{},{})第三个参数如下（session配置项）：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: |
| sessionKey | string | 无 | 不限 |
| seesionValue | string | 无 | 不限 |

### 2.2 ttsWithConfirm相关配置

```javascript
this.emit(':ttsWithConfirm', {
	tts: 'Hello World!',
	confirm: {
		confirmIntent: 'confirmIntent',
		confirmSlot: 'confirmSlot',
		optionWords: [],
		retryTts: '请重试'
		}
	}, {
		sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（ttsWithConfirm）

 this.emit(":ttsWithConfirm",{},{})第二个参数较tts增加confirm字段即可：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| confirm | object | 无（必填）| 无 |

confirm详细：

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| confirmIntent | string | 无（必填）| 不限 |
| confirmSlot | string | 无（必填）| 不限 |
| optionWords | array | 无（选填）| 不限 |
| retryTts | string | 无（选填）| 不限 |

### 2.3 ttsWithCard相关配置

```javascript
this.emit(':ttsWithCard', {
	tts:'Hello World!',
	card: {
		type: 'ACCOUNT_LINK'
	}
	}, {
	sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（ttsWithCard）

 this.emit(":ttsWithCard",{},{})第二个参数较tts增加card字段即可：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| card | object | 无（必填）| 无 |

card详细：

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| type | string | 无（必填）| ACCOUNT_LINK/CHAT |
| content | string | 无（CHAT时必填）| 不限 |


### 2.4 ttsWithPickup相关配置

```javascript
this.emit(':ttsWithPickup', {
	tts:'Hello World!',
	pickup: {
		enable: true,
		durationInMilliseconds: 6000,
		retryTts: '请重试'
		}
	}, {
	sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（ttsWithPickup）

 this.emit(":ttsWithPickup",{},{})第二个参数较tts增加pickup字段即可：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| pickup | object | 无（必填）| 无 |

pickup详细：

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| enable | boolean | 无（必填）| true/false |
| durationInMilliseconds | number | 6000（选填）| 0至6000 |
| retryTts | string | 无（选填）| 不限 |

### 2.5 media相关配置

```javascript
this.emit(':media', {
		itemType: 'AUDIO',
		url: 's.rokidcdn.com/temp/rokid-ring.mp3'
	}, {
		sessionKey: {
			key: 'xxx'
		}
	})
```

上述语法是rokid-sdk用于同步响应对象的"media"响应方法。注：传入":media"方法的参数对象中"url"和属性"itemType"是必须的！session根据需求选择。

##### 开发者相关字段（media）
this.emit(":media",{},{})第二个参数如下（media相关信息配置项）：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: |
| type | string |  NORMAL  | NORMAL/EXIT |
| form | string |  cut  | scene/cut/service |
| shouldEndSession | boolean | true | true/false |
| disableEvent | boolean | false | true/false |
| action | string | PLAY | PLAY/PAUSE/RESUME/STOP |
| itemId | string | 无（选填）| 不限 |
| token | string | 无 | 不限 |
| itemType(对应文档item里的type) | string | 无（必填）| AUDIO/VIDEO |
| url | string | 无（必填）| 可用媒体流url |
| offsetInMilliseconds | number | 0 | 间于媒体流时间长度 |


this.emit(":media",{},{})第三个参数如下（session配置项）：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: |
| sessionKey | string | 无 | 不限 |
| seesionValue | string | 无 | 不限 |

### 2.6 mediaWithConfirm相关配置

```javascript
this.emit(':mediaWithConfirm',{
	itemType: 'AUDIO',
	url: 's.rokidcdn.com/temp/rokid-ring.mp3',
	confirm: {
		confirmIntent: 'confirmIntent',
		confirmSlot: 'confirmSlot',
		optionWords: [],
		retryTts: '请重试'
		}
	},{
		sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（mediaWithConfirm）

 this.emit(":mediaWithConfirm",{},{})第二个参数较media增加confirm字段即可：
 
| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| confirm | object | 无（必填）|

confirm详细：

| 字段       |   类型 | 默认值 |
| :-------- |--------:| :--: |
| confirmIntent | string | 无（必填）|
| confirmSlot | string | 无（必填）|
| optionWords | array | 无（选填）|
| retryTts | string | 无（选填）| 不限 |

### 2.7 mediaWithCard相关配置

```javascript
this.emit(':mediaWithCard', {
	itemType: 'AUDIO',
	url:'s.rokidcdn.com/temp/rokid-ring.mp3',
	card:{
		type: 'CHAT',
		content: 'xxx'
	}
	}, {
		sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（mediaWithCard）

 this.emit(":mediaWithCard",{},{})第二个参数较media增加card字段即可：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| card | object | 无（必填）| 无 |

card详细：

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| type | string | 无（必填）| ACCOUNT_LINK/CHAT |
| content | string | 无（CHAT时必填）| 不限 |

### 2.8 mediaWithPickup相关配置

```javascript
this.emit(':mediaWithPickup', {
	itemType: 'AUDIO',
	url:'s.rokidcdn.com/temp/rokid-ring.mp3',
	pickup:{
		enable: true,
		durationInMilliseconds: 6000，
		retryTts: '请重试'
			}, {
		sessionKey: {
			key: 'xxx'
		}
	})
```

##### 开发者相关字段（mediaWithPickup）

 this.emit(":mediaWithPickup",{},{})第二个参数较media增加pickup字段即可：
 
| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| pickup | object | 无（必填）| 无 |

pickup详细：

| 字段       |   类型 | 默认值 | 可选值 |
| :-------- |--------:| --: | :--: | 
| enable | bolean | 无（必填）| true/false |
| durationInMilliseconds | number | 6000（选填）| 0至6000 |
| retryTts | string | 无（选填）| 不限 |


具体字段定义可参见：<https://rokid.github.io/docs/3-ApiReference/cloud-app-development-protocol_cn.html#3-response>

## 3. 在Rokid对象中封装的工具

##### 开发者可直接调用封装在Rokid对象中的所有工具方法，现有如下：

可用参数：

| 获取字段       |   获取方式 | 备注 |
| :-------- |--------:| :--: |
| sentence | Rokid.param.request.content.sentence | 用户说的话|
| intent | Rokid.param.request.content.intent | 用户的意图 |
| slot | Rokid.param.request.content.slots | 获取到的是slots的value值 |
| session | Rokid.param.session.attributes | 暂时只支持在设备上测试时获取 |
| userId | Rokid.param.context.user.userId | 暂时只支持在设备上测试时获取 |

可用函数：
- Rokid.handler(event,contxt,callback):用于调用Rokid-sdk。
- Rokid.request(options,callback):异步请求，具体使用方法参见<https://www.npmjs.com/package/request>。
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
                this.emit(':tts',{tts: error});
                this.callback();
            }else{
                this.emit(':tts',{tts: result});
                this.callback();
            }
        });
    },
    'get':function() {
        Rokid.dbServer.get('user001', (error, result) => {
            if(error) {
                this.emit(':tts',{tts: error});
                this.callback();
                return;
            }else{
                result = JSON.parse(result);//根据取出的数据进行处理
                this.emit(':tts',{tts: result[0]});
                this.callback();
            }
        });
    },
    'delete':function() {
        Rokid.dbServer.delete('user001', (error, result) => {
            if(error) {
                this.emit(':tts',{tts: error});
                this.callback();
                return;
            }else{
                this.emit(':tts',{tts: result});
                this.callback();
            }
        });
    }
};
```

## 4. 关于调试
在“配置”页里，目前已支持单点测试，仅测试js应用脚本正确性。

 * 配置测试用例，其中的intent和slot是需要开发者在默认用例基础上对应于“语音交互”中作相应调整。
 * 调试结果中将测试用例作为request，response和log日志则是根据应用脚本产出的真实结果。

确保js应用脚本的正确性情况下，可在“集成测试”页中进行全链路集成测试。

## 5. 关于日志
- 在应用脚本中可调用console.log( )输出你想要看的日志。
- 须保证在“命中语音指令”的情况下才可查看日志。
- 此日志仅是应用脚本执行的日志，不包括其他链路的日志。
- 尽量在脚本中采用try-catch中调用callback传回状态，详细参见本文sample。

## 6. Sample

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
         this.callback();
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
            //根据返回结果进行不同处理。在此返回的一个数组，因此forEach处理。
                ttsRes += item + ',';
            });
            self.emit(':tts', { tts: ttsRes });
            self.callback();
        });
    },
    'MediaRequest': function () {
     try{
   this.emit(':media', { itemType: 'AUDIO', url: 's.rokidcdn.com/temp/rokid-ring.mp3' });
   this.callback();
  }catch(error){
   this.callback(error);
  }
    }
};
```

## 7. Q&A

#### Q：为什么我有时候结果输出的会包含[Object,Object]？
A：需要注意在emit的时候写入{tts:xxx}对象时，xxx必须为string类型，如果object+string就可能出现以上现象。想要输出object的内容须用JSON.stringify()将其转换为string。

#### Q：为什么我的脚本一直超时？
A：1、脚本允许运行时间为2s，如在2s内未完成则会超时。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2、需要在emit之后立即调用callback。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3、在调用emit及callback时请注意“上下文this”的指向。

#### Q：同步请求处理总是报Unexpected token < in JSON at position 0；
A：开发者使用的请求地址，其返回体必须是json格式的。比如“http://xx.com/xx.html”这类地址是不可用的。

#### Q：为什么request请求总是不成功？
A：首先确保request的所有参数均正确。其次，可用postman进行请求模拟，需要严格按照postman提供的nodejs-request的请求。

### 8. 2.0版本补充说明
希望开发者自行开发时按照V2.0SDK进行开发。
SDK-V2.0说明文档：<https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/rokid-js-engine-tutorial.html>

