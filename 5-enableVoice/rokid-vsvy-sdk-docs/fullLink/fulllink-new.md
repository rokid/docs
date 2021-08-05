# Rokid语音Android SDK使用文档

## 目录

- [一、概述](#一、概述)
- [二、集成准备](#二、集成准备)
  - [开发者账号注册](#开发者账号注册)
  - [设备注册](#设备注册)
  - [SDK获取](#SDK获取)
- [三、主要API参考](#三、主要API参考)

## 一、概述

语音SDK是语音技能全链路解决方案的核心引擎，通过speech、云端来进行语音语义识别，使用若琪智能音箱语音交互功能，

此SDK面向Android 软件开发工程师，通过封装若琪语音交互协议，简化接入流程，更方便用户接入Rokid AI语音技术，打造一款完美的智能语音交互体验设备。

## 二、集成准备

### 开发者账号注册

Rokid 有自己的开发者账号、社区体系，使用Rokid的技术需要在[Rokid开放平台](https://developer.rokid.com/#/)的注册**开发者账号**，同时可以获取相关技术支持。

### 设备注册

Rokid 语音技术需要硬件设备做承接，相关的硬件信息同时也需要在Rokid开发者网站上进行产品报备。在[Rokid开放平台](https://developer.rokid.com/#/)的控制台的语音接入中，创建对应的产品，Rokid后台会自动生成`Key`、`Secret`、`deviceTypeId`，同时会为每个设备预生成10个测试用的`deviceId(sn)`和`seed`，这些信息会被组合起来做授权认证，保证语音SDK正常初始化。

- **Rokid 开放平台介绍** ： https://developer.rokid.com/docs/

- **产品创建及Sn导入** ： https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/rookie-guide-end.html

### SDK获取

1、最新SDK：https://github.com/rokid/RokidVoiceAISDK

2、SDK参考Demo程序：https://github.com/rokid/RokidVoiceAIDemo

## 三、主要API参考

{% urlembed %}
https://leoeco2000.github.io/ActionTest/vai-sdk-docs/java-api/index.html
{% endurlembed %}

{% urlembed %}
https://leoeco2000.github.io/ActionTest/vai-sdk-docs/cxx-api/index.html
{% endurlembed %}

