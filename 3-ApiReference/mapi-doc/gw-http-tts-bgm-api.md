## 获取背景音乐列表接口文档

### 概述

本文档目的是描述Rokid云背景音乐列表HTTP接口协议，面向想要获取背景音乐列表，并具有一定开发能力的开发者或用户。


### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | https://mapi.open.rokid.com/rest/getBgmList     | 对外提供的正式稳定环境 |


### 协议详解

- 请求认证：在建立http连接时，通过http header authorization 进行权限认证
- 背景音乐列表获取

#### HTTP API 接入参考Demo
```shell
curl -X POST \
--header "Content-Type:application/json" \
--header "Authorization:${Authorization}" \
https://mapi.open.rokid.com/rest/getBgmList
```

**注** `${Authrization}`为您根据[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)得到的字符串

### 协议概述

此协议遵循http协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 https 连接，注意是 **https**，在此基础上进行[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
* service 设置为 getBgmList，此连接后续可进行一次背景音乐列表获取

#### 背景音乐列表获取

##### 请求

1. 需要带包含认证信息的 **authorization** 的 http header [请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
2. 使用 **HTTP POST** 方式
3. 其中 Content-Type 为 **Content-Type:application/json**
4. 请求内容为空

##### 响应

1. 响应是json格式的，字段如下：

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| recode  | string | 返回码  | 
| message | string | 返回描述 | 
| success | bool   | 是否成功 |
| data    | list   | 返回结果集 |

2. data里对象参数详解

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| id     | string | 背景音乐ID  | 
| bgmurl | string | 背景音乐mp3文件地址 | 
| bgmname | string | 背景音乐名称 |

3. 返回码表 

| code 值         | 涵义           |
| ----------------- | -------------- |
| 0000           | 成功 |
| 1000           | 系统异常       |
| 3004           | 验签失败 | 

4. 返回参数示例

```json
{
    "data": [
        {
            "id": "8899576FE6CC1D92E0530100007F2CFA",
            "bgmurl": "https://club.10155.com/wxringpic/1557562775613022692.mp3",
            "bgmname": "第2个",
        },
        {
            "id": "872DF013C0BE5272E0530100007F3048",
            "bgmurl": "https://club.10155.com/wxringpic/1556005104221682472.mp3",
            "bgmname": "正常测试",
        }
    ],
    "recode": "000000",
    "success": true,
    "message": "成功"
}
```
