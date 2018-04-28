
# Siren API v4
项目地址：https://github.com/Rokid/rokid-blacksiren

## 简介
Siren包括C的API和Java的API，API形式完全等价，下面详细分析API的时候会给出相关说明。Siren使用JSON形式的配置文件，配置文件可以通过文件绝对路径或者直接字符串两种方式进行加载。

## 配置文件字段

### basic_config 基础配置

```mic_num```: 麦克风数目（包括AEC参考音源数目）   
```mic_channel_num```: 麦克风通道数目（包括参考音源通道），一般情况下和mic_num相同   
```mic_sample_rate```: 麦克风音频采样率   
```mic_audio_byte```: 麦克风音频位宽，一般取值为2（16位），4（32位）两种   
```mic_frame_length```: 建议的每一语音帧的时长，建议语音帧长度为10ms。   
```siren_ipc```: 使用channel的方式进行ipc还是share memory，目前仅支持channel   
```siren_channel_rmem```: channel写缓存的大小  
```siren_channel_wmem```: channel读缓存的大小  
```siren_input_err_retry_num```: 输入音频流出错时重试的最大连续次数，已废弃
```siren_input_err_retry_timeout```: 两次重试间间隔的时间，单位时毫秒，已废弃

### alg_config 算法配置
```alg_use_legacy_config_file```: 是否使用老siren的ssp配置文件方式，已废弃   
```alg_legacy_config_file_path```: 使用老siren的配置文件方式，指出ssp配置文件位置，已废弃   
```alg_lan```: 当前语言配置，zh/en，默认zh，已废弃   
```alg_rs_mics```: 降采样通道配置，数组形式，告知需要降采样的通道   
```alg_aec```: 是否进行aec   
```alg_aec_mics```: aec音频通道，数组形式，告知aec的音频数据通道     
```alg_aec_ref_mics```: 参考音源通道，数组形式，用来告知AEC算法哪些通道是参考通道   
```alg_aec_shield```: 默认200.0f   
```alg_aec_aff_cpus```: aec处理线程的亲和性   
```alg_aec_mat_aff_cpus```: aec矩阵运算的亲和性   
```alg_raw_stream_sl_direction```:  裸数据流sl方向   
```alg_raw_stream_bf```: 裸数据流是否需要bf处理   
```alg_raw_stream_agc```: 裸数据是否需要agc处理   
```alg_vt_enable```: 是否需要vt事件   
```alg_vad_enable```: 是否需要vad事件，此事前端处理流程退化成raw stream
```alg_vad_mics```: vad使用的音频通道，数组形式    
```alg_mic_pos```: 所有麦克风的位置，每个位置由x,y,z三个double坐标描述。     
```alg_sl_mics```: 寻向使用的音频通道。   
```alg_bf_mics```: 波束成形使用的音频通道。   
```alg_opus_compress```:   是否输出opus编码后的语音   
```alg_vt_phomod```:   存放音素对应表的绝对路径   
```alg_vt_dnnmod```:   存放DNN模型的绝对路径
```alg_rs_delay_on_left_right_channel```: 左右声道是否存在不一致的delay，常发生在i2s采集的情况上   
```raw_stream_channel_num```: 裸音频流输出的通道数，默认为1。   
```raw_stream_sample_rate```: 裸音频流输出的采样率，默认为16000。   
```raw_stream_byte```: 裸音频输出的位宽，默认为2。    

### alg_def_vt 默认激活词配置
```vt_type```: 激活词类型，1是激活词，2是睡眠词，3是热词   
```vt_word```: 激活词，utf-8的汉字   
```vt_phone```: 激活词音素，拼音，假如激活词是“你好”，则这里填ni2hao3，声调轻声使用数字5   
```vt_block_avg_score```: 所有phone声学平均得分门限   
```vt_block_min_score```: 单个phone声学最低得分门限
```vt_left_check```: 是否进行前置静音检测   
```vt_right_check```: 是否进行后置静音检测   
```vt_remote_check_with_aec```: 是否在aec状态下进行远程asr确认，如果为true，则不会发出_nocmd类型事件   
```vt_remote_check_without_aec```: 是否在非aec状态下进行远程asr确认    
```vt_local_classify_check```: 是否进行本地激活二次确认    
```vt_classify_shield```: 本地激活二次确认门限
```vt_nnet_path```: 激活词模型绝对路径   

### debug_config DEBUG选项
```debug_record_path```: 录音结果存放绝对路径   
```debug_mic_array_record```: 是否针对输入进行录音   
```debug_pre_result_record```: 是否针对预处理语音进行录音   
```debug_proc_result_record```: 是否针对处理过的语音进行录音，如果alg_opus_compress为true则录音得到的opus编码的数据，否则是16K，32float，1ch的PCM流   
```debug_rs_record```: 是否针对降采样的语音进行录音   
```debug_aec_record```: 是否针对自身音源消除后的语音进行录音   
```debug_bf_record```: 是否针对波束成形后的语音进行录音   
```debug_bf_raw_record```: 废弃
```debug_vad_record```: 是否对vad的结果进行录音   
```debug_opu_record```: 废弃

## 数据结构与回调方法

###  siren_input_if_t

#### 功能

> 音频流输入回调函数集合

#### 说明

该结构体由和音频输入相关得回调函数指针组成

##### 初始化音频流

##### 函数功能

> 当调用init_siren后，并且配置成功后，回调该接口，该方法应该分配音频流相关资源

##### 原型

``` int (*init_input_stream)(void *token) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |

##### 返回值

操作成功返回0，否则init_siren会返回siren_status_error。

##### 结束音频流

##### 函数功能

> 当调用destroy_siren时回调该方法，该方法应该释放音频流相关资源

##### 原型

``` void (*release_input_stream)(void *token) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |

##### 返回值

无

##### 打开音频流

##### 函数功能

> 该方法应该打开音频流，该回调将在第一次调用start_siren_process_stream或start_siren_raw_stream时被调用

##### 原型

``` int (*start_input_stream)(void *token) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |

##### 返回值

返回0将告知blacksiren打开音频流成功，返回非0会告知blacksiren打开音频流失败，此时blacksiren的录音线程将不会启动

##### 停止音频流

##### 函数功能

> 该方法应该暂停音频流，该回调将在最后一次调用stop_siren_process_stream或stop_siren_raw_stream时被调用

##### 原型

``` void (*stop_input_stream)(void *token) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |

##### 返回值

无

##### 5. 从音频流中读取音频数据

##### 函数功能

> 该方法应该根据配置正确返回音频流，音频流的大小和格式根据配置决定，缓冲区由siren负责分配和释放，该方法应该阻塞输入至少length字节的音频数据。

##### 原型

``` int (*read_input_stream)(void *token, char *buffer, int length) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |
| buffer | char * | 需要填写音频流数据的缓冲区，不要超过length的长度 |
| length | int | 音频缓冲区的长度 |

##### 返回值

返回值0表示从音频流成功读取了length字节的音频数据，其他值表示出错，出错后siren会调用
stop_input_stream最后重新尝试调用start_input_stream重新开始读取音频流数据。如果多次出错，则调用on_err_input_stream

##### 6. 处理音频流错误

##### 函数功能

> 当read_input_stream多次出错后，会回调该方法

##### 原型

``` void (*on_err_input_stream)(void *token) ```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |

##### 返回值

无

### siren_proc_callback_t

#### 功能

> 语音处理事件的回调接口

##### 语音事件回调接口

##### 函数功能

> 当发生特定语音事件时，siren会回掉该接口

##### 原型

``` void (on_voice_event*)(void *token, voice_event_t *voice_event)```

##### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * | 通过init_siren传入的token |
| voice_event | voice_event_t | 语音信息 |


voice_event_t结构体成员如下

| 成员 | 类型 | 说明 |
| ------| ------ | ------ |
| event | siren_event_t | 语音事件，详见下面语音事件说明 |
| length | int | 如果包含寻向信息指的是激活词中文的长度，如果是语音帧则是语音数据的长度 |
| flag | int | 可以使用HAS_VOICE, HAS_SL和HAS_VT来判断是否是语音帧，是否包含寻向信息，是否包含激活信息 |
| sl | double | 寻向角度 |
|background_energy| double | 归一化后的背景声能量，越大表明当前帧能量越大 |
|background_threshold| double | 背景声能量阈值，越大表明背景越吵 |
| vt | vt_event_t | 激活信息，具体见下面说明 |
| buff | void *| 如果HAS_VOICE，则是语音数据，长度由length表明，如果HAS_VT，则表示激活词名字字符串长度，如果HAS_SL，则为0 |

vt_event_t结构体成员如下

| 成员 | 类型 | 说明 |
| ------| ------ | ------ |
| start | int | 在下面第一个SIREN_EVENT_VAD_DATA语音帧中激活词所在的开始，单位是float |
| end | int | 语音帧中激活词结尾 |
| energy | float | 激活词的能量绝对值 |


##### 返回值

无

##### 语音事件说明

```SIREN_EVENT_VAD_START```: VAD_START事件，通常可以认为是一个语音帧的开始。
```SIREN_EVENT_VAD_DATA```: VAD_DATA事件，携带语音信息的语音帧。

```SIREN_EVENT_VAD_END```: VAD_END事件，语音帧的结束帧。

```SIREN_EVENT_VAD_CANCLE```: 因为误激活引发的VAD_CANCLE事件。

```SIREN_EVENT_WAKE_VAD_START``` :   
```SIREN_EVENT_WAKE_VAD_DATA``` :   
```SIREN_EVENT_WAKE_VAD_END``` :    
```SIREN_EVENT_WAKE_PRE``` : 疑似激活词的开始，不能作为激活标准，已废弃。

```SIREN_EVENT_WAKE_NOCMD```: 单独激活事件。
```SIREN_EVENT_WAKE_CMD```: 以激活词开头，以其他语音结尾的混合激活事件，需要通过asr来进一步判断激活情况。

```SIREN_EVENT_WAKE_CANCLE```: 可以本地判断的误激活事件。

```SIREN_EVENT_SLEEP```: 睡眠激活词。

```SIREN_EVENT_HOTWORD``` :   
```SIREN_EVENT_VOICE_PRINT```: 声纹事件，包含声纹信息。  
```SIREN_EVENT_DIRTY``` : 


## Siren接口说明 

### 初始化

#### 函数功能

> 初始化Siren软件栈

#### 函数原型

``` siren_t init_siren(void *token, const char *path, siren_input_if_t *input)```  

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| token | void * |将在后续回调方法中被调用      |
| path | const char * | JSON配置文件所在的本地文件绝对地址 |
| input | siren_input_if_t * | siren语音输入接口 |

#### 返回值

返回siren对象，如果失败则返回nullptr，siren对象用于后续操作的第一个参数


### 打开语音处理音频流

#### 函数功能

> 打开语音处理流，此时siren将源源不断的从siren_input_if_t提供的输入接口中读取音频数据，直到stop_siren_process_stream或stop_siren_stream被调用 

#### 函数原型

``` void start_siren_process_stream(siren_t siren, siren_proc_callback_t *proc_callback) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| proc_callback | siren_proc_callback_t * | 处理结果回调接口 |

#### 返回值

无

###  打开裸数据音频流

#### 函数功能

> 打开裸数据流，此时siren将源源不断的从siren_input_if_t提供的输入接口中读取音频数据，直到stop_siren_raw_stream或stop_siren_stream被调用

#### 函数原型

``` void start_siren_raw_stream(siren_t siren) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|

#### 返回值

无

### 关闭数据处理音频流

#### 函数功能

> 关闭数据处理音频流，如果此时没有打开裸数据音频流，那么将调用siren_input_if_t的stop_stream方法

#### 函数原型

``` void stop_siren_process_stream(siren_t siren) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|

#### 返回值

无

###  关闭裸数据音频流

#### 函数功能

> 关闭裸数据音频流，如果此时没有打开语音处理音频流，那么将调用siren_input_if_t的stop_stream方法

#### 函数原型

``` void stop_siren_raw_stream(siren_t siren) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|

#### 返回值

无

### 关闭音频流

#### 函数功能

> 强制关闭音频流，将调用siren_input_if_t的stop_stream方法

#### 函数原型

``` void stop_siren_stream(siren_t siren) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|

#### 返回值

无

### 强制设置当前siren的激活/睡眠状态

#### 函数功能

> 强制设置siren的激活/睡眠状态

#### 函数原型

``` void set_siren_state(siren_t siren, siren_state_t state, state_changed_callback_t *callback)```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| state | siren_state_t | 可以在siren_state_awake和siren_state_sleep中选择 |
| callback | state_changed_callback_t * | 如果不是NULL则调用为异步，否则为同步，异步调用会在完成时调用callback接口 |

#### 返回值

无

### 强制设置当前寻向角度

#### 函数功能

> 强制设置水平和垂直寻向角度

#### 函数原型

``` void set_siren_steer(siren_t siren, float ho, float ver)```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| ho | float | 水平角度 |
| ver | float | 垂直角度 |

#### 返回值

无

### 关闭siren软件栈

#### 函数功能
> 关闭siren软件栈，回收所有内存

#### 函数原型

``` void destroy_siren(siren_t siren)```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|

#### 返回值

无

### 添加唤醒激活词

#### 函数功能
> 添加一个激活词

#### 函数原型

``` siren_vt_t add_vt_word(siren_t siren, siren_vt_word *word, bool use_default_config) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| word | siren_vt_word * | 激活词信息 |
| use_default_config| bool | 是否自动使用默认配置 |

siren_vt_word 结构体说明


| 成员 | 类型 | 说明 |
| ------| ------ | ------ |
| vt_type | int | 激活词类型，1是激活词，2是睡眠词，3是热词 |
| vt_word | std::string | 激活词，utf-8任意文字 |
| vt_phone | std::string | 激活词拼音，在add_vt_word成功调用后，这里会自动转化成音素 |
| use_default_config| bool | 是否对算法相关配置使用默认配置 |
| alg_config| siren_vt_alg_config | 激活词算法相关配置 |


siren_vt_alg_config 结构体说明

| 成员 | 类型 | 说明 |
| ------| ------ | ------ |
| vt_block_avg_score | float | 见默认激活词配置中的说明，默认值为4.2 |
| vt_block_min_score | float | 见默认激活词配置中的说明，默认值为2.7 |
| vt_left_sil_det| bool | 见默认激活词配置中的说明，默认值为true |
| vt_right_sil_det| bool | 见默认激活词配置中的说明，默认值为false |
| vt_remote_check_with_aec | bool | 见默认激活词配置中的说明，默认为false |
| vt_remote_check_without_aec | bool | 见默认激活词配置中的说明，默认值为false |
| vt_local_classify_check|bool|见默认激活词配置中的说明，默认值为false|
| vt_classify_shield|float|见默认激活词配置中的说明，默认值为-0.3|
|nnet_path|std::string|见默认激活词配置中的说明，默认值为""|

#### 返回值

成功添加激活词，返回SIREN_VT_OK
激活词已经存在，返回SIREN_VT_DUP
添加激活词失败，返回SIREN_VT_ERROR

### 删除激活词

#### 函数功能
> 删除一个指定激活词，使用激活词名字来删除

#### 函数原型

``` siren_vt_t remove_vt_word(siren_t siren, const char *word) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| word | const char *| 激活词名字 |

#### 返回值

成功删除一个激活词，返回SIREN_VT_OK
删除激活词失败，返回SIREN_VT_ERROR
激活词不存在，返回SIREN_VT_NO_EXIT

### 查询所有激活词

#### 函数功能
> 查询所有激活词

#### 函数原型

``` int get_vt_word(siren_t siren, siren_vt_word **words) ```

#### 参数

| 参数 | 类型 | 说明 |
| ------| ------ | ------ |
| siren | siren_t | siren对象|
| words | siren_vt_word *| 所有激活词数组，数目由返回值给出 |

#### 返回值

-1表示错误，其他表示激活词数目




