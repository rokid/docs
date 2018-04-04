# Rokid.Discovery

## Discover

搜索用户账号下的所有终端，如真实的设备、虚拟设备、子设备等

#### Example Request
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Discovery",
    "name": "Discover",
    "payloadVersion": "1",
    "authentication": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "payload": {}
}
```

#### Example Response
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "DiscoveryResponse",
    "payloadVersion": "1"
  },
  "endpoints": [
    {
      "endpointId": "device:an-id-unique-to-user",
      "displayName": "大米台灯",
      "description": "一盏台灯",
      "manufacturerName": "特许贸易公司",
      "modelName": "FA♂︎Q",
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
          "timeOfSample": "20180315T18:00:00.000Z"
        },
        {
          "interface": "Color",
          "value": 12345,
          "timeOfSample": "20180315T18:00:00.000Z"
        }
      ]
    }
  ],
  "payload": {}
}
```
