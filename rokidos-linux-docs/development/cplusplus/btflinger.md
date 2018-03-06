# btflinger

btflinger是RokidOS提供的蓝牙服务

# 以下为相关的接口：

```
int bluetooth_rokid_open(char *name);//打开蓝牙

int bluetooth_rokid_close(void);//关闭蓝牙

int bluetooth_rokid_use_ble(char *name);//使用BLE服务

int bluetooth_rokid_get_ble_rsp(struct bt_ble_rsp_msg  *message);//获取BLE client端输入的信息

int bluetooth_rokid_use_ble_close(void);//关闭BLE服务

int bluetooth_rokid_use_a2dp_sink(void);/使用a2dp sink服务

int bluetooth_rokid_use_avrcp_cmd(enum bluetooth_avrcp_cmd cmd);//使用avrcp命令,a2dp sink打开之后才可使用

```

以上各个API的参数在接口头文件中有详细说明（btflinger\_api.h\)。

调用的时候需要注意顺序：

```
bluetooth_rokid_use_ble  ---> bluetooth_rokid_get_ble_rsp  ---> bluetooth_rokid_use_ble_close
bluetooth_rokid_open     ---> bluetooth_rokid_use_a2dp_sink---> bluetooth_rokid_close
```

 BLE单独开关接口，只有关掉BLE以后，才可使用其他服务，比如a2dp sink。同理，只有其他服务关闭以后，才能使用BLE。

