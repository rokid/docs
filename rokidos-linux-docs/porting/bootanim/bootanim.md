# 开机动画

开机动画由bootanim进程控制，bootanim开机自动高优先级启动。

bootanim启动后会判断`/var/run/bootcomplete`是否存在，当存在此文件且灯效全部亮起时，自动退出启动效果。

bootanim配置文件位于`/etc/bootanim.conf`下，其中的项目：

* ### max_bright:

    最大亮度，控制灯光最大的亮度。

    default value:100

* ### flash_times:

    闪动次数，每个灯开启过程中熄灭再点亮的次数。

    default value:2

* ### single_delay:

    每次delay时间，主要用于控制灯光持续时间。

    default value:40000 微秒

* ###colorR、colorG、colorB:

    以上三项一起用于控制配置灯光的颜色。

    default value:255、0、255

当配置文件出错时、配置文件不存在或者配置文件中项目不存在时，使用默认值配置。可通过更改配置文件方便地更改开机动画效果。
