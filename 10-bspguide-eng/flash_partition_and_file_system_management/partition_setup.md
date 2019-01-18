## Partition Setup {#partition-setup}

K18 Flash partition is setup in uboot as below：

$(K18DIR)/uboot/include/configs/leo_k18_universal.h

#define KERNEL_SIZE_NAND 0x500000

#define CONFIG_KERNEL_OFFS 0x500000

#define CONFIG_KERNEL_SIZE KERNEL_SIZE_NAND

#define CONFIG_FDT_ADDR 0x10000100

#define CONFIG_FDT_OFFS 0x280000

#define CONFIG_FDT_SIZE 0x80000

#define CONFIG_OTA_OFFS 0xA00000

#define CONFIG_OTA_SIZE 0x800000

#define CONFIG_FDT_IMAGE &quot;leo_k18_universal.dtb&quot;

#define CONFIG_ROOTFS_OFFS 0x1200000

#define CONFIG_ROOTFS_SIZE 0x3200000

#define CONFIG_ROOTFS_POS 9

#define CONFIG_MEM_SIZE 127

#define CONFIG_PSTORE_MEM_ADDRESS 0x17f00000

#define CONFIG_PSTORE_MEM_SIZE 0x100000

/* * mtd partitioning for serial NOR/NAND flash

*

* device &lt;spinand_mcu&gt;, # parts = 10

* #: name size offset mask_flags

* 0: mcu 0x00100000 0x00000000 0

* 1: uboot-stage1 0x00040000 0x00100000 0

* 2: uboot_env 0x00040000 0x00140000 0

* 3: uboot-stage2 0x00080000 0x00180000 0

* 4: boot_music 0x00080000 0x00200000 0

* 5: kernel_dtb 0x00080000 0x00280000 0

* 6: misc 0x00200000 0x00300000 0

* 7: kernel 0x00500000 0x00500000 0

* 8: ota 0x00800000 0x00A00000 0

* 9: rootfs 0x03C00000 0x01200000 0

* 10: data 0x03200000 0x04E00000 0 * */

#define MTDIDS_NOR &quot;spi32766.1&quot;

#define MTDIDS_NAND &quot;spinand_mcu&quot;

#define MTDPARTS_DEFAULT &quot;mtdparts=${mtdids_default}:&quot; \

&quot;1m(mcu),&quot; \

&quot;256k(uboot_stage1),&quot; \

&quot;256k(uboot_env),&quot; \

&quot;512k(uboot_stage2),&quot; \

&quot;512k(boot_music),&quot; \

&quot;${fdt_size}@${fdt_offs}(kernel_dtb),&quot; \

&quot;2m(misc),&quot; \

&quot;${kernel_size}@${kernel_offs}(kernel),&quot; \

&quot;${ota_size}@${ota_offs}(ota_kernel),&quot; \

&quot;${rootfs_size}@${rootfs_offs}(rootfs),&quot; \

&quot;60m(data)&quot;

Note:

When partition is modified, the image burning script file $(K18DIR)/openwrt/target/linux/leo/k18-universal/download.sh also need be modified for partition start offset changing：

# partition start address

MCU_OFFSET=0x0

SPL_OFFSET=0x100000

UBOOT_OFFSET=0x180000

BOOTMUSIC_OFFSET=0x280000

KERNEL_DTB_OFFSET=0x300000

MISC_OFFSET=0x380000

KERNEL_OFFSET=0x480000

OTA_OFFSET=0x980000

ROOTFS_OFFSET=0x1180000

DATA_OFFSET=0x3A00000

FLASH_SIZE=0x8000000