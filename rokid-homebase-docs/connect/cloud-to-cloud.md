# Homebase 云云对接

## 简介

![云云对接示意图](https://s.rokidcdn.com/homebase/upload/BygMjQZwM.jpg)

智能家居 Skill 对接基于 [智能家居协议](../v2/message-reference.md)

对接步骤：

1. 完成用户授权，授权用户
2. 开发智能家居 Skill, 提供设备列表接口和设备控制接口
3. 完成测试
4. 提交 Skill 信息给 Rokid

## 完成用户授权，授权用户

使用标准 OAuth 2.0 协议接入用户授权

- [标准 OAuth2.0 接入](rfc6749.md)

## 开发智能家居 Skill, 提供设备发现接口和设备控制接口

智能家居 Skill 开发参考 [智能家居协议](../v2/message-reference.md) 来开发, 调试可以使用 [rhome 命令行工具](../tools/rhome.md)

## 测试

填写如下测试用例表格：

[测试用例下载](https://s.rokidcdn.com/homebase/upload/HkOw4tzcf.xlsx)

## 上线

提交智能家居 Skill 给 Rokid （可以通过邮箱： smarthomeconnect@rokid.com ），申请上线到 Rokid 智能品牌列表

- 图标 1024*1024 jpg 格式 方形无圆角
- 厂商名称
- 厂商 app下载地址 (可选)
- Skill 介绍
  - 支持设备列表
  - 服务联系方式
  - 安装配置说明
- 测试报告

想要获取帮助，可以发邮件到如下商务邮箱： `smarthomeconnect@rokid.com`
