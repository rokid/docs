## Session

Session 为会话的信息，每一次对云端技能发起请求都会产生会话信息，会话的信息和状态由开放平台的系统更新。Session也提供了attributes字段留给云端技能来保存一些上下文信息。具体阐述如下：
```
"session": {
    "sessionId": "D75D1C9BECE045E9AC4A87DA86303DD6",
    "newSession": true,
    "attributes": {
      "key1": {"type":"","value":""}
    }
  }
  ```
| 字段	| 类型	| 可能值 |
| ------------- | :-------------:| :-----:|
|sessionId	| string	| 每次会话的唯一ID，由系统填充
|newSession	|boolean	|true / false (由系统填充)
|attributes	| key-object map	|一个string-object map

- sessionId - 每次会话的唯一ID，由系统填充
- newSession - 向CloudApp表明此次会话是新的会话还是已经存在的会话，true为新会话，false为老会话
- attributes - 为CloudApp提供attributes字段留保存上下文信息的字段，开发者目前只能通过INTENT类型的Request拿到attributes信息，EVENT类型的Reuqest还不能拿到，后续我们会做修改，attributes是一个key-object map 类型数据，开发者可以自定义传key和object，上述json只是一个样例，并不代表完全限制智能传递type和value。


Session目前只能作用在同一Domain下，**切换Domain会清空Session**。此时`newsession` = `true`。`attributes`也会被清空。

### 以问天气为例
当询问天气技能：“今天天气怎么样”时，会开启一个新的session，此时`attributes`为空，`newSession` = `true`，将会发送如下Request给此技能的后端服务：

```json
{
 "context": {
  "application": {
   "applicationId": "xxx"
  },
 },
 "request": {
  "content": {
   "domain": "custom.skill.xxx",
   "intent": "query_weather",
   "slots": {"date":"今天"}
  },
  "reqId": "57792AB32F114788A3E48910FB9CD7BC",
  "reqType": "INTENT"
 },
 "session": {
  "attributes": {},
  "newSession": true
 },
 "version": "2.0.0"
}
```

收到询问天气的请求后，后端服务会给出Response。
在这一步中，开发者需要让后端服务把`city`值插入到Response的`attributes`中，如下：

```json
{
 "response": {
  "action": {
   "shouldEndSession": false,
   "type": "NORMAL",
   "version": "2.0.0",
   "voice": {
    "behaviour": "REPLACE_ALL",
    "item": {
     "tts": "杭州今天的天气很好"
    },
    "needEventCallback": false
   }
  }
 },
 "version": "2.0.0",
 "session": {
        "attributes": {
           "city":"杭州"
        }
    }
}
```

之后，用户继续向天气技能询问：“明天呢？”。
此时Rokid开发者社区会把`attributes`中的city属性带到这次的Request中：

```json
{
 "context": {
  "application": {
   "applicationId": "xxx"
  },
 },
 "request": {
  "content": {
   "domain": "custom.skill.xxx",
   "intent": "query_weather",
   "slots": {"date":"明天"}
  },
  "reqId": "57792AB32F114788A3E48910FB9CD7BC",
  "reqType": "INTENT"
 },
 "session": {
  "attributes": {"city":"杭州"},
  "newSession": false
 },
 "version": "2.0.0"
}
```

以此类推。
但当切换Domain，比如用户说：“我想听一首歌”时，session将会被清空。