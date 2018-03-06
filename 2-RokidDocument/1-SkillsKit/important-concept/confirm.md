## Confirm

当您的技能需要在某些场景下对用户的意图进行确认时（尤其是一些不完整的意图，比如当用户说“我饿了”时，您需要向用户确认他想吃什么东西），您可以使用confirm功能来完成语音交互。

以下是一个例子。
补全用户的不完整意图
当用户在您的技能中说：“若琪，我饿了”这样一个不完整意图时，您希望能够去确认并在用户的帮助下补全这个意图。可以参照如下进行语音交互配置。
```
{
    "intents": [
        {
            "intent": "eat", 
            "slots": [
                {
                    "name": "food", 
                    "type": "list"
                }
            ], 
            "user_says": [
                "!我要吃$food" //注意：Confirm语句前一定要加叹号
            ]
        }, 
        {
            "intent": "confirmeat", 
            "slots": [ ], 
            "user_says": [
                "我饿了"
            ]
        }
    ]
}
```

语音交互流程
以下是上述场景的完整交互流程: 
第一步：当用户说“我饿了”时，交由Rokid Server 处理后，告知技能“我饿了”是confirm类型的用户语句。Request内容如下：
```
{
    "request": {
        "reqType": "intent", 
        "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a", 
        "content": {
            "applicationId": "com.rokid.confirm", 
            "intent": "confirmeat", 
            "slots": { }
        }
    }
}
```
第二步：技能收到Confirm用户语句时，回传Rokid Server Response，内容示例如下：
```
{
    "response": {
        "action": {
            "voice": {
                "action": "PLAY", 
                "item": {
                    "tts": "你要吃什么"
                }
            }
        }, 
        "confirm": {
            "confirmIntent": "eat", 
            "confirmSlot": "food", 
            "optionWords": [
                "西瓜", 
                "桔子"
            ]
        }
    }
}
```
Rokid Server处理消息并向用户询问“你要吃什么”。
第三步：用户回答“我要吃西瓜”，Rokid Server处理消息告知技能{food: 西瓜}。
```
{
    "request": {
        "reqType": "intent", 
        "reqId": "010116000100-ad1f462f4f0946ccb24e9248362c504a", 
        "content": {
            "applicationId": "com.rokid.confirm", 
            "intent": "eat", 
            "slots": {
                "food": "西瓜"
            }
        }
    }
}
```

如何退出confirm
-	若用户回答的内容，不在预设的词表内，则将重复询问用户，总共三次。三次回答均不符合词表内容将退出confirm。
-	若用户不回答任何内容，超过5分钟后将推出confirm
-	若用户想要强制退出confirm，可以通过“退出+技能激活词”的句式退出。
