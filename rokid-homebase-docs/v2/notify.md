# 设备状态主动推送

## 流程说明

1. 在开放平台-智能家居-品牌管理-权限管理中开启**上报设备状态**开关。此时会得到平台分配的 clientId，clientSecret。
2. 在用户绑定此品牌时，在 rokid 开放平台智能家居品牌中配置的 endpoint 地址会收到一个`AcceptGrant`（具体描述见下文）指令，payload 中会包含 code 和用户在 rokid 的用户 id。
3. 厂商需要按照 OAuth2.0 的标准，携带上一步得到的 code，去 rokid OAuth2.0 [token endpoint](https://tools.ietf.org/html/rfc6749#section-3.2)（地址: [https://oauth-service.rokid.com/oauth/token](https://oauth-service.rokid.com/oauth/token)）换取 access_token,refresh_token (具体描述见 [https://tools.ietf.org/html/rfc6749#section-4.1.3](https://tools.ietf.org/html/rfc6749#section-4.1.3))，然后按照下文协议描述正确响应`AcceptGrant`指令。
4. 厂商需在 token 过期时间以内主动刷新 token，保证 token 永不过期。
5. 厂商状态上报地址为 [https://homebase-openapi.rokid.com/async/events](https://homebase-openapi.rokid.com/async/events)

## AcceptGrant 指令

- **AcceptGrant**

Rokid 向厂商发送`AcceptGrant`指令 (POST)

```json
{
  "header": {
    "namespace": "Rokid.Authorization",
    "name": "AcceptGrant",
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    },
    "payloadVersion": "v1"
  },
  "payload": {
    "grant": {
      "type": "OAuth2.AuthorizationCode",
      "code": "VGhpcyBpcyBhbiBhdXRob3JpemF0aW9uIGNvZGUuIDotKQ==",
      "userId": "12e213e345" //用户在rokid的用户id
    }
  }
}
```

- **AcceptGrant.Response**

权限获取成功后的正常返回

```json
{
  "header": {
    "messageId": "abc-123-def-456",
    "namespace": "Rokid.Authorization",
    "name": "AcceptGrantResponse",
    "payloadVersion": "v1"
  },
  "payload": {}
}
```

> 如果失败，请按协议返回标准错误。

---

## 推送消息类型

消息推送地址 POST [https://homebase-openapi.rokid.com/async/events](https://homebase-openapi.rokid.com/async/events)

当设备状态变化时，支持以下三种异步消息

| 类型                  | 描述                                                                                                                                         |
| :-------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| **ChangeReport**      | 在设备发现接口返回的设备列表中，如果你将设备标记成`proactivelyReported`，那么，在此设备<u>**状态**</u>发生了变化时，应向异步接口发送此消息。 |
| **AddOrUpdateReport** | 当设备新增或者设备<u>**属性**</u>发生变化时，应当向异步接口发送此消息。                                                                      |
| **DeleteReport**      | 当有设备被删除时，应当向异步接口发送此消息。                                                                                                 |
| **EventSource**       | 当事件源类型设备触发事件时，应当向异步接口发送此消息。                                                                                       |
| **Response**          | 通用 Response。在异步通知中一般用作非实时控制的响应。例如控制耗时较长的设备。                                                                |

- **ChangeReport**

```json
{
  "header": {
    "messageId": "abc-123-def-456",
    "namespace": "Rokid",
    "name": "ChangeReport",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    }
  },
  "endpoint": {
    "endpointId": "appliance-001",
    "additionalInfo": {
      "key1": "value"
    },
    "states": [
      {
        "interface": "Switch",
        "value": "On",
        "timeOfSample": "2018-03-15T18:00:00.000Z"
      },
      {
        "interface": "Color",
        "value": 12345,
        "timeOfSample": "2018-03-15T18:00:00.000Z"
      }
    ]
  },
  "payload": {
    "change": {
      "cause": {
        "type": "PHYSICAL_INTERACTION"
      },
      "states": [
        {
          "interface": "Switch",
          "value": "On",
          "timeOfSample": "2018-03-15T18:00:00.000Z"
        }
      ]
    }
  }
}
```

- **AddOrUpdateReport**

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Discovery",
    "name": "AddOrUpdateReport",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    }
  },
  "payload": {
    "endpoints": [
      {
        "endpointId": "开发者自己定义的终端Id",
        "displayName": "大米台灯,",
        "displayType": "light",
        "recommendRoomName": "厨房",
        "recommendHomeName": "杭州的家",
        "additionalInfo": {
          "key1": "value"
        },
        "capabilities": [
          {
            "interface": "Switch",
            "supportedOperations": ["On", "Off"],
            "proactivelyReported": true,
            "retrievable": true
          },
          {
            "interface": "Color",
            "supportedOperations": ["Set"],
            "proactivelyReported": true,
            "retrievable": true
          }
        ],
        "states": [
          {
            "interface": "Switch",
            "value": "On",
            "timeOfSample": "2018-03-15T18:00:00.000Z"
          },
          {
            "interface": "Color",
            "value": 12345,
            "timeOfSample": "2018-03-15T18:00:00.000Z"
          }
        ]
      }
    ]
  }
}
```

- **DeleteReport**

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Discovery",
    "name": "DeleteReport",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    }
  },
  "payload": {
    "endpoints": [
      {
        "endpointId": "endpointId-1"
      },
      {
        "endpointId": "endpointId-2"
      }
    ]
  }
}
```

- **EventSource** (DoorbellPress 每次按下抬起为一次事件 )

```json
{
  "header": {
    "messageId": "9eac4fa2-9de0-4e75-ac38-9dde79abb1bd",
    "namespace": "Rokid.EventSource",
    "name": "DoorbellPress",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    }
  },
  "payload": {
    "endpointId": "endpoint-001",
    "cause": {
      "type": "PHYSICAL_INTERACTION"
    },
    "timestamp": "2018-06-09T23:23:23.23Z"
  }
}
```

- **Response**

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "access-token"
    },
    "correlationToken": "abcdef-123456" // 关联token
  },
  "endpoint": {
    "endpointId": "开发者自己定义的终端Id",
    "additionalInfo": {
      "key1": "value"
    },
    "states": [
      {
        "interface": "Color",
        "value": 12344
      }
    ]
  },
  "payload": {}
}
```

## Q&A

### 如何开启此功能？

> rokid 开放平台-智能家居-品牌管理-基础信息-权限管理-上报设备状态 打开。

### 老用户如何迁移？

> 开关打开后，新绑定的用户自动拥有此功能；老用户需被告知重新绑定即可。

### 当 access_token 失效并且 refresh 不成功时，该如何做？

> 为了保证良好的用户体验，我们需要一种机制让用户在*状态上报链路*失效时感知到。
> 为此我们提供了接口 ~~[https://homebase-openapi.rokid.com/report/failed](https://homebase-openapi.rokid.com/report/failed)~~ (WIP **_暂未完成_**)
> 当 access_token 失效并且不能成功刷新时，厂商应当将`AcceptGrant`指令带来的 userId，和自身 clientId 上报告知 rokid，rokid 会选择合适的方式通知用户（包括在 rokid App 内发送通知、短信通知等）。
> 上报请求举例：

``` 
POST /report/failed HTTP/1.1
Host: homebase-openapi.rokid.com
Content-Type: application/x-www-form-urlencoded

userId=2erf3gfeg3gt&clientId=SplxlOBeZQQYbYS6WxSbIA&sign=3sdfsfesdfeffffffffff
```

> 签名算法：Hmac, sha256
> 代码举例（nodejs）

```javascript
const crypto = require("crypto");

function sign(data, secret) {
  const hmac = crypto.createHmac("sha256", secret);
  hmac.update(data);
  return hmac.digest("hex");
}

sign(
  "userId=2erf3gfeg3gt&clientId=SplxlOBeZQQYbYS6WxSbIA",
  "the_client_secret"
);
```
