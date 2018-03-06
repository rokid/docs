## 智能设备语音接入平台
智能设备语音接入平台能够为配有麦克风和扬声器的联网硬件设备开启若琪所提供的智能语音交互能力。用户可以直接使用语音让搭载若琪的设备播放音乐、查天气、播报新闻，以及其他技能（Skill）所提供的各种服务。

### Rokid 语音接入与Rokid 技能
当您的设备接入若琪后，即可使用众多丰富有趣的 Rokid 公有技能，也可以为您的设备创建个性化的私有技能。

## 开始接入
### 1. 注册设备
#### 设备信息
在「开发者社区-->语音接入」中注册您的设备，并完善设备名称、设备图片、设备分类及描述。

#### 认证文件
您需要为您的设备创建一个认证文件，以获取接入若琪的权限。具体方法请查看[获取认证文件](./get-the-certification-file.md)。

### 2. 为您的产品接入Rokid语音能力

#### ① 给您的Rokid ALL in ONE 全栈开发套件刷写代码

- 请参见 [ALL in ONE 开发板 AMLOGIC 905D android代码编译烧写教程](https://developer-forum.rokid.com/t/topic/991)

#### ② 在您的产品中接入Rokid SDK
Rokid开发者社区SDK包含Siren、Speech、NLP、ASR、TTS几大模块。

- Siren：拾音模块，接收HAL的音频数据，算法处理，滤波；
- TTS：文字转语音；
- Speech和ASR：都是语音转文字，不同的是Speech专门处理Siren的语音事件。

通过[Rokid SDK 接入指南](https://developer-forum.rokid.com/t/topic/991)，了解如何快速在您的产品中接入Rokid SDK。

#### 和您的设备做一次互动
您可以创建一个[开始创建第一个技能：讲个笑话](/2-RokidDocument/1-SkillsKit/getting-started/create-skill.md)，并将您的设备添加到此技能的测试设备列表中，就可以与设备进行互动啦。


