# 电信集团接入文档

## 方案介绍

* 本方案的目的是为了让厂商快速集成中国电信终端信息上报的能力，并进入电信集团终端产品库。

## 业务介绍

* 电信集团系统端分为两个部分。
    - 1. 上报到天翼终端公司的数据部分。
    - 2. 上报到电信南京平台的开机上报及心跳上报。

## 代码移植流程

####拉取运营商（南京电信）相关代码

* 厂家在自家的 `xml` 里添加电信代码仓库，以 `naboo-20181228-yodaos-telecomnj.xml` 为例如下：

`$ vi .repo/manifests/naboo-20181228-yodaos-telecomnj.xml`

* 添加如下代码到文件中：

`<project name="open-platform/client/china_telecom" path="applications/chinatelecom" revision="d1769449912d788a5e7d16518bce6ddd25285592" upstream="refs/tags/v1.4"/>`

* 添加完之后，保存退出，拉取最新代码：

`$ repo sync`

* 拉取到的代码在 `application/chinatelecom` 目录下。

## 产品编译配置

* 添加以下应用配置，以 `naboo-yodaos` 为例

`$ vi products/rokid/naboo-yodaos/CMakeLists.txt`

添加配置如下：

```
cmake_minimum_required(VERSION 3.0)
project(naboo-yodaos CXX)
include(ExternalProject)

INSTALL(DIRECTORY ./res/media DESTINATION  ${CMAKE_INSTALL_DIR}/opt)
INSTALL(DIRECTORY ./res/light DESTINATION  ${CMAKE_INSTALL_DIR}/opt)
INSTALL(DIRECTORY ./etc/yoda  DESTINATION  ${CMAKE_INSTALL_DIR}/etc)

function(YodaLocalApp NAME)
ExternalProject_Add(${NAME}
  SOURCE_DIR "$ENV{TOPDIR}/../applications/${NAME}"
  CMAKE_ARGS -DCMAKE_INSTALL_DIR=${CMAKE_INSTALL_DIR})
endfunction()

# applications
YodaLocalApp("chinatelecom")
```


## 常见问题

Q：配网时 App 配网失败，设备配网成功？
A：设备的 Mac 地址没有添加到若琪平台，需要先将设备的 Mac 地址进行导入若琪平台，App 再验证时才能拉到这台设备的信息。

Q：南京电信平台数据上报时上报失败？
A：检查设备的 CTEI 码是否为电信非配的范围之内，大多数情况下是因为 CTEI 码不对，常见错误码为 300。


