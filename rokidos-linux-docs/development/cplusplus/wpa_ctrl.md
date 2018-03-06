# WiFi控制

RokidOS 将一些常用 WiFi 控制函数已经封装成接口，并提供通用API方便开发者进行扩展。

## STATION 模式API

现有基本上所有的 Linux 内核嵌入式 WiFi 设备都支持 wpa\_supplicant 进行 WiFi STATION 模式的管理和配置。所以 RokidOS 也是将 WiFi 控制封装成 wpa\_supplicant 控制接口。第三方开发者也可以移植到其他依赖于 wpa\_supplicant 控制的第三方设备中。代码相关路径位于 robot/external/wpa\_ctrl，常用接口如下：

```c
// connect network ssid : net->ssid psk: net->psk key :net->key_mgmt
int wifi_join_network(struct wifi_network *net);

// join network need reset dhcp
void dhcp_reset();

// save current ssid psk config to wpa_supplicant.conf
int wifi_save_network();

// get current ap signal
int wifi_get_signal(int *sig);

// get current wifi status
int wifi_get_status(int *status);

// get wifi ap list , must after scan 
int wifi_get_scan_result(struct wifi_scan_list *list);

// get current net status by ping taobao
int network_get_status(int *status);

// get list network , return num:1 have configed
int wifi_get_listnetwork(int *num);

// trigger wifi scan 
int wifi_scan();

// get wpa_supplicant monitor socket
int wifi_connect_moni_socket(const char * path);

// get monitor socket data
int wifi_ctrl_recv(char *reply, int *reply_len);

// close monitor socket
void wifi_monitor_release();

// disable network id 
int wifi_disable_network(int *id);

// disable all network
int wifi_disable_all_network();

```

同时我们提供了一个通用接口，上述所有接口均是通过这个接口来实现的。

```c
// current supplicant cmd
enum {
    WIFI_COMMAND_SCAN,
    WIFI_COMMAND_ADDNETWORK,
    WIFI_COMMAND_SETNETWORK_SSID,
    WIFI_COMMAND_SETNETWORK_PSK,
    WIFI_COMMAND_SETNETWORK_KEYMETH,
    WIFI_COMMAND_ENABLENETWORK,
    WIFI_COMMAND_SELECTNETWORK,
    WIFI_COMMAND_RECONFIGURE,
    WIFI_COMMAND_REATTACH,
    WIFI_COMMAND_GET_STATUS,
    WIFI_COMMAND_GET_SIGNAL,
    WIFI_COMMAND_SAVECONFIG,
    WIFI_COMMAND_SCAN_R,
    WIFI_COMMAND_LISTNETWORK,
}WIFI_COMMAND;

int wifi_send_command(int cmd, void *value, int val_len, void *res, int res_len);
```

## AP模式API

对于目前支持 RokidOS 的几款官方开发板，采用的 WiFi 模组是“博通”公司的 AP6255 芯片，“博通”公司的 wifi 芯片 AP 与 STATION 切换需要对网卡驱动进行卸载重装，所以配网方式不建议使用 AP 模式配网，这会造成多次 WiFi 模式的切换，耗时可能比较严重。不过给出以下方法，开发者可以自行配置，进入 AP 模式。

首先，buildroot 需要增加 dnsmasq 的软件包。如果配置对应的 config 文件， 以 A113 来讲，对应路径是: buildroot/configs/banban\_m\_a113\_release\_defconfig。

```shell
BR2_PACKAGE_DNSMASQ=y
BR2_PACKAGE_DNSMASQ_TFTP=y
BR2_PACKAGE_DNSMASQ_DHCP=y
```

如果需要进入 AP 模式，需要依次执行以下命令，对应的 hostapd 和 dnsmasq 没有提供对应的 systemd service 服务文件，开发者如果需要添加，可以参考我们的 supplicant.service 服务进行配置。

```shell
# 关闭 wpa_supplicant 服务和 wifimonitor 服务
systemctl stop supplicant
systemctl stop wifimonitor

# 卸载 WiFi 驱动
rmmod dhd

# 把 WiFi 驱动加载成 AP 模式
multi_wifi_load_driver ap 1

# 构造 WiFi AP 参数，其中 ssid 和 wpa_passphrase 分别对应 SSID 和 密码， 例如此配置文件对应的 SSID 是 rokid，密码是 rokidos_psk
echo "interface=wlan0
driver=nl80211
ctrl_interface=/var/run/hostapd
ssid=rokid
channel=6
ieee80211n=1
ieee80211ac=1

hw_mode=g
hw_mode=a

ignore_broadcast_ssid=0
wpa=3
wpa_passphrase=rokidos_psk
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP CCMP
rsn_pairwise=CCMP"  > /etc/hostapd_temp.conf


# 启动 hostapd (AP 管理软件)
hostapd -B /etc/hostapd_temp.conf

# 配置网卡的 IP 地址
ifconfig wlan0 192.168.2.1

# 启动 dns 和 dhcp 服务， 其中注意 IP 参数要与 IP 地址相对应
dnsmasq -iwlan0  --dhcp-option=3,192.168.2.1 --dhcp-range=192.168.2.50,192.168.2.200,12h -p100
```

## 配网

RokidOS 配套的开发板支持 WiFi 连接 internet ，系统提供了一些控制 WiFi 连接的接口，配网业务及网络监控服务。设备第一次连接网络需要第三方设备发送 WiFi 相关信息如 SSID ， PSK 和加密方式到设备，第一次联网方式支持如下方式：

#### 蓝牙配网

#### AP 模式配网



