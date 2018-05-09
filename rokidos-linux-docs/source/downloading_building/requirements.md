# 要求

下载和编译 RokidOS 源代码之前，请先确保您的系统符合以下要求。然后，请参阅[构建编译环境](build_env.md)，查看适用于相应操作系统的安装说明。

## 硬件要求
您的开发工作站必须达到或超出以下硬件要求：

* 需要使用64位环境，编译需要的空间约20G。

## 软件要求

RokidOS 我们官方的开发环境是在 Ubuntu 14.04.5 LTS (64bits) 版本进行开发测试的，但您也可以使用其他 Ubuntu 发行版本。
您的工作站必须具有下面列出的软件。要查看所需的其他程序包以及用于安装这些程序包的命令，请参阅[构建编译环境](build_env.md)。

## 操作系统

RokidOS 建议您用 GNU/Linux 操作系统进行编译。

GNU/Linux
* Ubuntu 14.04.5 LTS (64bits)
* gcc 4.8.4 及以上

## 其他

* [Buildroot](https://buildroot.org/) 嵌入式开发环境

RokidOS 目前已经支持的Buildroot嵌入式开发环境。

如果您采用的芯片或开发板是Amlogic厂商所提供的，并且您对Buildroot缺乏了解，请先详细阅读 [The Buildroot user manual](https://buildroot.org/downloads/manual/manual.html) 文档。

* [Openwrt](https://openwrt.org/) 嵌入式开发环境

RokidOS 目前正在支持开源社区普遍使用的Openwrt编译框架。

