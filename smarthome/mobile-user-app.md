# Rokid 智能家居 H5 配置界面

## 特性介绍

@绍铨

## 准备工作

1. 通过 [Rokid Mobile SDK 接入文档](https://rokid.github.io/mobile-sdk-android-docs/) 集成 SDK 到您的应用中

2. 实现使用智能家居模块所**必需**的 SDK webbridge 方法：[智能家居 H5 接入指南](https://rokid.github.io/mobile-sdk-android-docs/res/skill/homebase.html)、[WebBridge 快速接入指南](https://rokid.github.io/mobile-sdk-android-docs/res/71_use_bridge.html)


## 常见问题

Q: 配置设备完成按钮点击无效

A: 请确认 "准备工作2" 中的工作已经完成

Q: 前端日志抓取步骤：


1. 打开手机的开发者模式（请自行搜索开发者模式打开方式）

	在系统设置中找到开发者选项，并点击进入
    ![alt_text](https://s.rokidcdn.com/homebase/upload/Byn5u506m.png "image_tooltip")




2. 打开手机的 USB 调试功能
![alt_text](https://s.rokidcdn.com/homebase/upload/B1qpOcApX.jpeg "image_tooltip")
3. 手机通过数据线连接电脑，并选择USB传输文件选项
![alt_text](https://s.rokidcdn.com/homebase/upload/S1VlK9R6X.png "image_tooltip")
4. 打开 Chrome 浏览器，输入网址 `chrome://inspect/#devices`
![alt_text](https://s.rokidcdn.com/homebase/upload/Syf7FcRaQ.png "image_tooltip")

5. 点击 https://s.rokidcdn.com/homebase/rokid/index.html#/homes/index 打开新页面
![alt_text](https://s.rokidcdn.com/homebase/upload/ryx2BF9AaQ.png "image_tooltip")

6. 选择 console 栏目查看日志
7. 出错时，保留现场，点击刷新，将日志截图，发送到群里
