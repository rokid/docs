### 电量查询

RokidOS 提供的电量服务依赖于 Amlogic 电池驱动接口。

#### 电量API

RokidOS 提供了一个电池查询接口，可以实时查询当前电量，相关代码路径：robot/external/power\_ctrl

```c
struct power_state {
    int status;              // 电池状态：BATTERY_STATUS_STATE
    int capacity;            // 电池当前容量：
    int health;              // 电池是否正常；BATTERY_HEALTH_STATE
    int present;             
    int voltagenow;          // 电池当前电压
    int voltagemax;          // 电池最大电压
    int voltagemin;          // 电池最小电压
    int currentnow;          // 电池当前电流
};

int power_get_property(struct power_state *state);
```

#### 查询demo

```c
#include "power_ctrl.h"

int main(int argc, char **argv)
{
    struct power_state power;

    memset(&power, 0, sizeof(power));

    while (1) {
        power_get_property(&power);

        printf("power :: status :: %d, capacity :: %d, health :: %d, present :: %d voltagemin :: %d voltagemax :: %d   voltagenow :: %d currentnow :: %d \n", power.status, power.capacity, power.health, power.present, power.voltagemin, power.voltagemax, power.voltagenow, power.currentnow);
        sleep(1);
    }
    return 0;
}
```



