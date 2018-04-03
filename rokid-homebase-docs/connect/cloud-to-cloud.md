# Homebase 云云对接

## 简介

![云云对接示意图](https://s.rokidcdn.com/homebase/upload/BygMjQZwM.jpg)

云云对接基于 [HTTP 远程驱动协议](http-remote-driver.md)

对接步骤：

1. 完成用户授权，授权用户
2. 开发远程驱动, 提供设备列表接口和设备控制接口
3. 完成测试
4. 提交驱动信息给 Rokid

## 完成用户授权，授权用户

使用标准 OAuth 2.0 协议接入用户授权

- [标准 OAuth2.0 接入](rfc6749.md)

## 开发远程驱动, 提供设备列表接口和设备控制接口

远程驱动开发 参考 [远程驱动文档](http-remote-driver.md) 来开发, 调试可以使用 [远程调试驱动](../tools/developer-driver.md)

## 测试

填写如下测试用例表格：

[测试用例下载](https://s.rokidcdn.com/homebase/upload/HkOw4tzcf.xlsx)

## 上线

提交远程驱动给 Rokid （可以通过邮箱： smarthomeconnect@rokid.com ），申请上线到 Rokid 智能品牌列表

- 图标 1024*1024 jpg 格式 方形无圆角
- 厂商名称
- 厂商 app下载地址 (可选)
- 驱动介绍
  - 支持设备列表
  - 服务联系方式
  - 安装配置说明
- 测试报告

想要获取帮助，可以发邮件到如下商务邮箱： `smarthomeconnect@rokid.com`
