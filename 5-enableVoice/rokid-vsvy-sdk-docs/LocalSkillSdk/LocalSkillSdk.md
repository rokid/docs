## Local Sdk Tool 文档

### 目录
* [一、概述](#一、概述)
  * [主要功能](#主要功能)
  * [主要开发步骤](#主要开发步骤)
* [二、各步骤详细说明](#三、各步骤详细说明)
  * [本地技能注册](#本地技能注册)
  * [意图或词表补全](#意图或词表补全)
  * [本地技能App配置](#本地技能App配置)
  * [本地技能SDK调用](#本地技能SDK调用)
* [三、API参考](#三、API参考)
  * [LocalSdkManager功能说明](#LocalSdkManager功能说明)
  * [样例及说明](#样例及说明)



### 一、概述

Rokid 语音SDK 本地技能快速开发工具，方便开发配合Rokid语音SDK一起使用的本地技能。

##### 主要功能：

* 提供将nlp、action解析成通用实体类的工具；

* 设置当前技能到技能栈栈顶、清空技能栈；

* 设置或取消“关键词”二次确认（confim）功能；

* 提供公共TTS功能，可以把“文字“转换成tts语音播放出来；

* 方便语音本地技能开发，保证基础功能体验统一。

##### 主要开发步骤：

  1、 在Rokid开发者网站注册相应的本地技能；

  2、补全语音交互中的意图和词表配置，并编译通过；

  3、将技能ID配置到AndroidManifest.xml的Activity或Service中；

  4、直接使用LocalSdkManager开发复杂本地语音技能，或者使用handy工具开发简易本地语音技能；

  5、完善每个意图所对应的实际功能。



### 二、各步骤详细说明

##### 本地技能注册

- 在  https://developer.rokid.com/  注册开发者帐号；

- 登录后，选择“控制台”，点击技能开发，按照技能开发步骤，进行填写；

- 详细技能开发文档：https://rokid.github.io/docs/2-RokidDocument/1-SkillsKit/getting-started/creat-and-publish.html

##### 意图或词表补全

- 意图、词表填写测试步骤请参考详细技能开发文档 https://rokid.github.io/docs/2-RokidDocument/1-SkillsKit/getting-started/creat-and-publish.html ；

- 意图介绍：
	* 技能进入："ROKID.INTENT.WELCOME"
	* 技能初次Confirm失败后再次确认："ROKID.INTENT.CONFIRM_RETRY"
	* 其他：https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/important-concept/intend.html

- 词表介绍：
	* https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/important-concept/word-list.html

##### 本地技能App配置

- 主要概念：
  * ``` "com.rokid.ai.skill.local.ID" ```：SKILL_ID，Manifest文件中技能ID meta-data 描述。
  * ``` "com.rokid.ai.skill.local.FORM" ```：SKILL_FORM， Manifest文件中技能FORM 信息 meta-data 描述, cut、scene、service。
  * ``` "com.rokid.ai.skill.local.TYPE" ```：SKILL_TYPE， Manifest文件中技能TYPE 信息 meta-data 描述, activity、service。
  * ``` "com.rokid.ai.skill.local.COMPONENT" ```：SKILL_COMPONENT，Manifest文件中技能COMPONENT 信息 meta-data 描述，可以取技能承接的Activity或Service的全名，如 "com.rokid.localskills.TestHandyActivity"。
  * ``` "com.rokid.ai.skill.local.EXTRA" ```：SKILL_EXTRA，Manifest文件中技能EXTRA 信息 meta-data 描述, 意图命中后会回传给相应的Activity或Service。
  * ``` "cmd" ```：SEND_PARAM_CMD，技能启动参数：cmd，值为”send_nlp“代表本地技能nlp命中。
  * ``` "send_nlp" ```：SEND_CMD_VALUE，技能启动参数cmd的值："send_nlp"。
  * ``` "id" ```：SEND_PARAM_ID，技能id，在bundle中传递。
  * ``` "type" ```：SEND_PARAM_TYPE，技能type，在bundle中传递，可以为"activity"、"service"
  * ``` "form" ```：SEND_PARAM_FORM，技能form，在bundle中传递，可以为"cut"、"scene"、"service"
  * ``` "extra" ```：SEND_PARAM_EXTRA，技能extra，在bundle中传递，一般用来传递一些附加信息
  * ``` "nlp" ```：SEND_PARAM_NLP，技能nlp，在bundle中传递
  * ``` "action" ```：SEND_PARAM_ACTION，技能action，在bundle中传递
  * ``` "asr" ```：SEND_PARAM_ASR，技能asr，在bundle中传递

- 技能承接配置：
  本地技能能够被Rokid语音SDK识别并发现，需要在app的AndroidManifest.xml中做技能信息的相关配置。
  	* Android中，只有Activity和Service能够用来承接一个本地技能，当做技能承接者。
  	* 一个技能承接者只能承接一个本地技能，不支持承接多个。
  	* 一个App可以有多个本地技能承接者，但推荐一个app只用来整体承接一个本地技能。
  
- Application 方式：
  ```java
  <application
        ...
        >
      <meta-data android:name="com.rokid.ai.skill.local.ID" android:value="R92F3639E0DA4E9E983BE1B09D2F6893"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.FORM" android:value="scene"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.TYPE" android:value="activity"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.COMPONENT" android:value="com.rokid.localskills.TestHandyActivity"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.EXTRA" android:value="hello, hello, hello"></meta-data>
  </application>
  ```
- Activity 方式：
  ```java
  <activity android:name="com.rokid.localskills.TestHandyActivity"
      android:launchMode="singleTask"
      android:enabled="true"
      android:exported="true">
      <meta-data android:name="com.rokid.ai.skill.local.ID" android:value="REF7DAAECE0946918BD3F2683FCCFEE7"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.FORM" android:value="scene"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.EXTRA" android:value="handy, handy, handy"></meta-data>
  </activity>
  ```
- Service 方式：
  ```java
  <service android:name="com.rokid.localskills.TestHandyService"
      android:enabled="true"
      android:exported="true">
      <meta-data android:name="com.rokid.ai.skill.local.ID" android:value="R92F3639E0DA4E9E983BE1B09D2F6893"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.FORM" android:value="scene"></meta-data>
      <meta-data android:name="com.rokid.ai.skill.local.EXTRA" android:value="hello, hello, hello"></meta-data>
  </service>
  ```
- 注意：
	* 必须让 android:enabled="true"，android:exported="true"
	* 需要本地技能承接者能够让语音SDK所在的app，通过Android启动机制访问到。

##### 本地技能SDK调用

- SDk aar 引入；
    * 引入localsdk aar
    * 引入 gson （localsdk中部分功能依赖gson）
  ```gradle
      // 外部用户：先将 localsdk-1.0.3.aar 放入libs目录中
      android {
          ...

          repositories{
              flatDir{
                  dirs 'libs'
              }
          }
          ...
      }

      dependencies {
          implementation fileTree(dir: 'libs', include: ['*.jar'])
          implementation (name:'localsdk-1.0.3', ext:'aar')
          implementation 'com.google.code.gson:gson:2.8.5'
          ...
      }

      // 内部用户
      dependencies {
          ...
          implementation 'com.rokid.ai.skill:localsdk:1.0.3'
          ...
      }
  ```

- LocalSdkManager使用实例；
  ```java
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ... 初始需要处理权限
        
        // 初始化
        LocalSdkManager.newInstance(MainActivity.this.getApplicationContext());
        
        dispatchIntent(getIntent());
    }

    /**
     * 处理Intent
     * @param intent
     */
    @Override
    protected void onNewIntent(Intent intent) {
        dispatchIntent(intent);
        super.onNewIntent(intent);
    }

    /**
     * 解析nlp,并且处理intent
     * @param intent
     */
    public void dispatchIntent(Intent intent) {
        if (intent == null) {
            Logger.d(TAG, "the intent is null");
            return;
        }
        if (LocalSdkConfig.SEND_CMD_VALUE.equals(intent.getStringExtra(LocalSdkConfig.SEND_PARAM_CMD))) {
            String id = intent.getStringExtra(LocalSdkConfig.SEND_PARAM_ID);
            String action = intent.getStringExtra(LocalSdkConfig.SEND_PARAM_ACTION);
            String type = intent.getStringExtra(LocalSdkConfig.SEND_PARAM_TYPE);
            String extra = intent.getStringExtra(LocalSdkConfig.SEND_PARAM_EXTRA);

            Logger.d(TAG, "dispatchIntent id = " + id);
            Logger.d(TAG, "dispatchIntent action = " + action);
            Logger.d(TAG, "dispatchIntent type = " + type);
            Logger.d(TAG, "dispatchIntent extra = " + extra);
        }

        String nlp = intent.getStringExtra(LocalSdkConfig.SEND_PARAM_NLP);

        Logger.d(TAG, "dispatchIntent nlp = " + nlp);

        if (TextUtils.isEmpty(nlp)) {
            Logger.d(TAG, "the nlp is null");
            return;
        }

        final NlpAsrBean mNlpAsrBean = LocalSdkManager.analysisNlp(nlp);
        Logger.d(TAG, "the NlpAsrBean is" + mNlpAsrBean.toString());

        String intentEvent = mNlpAsrBean.getIntent();
        LocalSdkManager.reportSkillStack(mNlpAsrBean.getAppId(), SKILL_TYPE_SCENE);

        switch (intentEvent) {
            case "ROKID.INTENT.WELCOME":
                // 技能入口，这个意图为用户直接说技能入口词进入技能时返回
                break;
            case "意图...":
                // 用户在注册技能时自定义的意图，由相应的意图词触发
                break;
            case "触发confirm意图":
                // 用户自己自定义的触发confirm请求的意图，这里用来展示LocalSdkManager的tts功能、confirm功能
                try {
                    LocalSdkManager.speakTTS("你喜欢喝什么", new ITtsCallback.Stub() {
                        @Override
                        public void onStart(int id) throws RemoteException {

                        }

                        @Override
                        public void onComplete(int id) throws RemoteException {
                            Logger.d(TAG, "the onComplete callback");
                            LocalSdkManager.requestConfirm(EAT_INTENT,"food", mNlpAsrBean.getAppId(), "1");
                        }

                        @Override
                        public void onCancel(int id) throws RemoteException {

                        }

                        @Override
                        public void onError(int id, int err) throws RemoteException {

                        }

                        @Override
                        public void onFilterOut(String content, String key, int existId) throws RemoteException {

                        }
                    });
                } catch (Exception e) {
                    e.printStackTrace();
                }
                break;
            case "food":
            case "ROKID.INTENT.CONFIRM_RETRY":
                // food 为用户定义的confirm 技能意图，"ROKID.INTENT.CONFIRM_RETRY"为第一次用户没有说对，自动再次确认的意图
                LocalSdkManager.speakTTS("我知道了你喜欢喝" + mNlpAsrBean.getAsr() + "了");
                break;
                default:
                    break;
        }
    }
  ```
- 简易意图及confirm形式配置；
  ```javascript
    {
      "intents": [
        {
          "intent": "up_press",
          "slots": [],
          "user_says": [
            "上一首"
          ]
        },
        {
          "intent": "confirmeat",
          "slots": [],
          "user_says": [
            "我饿了"
          ]
        },
        {
          "intent": "next_press",
          "slots": [],
          "user_says": [
            "下一首"
          ]
        },
        {
          "intent": "eat",
          "slots": [
            {
              "name": "food",
              "type": "list"
            }
          ],
          "user_says": [
            "!$food"
          ]
        }
      ]
    }
  ```
  详细参见 [意图或词表补全](#意图或词表补全)

- 简易confirm词表配置：
  ```javascript
    name: food
    type: list

    1. 西瓜
    2. 可乐
    3. 饺子
  ```
  详细参见 [意图或词表补全](#意图或词表补全)

- 简易意图HandyManager使用：
  ```java
    public class GlassHandyActivity extends Activity {

        private static final String TAG = GlassHandyActivity.class.getSimpleName();

        private TextView mTextView;

        private HandyManager mHandyManager;

        /**
         * 技能ID, 开发者网站创建技能时会自动生成
         */
        private static final String SKILL_ID = "";

        /**
         * 技能类型,scene为其中一种，还可以是cut、service
         */
        private static final String SKILL_TYPE_SCENE = "scene";

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_glass_handy);
            mTextView = findViewById(R.id.handy_text);
            mHandyManager = new HandyManager(getApplicationContext(), SKILL_ID, SKILL_TYPE_SCENE);
            mHandyManager.setHandyListener(mHandyListener);

            dispatchIntent(getIntent());
        }

        @Override
        protected void onStart() {
            super.onStart();
            if (mHandyManager != null) {
                // 当前技能已经运行，需要更新技能栈，将当前技能提升到技能栈顶
                mHandyManager.updateStack();
            }
        }

        @Override
        protected void onNewIntent(Intent intent) {
            super.onNewIntent(intent);
            dispatchIntent(intent);
        }

        /**
         * 解析nlp,并且处理intent
         * @param intent
         */
        public void dispatchIntent(Intent intent) {
            if (mHandyManager != null) {
                mHandyManager.handyIntent(intent);
            }
        }

        private HandyManager.IHandyListener mHandyListener = new HandyManager.IHandyListener() {
            @Override
            public boolean dispatchLocal(LocalSdkConfig.LocalBean localBean) {
                // 如果想要拦截localBean处理，此处返回true，否则返回false，dispatchNlp()
                return false;
            }

            @Override
            public boolean dispatchNlp(String nlp, LocalSdkConfig.LocalBean localBean) {
                // 如果想要拦截nlp处理，此处返回true，否则返回false，进入dispatchIntent()
                return false;
            }

            @Override
            public boolean dispatchIntent(String intent, LocalSdkConfig.LocalBean localBean) {
                Logger.d(TAG, "dispatchIntent " + intent + ", asr = " + localBean.asr);
                setText(localBean.asr + "\n" + intent);
                switch (intent) {
                    case LocalSdkConfig.INTENT_WELCOME:
                        return true;
                    case "自定义意图...":
                        return true;
                    // ...
                    // 如果是主动结束应用程序的意图：如关闭**技能，推荐做一下清空技能栈的操作
                    //  if (mHandyManager != null) {
                    //      mHandyManager.clearAllStack();
                    //  }
                    
                        default:
                            break;
                }
                return false;
            }
        };

        private void setText(final String content) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mTextView != null) {
                        mTextView.setText(content);
                    }
                }
            });
        }

        @Override
        protected void onDestroy() {
            if (mHandyManager != null) {
                mHandyManager.onDestroy();
                mHandyManager = null;
            }
            super.onDestroy();

        }
    }
  ```

### 三、API参考

##### LocalSdkManager功能说明

- 获得LocalSdkManager单例。
```
public static LocalSdkManager newInstance(Context applicationContext)
```

- 解析nlp中的String字符串，获得其中的解析类
```
public static NlpAsrBean analysisNlp(String nlp)
```
- confirm接口，打开拾音，然后拿到填补技能槽
```
public void requestConfirm(String confirmIntent, String slot, String appid, String type)
```
| 参数 | 含义 |
|------| ----- |
|confirmIntent| 需要填补地技能槽意图|
|slot| 填补地技能槽|
|appid| 技能appid|
|type| 技能类型|

- 取消confirm
```
public void cancelConfirm(String appid)
```

- 设置云端堆栈队列 
```
public void reportSkillStack(String appId, String type)
```
|参数|含义|
|----|----|
|appid| 技能ID|
|type| 技能类型|

- 清空技能堆栈
```
public static void clearAllSkillStack() 
```
- 暂停tts的播放
```
public static void pauseTTS()
```

- 停止tts的播放
```
public static void stopTTS(boolean isNeedCheckRunningStats)
```
- 获得action的对应字符串，并且解析
```
public NLPControlMsgBean analysisAction(String action)
```

- 播放文字，文字转换为语音
```
public static void speakTTS(final String ttsContent, final ITtsCallback callback)
```

| 参数 |含义|
|----|---|
|ttsContent| 需要播放地音频文字|
|ITtsCallback | 播放状态的回调接口|

- ITtsCallback 接口
| 参数 |含义|
|----|---|
| onStart| 开始播放音频 |
| onComplete| 完成音频播放 |
| onCancel | 取消播放 |
| onError | 播放错误 |
| onFilterOut | 过滤掉相同key值的tts |

##### 样例及说明

- SDK 版本：1.0.3
- SDK 地址：https://github.com/Rokid/RokidAiLocalSkillDemo/tree/master/aar
- 使用接口方法可参考sample demo
- 地址: https://github.com/Rokid/RokidAiLocalSkillDemo
