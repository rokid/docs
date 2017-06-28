
# Rokid 预定义词表
目前已开放的预定义词表，持续更新中。

## 1 数字、日期和时间相关
数字的预定义词表。

| 自定义词表类型  | 简介           | 支持语言 |
| ------------- | :-------------:| :-----:|
| ROKID.NUMBER_ZH | 阿拉伯数字及汉语数字 |   中文 |
| ROKID.DATE_ZH | 描述某年某月某一天      |   中文 |
| ROKID.RECENT_ZH | 描述「近期」的时间词汇    |   中文 |
| ROKID.YEAR_ZH | 描述以「年」为单位的时间词汇 |  中文 |
| ROKID.MONTH_ZH | 以「月」为单位的时间词汇 |  中文 |
| ROKID.DAY_ZH | 以「日」为单位的时间词汇|   中文 |
| ROKID.HOUR_ZH | 描述以「小时」为单位的时间词汇 |  中文 |
| ROKID.MINUTE_ZH | 以「分钟」为单位的时间词汇  |   中文 |
| ROKID.SECOND_ZH | 以「秒」为单位的时间词汇    |   中文 |
| ROKID.TIME_ZH | 描述具体的时间或时间段    |   中文 |



## 2 常用名词词汇
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
| ROKID.MOVIE_ZH | 电影   |   中文 |




## 3 其他词汇

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


## 4 ROKID.ANY

ROKID.ANY为提供给用户使用的特殊预定义词表，它可以匹配任何非空输入内容。主要用法有：

- 在用户语句中引用。例如，`我想听$any`可以将“听”字之后的任意内容作为词表内容进行歌曲搜索。

### 举个例子
这里是一个播放音乐的意图，示例如下：

	{
		 "intents": [
		  {
          {
            "intent": "playmusic",
            "slots": [
	            {
			        "name":"music"
		            "type":"list_of_music"
				}
                {
                    "name": "any",
                    "type": "ROKID.ANY"
                }
            ], 
		    "user_says":[
			       "我想听$music",
			       "我想听$any"
	        ]
		  }
		 ]
		}

1. 假设「十年」这首歌不在您的`music`词表中，用户说“我想听十年”，将无法通过`我想听$music`命中`playmusic`这个意图。
2. 在引用了`ROKID.ANY`，并添加了`我想听$any`语句之后，“我想听十年”将能够命中`playmusic`意图。并将「十年」作为词表的值传递给您的后端服务。
3. 您可以参考这些命中`any`词表的歌曲，补充到音乐的自定义词表中。


### 注意
- 请勿将ANY作为整句用户语句使用。
- 请勿在词表中引用`ROKID.ANY`这个值。






