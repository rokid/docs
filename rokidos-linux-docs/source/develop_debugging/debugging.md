# 开发调试

这里主要介绍如何进行调试开发板，如系统登录，串口登录，日志查看等

## 系统登录

1. 串口登录（插上 Debug 板上typec 线，此时必须先插上供电口 typec 线）<br>
插上 Debug 板 typec 线，接上串口后，输入用户名:root，密码无，即可登录系统

2. adb 登录（插上开发板电源供电口typec线)<br>
通过命令 adb shell 即可登录
（如果在 windows 系统下 adb shell 找不到可用设备，可前往谷歌下载最新驱动：https://developer.android.com/studio/releases/platform-tools.html#revisions）

## 日志查看
目前系统所有日志由 systemd journalctl 服务来接管，可以通过journalctl -h 来查看该服务用法，常见命令如下：<br>
实时显示所有日志：journalctl -f

实时查看某个服务的日志：如vui服务日志，journalctl -u vui -f

查看内核日志：journalctl -k

## 服务使用

RokidOS 目前使用 systemd 来管理系统所有服务，重要服务如 vui、openvoice_proc pulseaudio 等

重启服务：systemctl restart xxx

使能服务：systemctl enable xxx

停止服务：systemctl stop xxx

详细使用方法可以查看 systemctl -h

## 属性查看
1. 属性查看，如序列号(sn)，seed 号，使用命令: getprop <br>

2. 属性设置，相关命令为 setprop xxx value （注意 ro（只读）属性不能设置）

## 播放／录音

1. 播放（wav文件）
使用 pulseaudio paplay 播放, 直接输入命令 paplay xxx.wav<br>
使用 alsa aplay 播放，由于 pulseaudio 独占了声卡，需要输入如下两条命令：<br>
```
systemctl stop pulseaudio
aplay xxx.wav
```

2. 录音
由于服务 openvoice_proc 独占了录音接口，需要录音输入如下两条命令来：<br>
```
systemctl stop openvoice_proc
arecord -r48000 -f S32_LE -c 8 /data/1.wav
```
