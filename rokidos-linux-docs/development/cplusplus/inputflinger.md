# inputflinger

inputflinger为输入事件服务，基于android源码修改。

源码路径:robot/frameworks/native/services/inputflinger

此服务为系统级服务，不允许第三方应用直接调用，不支持多实例运行。可由类似AMS(Apps Manager Service)级别的系统进程注册input服务，并处理对应的input的事件，选择性通知给需要的APPs

inputflinger主要源码：

EventHub.cpp 监听底层上报的input事件

InputReader.cpp 读取input事件

InputListener.cpp 监听InputReader事件并通知给InputDispatcher

InputDispatcher.cpp 分发各类input事件

InputManager.cpp 创建管理InputReader、InputDispatcher

rkinputmanager.cpp 提供接口供系统应用（如AMS）使用，并回调事件给系统应用处理。本文将主要介绍

InputApplication.cpp 和InputWindow.cpp 暂时无需关心


## rkinputmanager
主要有两个类:

class InputServerInterface 需要系统服务（如AMS）注册并实现的回调函数接口类，其input事件处理和分发给APPs都在此接口实现。

class NativeInputManager 提供系统应用(如AMS)控制注册input服务的接口，并创建InputManager对象


### InputServerInterface：

- **void notifySwitch(nsecs_t when, uint32_t switchValues, uint32_t switchMask)**

  功能：处理分发switch事件
  
  switchValues: switch事件的值，如耳机耳麦jack事件的插入和拔出
  
  switchMask：switch事件类型，如SW_JACK_BITS耳机类事件


- **void dispatchKey(struct inputkey_event\* event)**

  功能：处理分发按键事件


- **void dispatchMotion(struct inputmotion_event\* event)**
  
  功能：处理分发Motion事件
  
  注：目前可以空实现，待扩展。

### NativeInputManager：
其中许多接口继承android框架但并未使用，其内部为空实现，待扩展。

主要关注和使用的接口如下：

- **NativeInputManager(const sp<InputServerInterface>& InputServer)**
  
  构造函数，注册InputServerInterface回调函数接口类，并创建InputManager对象


- **sp<InputManager> getInputManager()**
  
  获取InputManager对象
  
```
  InputManager::start（）//run InputReader,InputDispatcher线程，需要手动调用。
  InputManager::stop（）//销毁InputReader,InputDispatcher线程，在InputManager销毁时会自动调用，无需关心。
```


- **void setInputDispatchMode(bool enabled, bool frozen)**
  
  功能：设置分发模式
  
  enabled: 使能InputDispatcher模块，并唤醒分发线程。
  
  frozen：冻结InputDispatcher模块，不进行事件分发



