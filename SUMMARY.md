# Summary

* [Rokid 开放平台](README.md)
* Rokid 技能开放平台
    * [技能开放平台简介](2-RokidDocument/1-SkillsKit/platform-introduction.md)
    * 快速入门
        * [准备工作](2-RokidDocument/1-SkillsKit/getting-started/prepare.md)
        * [创建技能](2-RokidDocument/1-SkillsKit/getting-started/create-skill.md)
        * [技能信息](2-RokidDocument/1-SkillsKit/getting-started/skill-information.md)
        * [语音交互](2-RokidDocument/1-SkillsKit/getting-started/voice-interaction.md)
        * [配置](2-RokidDocument/1-SkillsKit/getting-started/configuration.md)
        * [集成测试](2-RokidDocument/1-SkillsKit/getting-started/test.md)
        * [发布](2-RokidDocument/1-SkillsKit/getting-started/publish.md)
        * [隐私与合规](2-RokidDocument/1-SkillsKit/getting-started/private-and-compliance.md)
        * [技能展示](2-RokidDocument/1-SkillsKit/getting-started/skill-store.md)
        * [技能示例代码](2-RokidDocument/1-SkillsKit/skill-sample.md)
    * 重要概念
        * [意图](2-RokidDocument/1-SkillsKit/important-concept/intend.md)
        * [词表](2-RokidDocument/1-SkillsKit/important-concept/word-list.md)
        * [用户语句](2-RokidDocument/1-SkillsKit/important-concept/usersays.md)
        * [confirm](2-RokidDocument/1-SkillsKit/important-concept/confirm.md)
        * [session](2-RokidDocument/1-SkillsKit/important-concept/session.md)
        * [NLP 正则表达式](2-RokidDocument/1-SkillsKit/important-concept/regular-expression.md)
    * 开发指南
        * [Rokid 语音交互设计指南](2-RokidDocument/1-SkillsKit/rokid-voice-interaction-guidelines.md)
        * [Rokid Force System 使用指南](2-RokidDocument/1-SkillsKit/rokid-force-system-tutorial.md)
        * [Rokid Force JS 使用指南](2-RokidDocument/1-SkillsKit/rokid-force-js-tutorial.md)
        * [SSML 使用指南](2-RokidDocument/1-SkillsKit/ssml-document.md)
        * [Rokid Oauth 使用指南](2-RokidDocument/1-SkillsKit/rokid-oauth.md)
        * [获取 SSL 证书指南](2-RokidDocument/1-SkillsKit/get-SSL-certificate-tutorial.md)
        * [技能开发 Java 版指南](https://github.com/Rokid/rokid-skill-sample/tree/master/rokid-skill-sample-java)
    * 调试
        * [基于 VS Code 的 Yeoman & 测试脚本](https://github.com/Rokid/generator-rokid/blob/master/generators/rfs)
    * 规范与协议
        * [Rokid 云端技能协议](3-ApiReference/cloud-app-development-protocol_cn.md)
        * [技能发布标准](4-TermsAndAgreements/rokid-skill-release-standard.md)
        * [技能审核规范](4-TermsAndAgreements/rokid-skill-examine-and-verify-standard.md)
    * [读取语音交互日志](2-RokidDocument/1-SkillsKit/test-skill-through-device-log.md)

* Rokid 智能家居设备接入平台
  * 平台介绍
    * [平台简介](rokid-homebase-docs/README.md)
    * [智能家居设备接入流程](rokid-homebase-docs/intro/flow.md)
    * [名词解释](rokid-homebase-docs/intro/glossary.md)
  * 开发指南
    * [云云对接](rokid-homebase-docs/connect/cloud-to-cloud.md)
    * [局域网对接](rokid-homebase-docs/connect/via-lan.md)
  * 调试
    * [命令行接口校验工具](rokid-homebase-docs/tools/rhome.md)
    * [自定义接入](rokid-homebase-docs/tools/developer-driver.md)
  * 智能家居协议(Beta)
    * [技能授权](rokid-homebase-docs/connect/rfc6749.md)
    * [消息格式参考](rokid-homebase-docs/v2/message-reference.md)
    * 提供接口
        * [搜索发现 Discovery](rokid-homebase-docs/v2/discovery.md)
        * [终端控制 Control](rokid-homebase-docs/v2/control.md)
    * 终端描述
      * [终端](rokid-homebase-docs/v2/endpoint.md)
      * [终端类型](rokid-homebase-docs/v2/endpoint-type.md)
      * [终端能力与状态](rokid-homebase-docs/v2/rokid-interface.md)
    * [当发生了错误](rokid-homebase-docs/v2/error-response.md)
  * 智能家居 JSON RPC 协议
    * [局域网自动发现](rokid-homebase-docs/connect/ssdp-auto-discovery.md)
    * [JSON RPC 控制协议](rokid-homebase-docs/connect/json-rpc-over-tcp.md)
  * 旧版协议
    * [HTTP 远程驱动](rokid-homebase-docs/connect/http-remote-driver.md)
    * 设备描述
      * [设备](rokid-homebase-docs/v1/device/device.md)
      * [设备类型](rokid-homebase-docs/v1/device/type.md)
      * [设备能力与状态](rokid-homebase-docs/v1/device/actions-and-state.md)
      * [设备房间](rokid-homebase-docs/v1/device/room-name.md)
      * [标准错误](rokid-homebase-docs/v1/errors.md)
    * 如何调试
      * [测试 Command 接口](rokid-homebase-docs/tools/oauth-test.md)
    * 其他授权方式
        * [Homebase OAuth 授权](rokid-homebase-docs/v1/oauth.md)
        * [Homebase OAuth2.0 授权](rokid-homebase-docs/v1/OAuth2.0.md)
  * 高级功能
    * [Webhook](rokid-homebase-docs/webhook/index.md)

* Rokid 语音接入平台
    * [平台简介](5-enableVoice/rokid-vsvy-sdk-docs/introduction.md)
    * 新手入门
        * [创建设备流程](5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/create-device.md)
        * [认证文件使用方法](5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/usage.md) 
    * Android 全链路通用方案
        * [概述](5-enableVoice/rokid-vsvy-sdk-docs/fullLink/introduce.md)
        * [SDK 目录结构](5-enableVoice/rokid-vsvy-sdk-docs/fullLink/sdk_dir.md)
        * [快速集成](5-enableVoice/rokid-vsvy-sdk-docs/fullLink/init_quick.md)
        * [API 参考](5-enableVoice/rokid-vsvy-sdk-docs/fullLink/api_voicerecognize.md)
    * Android 基础语音模块
        * [概述](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/introduce.md)
        * [SDK 目录结构](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/sdk_dir.md)
        * [快速集成](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/init.md)
           * [集成前准备](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/init_prepare.md)
           * [语音识别服务快速集成](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/init_speech.md)
           * [语音合成服务快速集成](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/init_tts.md)
        * [API参考](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/api.md)
           * [语音识别服务](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/api_speech.md)
           * [语音合成服务](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/api_tts.md)
        * [示例源码](https://github.com/Rokid/RokidSpeechTTSDemo) 
    * Linux基础架构
        * [概述](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/introduce.md)
        * [目录结构](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/sdk_linux_dir.md)
        * 快速集成
           * [集成前准备](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/init_linux_prepare.md)
           * [开始集成](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/begin_integrate.md)
        * API 接口
           * [语音合成服务](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/linux_tts_api.md)
           * [语音识别服务](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/linux_speech_api.md)
    * 接口文档
        * [拦截器接口文档](3-ApiReference/rokid-interceptor.md)
        * [设备接口文档](3-ApiReference/open-device-manager.md)
        * [Rokid 客户端协议](3-ApiReference/rokid-client-sdk-doc.md)
    * Mobile SDK 接入文档
        * [Rokid Moblie Android SDK](https://rokid.github.io/mobile-sdk-android-docs/)
        * [Rokid Moblie ios SDK](https://rokid.github.io/mobile-sdk-ios-docs/)
    * [重要概念](5-enableVoice/rokid-vsvy-sdk-docs/important-concept.md)
    * [错误码](5-enableVoice/rokid-vsvy-sdk-docs/common/err_code.md)
    * [Json格式配置字串](5-enableVoice/rokid-vsvy-sdk-docs/common/api_json.md) 
    * [云端应用接口开发协议](3-ApiReference/openvoice-api.md)
* Rokid 智能开发套件
    * [智能开发套件简介](rokidos-linux-docs/README.md)
    * 开发套件使用手册
        * [基本参数](rokidos-linux-docs/reference/dev_board/board_list.md)
        * [联网教程](rokidos-linux-docs/source/system_setting/connect_to_internet.md)
        * 编译指南
            * [A113](rokidos-linux-docs/reference/dev_board/amlogic/usermanual_a113.md)
            * [S905D](rokidos-linux-docs/reference/dev_board/amlogic/usermanual_s905d.md)
        * [刷机教程](rokidos-linux-docs/source/downloading_building/burn_image.md)
        * [自定义激活词配置](rokidos-linux-docs/source/system_setting/custom_activation.md)
    * [RokidOS](rokidos-linux-docs/source/getting_started/overview.md)
        * 下载和构建
            * [概览](rokidos-linux-docs/source/downloading_building/requirements.md)
            * [搭建编译环境](rokidos-linux-docs/source/downloading_building/build_env.md)
            * [下载源代码](rokidos-linux-docs/source/downloading_building/downloading_codes.md)
            * [准备构建](rokidos-linux-docs/source/downloading_building/building.md)
        * [设备使用](rokidos-linux-docs/source/system_setting/overview.md)
            * [语音接入配置](rokidos-linux-docs/source/system_setting/openvoice_access_config.md)
        * [设备调试](rokidos-linux-docs/source/develop_debugging/debugging.md)
        * [系统移植](rokidos-linux-docs/porting/overview.md)
            * 音频
                * [概览](rokidos-linux-docs/porting/audio/overview.md)
                * [术语](rokidos-linux-docs/porting/audio/terminology.md)
            * [开机动画](rokidos-linux-docs/porting/bootanim/bootanim.md)
            * [WiFi](rokidos-linux-docs/porting/wifi/wifi.md)
            * [系统升级](rokidos-linux-docs/porting/upgrade/upgrade.md)
            * [蓝牙服务](rokidos-linux-docs/porting/bluetooth/bluetooth.md)
        * [应用开发](rokidos-linux-docs/development/overview.md)
            * [Node.js](rokidos-linux-docs/development/tutorial-nodejs.md)
            * [C/C++](docs/rokidos-linux-docs/development/tutorial-cplusplus.md)
                * [语音合成](rokidos-linux-docs/development/cplusplus/tts.md)
                * [音量控制](rokidos-linux-docs/development/cplusplus/volume_ctrl.md)
                * [多媒体播放](rokidos-linux-docs/development/cplusplus/mediaplayer.md)
                * [灯光效果](rokidos-linux-docs/development/cplusplus/lumenflinger.md)
                * [WiFi控制](rokidos-linux-docs/development/cplusplus/wpa_ctrl.md)
                * [输入服务](rokidos-linux-docs/development/cplusplus/inputflinger.md)
                * [电量查询](rokidos-linux-docs/development/cplusplus/power_ctrl.md)
                * [系统升级](rokidos-linux-docs/development/cplusplus/upgrade.md)
                * [蓝牙](rokidos-linux-docs/development/cplusplus/btflinger.md)
* 硬件设计参考方案
    * [Rokid 语音产品硬件设计指南](2-RokidDocument/2-EnableVoice/rokid-hardware-design-guide.md)
    * [Rokid 硬件交互设计指南](2-RokidDocument/2-EnableVoice/rokid-hardware-ux-design-guidelines.md)
* [服务协议](4-TermsAndAgreements/community-service-agreement.md)
* [免责声明](4-TermsAndAgreements/community-disclaimer.md)
* [联系我们](contact-us.md)
* [Rokid 讨论区](https://developer-forum.rokid.com)
