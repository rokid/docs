# Flash分区及文件系统管理 {#flash}

Kamino18在Linux内核中，引入MTD（Memory Technology Device）层为NOR FLASH和NAND FLASH设备提供统一接口。MTD将文件系统与底层FLASH存储器进行了隔离。

![](assets/flash.png)