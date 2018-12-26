[rokid_gitbook_path]: # (10_模块简介/15_yimo.md)
# Yimo

## 1. 简介

Yimo 工程的主要目的是

1. 实现类似 iOS 和 Android 系统中应用开发所需要的基础模块，比如 runloop，timer，av，ui 等
2. 快速接入外部SDK，比如 tvs，avs 等，实现基本但功能完整的业务逻辑
3. 接入内部实现的前沿框架，提供可见的产品实现，供外部参考

Yimo 中虽然包含具体的产品实现，但是不会有产品经理介入，所以产品实现应该保持简洁，避免不必要的复杂业务逻辑。

Yimo 输出

1. libyimo.so：包含所有的基础模块，未来模块复杂之后可能需要拆分成多个 so 文件
2. targets：具体的产品实现，比如 tvs，avs，可以配置 CMAKE_OPTIONS 选择要编译的 target，支持同时编译多个target；最终的可执行文件名包含 `yimo-` 前缀

## 2. cmake 选项

主要提供两种 cmake 选项，target和feature

* target 类型：YIMO\_TARGET\_ 前缀，选择要编译的 target
* feature 类型：YIMO\_ENABLED\_ 前缀，是否打开某个特性或者外部库

现有的 cmake 选项

选项 | 说明
---|---
YIMO_TARGET_DEMO | 是否编译 demo target
YIMO_TARGET_TVS | 是否编译 tvs target
YIMO_TARGET_AVS | 是否编译 avs target
YIMO_ENABLED_LIB_INPUT_EVENT | 是否使用 input-event 库
YIMO_ENABLED_LIB_DISPLAY | 是否使用 display 库

另外一个选项 `YIMO_HARDWARE` 指定硬件抽象接口实现，会根据该选项编译 `src/hw` 中对应的子目录；**未定义或子目录不存在时会返回错误中止编译**。

目前工程中只有根目录一个CMakeList.txt文件。

## 3. 模块说明

### 3.1 target

`src/targets` 目录包含所有的 target，其中 `main.cpp` 作为程序入口，最主要的工作是为 `Context` 指定 delegate 并启动；其次是解析所需的命令行参数。

`ContextDelegate` 是业务逻辑的主要入口，继承自 `ContextDelegateInterface` ，包含以下虚函数

    virtual void contextWillBegin();
    virtual void contextDidEnd();
    virtual bool acceptEvent(Event *event);
    virtual void handleEvent(Event *event);

在 `Context` 开始，结束和收到事件后执行必要的操作。

### 3.2 hardware

`src/hw` 目录中包含所有支持的硬件平台。基础模块比如av可能有一些接口需要不同的硬件平台实现，可以使用 `YIMO_HARDWARE` cmake 选项指定对应的平台。

### 3.3 基础模块

几个基础模块core，av，net，application相对比较独立。

#### 3.3.1 core

提供应用开发核心的功能，比如 runloop，timer，event抽象，buffer 等

* Object：几乎所有类的基类。构造时保存一个 weak\_ptr 引用，执行异步操作时 AsyncBlock 只 capture 这个弱引用，避免循环引用
* Runloop：基于 `libuv`，提供事件循环，是应用开发事件驱动模型的基础
* Timer：基于 `libuv/uv_timer_t`，实现单次或重复的定时器
* Context：封装 Runloop，管理 delegate，分发事件
* Task：类似 JavaScript 中的 Promise，支持异步操作链式执行
* Event：语音，按键事件基类，处理时使用 `dynamic_cast` 判断具体的类型
* Buffer：内存 buffer

#### 3.3.2 av

audio & video模块，目前只有 audio。

* Audio：提供音频的基本描述，encoding，format，packet等；抽象录音接口，需要硬件平台实现
* MediaCenter：管理播放器，音量通道等

#### 3.3.3 net

网络相关模块，目前只有 http 接口，可能还需要有 websocket，mqtt 等。

* Http：发出 http 请求，**回调在 Runloop 主线程执行**

#### 3.3.4 ui

* ~~Stupid：临时实现，屏幕居中显示云端或本地图片~~

#### 3.3.5 application

应用模块，与业务无关。

* Directive：指令是 app 执行的最小单位，支持单个或者 Group 指令，支持暂停，取消等操作
* SimpleApp：一个简单的 app，一般是单例，只能按顺序执行指令

## 4. 异步开发

Yimo 中的异步实现主要依赖一下几个模块

* core/Runloop：提供事件循环，`async` 和 `background` 等函数，统一的 `AsyncBlock` **lambda 原型**定义
* core/Object：使用 make\_shared 构造对象，返回 shared\_ptr 前设置 weak\_ptr，AsyncBlock 中引用 weak\_ptr，避免循环引用
* core/Task：类似 JavaScript 中的 [Promise](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)，支持链式的异步操作，和 Promise 一样没有 cancel 方法。`net/Http` 模块提供 `Task` 接口，也可以使用 `Task<T>::create` 函数构造 `Task` 实例
* application/Directive：抽象的语音指令，支持单条或者组合指令，通常继承 `Directive` 实现自定义指令，比如 tts 和音乐播放

### 4.1 Runloop

`core/Runloop` 基于 `libuv` ，包含一个主线程，遇到事件时执行相应的函数，没有事件时等待；还有数个后台线程，调用`background` 指定的 AsyncBlock 会分配到这些后台线程执行，执行完毕后回调依旧在主线程调用。

`core/Runloop` 目前封装的功能见下表

libuv | core/Runloop
---|---
uv_async_t | async 函数
uv_work_t | background 函数
uv_poll_t | watch 函数
uv_timer_t | after 函数和 Timer 类

### 4.2 返回 shared\_ptr

模块的 public 接口不应该返回裸指针，要返回的类型应该继承 `Object`，使用 `NEW_OBJECT` 宏构造，返回 shared\_ptr 类型。单例接口(`shared()`)一般返回单例的引用。

### 4.3 示例

#### 4.3.1 最简单的异步操作

    // 获取 this 弱引用
    auto weak = this->weakRef<ClassOfThis>();
    Context::shared().async([=] {
        // 检查弱引用是否有效，如果无效说明 this 已经被析构
        YIMO_CHECK_WEAK_REF(strong, weak);
        // 执行操作
        strong->doSomeThing();
    });

#### 4.3.2 从云端下载图片并显示

    // 获取 this 弱引用
    auto weak = this->weakRef<ClassOfThis>();
    // 下载图片
    Http::request("http://xxx.com/yyy.img", "GET", 0, [=](Http::Handle *handle) {
        // 检查弱引用是否有效，如果无效说明 this 已经被析构
        YIMO_CHECK_WEAK_REF(strong, weak);
        auto resp = handle->response;
        // 绘制图片
        strong->drawImage(resp.body, resp.contentLength);
    });

#### 4.3.3 请求云端大段的数据，处理后把结果保存到本地

    // 获取 this 弱引用
    auto weak = this->weakRef<ClassOfThis>();
    // 请求数据
    Http::request("http://xxx.com/yyy.json", "GET", 0, [=](Http::Handle *handle) {
        // 检查弱引用是否有效，如果无效说明 this 已经被析构
        YIMO_CHECK_WEAK_REF(strong, weak);

        auto result = process(handle->body, handle->contentLength);
        Context::shared().background([=] {
            save(result, "path/to/file");
        }, [=] (int error) {
            // 每个 AsyncBlock 里都要检查弱引用
            YIMO_CHECK_WEAK_REF(strong, weak);
            strong->onSave();
        });
    });

#### 4.3.4 使用 task 链式执行

    // 获取 this 弱引用
    auto weak = this->weakRef<ClassOfThis>();
    // 请求数据
    auto reqTask = Http::task("http://xxx.com/yyy.json")
    auto processTask = reqTask
    ->then<int>([=](Http::Handle *handle) -> int {
        // 检查弱引用是否有效，如果无效说明 this 已经被析构
        YIMO_CHECK_WEAK_REF(strong, weak);
        int result = process(handle->body, handle->contentLength);
        strong->onResult(result);
        // 还不支持 void 类型 Task
        return result;
    })
    ->fail(0, [=](int error) {
        // 检查弱引用是否有效，如果无效说明 this 已经被析构
        YIMO_CHECK_WEAK_REF(strong, weak);
        strong->onError(error);
    });

## 5. TVS

`tvs-sdk` 主要提供唤醒识别，ASR，NLP 和 TTS，功能等同于 rokid 的`turen` 模块，所以 `tvs` target 主要的工作是(NLP 在 `tvs-sdk` 中被称为 `semantic`，为了方便理解和统一，本文档中还是使用 `NLP` 这个名字)

1. 录音(signed 16 bit，16k，单通道)，输入到`tvs-sdk`
2. 按流程切换状态获取 ASR 和 NLP
3. 解析和执行 NLP

### 5.1 录音

`src/hw/k18` 中实现了 `av/Audio.h` 中定义的 `AudioRecorderInterface`，支持录制原始数据和经过 AEC 处理过的数据(使用 `YIMO_K18_RECORD_AEC` 宏切换)。

`tvs/Tvs` 作为 `tvs-sdk` 的封装，读取录音并输入到`tvs-sdk`。

### 5.2 状态管理

状态管理也在 `tvs/Tvs`，所有的状态如下表

状态 | 说明
---|---
NONE | 初始状态，只会在初始化阶段使用该状态，之后不会再出现
REQUEST\_WAKEUP\_DETECT | 请求激活状态，`tvs-sdk` 返回请求成功后才可以进入等待激活状态
WAKEUP_DETECTING | 等待激活状态，静置设备时应该在此状态，**此时录音数据输入到 `tvs-sdk` 唤醒模块**
REQUEST_ASR | 激活后请求开始ASR识别，`tvs-sdk` 返回请求成功后才可以进入 ASR 识别状态
ASR_RECOGNING | ASR 识别状态，**此时录音数据输入到 `tvs-sdk` asr模块**
REQUEST_SEMANTIC_PARSE | 请求 NLP 状态，输入为 ASR_RECOGNING 状态结束时返回的 ASR

REQUEST_SEMANTIC_PARSE 请求返回后会重新进入 REQUEST\_WAKEUP\_DETECT 状态；任何请求发生错误后也会重新进入 REQUEST\_WAKEUP\_DETECT 状态。

_`src/Tvs` 还封装了 TTS 请求，但是播放 TTS 时应该使用 `tvs/SpeechDirective`。_

### 5.3 执行 NLP

`tvs-sdk` 的 NLP 也有 rokid NLP 中 appId，intent，slots 等内容，只是名称或结构有差异；同时 `data` 节点比较规整，与 rokid cloud app 的 action 比较相似。

解析和执行 NLP 主要在 `tvs/Executor` 中完成，播放音乐的 NLP 结构见下图

![yimo_tvs_nlp](./tvs_tvs_nlp.png)

`tvs/Executor` 中普通应用根据 data/controlInfo/type(`AUDIO`/`TEXT`) 将 data/listItems 列表转换为音乐(MediaCenter::ListPlayingHandle)或 speech(SpeechDirective)指令；部分应用做了特殊处理，比如音乐除了可以播放，还要支持”上一首“和”下一首“控制指令。

音乐除了不只解析资源的 URL，同时还有专辑，歌手，封面等信息，方便进行功能扩展。

解析出指令(`application/Directive`)列表后会交给一个单例的 `application/SimpleApp` 执行。






