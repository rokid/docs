# TTSFFLINGER逻辑框图

# 接口

##1.接口文件目录

```
	usr/include/rokid/tts/tts_client.h
```
##2.接口解析

###调用接口

```
*int tts_init();
	> tts初始化接口
*int tts_speak(const char* content, void* userdata);
	> tts播放接口，参数content：要播放内容，userdata：用户私有数据
* void tts_cancel(int id, void* userdata);
	> tts取消借口，参数id：代表要取消的tts的id，userdata：用户私有数据
* void tts_set(struct tts_callback *func);
	> tts设置的接口，参数func代表要实现的接口
* void tts_destory();
	> tts退出接口
```
###回调接口

```
*void (*onStart)(int id, void* userdata);
	> tts服务开始事件
*void (*onCancel)(int id, void* userdata);
	> tts服务取消事件
*void (*onComplete)(int id, void* userdata);
	> tts服务结束事件
*void (*onError)(int id, int err, void* userdata);
	> tts服务出错事件
```
##示例

```
void onStart(int id, void* userdata) {
	xxx
}

void onCancel(int id, void* userdata) {
	xxx
}

void onComplete(int id, void* userdata) {
	xxx
}

void onError(int id, int err, void* userdata) {
	xxx
}

int main(int argc, char** argv)
{
    int id;
    int complte;
    struct tts_callback func = {onStart, onCancel, onComplete, onError};
    tts_init();
    tts_set(&func);

    id = tts_speak((const char *)argv[1], &complte);
    return 0;
}

```



