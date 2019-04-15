### 在语音合成系统中使用SSML
语音合成标记语言（Speech Synthesis Markup Language, SSML）是一种基于XML的标记语言，用于提供语音合成的文本注释。用户通过给输入文本加上SSML中预先定义的标签，可以很好地指导合成器按照其需求进行操作。在接收到完整的SSML输入后，语音合成引擎对文本所有标签进行解析，再在标签的指导下合成合成声音。
如果您需要对TTS进行诸如插入停顿、音频、改变多音字读音、改变语速、改变发音人等更加灵活的自定义，可以使用下述的语音合成标签。

### 目录
- [在语音合成系统中使用SSML](#%E5%9C%A8%E8%AF%AD%E9%9F%B3%E5%90%88%E6%88%90%E7%B3%BB%E7%BB%9F%E4%B8%AD%E4%BD%BF%E7%94%A8ssml)
- [目录](#%E7%9B%AE%E5%BD%95)
- [如何在您技能的Response中使用SSML](#%E5%A6%82%E4%BD%95%E5%9C%A8%E6%82%A8%E6%8A%80%E8%83%BD%E7%9A%84response%E4%B8%AD%E4%BD%BF%E7%94%A8ssml)
- [目前可使用的SSML标签](#%E7%9B%AE%E5%89%8D%E5%8F%AF%E4%BD%BF%E7%94%A8%E7%9A%84ssml%E6%A0%87%E7%AD%BE)
  - [audio](#audio)
    - [将音频文件转换为Rokid可用的格式](#%E5%B0%86%E9%9F%B3%E9%A2%91%E6%96%87%E4%BB%B6%E8%BD%AC%E6%8D%A2%E4%B8%BArokid%E5%8F%AF%E7%94%A8%E7%9A%84%E6%A0%BC%E5%BC%8F)
  - [break](#break)
  - [lang](#lang)
  - [mark](#mark)
  - [p](#p)
  - [phoneme](#phoneme)
  - [prosody](#prosody)
  - [s](#s)
  - [say-as](#say-as)
  - [speak](#speak)
  - [sub](#sub)
  - [voice](#voice)
  - [token/w](#tokenw)
  - [sing](#sing)
    

### 如何在您技能的Response中使用SSML
直接在返回的TTS中加入SSML格式，完整Voice Response协议请查看[Rokid 技能协议文档Voice部分](3-ApiReference/cloud-app-development-protocol_cn.md)。

```json
"item": {
    "tts": "<speak>Rokid TTS语音支持SSML。</speak>"
}
```

下面是一个更加完整的SSML文档示例：
```html
<speak>
<s>hello 大家好，我是若琪，我现在支持语音合成标记语言啦！</s>
<s>现在我们给大家展示一下，我的超能力！</s>
<s>首先我给大家展示一下文本正则的能力。</s>

<p>
  <!--基数词朗读-->
  <s>读基数词是这样：</s>
  <s>昨天逛超市花了<say-as interpret-as="cardinal">316</say-as>块，</s>
  <s>其中，买菜花了<say-as interpret-as="number">56</say-as>块。</s>

  <!--序数词朗读-->
  <s>读序数词是这样：</s>
  <s>你的房号是<say-as interpret-as="digits">666</say-as>，</s>

  <!--电话号码朗读-->
  <s>读电话号码是这样：</s>
  <s>电话号码是<say-as interpret-as="telephone">+8615220539251</say-as>。</s>

  <s>当然我还可以做文本替换，比如：</s>
  <s>今天的比分是四<sub alias="比">：</sub>二。</s>
  <s>我喜欢吃<sub alias="橘子">你想吃的水果是？</sub>，他喜欢吃<sub alias="香蕉">他呢？</sub>。</s>
</p>

<p>
  <s>接下来，我给大家展示一下我对分词控制的能力。</s>
  <s>比如这句话：</s>
  <s>南京市长江大桥</s>
  <s>我可以强制控制分词，从而来影响韵律的预测：比如，我把“市长”两个字分割到一起，就可以读成：</s>
  <s>南京<w>市长</w>江大桥</s>
</p>

 <s>接下来，我给大家展示一下对注音控制的能力。</s>

<p>
  <s>在中文有很多多音字，对我来说太难了，我可能会读不对，比如下面这一句</s>
  <s>人要行，干一行行一行，行行都行。要是不行，干一行不行一行，行行不行。</s>
  <s><break time="0.5s"/>是不是读得很差劲？</s>
  <s>所以在这个注音的接口里，你可以指导我让我正确的发音，像下面这样：</s>
  <s>人要行，干一行<phoneme alphabet="py" ph="xing2">行</phoneme>
  一<phoneme alphabet="py" ph="hang2">行</phoneme>，
  行行都行。要是不行，干一<phoneme alphabet="py" ph="hang2">行</phoneme>
  不行一<phoneme alphabet="py" ph="hang2">行</phoneme>，行行不行。</s>
</p>

<s>接下来，嘀嗒给大家展示一下韵律控制的能力。</s>

<p>

  <s>我可以在句子里强制加不同级别的停顿，比如说读古诗：</s>
  <prosody rate="slow">
  <s>
    明月<break strength="weak"/>几时有，<break strength="medium"/>
    把酒<break strength="weak"/>问青天，<break strength="medium"/>
    不知<break strength="weak"/>天上宫阙，<break strength="medium"/>
    今夕<break strength="weak"/>是何年！<break strength="medium"/>
  </s>

  <s>
    我欲<break strength="weak"/>乘风归去！<break strength="medium"/>
    又恐<break strength="weak"/>琼楼玉宇，<break strength="medium"/>
    高处<break strength="weak"/>不胜寒。<break strength="medium"/>
    起舞<break strength="weak"/>弄清影，<break strength="medium"/>
    何似<break strength="weak"/>在人间。
  </s>
  </prosody>
  
</p>

<s>接着，我给大家展示一下对音量、音高、语速的控制能力。</s>
<p>
  <s>这句话是普通音量。</s>
  <s><prosody volume="x-loud">第二句话增加了音量。 接下来</prosody>,<prosody rate="x-slow">语速会变慢。</prosody></s>
  <s>我还可以把我的音调变高。</s>
  <s><prosody pitch="x-high">比如这样</prosody></s>
  <s>但同样可以降低.</s>
  <s><prosody pitch="low">变成这样。</prosody></s>
</p> 

<s>最后，唱一首快乐的歌曲送给你！</s>

<sing tempo="120" tone="0">
  
  <s pd="A3 0.25;C4 0.25;C4 0.25;A3 0.25;G4 0.5;E4 0.5;E4 1.5">
  大王叫我来巡山
  </s>
  
  <s pd="A3 0.25;E3 0.25;A3 0.25;A3 0.25;C4 0.25 A3 0.25;G3 0.25 A3 0.25;G3 1.5">
  我把人间转一转
  </s>

  <s pd="A3 0.25;A3 0.25;G3 0.25;A3 0.25;E3 0.25 G3 0.25 A3 0.5;A3 0.25;A3 0.25;G3 0.25;A3 0.25;G4 0.25 E4 0.25">
  打起我的鼓敲起我的锣
  </s>
  
  <s pd="D4 0.25;D4 0.25;D4 0.25;C4 0.25;G4 0.5;G4 0.25 E4 0.25;D4 1.5">
  生活充满节奏感
  </s>

  <s pd="A3 0.25;C4 0.25;C4 0.25;A3 0.25;G4 0.5;E4 0.5;E4 0.75 D4 0.25 C4 1">
  大王叫我来巡山
  </s>
  
  <s pd="A3 0.375;G3 0.125;A3 0.25;G3 0.25;G3 0.25 E3 0.25;C3 0.25 D3 0.25;G3 1.5">
  抓个和尚做晚餐
  </s>

  <s pd="G3 0.5;A3 0.24;A3 0.25 G3 0.25;A3 0.25;E3 0.25 G3 0.75;A3 0.25;G3 0.5;A3 0.25;G4 0.5 G4 0.5">
  这山涧的水无比的甜
  </s>
  
  <s pd="D4 0.375;E4 0.125;D4 0.25;C4 0.25;E4 0.5;E4 0.25 D4 0.25;C4 2">
  不羡鸳鸯不羡仙
  </s>

</sing>
</speak>
```

### 目前可使用的SSML标签

#### audio
在合成语音中插入一段音乐。可以包含于除token/w/say-as/sub/break的任意标签。

| 参数  | 可选值                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| :---- | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `src` | 背景音仅支持通过URL提供的`.wav`文件，并且需要满足以下要求。<ul><li>WAV文件必须被放在一个可靠的HTTPS终端中，且HTTPS域名需要有合法的SSL证书。</li><li>WAV文件不能够含有个性化定制的内容以及敏感内容。</li><li>音频文件的长度需限制在90秒内。</li><li>比特率为16 bit，单声道 mono，采样率为24000 HZ。</li><li>WAV文件头的长度暂时只支持44字节，如果超出，则会出现爆音。</li></ul> 您需要使用[下方推荐的转换工具](https://www.ffmpeg.org/)将音频文件转换为符合上述要求的WAV文件。 |

像如下例子中一样，在TTS回复中用`speak`标签包裹`audio`标签后，您的回复将带有背景音。

```html
<speak>
    欢迎成为Rokid开发者。
    <audio src="s.rokidcdn.com/temp/rokid-ring.wav" /> 
    您会听到一段悦耳的铃声。 
</speak> 
```

注意：

- 单条response中最多只能插入5个音频文件
- 单条response中的所有音频长度加总不能超过90秒。

##### 将音频文件转换为Rokid可用的格式
您需要使用转换工具将需要插入的TTS中的音频转为WAV文件，16 bit，mono 24000HZ。推荐使用开源的命令行工具[FFmpeg](https://www.ffmpeg.org/)。下方的命令可以帮您将`<input-file>`转换为`audio`标签可用的WAV文件。

**MP3转WAV：**

```
ffmpeg -i <input-file.mp3> -acodec pcm_s16le -ac 1 -ar 24000 <output-file.wav>
```

**PCM转WAV：**

```
ffmpeg -f s16le -ar 24k -ac 1 -i <input-file.pcm> <output-file.wav>
```

**MP4转WAV：**

```
ffmpeg -i <input-file.mp4> -acodec pcm_s16le -ac 1 -ar 24000 <output-file.wav>
```

**WAV头部规整：**

如果wav格式符合以上格式，但在播放时最前面有爆音现象，是由于头部长度不是44字节，可以使用另一开源的命令行工具[sox](http://sox.sourceforge.net/)进行修正：
```
sox -r 24000 -e signed -b 16 -c 1 old.wav new.wav
```


#### break
在TTS语句中插入停顿。

| 参数       | 可选值                                                                                                                                                                                                                                                                                                                                                       |
| :--------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `strength` | <ul><li>none: 无停顿。常用于消除默认停顿的部分。</li><li>x-weak: 无停顿。和<code>none</code>效果一致。</li><li>weak: 小停顿，停顿时间比标准停顿更短。</li><li>medium: 标准停顿，相当于逗号的效果。</li><li>strong: 句子停顿。等同于句号以及<code>&lt;s&gt;</code>标签的效果。</li><li>x-strong: 段落停顿。等同于<code>&lt;p&gt;</code>标签的效果。</li></ul> |
| `time`     | 停顿时长，秒（`s`）或者毫秒（`ms`）为单位，最大时长为10s。                                                                                                                                                                                                                                                                                                   |

注意，如果strength和time都没有出现，则默认为strength="medium"。
如果同时输入strength和time，则以time优先。


```html
<speak>
    这句话之后会有3.3秒钟的停顿 <break time="3.3s"/> 
    然后才会继续说。
</speak>
```

#### lang
指定文本朗读的语言。lang的引用场景为可以强制数字或者字母按照英语的方式来朗读。
lang标签可以包含`audio/break/lang/mark/phoneme/prosody/say-as/sub/token/w/voice`标签，
可以包含于`lang/phoneme/prosody/voice`标签。

| 参数       | 可选值                                             |
| :--------- | :------------------------------------------------- |
| `xml:lang` | 指明音标规范 <ul><li>`en-US`: 美式英语。</li></ul> |

```html
<speak>                                         
  数字三十二用英文读是：<lang xml:lang="en-US">32</lang>。
</speak>    

```
#### mark 
用于标记语音合成事件。普通用户对于此项可以忽略，仅对TTS发音音素二次开发用户有用。
在语音合成中，外部用户可能需要和语音合成引擎同步。因此需要知道当前合成的位置，并通知调用者mark事件的发生。

| 参数   | 可选值                                                                                                                         |
| :----- | :----------------------------------------------------------------------------------------------------------------------------- |
| `name` | mark事件的名字，用户可以自定义名字以及名字信息编码。合成引擎负责在语音合成流中生成一个mark事件，并通过回调通知用户事件的发生。 |

```html
                                   
<speak>大家好，<mark name="action:beckoned"/>我是若琪。今天<mark name="emotion:happy"/>好开心啊！
</speak>    
```

#### p
表示一个段落。将会在段尾为TTS语音插入一个强停顿，等同于`<break strength="x-strong">`。如果用户没有为文本包裹`p`标签，合成
引擎会自动决定是否加`p`标签。如果加了`p`标签，合成引擎时会在段落之后加入段落停顿。
P标签可包含`audio/break/lang/mark/phoneme/prosody/say-as/sub/s/t/voice`标签，不能被除`speak`以外的标签包含。


```html
<speak>                                         
    <p>这是第一段话。说完之后将会停顿一会。</p>       
    <p>这是第二段话。</p> 
</speak>    
```

#### phoneme
指明标签内文本的读音。读音长度需和文本长度一致。目前仅支持带调汉语拼音，拼音之间用左斜杠隔开。 `phoneme`标签不可以包含任何标签，只能包含文本；可以包含于`speak/p/s/lang/prosody/lang/voice/w/token`标签。

| 参数     | 可选值                                    |
| :------- | :---------------------------------------- |
| alphabet | 指明音标规范 <ul><li>py: 拼音。</li></ul> |
| ph       | 音标的具体序列。                          |

```html
<speak>
    我的指甲又 <phoneme alphabet="py" ph="zhang3/chang2">长长</phoneme>了。 
</speak>   
```

#### prosody
用于修改音量，音高和语速。
`prosody`标签可以包含如下标签：`audio/break/lang/mark/p/phoneme/prosody/say-as/sub/s/token/w/voice`.
可以包含于如下标签：
`speak/p/s/prosody/voice`。
注意：如果有多个`prosody`嵌套，那么每个属性的具体取值由相应文本的最内层属性决定。

| 参数     | 可选值                                                                                                                                                                                                                                   |
| :------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `rate`   | 语句的发音速度 <ul><li>枚举值：`x-slow, slow, medium, fast, x-fast`</li><li>百分比：按照指定的百分比来增加或者降低说话速度：<ul><li>100% 表示无变化</li><li>50%表示减速到正常速度的一半</li><li>200%表示提速到正常速度的两倍</li></ul>   |
| `pitch`  | 语句的语调 <ul><li>枚举值：`x-low, low, medium, high, x-high`</li><li>相对百分比：<ul><li>通过使用+n%或者-n%的方式来增加或者降低音高x个百分点。注意：“%”符号是必须的，但是“+/-”不是必须的。</li><li>0%表示无变化</li></ul>           |
| `volume` | 声音的高低 <ul><li>枚举值：`silent, x-soft, soft, medium, loud, x-loud`</li><li>相对值(分贝)：<ul><li>+ndB表示调高音量n分贝，-ndB表示降低音量n分贝。注意：“`dB`”符号是必须的，但是“+/-”不是必须的。</li><li>+0dB表示无变化</li></ul> |

```html
<speak>
    这句话是普通音量。
    <prosody volume="x-loud">第二句话增加了音量。</prosody>。
    <prosody volume="+6dB">这句话增加音量为原来的一倍。</prosody>
    <prosody volume="-6dB">这句话减少到原来的一半。</prosody>
    接下来, <prosody rate="50%">语速会变慢一半</prosody>。
    <prosody rate="200%">接着会变快一倍</prosody>。
    我还可以把我的音调变高。 
    <prosody pitch="+30%"> 比如这样。 </prosody>，
    但同样可以降低， <prosody pitch="-30%">变成这样</prosody>。
</speak>  
```

#### s
表示一个句子。将会在句后插入一个停顿。
等同于：

- 在句末加入句号`。`
- 插入一个停顿 `<break strength="strong"/>`

对于`s`标签之外的文本，引擎会按照标点符号进行切分，并自动将内容添加到一个新的`s`节点下面。
`s`标签可以包含`audio/break/emphasis/lang/mark/phoneme/prosody/say-as/sub
/token/w/voice`标签，可以包含于`speak/prosody/p/lang/voice`标签。
```html
<speak>
    <s>这是一个句子</s>
    <s>刚才你听到了停顿</s> 
    这个句子句末的句号将提供相同的停顿效果。
</speak> 
```


#### say-as
为单词或语句指定以何种方式进行发音。
`say-as`不可以包含任何标签，只能包含文本；可以包含于`speak/p/s/prosody/lang/voice`标签。

| 参数           | 可选值                                                                                                                                                                                                                                                              |
| :------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `interpret-as` | <ul><li>`cardinal, number`: 按数值发音。比如“316”，将读作“三百一十六”。</li><li>`digits`: 按数字串发音。比如“666”，将读作“六六六”。</li><li>`telephone`: 按电话号码发音。比如“+8613568457845”，将读作“加八六，幺三五，六八四五，七八四五。”。</li></ul> |

```html
<speak>
    昨天逛超市花了<say-as interpret-as="cardinal">216</say-as>块。
    你的房号是 <say-as interpret-as="digits">666</say-as>。
    电话号码是<say-as interpret-as="telephone">+8615220539251</say-as>。
</speak> 
```

#### speak
所有SSML文档所`必需的根标签`，该标签有且仅能有一个，其他标签和文本都在该标签以内。`speak`可以包含`p/s/token/word/w/sayas/phoneme/break/prosody/mark`标签。

```html
<speak>
    这句话是没有任何SSML语法的效果。
</speak> 
```

#### sub
将指定的单词或句子替换为特定的读音，需要搭配 `alias`参数来使用。
`sub`不可以包含任何标签，只能包含文本；可以包含于`speak/p/s/prosody/lang/voice`标签

| 参数    | 可选值                       |
| :------ | :--------------------------- |
| `alias` | 为指定的单词或句子替换读音。 |

```html
<speak>
    今天的比分是4 <sub alias="比">：</sub>2。 
</speak> 
```

#### voice
使用不同的发音人进行发音。
允许的内层标签为：
`audio/break/lang/mark/p/phoneme/prosody/say-as/sub/s/token/w/voice`.

| 参数   | 可选值                                                                                                            |
| :----- | :---------------------------------------------------------------------------------------------------------------- |
| `name` | <ul><li>normal: 正常若琪。</li><li>robot: 机器人。</li><li>sweet: 甜美女生。</li><li>crayon: 蜡笔小新。</li></ul> |

```html
<speak>
    接下来出场的是蜡笔小新，
    <voice name="crayon">大家好，我是蜡笔小新</voice>。 
</speak> 
```

#### token/w
使指定的词组不被拆分,以保证不会有停顿。
注意：不能在一个分词内部有中英混的情况,否则会出现词中部分类容不发音的情况。

```html
<speak>
    这双<w>球鞋</w>是C罗送给我的。 
</speak> 

```

#### sing
通过指定发音的时长和音高让TTS唱出歌曲。

| 参数    | 可选值                                                                   |
| :------ | :----------------------------------------------------------------------- |
| `tempo` | 唱歌时，每分钟的拍子数，单位为`BPM`（beats per minute）                  |
| `tone`  | 用来调整整体音高，单位为半音（`semitone`）取值从-12到12。0代表正常音高。 |
为了给每句歌词的每个汉字指定音高和时长（也即是歌谱），需要在`s`标签中给`pd`(pitch/duration)属性赋值。具体规则是：
使用‘;’把pd的值分隔成很多段，各段按先后顺序一一对应文 字信息里面的各个音节(syllable)。曲谱和文字的对应关系是以syllable为基准的。汉语里面，通常每个汉字就 是一个syllable。英语里面，每个单词可能有多个syllable，但每个syllable里 有且只有一个元音。
每一个‘;’之间的内容是描述调值(Tone)和拍子数(Duration)。例如： ‘C4 0.5’代表半拍的1(do)：C4表示1(do)，0.5表示半拍。中间都要用空格格开。如果是空拍子，调值应该写“`NL`”。

```html
<speak>
<sing tempo="120",tone="0">

<s pd="G3 0.5;G4 0.5;F4 0.5;F4 0.5;E4 0.5;D4 0.5;D4 0.5;D4 0.5;D4 0.5 D4 1;E4 1;G3 1;NL 1">
我从来不曾抗拒你的魅力
</s>

<s pd="C4 0.5;G4 0.5;F4 0.5;F4 0.5;E4 1;C4 0.5;D4 1;E4 0.5;D4 0.5 D4 1;NL 1">
虽然你从来不曾对我着迷
</s>

</sing>
</speak>
```



