### Rokid.Discovery

#### Discover

搜索用户账号下的所有终端，如真实的设备、虚拟设备、子设备等

##### Response Payload

字段名 | 类型 | 描述
--- | --- | ---
endpoints | `Endpoint[]` | 一组终端描述符，具体终端描述请参考 [终端描述](./endpoint.md)

###### Example Request
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Discovery",
    "name": "Discover",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "payload": {}
}
```

###### Example Response
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "DiscoveryResponse",
    "payloadVersion": "v1"
  },
  "payload": {
    "endpoints": [
      {
        "endpointId": "device:an-id-unique-to-user",
        "displayName": "大米台灯",
        "displayType": "light",
        "recommendRoomName": "厨房",
        "additionalInfo": {
          "key1": "value"
        },
        "capabilities": [
          {
            "interface": "Switch",
            "supportedOperations": [ "On", "Off" ],
            "proactivelyReported": true,
            "retrievable": true
          },
          {
            "interface": "Color",
            "supportedOperations": [ "Set" ],
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
    ],
  }
}
```
