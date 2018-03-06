# lumenflinger

lumenflinger为灯光服务程序，源码路径:robot\services\lumenflinger
包括以下几个部分:

服务端：RKLumenFlinger.cpp IRKLumen.cpp

客户端：LumenClient.cpp LumenLight.cpp LumenEffects.cpp

其中 LumenLight.cpp、LumenEffects.cpp 为灯光 APP 提供调用接口，下面分别介绍


## LumenLight
class LumenLight提供了控制灯光服务的基本接口

m_platform：用于区别不同设备，实现不同客制化效果

m_frameSize：灯光buffer大小 = m_ledCount * m_pixelFormat

m_ledCount: 灯个数

m_pixelFormat：目前支持的RGB格式，值为3

m_fps：服务端的刷新频率，目前最大30fps,过快刷新灯光数据可能会丢帧


### 接口定义：

- **unsigned char\* lumen_get_data(unsigned char\* buf, int len)**

  功能：获取当前灯光效果的数据


- **void lumen_set_enable(bool cmd)**

  开启：唤醒灯光服务，线程等待写入数据
  
  关闭：此客户端无法对灯光服务操作写入。当客户端所有灯光都关闭时，灯光服务立即进入睡眠
  
  注意：请在设置灯光数据前开启，在设置完数据后(延迟10-20ms)关闭


- **int lumen_draw(unsigned char\* buf, int len)**

  功能：可设置所有灯光。buf所有数据为0则关闭灯


- **int lumen_set_color(unsigned char\* color, int pixelFormat)**
- **int lumen_set_led(int led_num)**

  一组调用，将led_num对应的灯设置为lumen_set_color的颜色，会关闭其他灯。
  
  led_num: 范围0 —— (m_ledCount-1)


- **int lumen_set_color(unsigned char\* color, int pixelFormat)**
- **int lumen_flinger(double angle)**

  一组调用，可将与0号灯相差角度为angle最近的灯设置为lumen_set_color的颜色，会关闭其他灯。






## lumeneffects

lumeneffects基于lumenflinger服务提供了一些简单的灯光效果接口。接口如下：（由LumenEffects.cpp、LumenEffects.h定义）。

### 提供的效果：

- **bool EffectFadeIn\(bool dir,u8 poi,u8 len,u8\* color,int speed\)**

  灯的渐入效果。

  dir:灯渐入方向；

  poi:灯渐入开始的灯（0-11）；

  len:涉及效果的灯的数量；

  color:需要渐入的灯的颜色数组指针，如{100,99,98,10,9,8,3,2,1}代表：

  ```
    第一颗灯：R:100,G:99,B:98
    第二颗灯：R:10,G:9,B:8
    第三颗灯：R:3,G:2,B:1
  ```

  speed:灯的变化速度，每speed微秒变化一次，不建议过快否则会出现反应不及时的问题。

- **bool EffectFadeOut\(bool dir,u8 poi,u8 len,u8\* color,int speed\)**

  灯的渐出效果。

  dir:灯渐出方向；

  poi:灯渐出开始的灯（0-11）；

  len:涉及效果的灯的数量；

  color:需要渐出的灯的颜色数组指针，如{100,99,98,10,9,8,3,2,1}代表：

  ```
    第一颗灯：R:100,G:99,B:98
    第二颗灯：R:10,G:9,B:8
    第三颗灯：R:3,G:2,B:1
  ```

  speed:灯的变化速度，每speed微秒变化一次，不建议过快否则会出现反应不及时的问题。

- **bool EffectPoint\(int degree\)**

  寻向函数的重载，用于调用默认的寻向效果。

- **bool EffectPoint\(int degree,u8_ color\_point,u8 len,u8_ color\_len,int speed\)**

  寻向函数的主函数。

  degree:寻向角度；

  color\_point:寻向灯的颜色，为三位u8的数组的指针，分别保存RGB值；

  len:寻向运动光带涉及灯的数量；

  color\_len:寻向运动光带颜色数组指针，如{100,99,98,10,9,8,3,2,1}代表：

  ```
    第一颗灯：R:100,G:99,B:98
    第二颗灯：R:10,G:9,B:8
    第三颗灯：R:3,G:2,B:1
  ```

  speed:寻向效果速度，以us为单位。

- **bool EffectStartRound\(void\)**

  旋转等待的重载，用于调用默认旋转效果。

- **bool EffectStartRound\(int start\_degree,int end\_degree,bool dir,u8 len,u8\* color,int speed,int acc\_spd,int max\_spd\)**

  旋转等待的主函数。

  start\_degree:开始角度；

  end\_degree:停止角度，可用ENDDEGREE\_WAIT占位表示一直旋转；

  dir:旋转方向；

  len:旋转灯效涉及灯的数量；

  color:寻向运动光带颜色数组指针，如{100,99,98,10,9,8,3,2,1}代表：

  ```
    第一颗灯：R:100,G:99,B:98
    第二颗灯：R:10,G:9,B:8
    第三颗灯：R:3,G:2,B:1
  ```

  speed:旋转速度，以us为单位。

  acc\_spd:旋转加速度，以us为单位。

  max\_spd:旋转最快速度，以us为单位。**注意max\_spd在数值上小于speed。**

- **bool EffectEndRound\(void\)**

  停止旋转函数的重载。在当前位置停止旋转。

- **bool EffectEndRound\(int end\_degree\)**

  停止旋转函数。

  end\_degree:停止的角度，`ENDDEGREE_NOW`代表当前位置立即停止，否则输入角度会在指定角度对应的灯停止。

- **bool EffectStop\(void\)**

  停止所有灯效并熄灭所有灯。

### 提供的可用的动画效果接口：

下述所有动画接口可参考上述动画函数的具体实现。

- **void InitLayers\(int speed\)**

  初始图层信息，在目前版本中负责设定动画的延迟，自定义 LED 动画。

- **bool LayerAddBackground\(u8\* color\)**

  将灯光背景设置为color。  
    color:颜色数组的指针，数组需为RGB三位。

- **bool LayerAddGroup\(bool dir,u8 poi,u8 len,u8\* color\)**

  增加一组灯效。

  dir:灯光方向；

  poi:灯光开始位置；

  len:灯光数量；

  color:颜色数组指针，如{100,99,98,10,9,8,3,2,1}代表：

  ```
    第一颗灯：R:100,G:99,B:98
    第二颗灯：R:10,G:9,B:8
    第三颗灯：R:3,G:2,B:1
  ```

- **bool LayerAddPoint\(u8 led\_num,u8\* color\)**

  增加单点灯效。

  poi:灯光开始位置；

  color:颜色数组的指针，数组需为RGB三位。

- **void DelLayers\(void\)**

  删除图层，目前仅在析构函数中调用。

- **bool LayersSetSpeed\(int speed\)**

  重新设定速度。

  speed:us为单位。

- **bool LayersSetLight\(u8 light\)**

  设定所有效果的最高亮度。

  light:\(0-255\)从最暗到最亮。

- **bool LayersShow\(void\)**

  显示所有效果，效果实现完后，必须调用才能够显示。



