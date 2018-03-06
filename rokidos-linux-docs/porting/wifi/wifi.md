# WiFi服务

 WiFi 网络提供了一个网络检测服务，来判断当前的 WiFi 连接状态，同时这也是运用上述 API 实现的一个 demo，当检测到网络断开时，会通过 dbus 的通信协议向 ams 上报网络断开消息。

wifi_monitor 代码路径: robot/services/wifi_monitor

流程图如下：

![wifi_monitor](../../files/wifi_monitor.png)
