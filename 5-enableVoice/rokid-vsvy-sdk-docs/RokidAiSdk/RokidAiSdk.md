### 目录
* [一、概述](#一、概述)
* [二、软件架构](#二、软件架构)
  * [1.整体架构图](#1.整体架构图)
  * [2.主要调用流程图](#2.主要调用流程图)
* [三、集成说明](#三、集成说明)
  * [硬件环境](#需要硬件环境)
  * [所需Android权限](#所需Android权限)
  * [整体Service形式接入](#整体Service形式接入，附带BSP模块，Service服务在com.rokid.ai.audioai单独进程中)
  * [不使用默认的BSP模块](#不使用默认的BSP模块：只列出上面代码的修改区块)
  * [单独使用算法处理过的pcm数据](#单独使用算法处理过的pcm数据：只列出上面代码的修改区块)
* [四、主要Api参考](#四、主要Api参考)
* [五、 其他说明](#五、其他说明)




#### 一、概述

RokidAiSdk集合Kenobi项目的BTS方案，算法端Turen相关功能，通过speech、云端来进行语音语义识别，并返回处理信息给三方开发者，附带Rokid的TTS功能。
面向Android 软件开发工程师, 提供aar形式的SDK，简化接入流程，适应单独apk形式的集成，更方便用户接入Rokid AI语音技术。


#### 二、软件架构

##### 1.整体架构图

   ![Tv项目架构](image/AudioAiSdk%20%E9%A1%B9%E7%9B%AE%E6%9E%B6%E6%9E%84.png)

   

##### 2.主要调用流程图

   ![AudioAiSdk 时序](image/AudioAiSdk%20%E6%97%B6%E5%BA%8F.png)

   

#### 三、集成说明

##### 需要硬件环境

使用默认BSP模块：

- Android 系统电视一台
- Kenobi 单片机及相关USB线

无默认BSP模块：

* Android 系统设备一台

##### 所需Android权限

```
<!-- 网络 -->
<uses-permission android:name="android.permission.INTERNET" />
<!-- 录音 -->
<uses-permission android:name="android.permission.RECORD_AUDIO" />
<uses-permission android:name="android.permission.MODIFY_AUDIO_SETTINGS" />
<!-- 读取SD卡 -->
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

##### 整体Service形式接入，附带BSP模块，Service服务在com.rokid.ai.audioai单独进程中

- 引入aar

  - 像引入jar包一样引入aar文件 
  - gradle配置：

  ```groovy
  eg: aar 命名为rokid_aisdk_1.2.2.aar
  // 把 libs 目录加入依赖：
  repositories {
      flatDir {
          dirs 'libs'
      }
  }
  
  dependencies {
      implementation fileTree(include: ['*.jar'], dir: 'libs')
      implementation(name: 'rokid_aisdk_1.2.2', ext: 'aar')
  }
  ```

  

- 实现代码：

```java
// 创建IRokidAudioAiService实例
private IRokidAudioAiService mAudioAiService;

@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    // 如果是Android 6.0以上系统，需要单独申请Android权限并用户通过
    requestPermission();
    // 开始绑定AudioAiService (sdk在独立进程方式)
    Intent mServiceIntent = AudioAiConfig.getIndependentIntent(this);
    // SDK和app在相同进程方式
    // Intent mServiceIntent = AudioAiConfig.getAttachmentIntent(this);
    bindService(mServiceIntent, mAiServiceConnection, BIND_AUTO_CREATE);
}

// 创建ServiceConnection，用来连接AudioAiService
private ServiceConnection mAiServiceConnection = new ServiceConnection() {
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        if (service != null) {
            mAudioAiService = IRokidAudioAiService.Stub.asInterface(service);
            try {
                // *** 启动服务
                mAudioAiService.srartAudioAiServer(getServiceConfig(), mAudioAiListener);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        mAudioAiService = null;
    }
};

// 配置启动服务参数
private ServerConfig getServiceConfig() {
    // "workdir_asr_cn": 算法配置文件在assets目录中的位置
    // "ttc": 算法库配置文件名 eg: device.ttc.cfg -> "ttc"
    // useOtherAudio: 是否使用用户自己的audio数据模块
    ServerConfig config = new ServerConfig("workdir_asr_cn", "ttc", false);
    // 设置日志配置
    config.setLogConfig(Logger.LEVEL_D, true, true);
    // key: Rokid开放平台注册时生成的Key
    String key = "BBF450D04CC14DBD88E960CF5D4DD697";
    // secret: Rokid开放平台注册时生成的Secret
    String secret = "29F84556B84441FC885300CD6A85CA70";
    // deviceTypeId: Rokid开放平台注册时生成的DeviceTypeId
    String deviceTypeId = "3301A6600C6D44ADA27A5E58F5838E02";
    // deviceId: 设备SN号，由6~15位的字母和数字组成，不能含有空格和特殊符号
    String deviceId = "57E741770A1241CP";
    
    config.setKey(key).setSecret(secret)
        .setDeviceTypeId(deviceTypeId).setDeviceId(deviceId);
    return config;
}

// 设置IRokidAudioAiListener监听，来接收算法处理结果数据
private IRokidAudioAiListener mAudioAiListener = new IRokidAudioAiListener.Stub() {...}

@Override
protected void onDestroy() {
	// 解绑AudioAiService，如果当前绑定数为0，则AudioAiService及语音识别进程会自动销毁
    unbindService(mAiServiceConnection);

    super.onDestroy();
}

// 用户在播放媒体声音时调用，方便SDK优化判断是否有外部声音干扰
if (mAudioAiService != null) {
    mAudioAiService.setUserMediaPlaying(true);
}

// 用户在停止播放媒体声音时调用，方便SDK优化判断是否有外部声音干扰
if (mAudioAiService != null) {
    mAudioAiService.setUserMediaPlaying(true);
}

// 使用TTS功能
if (mAudioAiService != null) {
    mAudioAiService.playTtsVoice("大家好，我是电视小精灵，若琪！");
}
```

##### 不使用默认的BSP模块：只列出上面代码的修改区块

```java
private RecordClientManager mRecordClientManager;

@Override
protected void onCreate(Bundle savedInstanceState) {
    ... ... 同上：略 ... ...
        
    mRecordClientManager = new RecordClientManager();
}
    

// 配置启动服务参数
private ServerConfig getServiceConfig() {
    // "workdir_asr_cn": 算法配置文件在assets目录中的位置
    // "ttc": 算法库配置文件名 eg: device.ttc.cfg -> "ttc"
    // useOtherAudio: 是否使用用户自己的audio数据模块
    ServerConfig config = new ServerConfig("workdir_asr_cn", "ttc", true);
    
    ... ... 同上：略 ... ...
        
    return config;
}

private IRokidAudioAiListener mAudioAiListener = new IRokidAudioAiListener.Stub() {

    @Override
    public void onIntermediateSlice(String asr) throws RemoteException {...}

    @Override
    public void onIntermediateEntire(String asr) throws RemoteException {...}

    @Override
    public void onCompleteNlp(String nlp, String action) throws RemoteException {...}

    @Override
    public void onVoiceEvent(int event, float sl, float energy) throws RemoteException {...}

    @Override
    public void onRecognizeError(int errorCode) throws RemoteException {...}

    @Override
    public void onServerSocketCreate(String ip, int port) throws RemoteException {
        if (TextUtils.isEmpty(ip) || port < 1) {
            return;
        }
        Logger.d(TAG,"onServerSocketCreate(): ip = " + ip + ", port = " + port);
        // SDK Server端数据接收服务已经准备好，启动ClientSocket来发送数据
        // mConnnectListener：socket连接状态监听
        // ClientSocket带自动重连功能
        if (mRecordClientManager != null) {
            mRecordClientManager.startSocket(ip, port, mConnnectListener);
        }
    }
    
    @Override
    public void onPcmServerPrepared() throws RemoteException {...}
};

// socket连接状态监听
private ClientSocketManager.IConnnectListener mConnnectListener = new ClientSocketManager.IConnnectListener() {
    @Override
    public void onConnectSuccess(ClientSocketManager socketManager) {
        // socket连接成功
        mSocketConnect = true;
        Logger.d(TAG,"IConnnectListener(): onConnectSuccess");
        new Thread(new Runnable() {
            @Override
            public void run() {
                // 读取文件中的pcm数据，不断发送给SDK
                sendPcmDataByFile();
            }
        }).start();
    }

    @Override
    public void onConnectFailed(ClientSocketManager socketManager) {
        // socket连接失效
        mSocketConnect = false;
        Logger.d(TAG,"IConnnectListener(): onConnectFailed");
    }
};

/**
 * 读取文件中的pcm数据，不断发送给SDK
 * 这里只做示例，具体请根据自己的需求方式来实现
 */
private void sendPcmDataByFile() {
    for (int i = testFileIndex; i < testFileList.length; i++){
        try {
            FileInputStream mFIleInput = new FileInputStream(testFileList[i]);
            byte[] myte = new byte[4224];
            int count = 0;
            while ((count = mFIleInput.read(myte)) > 0) {
                // 确保当前Socket连接可用
                if (!mSocketConnect) {
                    return;
                }
                if (count != 4224) {
                    Logger.d("count", "the count is error not 16128");
                }
                if (count == 4224) {
                    // 将数据通过socket来传递给SDK
                    RecordClientManager.getInstance().sendRecordData(myte);
                    Thread.sleep(50);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        testFileIndex = i + 1;
    }
}

@Override
protected void onDestroy() {
	... ... 同上：略 ... ...
        
    mRecordClientManager.onDestroy();
    mRecordClientManager = null;

    super.onDestroy();
}
```

##### 单独使用算法处理过的pcm数据：只列出上面代码的修改区块

```java
private PcmClientManager mPcmSocketManager;

@Override
protected void onCreate(Bundle savedInstanceState) {
    ... ... 同上：略 ... ...
        
    mPcmSocketManager = new PcmClientManager();
}

private IRokidAudioAiListener mAudioAiListener = new IRokidAudioAiListener.Stub() {

    @Override
    public void onIntermediateSlice(String asr) throws RemoteException {...}

    @Override
    public void onIntermediateEntire(String asr) throws RemoteException {...}

    @Override
    public void onCompleteNlp(String nlp, String action) throws RemoteException {...}

    @Override
    public void onVoiceEvent(int event, float sl, float energy) throws RemoteException {...}

    @Override
    public void onRecognizeError(int errorCode) throws RemoteException {...}

    @Override
    public void onServerSocketCreate(String ip, int port) throws RemoteException {...}
    
    @Override
    public void onPcmServerPrepared() throws RemoteException {
        Logger.d(TAG,"onPcmServerPrepared(): called");
        if (mPcmSocketManager != null) {
            mPcmSocketManager.startSocket(null, mPcmReceiver);
        }
    }
};

private IReceiverPcmListener mPcmReceiver = new IReceiverPcmListener() {
    @Override
    public void onPcmReceive(int length, byte[] data) {
        String s = "onPcmReceive(): len = " + length + "\n\r";
        Logger.d(TAG, s);
        // showPcmData(length, data);
    }
};

@Override
protected void onDestroy() {
	... ... 同上：略 ... ...
        
    mRecordClientManager.onDestroy();
    mRecordClientManager = null;

    super.onDestroy();
}
```

#### 四、主要Api参考

   * IRokidAudioAiService.java  ASR 主Service的binder接口

| 返回值 | 方法和说明 |
| ------ | ------------------------------------------------------------ |
| `void` | `playTtsVoice(java.lang.String text)`用tts服务播放text语音   |
| `void` | `setUserMediaPlaying(boolean userMediaPlaying)`通知当前设备是否有用户媒体流在播放 |
| `boolean` | `srartAudioAiServer(ServerConfig config, IRokidAudioAiListener listener)`根据配置信息启动服务, 并注册Asr语音服务处理结果的监听（若当前服务已启动，则不会重新启动）        true：表示监听添加成功，false：表示监听添加失败，config中的Key、Secret、DeviceTypeId三个值与服务启动时的config中的三个值不相等 |
| `void` | `unRegistAudioAiListener(IRokidAudioAiListener listener)`注销Asr语音服务处理结果的监听 |
| `void` | `setAngle(int angle)` 设置麦克风寻向角度 angle（0 ~ 360） |
| `void` | `setPickUp(boolean open)` 在单独的激活模块中，主动开启拾音和关闭拾音 true: 开启拾音, false: 结束拾音 |
     
   * IRokidAudioAiListener.java 监听AudioAiService服务对语音的处理结果

| 返回值 | 方法和说明 |
| ------ | ------------------------------------------------------------ |
| `void` | `onIntermediateSlice(String asr)`  返回语音识别中间结果片段    |
| `void` | `onIntermediateEntire(String asr)`  返回语音识别中间结果完整的数据 |
| `void` | `onCompleteNlp(String nlp, String action)` 返回最终语音识别结果（nlp：自然语义解析结果， action：云端skill结果） |
| `void` | `onVoiceEvent(int event, float sl, float energy)`  返回语音唤醒事件（event: 语音事件类型VoiceRecognize.Event的ordinal()值， sl：当前唤醒角度(0到360度之间)， energy：当前说话能量值(0到1之间的浮点数)） |
| `void` | `onRecognizeError(int errorCode)`  返回语音识别出错信息（errorCode：错误码 VoiceRecognize.ExceptionCode的ordinal()值） |
| `void` | `onServerSocketCreate(String ip, int port)` 接收pcm数据的socket启动成功时的回调 （ip：socket的ip地址， post：socket的端口） |
| `void` | `onPcmServerPrepared()`  发送算法处理过后的pcm数据的服务已经准备好  |

   * ServiceConfig.java 启动参数配置类

| 返回值 | 方法和说明 |
| -------------- | ------------------------------------------------------------ |
| `ServerConfig` | `setCertificate(java.lang.String secretKey)`设置服务启动密匙 |
| `ServerConfig` | `ServerConfig setAssetsConfigPath(String path) ` 设置Assets目录中算法库配置文件路径 |
| `ServerConfig` | `setConfigFileName(java.lang.String fileName)`设置初始化turen配置文件名 |
| `ServerConfig` | `setDeviceId(java.lang.String mDeviceId)`设置设备的DeviceId， sn号 |
| `ServerConfig` | `setDeviceTypeId(java.lang.String mDeviceTypeId)`设置开放平台注册时生成的Type ID |
| `ServerConfig` | `setKey(java.lang.String key)`设置开放平台注册时生成的KEY    |
| `ServerConfig` | `setLogConfig(int logLevel, boolean showTurenLog, boolean showDecoderSoLog)`设置log等级 |
| `ServerConfig` | `setMustInit(boolean mustInit)`设置是否强制初始化            |
| `ServerConfig` | `setSecret(java.lang.String secret)`设置开放平台注册时生成的Secret |
| `ServerConfig` | `setShowDecoderSoLog(boolean show)`设置decode so日志是否展示 |
| `ServerConfig` | `setShowTurenLog(boolean show)`设置Turen Log的展示           |
| `ServerConfig` | `setTestWays(boolean testWays)`设置是否开启测试模式，识别服务器会有区别 |
| `ServerConfig` | `setUseNlp(boolean useNlp)`设置是否输出NLP功能               |
| `ServerConfig` | `setUseOtherAudio(boolean useOtherAudio)`设置是否使用用户自己的audio数据模块（默认使用SDK的BSP Audio数据模块），功能尚未完成 |
| `ServerConfig` | `setUsePcm(boolean usePcm)`设置是否输出PCM功能               |

   * VoiceRecognize.Event  类型说明

| 类型 | 描述 |
| ---- | ------------------------------------------------------------ |
| enum | 语音唤醒事件枚举定义： `EVENT_VOICE_COMING` 激活即将开始 `EVENT_VOICE_LOCAL_WAKE` 本地已经激活`EVENT_VOICE_START` 开始上传VAD `EVENT_VOICE_NONE` 二次确认结果为空，只出于已经在激活状态下，直接说语音命令 `EVENT_VOICE_ACCEPT` 云端二次确认通过 `EVENT_VOICE_REJECT` 云端二次确认不通过 `EVENT_VOICE_CANCEL` 取消当前上传VAD `EVENT_VOICE_LOCAL_SLEEP` 通过休眠词从激活状态进入休眠状态 |

   * RecordClientManager 录音Pcm的Client Socket

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `boolean` | `isUseQueue()`查看是否使用队列缓存数据发送 |
| `void` | `onDestroy()` |
| `void` | `sendRecordData(byte[] data)`发送录音数据 |
| `void` | `setUseQueue(boolean useQueue)`设置是否使用队列缓存数据发送 |
| `void` | `startSocket(java.lang.String ip, int port, ClientSocketManager.IConnnectListener listener)` 启动一个socket长连接|

   * IRecordPcmReceiver 录音pcm数据获取后处理监听回调

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `void` | `onPcmReceive(int length, byte[] data)`录音pcm数据获取后处理 |

   * ClientSocketManager.IConnnectListener Socket连接监听

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `void` | `onConnectFailed(ClientSocketManager socketManager)`连接失败 |
| `void` | `onConnectSuccess(ClientSocketManager socketManager)`连接成功 |

   * PcmClientManager 录音Pcm的Client Socket

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `boolean` | `isUseQueue()`查看是否使用队列缓存数据发送 |
| `void` | `onDestroy()` |
| `void` | `sendRecordData(byte[] data)`发送录音数据 |
| `void` | `setUseQueue(boolean useQueue)`设置是否使用队列缓存数据发送 |
| `void` | `startSocket(ClientSocketManager.IConnnectListener listener, IReceiverPcmListener pcmReceiver)` 启动一个socket长连接 |

   * IReceiverPcmListener 算法pcm数据获取后处理监听回调

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `void` | `onPcmReceive(int length, byte[] data)`算法pcm数据获取后处理|

####五、 其他说明

SDK 版本：（aar）
    1.2.2 