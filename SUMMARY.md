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
        * [Rokid Force - JS v2.0 使用指南](2-RokidDocument/1-SkillsKit/rokid-force-js-tutorial.md)
        * [SSML 使用指南](2-RokidDocument/1-SkillsKit/ssml-document.md)
        * [Rokid Oauth 使用指南](2-RokidDocument/1-SkillsKit/rokid-oauth.md)
        * [获取 SSL 证书指南](2-RokidDocument/1-SkillsKit/get-SSL-certificate-tutorial.md)
        * [技能开发 Java 版指南](https://github.com/Rokid/rokid-skill-sample/tree/master/rokid-skill-sample-java)
    * 规范与协议
        * [Rokid 云端技能协议](3-ApiReference/cloud-app-development-protocol_cn.md)
        * [技能发布标准](4-TermsAndAgreements/rokid-skill-release-standard.md)
        * [技能审核规范](4-TermsAndAgreements/rokid-skill-examine-and-verify-standard.md)
    * [读取语音交互日志](2-RokidDocument/1-SkillsKit/test-skill-through-device-log.md)

* Rokid 智能家居技能接入
  * [什么是智能家居 Skill](rokid-homebase-docs/README.md)
  * 如何接入
    * [通过公网提供服务](rokid-homebase-docs/connect/cloud-to-cloud.md)
    * [通过局域网 SSDP 自动发现](rokid-homebase-docs/connect/via-lan.md)
  * 智能家居协议(Beta)
    * [技能授权](rokid-homebase-docs/connect/rfc6749.md)
    * [消息格式参考](rokid-homebase-docs/v2/message-reference.md)
    * 提供接口
        * [搜索发现 Discovery](rokid-homebase-docs/v2/discovery.md)
        * [终端控制 Control](rokid-homebase-docs/v2/control.md)
        * [终端查询 Query](rokid-homebase-docs/v2/query.md)
    * 终端描述
      * [终端](rokid-homebase-docs/v2/endpoint.md)
      * [终端类型](rokid-homebase-docs/v2/endpoint-type.md)
      * [终端能力与状态](rokid-homebase-docs/v2/rokid-interface.md)
    * [当发生了错误](rokid-homebase-docs/v2/error-response.md)
  * 智能家居 JSON RPC 协议
    * [局域网自动发现](rokid-homebase-docs/connect/ssdp-auto-discovery.md)
    * [JSON RPC 控制协议](rokid-homebase-docs/connect/json-rpc-over-tcp.md)
  * 如何调试
    * [命令行接口校验工具](rokid-homebase-docs/tools/rhome.md)
    * [开发者驱动](rokid-homebase-docs/tools/developer-driver.md)
  * [Webhook](rokid-homebase-docs/webhook/index.md)
  * 更多文档
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
        * [Homebase OAuth2.0 授权](rokid-homebase-docs/v1/oauth2.0.md)

* 智能设备语音接入平台
    * [智能设备语音接入平台简介](2-RokidDocument/2-EnableVoice/introduction.md)
    * 新手入门
        * [获取认证文件](2-RokidDocument/2-EnableVoice/get-the-certification-file.md)
        * [认证文件的使用方法](2-RokidDocument/2-EnableVoice/usage.md)
    * [重要概念](2-RokidDocument/2-EnableVoice/important-concept.md)
    * 接口文档
        * [语音接口文档](3-ApiReference/openvoice-api.md)
        * [拦截器接口文档](3-ApiReference/rokid-interceptor.md)
        * [设备接口文档](3-ApiReference/open-device-manager.md)
    * SDK 接入指南
        * [Rokid 客户端 SDK 接入指南](3-ApiReference/rokid-client-sdk-doc.md)
        * [Rokid Android SDK 接入指南](2-RokidDocument/2-EnableVoice/android-sdk-tutorial.md)
        * [Rokid Speech SDK 接入指南](https://github.com/Rokid/rokid-openvoice-sdk)
        * [Rokid Mobile SDK Android 接入指南](https://github.com/Rokid/RokidMobileSDKAndroidDemo)
        * [Rokid Mobile SDK iOS 接入指南](https://github.com/Rokid/RokidMobileSDKiOSDemo)
    * [前端降噪API文档](3-ApiReference/siren-api.md)

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
            * [C/C++](development/tutorial-cplusplus.md)
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
