# 系统升级

根据[系统升级](../../porting/upgrade/upgrade.md)介绍，应用层接口只需写入 misc 分区标志位接口。

## 接口
上层应用程序由 Nodejs 调用，底层提供了 librecovery C库，此库提供了写升级标志的接口，第三方厂商可以根据此进行修改自己的 OTA 升级。

``` c
struct boot_cmd {
    char boot_mode[32];               // 升级模式
    char recovery_path[256];          // 固件路径
    char recovery_state[32];          // 升级状态
};

int get_recovery_cmd_status(struct boot_cmd *cmd);
int set_recovery_cmd_status(struct boot_cmd *cmd);
```

升级需要调用 set_recovery_cmd_status 进入升级模式，参数设置如下：
 1. boot_cmd.boot_mode 设置为 BOOTMODE_RECOVERY ；
 2. boot_cmd.recovery_path 为 OTA 镜像的路径（放在 /data 目录下，注意 OTA 镜像是 rokid_upgrade_package.img ）；
 3. boot_cmd.recovery_state 设置为 BOOTSTATE_READY ；
 
其余状态为 OTA 升级切换使用。 get_recovery_cmd_status 可以获取升级状态, 最终升级完成后，boot_cmd.recovery_state 会变为 BOOTSTATE_OK 。

``` c

#define BOOTMODE_RECOVERY "boot_recovery"

// 升级状态
#define BOOTSTATE_NONE "none"
#define BOOTSTATE_READY "recovery_ready"
#define BOOTSTATE_RUN "recovery_run"
#define BOOTSTATE_OK "recovery_ok"
#define BOOTSTATE_ERROR "recovery_error"

```
