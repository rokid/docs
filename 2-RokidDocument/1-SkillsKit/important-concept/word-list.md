
## 词表

词表是用户与技能交互过程中的一个重要概念，是指某领域词汇的集合。当用户询问北京天气怎么样时，其中北京是城市信息，将北京、天津、上海等所有城市信息集合起来就组成了中国城市的词表。
目前开放平台有自定义词表和预定义词表


### 1. 数字、日期和时间相关
数字的预定义词表。

| 自定义词表类型  | 简介           | 支持语言 |
| ------------- | :-------------:| :-----:|
| ROKID.NUMBER | 阿拉伯数字及汉语数字 |   中文 |
| ROKID.DATETIME_ZH | 描述某年某月某一天      |   中文 |
| ROKID.RECENT_ZH | 描述「近期」的时间词汇    |   中文 |
| ROKID.YEAR_ZH | 描述以「年」为单位的时间词汇 |  中文 |
| ROKID.MONTH_ZH | 以「月」为单位的时间词汇 |  中文 |
| ROKID.DAY_ZH | 以「日」为单位的时间词汇|   中文 |
| ROKID.HOUR_ZH | 描述以「小时」为单位的时间词汇 |  中文 |
| ROKID.MINUTE_ZH | 以「分钟」为单位的时间词汇  |   中文 |
| ROKID.SECOND_ZH | 以「秒」为单位的时间词汇    |   中文 |
| ROKID.TIME_ZH | 描述具体的时间或时间段    |   中文 |



### 2. 常用名词词汇
常用名词的预定义词表。

| 自定义词表类型  | 简介           | 支持语言 |
| ------------- | :-------------:| :-----:|:-----:|
| ROKID.DEVICE_ZH | 家居电器类的词汇  |   中文 |
| ROKID.LAMPS_ZH | 各类灯具词汇  |   中文 |
| ROKID.COUNTRY_ZH | 国家 |   中文 |
| ROKID.WORLDCITY_ZH | 世界城市 |   中文 |
| ROKID.CN_PROVINCE_ZH | 中国省份 |   中文 |
| ROKID.CN_CITY_ZH | 中国城市 |   中文 |
| ROKID.CN_ARE_ZH | 中国县／区 |   中文 |
| ROKID.COLOR_ZH | 颜色 |   中文 |
| ROKID.CURRENCY_ZH | 国际货币单位 |   中文 |
| ROKID.VOICE_ZH | 描述声音、音量的词汇 |   中文 |
| ROKID.EXTRAINFO_ZH | 温度单位 |   中文 |
| ROKID.INFORMATION_ZH | 描述信息的词汇 |   中文 |
| ROKID.ALARM_ZH | 描述闹钟的词汇 |   中文 |
| ROKID.NETWORK_ZH | 描述网络的词汇  |   中文 |
| ROKID.FESTIVAL_ZH | 中外节日    |   中文 |
| ROKID.SOLARTERMS_ZH | 二十四节气    |   中文 |
| ROKID.LUNAR_ZH | 描述农历和公历      |   中文 |
| ROKID.ANIMALYEAR_ZH | 生肖年  |   中文 |
| ROKID.ERAYEAR_ZH | 干支年  |   中文 |
| ROKID.ZONE_ZH | 描述早上、晚上等某个时间段的词汇   |   中文 |
| ROKID.MOVIE | 电影   |   中文 |




### 3. 其他词汇

其他词汇的预定义词表。

| 自定义词表类型  | 简介           | 支持语言 |
| ------------- | :-------------:| :-----:|:-----:|
| ROKID.AH_ZH | 语气词  |   中文 |
| ROKID.ALL_ZH | 描述「所有」的词汇  |   中文 |
| ROKID.YES_ZH | 表示「肯定」的词汇  |   中文 |
| ROKID.NO_ZH | 表示「否定」的词汇  |   中文 |
| ROKID.HIGH_ZH | 描述「高、大、升」等词汇  |   中文 |
| ROKID.LOW_ZH | 描述「低、小、降」等词汇  |   中文 |
| ROKID.NEW_ZH | 描述「新」的词汇  |   中文 |
| ROKID.OLD_ZH | 描述「旧」的词汇  |   中文 |
| ROKID.TRIGGER_ZH | 描述「若琪」的词汇  |   中文 |

在Rokid开发者社区提供的预定义词表之外，开发者可以自定义自己的词表内容。在创建技能过程中的语音交互环节进行添加自定义词表内容，开发者可以把任何可以抽象的内容定义为词表，并在用户语句中通过$ + 词表名称进行调用。比如当您希望定义以下几种用户语句时：
```
我想喝咖啡
我要喝咖啡
我想要喝咖啡
我要喝可乐
我想喝果汁
可以抽象出两个词表：
iwant
我想
我要
我想要
drink
咖啡
可乐
果汁
并通过以下语句统一表达：
$iwant喝$drink
```
需要注意：
•	一个词表内容可以被多个不同的词表名称引用，用于把同一类的值输出到不同的应用场景中。比如在下例中，ROKID.NUMBER_ZH可以被不同的词表名称引用多次，在用户说出两小时十五分钟三十六秒的时候，能够输出
```
slots":{"hour":"两","min":"十五","sec":"三十六"}

 "intents": [
  {
          {
            "intent": "time",
            "slots": [
                {
                    "name": "hour",
                    "type": "ROKID.NUMBER_ZH"
                },
                {
                    "name": "min",
                    "type": "ROKID.NUMBER_ZH"
                },
                {
                    "name": "sec",
                    "type": "ROKID.NUMBER_ZH"
                }
            ], 
    "user_says":[
       "$hour小时",
       "$min分钟",
       "$sec秒",
        ]
  }
 ]
}
```
#### **一个技能中，所有词表内容的值的总数，不能超过10万个**。







