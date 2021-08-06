# Rokid.Query

#### Example Request

```json
{
  "header": {
    "messageId": "5f8a426e-01e4-4cc9-8b79-65f8bd0fd8a4",
    "namespace": "Rokid.Query",
    "name": "ReportState",
    "payloadVersion": "v1",
    "authorization": {
      "type": "BearerToken",
      "token": "a-token-from-skill"
    }
  },
  "endpoint": {
    "endpointId": "device:an-id-unique-to-user",
    "additionalInfo": {
      "key": "value"
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
    "name": "Response",
    "payloadVersion": "v1"
  },
  "endpoint": {
    "endpointId": "device:an-id-unique-to-user",
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
  "payload": {}
}
```
