# Rokid.Control

执行指定的操作，并返回终端最新状态

#### Example Request
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Control",
    "name": "Color.Adjust",
    "payloadVersion": "1",
    "authentication": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoints": [
    {
      "endpointId": "device:an-id-unique-to-user",
      "additionalInfo": {
        "key": "value"
      },
      "state": [
        {
          "interface": "Color",
          "value": 12345
        }
      ]
    }
  ],
  "payload": {
    "delta": -1,
  }
}
```
#### Example Response
```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid",
    "name": "Response",
    "payloadVersion": "1"
  },
  "endpoints": [
    {
      "endpointId": "device:an-id-unique-to-user",
      "state": [
        {
          "interface": "Color",
          "value": 12344
        }
      ]
    }
  ],
  "payload": {}
}
```
