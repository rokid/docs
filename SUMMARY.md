# Summary

* [Rokid 开放平台](README.md)
* Rokid 语音整体方案
    * [语音整体方案简介](5-enableVoice/rokid-vsvy-sdk-docs/introduction.md)
    * [语音方案接入流程](5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/rookie-guide.md) 
    * 语音方案介绍
        * [Android 全链路通用方案](5-enableVoice/rokid-vsvy-sdk-docs/fullLink/fulllink.md)
        * [Android 全链路APK级别方案](5-enableVoice/rokid-vsvy-sdk-docs/RokidAiSdk/RokidAiSdk.md)
        * [Android 基础语音模块](5-enableVoice/rokid-vsvy-sdk-docs/speechTTS/speechtts.md)
        * [Linux基础架构](5-enableVoice/rokid-vsvy-sdk-docs/linuxsdk/linuxsdk.md)
    * 语音接入接口文档
        * [拦截器接口文档](3-ApiReference/rokid-interceptor.md)
        * [设备接口文档](3-ApiReference/open-device-manager.md)
        * [Rokid 客户端协议](3-ApiReference/rokid-client-sdk-doc.md)
    * Mobile SDK 接入文档
        * [Mobile SDK 简介](5-enableVoice/rokid-vsvy-sdk-docs/mobliesdk/SDK.md)
        * [Rokid Moblie Android SDK](https://rokid.github.io/mobile-sdk-android-docs/)
        * [Rokid Moblie ios SDK](https://rokid.github.io/mobile-sdk-ios-docs/)
    * 语音接口开发协议
        * [语音websocket接口开发协议](3-ApiReference/openvoice-api.md)
        * [语音http接口开发协议](3-ApiReference/openvoice-api-http.md)
    * 错误码和重要概念
        * [重要概念](5-enableVoice/rokid-vsvy-sdk-docs/important-concept.md)
        * [错误码](5-enableVoice/rokid-vsvy-sdk-docs/common/err_code.md)
        * [Json格式配置字串](5-enableVoice/rokid-vsvy-sdk-docs/common/api_json.md) 

* Rokid 技能开发工具
    * [技能开发工具简介](2-RokidDocument/1-SkillsKit/platform-introduction.md) 
    * 技能创建流程
        * [技能语音交互规范](2-RokidDocument/1-SkillsKit/rokid-voice-interaction-guidelines.md)  
        * 重要概念
           * [意图](2-RokidDocument/1-SkillsKit/important-concept/intend.md)
           * [词表](2-RokidDocument/1-SkillsKit/important-concept/word-list.md)
           * [用户语句](2-RokidDocument/1-SkillsKit/important-concept/usersays.md)
           * [confirm](2-RokidDocument/1-SkillsKit/important-concept/confirm.md)
           * [session](2-RokidDocument/1-SkillsKit/important-concept/session.md)
           * [NLP 正则表达式](2-RokidDocument/1-SkillsKit/important-concept/regular-expression.md)
        * [开发流程](2-RokidDocument/1-SkillsKit/getting-started/creat.md)
        * [自定义功能](2-RokidDocument/1-SkillsKit/more-fuction.md)  
        * 技能审核和上线规范
           * [技能发布标准](4-TermsAndAgreements/rokid-skill-release-standard.md)
           * [技能审核规范](4-TermsAndAgreements/rokid-skill-examine-and-verify-standard.md)
    * 云端技能协议
        * [Rokid 云端技能协议](2-RokidDocument/1-SkillsKit/important-concept/cloud-app-development-protocol_cn.md)
    * 技能开发指南
        * [Rokid Force System 使用指南](2-RokidDocument/1-SkillsKit/rokid-force-system-tutorial.md)
        * [Rokid Force JS 使用指南](2-RokidDocument/1-SkillsKit/rokid-force-js-tutorial.md)
        * [SSML 使用指南](2-RokidDocument/1-SkillsKit/ssml-document.md)
        * [Rokid Oauth 使用指南](2-RokidDocument/1-SkillsKit/rokid-oauth.md)
        * [获取 SSL 证书指南](2-RokidDocument/1-SkillsKit/get-SSL-certificate-tutorial.md)
        * [技能开发 Java 版指南](https://github.com/Rokid/rokid-skill-sample/tree/master/rokid-skill-sample-java)
        * [基于 VS Code 的 Yeoman & 测试脚本](https://github.com/Rokid/generator-rokid/blob/master/generators/rfs)
        * [读取语音交互日志](2-RokidDocument/1-SkillsKit/test-skill-through-device-log.md)

* Rokid 智能家居设备接入
  * 平台介绍
    * [平台简介](rokid-homebase-docs/README.md)
    * [智能家居设备接入流程](rokid-homebase-docs/intro/flow.md)
    * [语控引擎接入流程](rokid-homebase-docs/intro/sdk.md)
  * 开发指南
    * [云云对接](rokid-homebase-docs/connect/cloud-to-cloud.md)
    * [局域网对接](rokid-homebase-docs/connect/via-lan.md)
    * [FAQ](rokid-homebase-docs/faq.md)
  * 如何调试
    * [RHOME 桌面版调试工具](rokid-homebase-docs/tools/rhome-desktop.md)
    * [自定义接入](rokid-homebase-docs/tools/developer-driver.md)
  * 智能家居协议(v2)
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
  * 智能家居协议(v1)
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
        * [基于 JWT 签名的服务端授权](rokid-homebase-docs/connect/rfc7519.md)
  * 高级功能
    * [Webhook](rokid-homebase-docs/webhook/index.md)

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
* Rokid 能力介绍
    * [Rokid 语音识别](6-asrandtts/asr.md)
    * [Rokid 语音合成](6-asrandtts/tts.md)
* [服务协议](4-TermsAndAgreements/community-service-agreement.md)
* [免责声明](4-TermsAndAgreements/community-disclaimer.md)
* [联系我们](contact-us.md)
* [Rokid 讨论区](https://developer-forum.rokid.com)
