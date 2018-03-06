# 多媒体播放

我们事实上对上游芯片厂商自带的播放器方式做了调整。

* Amlogic 芯片 BaseCode<br>
我们禁用了芯片厂商的原生代码的 **libplayer** 包，原因是芯片厂商的播放器是直接使用 ALSA 框架来调用音频播放功能的。
这对我们 RokidOS 平台让多个进程使用音频设备造成阻碍。基于这个因素，我们使用了 RokidOS 开发的媒体播放库 **librplayer** 。
因为我们不使用 Amlogic 原厂的 **libplayer** ，目前的 **librplayer** 是没有支持硬件解码的，是纯软件解码方式。我们后续会尝试将硬件解码功能实现起来。


## **librplayer**

> 目前请各开发者、厂商使用 C++ 接口，C 的接口定义不是很友好，我们会对接口重新设计，但对 C++ 接口是透明的。

### C++ 接口使用说明

* MediaPlayer<br>
媒体播放类的接口与 Android 系统的媒体播放器接口保持一致，主要接口如下：

	* setDataSource<br>
	设置播放源，可以是本地文件或URL地址
	* setListener<br>
	可以设置外部侦听器
	* prepare<br>
	同步等待数据缓冲，以便足够一次播放
	* prepareAsync<br>
	异步数据缓冲，侦听器能接收到 PREPARED 事件，表示缓存Ready，可以调用 start 开始播放
	* start<br>
	调用开始播放
	* stop<br>
	停止播放
	* pause<br>
	暂停播放
	* isPlaying<br>
	是否正在播放
	* seekTo<br>
	跳到指定位置播放
	* getCurrentPosition<br>
	获取当前播放位置(时间)
	* getDuration<br>
	获取媒体的播放长度(时间）
	* reset()<br>
	<br>
	* setLooping<br>
	<br>
	* isLooping<br>
	<br>
