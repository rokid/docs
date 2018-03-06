# 蓝牙相关代码目录：

buildroot/package/aml\_brcm\_bsa:博通模组厂商提供的代码包，主要是mk file和config.in文件

vendor/broadcom/brcm-bsa：以上代码包实际所包含的代码所在

rokid\_br\_external/package/btflinger：蓝牙的service的代码包，主要是mk file和config.in文件，相关启动脚本

robot/services/btflinger：以上代码包实际所包含的代码所在

```shell
├── api                              接口文件
│   ├── bluetooth_msgque.c
│   └── btflinger_api.c
├── include                          接口相关头文件
│   ├── bluetooth_msgque.h           
│   └── btflinger_api.h              
├── src                              service源代码，启动脚本。 源代码暂时不开放，只提供bin文件
│   ├── bsa_server_service_ctl.sh
│   ├── btflinger
│   └── bt_service_ctl.sh
└── test                             模块测试文件，接口的调用方法可以参考此文件
    └── bluetooth_test.c
```

# 更新代码后如果发生编译通不过或者运行时错误的情况：

* 删掉 output/banban\_m\_a113/build/aml\_brcm\_bsa-0107\_00.26.00/
* 删掉 output/banban\_m\_a113/build/btflinger/
* 再重新make

# 如果模组相同，只是迁移平台：

将相关代码目录直接覆盖过去即可：

buildroot/package/aml\_brcm\_bsa

vendor/broadcom/brcm-bsa

rokid\_br\_external/package/btflinger

robot/services/btflinger

## 如果模组切换，则还需要增加的步骤：

修改robot/services/btflinger/src/bsa\_server\_service\_ctl.sh

![](/files/bluetooth/fw.png)

将红框处的路径修改成新的模组的固件的路径即可

注意：目前只支持在博通的模组间切换，如果是非博通的模组目前暂时不支持。

## 如果厂商需要定义自己的 BLE 的 UUID：

修改rokid\_br\_external/configs/rokid\_common\_packages.frag文件

![](/files/bluetooth/uuid.png)

## 如何确认蓝牙服务已经正常：

ADB shell中敲入以下命令：

* systemctl stop btflinger
* btflinger\(此时会有log出现，可以检查是否出错）

重新开一个adb shell窗口，敲入：

* bluetooth\_test

  然后会有列表显示出来，可以选择各个接口进行验证（需要和 应用开发--&gt; C/C++ ---&gt; 蓝牙）章节联系起来一起理解，分析

Exa\(测试BLE是否正常\)：

* 在bluetooth\_test中，选择：

* 1. ble

* 2. ble rsp

* 手机上用BLEdebuger软件搜，能搜到my bt ble test device这个设备，点进去，会看见3个服务。选择第3个服务，点进去，选择write， 填入字符

* bluetooth\_test界面会打印出收到的字符。如果和填入的字符匹配，就证明BLE服务层没有问题。



