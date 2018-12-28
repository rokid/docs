### 音量控制

这是一个音量控制的接口，可以控制整体音量，也可以控制单个通道的音量。下面是头文件：

```c
#include <vol_ctrl/volumecontrol.h>
```

除了要 `include` 头文件外，还需要链接 `-lrkvolumecontrol.so`。

#### API

```c
int set_all_volume(int vol);
// 设置整体音量接口,参数vol: 音量的大小

int get_all_volume();
// 获取整体音量接口

int set_app_volume(char* name, int vol);
// 设置单个通道音量接口，参数name: 通道名称，vol：音量的大小

int get_app_volume(char* name)
// 获取单个通道音量接口，参数name: 通道名称

```

#### 示例

```c
#include <stdio.h>
#include <strings.h>

#include <vol_ctrl/volumecontrol.h>

int main(int argc, char** argv)
{
    int vol;
    if (argc < 2 || argc > 4) {   
        printf("need one param at least\n");
        return -1; 
    }   
    if (strcmp(argv[1],"setappvolume") == 0)
        set_app_volume(argv[2],atoi(argv[3]));
    else if (strcmp(argv[1],"getappvolume") == 0) { 
        vol = get_app_volume(argv[2]);
        printf("get %s volume:%d\n",argv[1],vol);
    } else if (strcmp(argv[1],"setvolume") == 0) {
        set_all_volume(atoi(argv[2]));
    } else if (strcmp(argv[1],"getvolume") == 0) {
        vol = get_all_volume();
        printf("get volume:%d\n",vol);
    } else {   
        printf("%s {setappvolume <appname> <value> | getappvolume <appname> | setvolume <name> <value> | getvolume }\n"
            , argv[0]);
    }   
    return 0;
}
```
