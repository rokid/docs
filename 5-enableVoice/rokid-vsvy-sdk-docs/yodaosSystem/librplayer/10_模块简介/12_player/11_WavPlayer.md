## 介绍：
WavPlayer 支持只 wav 格式的文件，该播放器是单例模式的，最新的一次播放可以中断上次播放，其设计的主要目是为了快速播放本地 wav 音频文件

## 接口：
1. int prePrepareWavPlayer( const char* fileNames[], int num);
  * 预加载文件到内存，可加载的最大文件数是 10，该接口是可选
  * @param {Array} filenames - 所有预加载文件的路径
  * @param {int} num - 预加载文件数目
   
2. int prepareWavPlayer(constchar* filePath = NULL, const char* tag = NULL,boo    l holdConnect = true);

  * 创建播放器以及创建播放线程
  * @param {string} filename - 要播放的文件名称
  * @param {number} tag -该播放器 stream 的 tag
  * @param {boolean} holdConnect - 是否保持与 pulseaduio 服务端的链接，保持链接需要 2% ～ 3% 的 CPU 消耗

3. void startWavPlayer();
  * 开始播放.
   
4. void stopWavPlayer();
  * 停止播放.


## 测试结果说明 
File| File Size（bytes） |Format| Media Duration（ms）|Delay Time of PulseAudio Playback (ms)
---|---|---|---|---|---|---|---
 awake_01.wav|16610|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb|390|80~90
 awake_02.wav|10992|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|341|75~80
 awake_03.wav|8762|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|271|90~100
 awake_04.wav|6534|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|202|70~80
 awake_05.wav|18886|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|588|80~90
 mic_close_tts.wav|49310|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|1540|80~90
 mic_open.wav|19608|pcm_s16le, 16000 Hz, 1 channels, s16, 256 kb/s|610 |80~90
 hibernate.wav|88930| pcm_s16le, 44100 Hz, 2 channels, s16, 1411 kb/s|500|80～90
## 说明
1. 建立一次链接平均用时 100 毫秒
2. 保持长链接会消耗 2%～3% 的CPU

为实现快速的播放 wav 文件，建议播放文件较小，类型相同的wav 音频，提前加载文件，并且保持长链接


