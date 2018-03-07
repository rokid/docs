## RokidOS 系统移植适配

### 硬件相关
#### 硬件设计相关文档

我们为各位开发者提供了几款硬件开发板的**参考实现**，如果您需要了解或查询硬件配置、原理图、开发板样式等信息，请结合您所使用的硬件设备，到[开发板用户手册](../reference/dev_board/board_list.md)章节了解相应信息。

### 软件相关
#### RokidOS 板级配置体系

为了让开发者、移植适配厂商能简单、快捷的定制开发板，我们构建了一套简洁的板级配置体系。
引入了一套 RokidOS 定义的板级变量及使用规则。如果您打造的设备与 Rokid **参考实现**在硬件选型上有所不同，您可以通过控制板级变量，轻松适配 RokidOS 系统。

#### 系统定义的板级配置变量

**板级变量定义文件位置:** ```buildroot/board/rokid/common/rokidos_config.in```

* **ROKIDOS_BOARDCONFIG_CAPTURE_DEVICEID** <br>
	* 变量类型: **int**<br>
	* 变量默认值: **0**<br>
	* 说明:<br>
		该变量在**麦克风阵列**采集语音数据时，所使用的**设备ID号**与**播放设备号**不相同的情况下使用。<br> 

* **ROKIDOS_BOARDCONFIG_PLAYBACK_DEVICEID**<br>
	* 变量类型: **int**<br>
	* 变量默认值: **0**<br>
	* 说明:<br>
		该变量在**音频播放设备**播发声音时，所使用的**设备ID号**与**麦克风采集设备号**不相同的情况下使用。<br>

* **ROKIDOS_BOARDCONFIG_STORAGE_DEVICETYPE**<br>
	* 变量类型: **int**<br>
	* 变量默认值: **1**<br>
	* 说明:<br>
		该变量设置为0，表示存储设备是MMC设备；变量为1，表示存储设备是NAND设备。<br>

* **ROKIDOS_BOARDCONFIG_MICARRAY_NAME**<br>
	* 变量类型: **string**<br>
	* 变量默认值: **""**<br>
	* 说明:<br>
		该变量用于指定在编译**BlackSiren**库时，选用*resource*目录下的哪个子目录作为**麦克风**及相关算法的配置。<br>

* **ROKIDOS_BOARDCONFIG_BLE_UUID_SERVICEID**<br>
	* 变量类型: **hex**<br>
	* 变量默认值: **0xFFE1**<br>
	* 说明:<br>
		该变量用于指定在编译蓝牙模块时，指定BLE功能的*Service*服务ID值。您可以通过修改该值，使用您自己的 BLE Service ID 。<br>

* **ROKIDOS_BOARDCONFIG_BLE_UUID_CHARACTER**<br>
	* 变量类型: **hex**<br>
	* 变量默认值: **0x2A06**<br>
	* 说明:<br>
		该变量用于指定在编译蓝牙模块时，指定BLE功能的*Character*服务ID值。您可以通过修改该值，使用您自己的 BLE Character ID 。<br>

