# 快速集成

##1. 解压 Rokid_voice_sdk_v2_[timestamp].zip 安装包

将下载的 Rokid_voice_sdk_v2_[timestamp].zip 安装包放在你的目录下

   ```
$ unzip Rokid_voice_sdk_v2_[timestamp].zip
$ cd speech_sdk
   ```

解压后生成两个文件夹 **speech** 和 **uws**

例如：timestamp = 20180311170803

## 2. 编译

###非交叉编译（ubuntu & 树莓派）

非交叉编译适用于 ubuntu 系统或在树莓派上安装 ubuntu 系统的环境。方法如下：

* 安装 cmake
  ```
  $ sudo apt-get install cmake
  ```
  
* 安装 openssl 

  编译 uWS 模块时要依赖 openssl 库，所以要先安装 openssl 库

  ```
  $ sudo apt-get install libssl-dev
  ```

* 编译 uWS 模块

  ```
  $ cd /[your_path_to]/uWS/ 
  $ make
  ```

* 编译 speech 模块

  * 安装 opus 库

    speech 在传输的过程中要进行编解码，而 opus 是一个开放的，功能强大的编解码器

    ```
    $ cd ../speech/
    $ sudo apt-get install libopus-dev
    ```

    * 编译生成 build 目录

    build 目录是生成 tts、speech 可执行程序的目标文件夹

    ```
    $ rm-rf build/
    $ ./config --uws=../uWS/build/
    ```

###交叉编译

如果您的机器镜像是通过ARM交叉编译器编译，则使用如下方法进行编译：

* 首先需要保证您的交叉编译环境包含 openssl 、libopus 两个开源库，再交叉编译 uWS，并保证生成的库文件和头文件安装到您的交叉编译工具链依赖中
* 编译

```
$ cd /[your_path_to]/speech/
$ ./config --toolchain=工具链安装目录 --cross-prefix=工具链编译命令前缀 --cross-root-path=搜索依赖库的根路径
```

**注意：以上要输入的目录和路径等为你的机器工具存放的位置，并且在输入工具链安装目录，工具链编译命令前缀和搜索依赖库的根路径时必须填写绝对路径**

例如：在 Rokid A113 开发板上编译，相应命令如下：

```
./config --toolchain=~/A113/output/banban_m2_a113/host/usr --cross-prefix=aarch64-linux-gnu- --cross-root-path=~/A113/output/banban_m2_a113/host/usr/aarch64-linux-gnu/sysroot/
```

##3. 填写认证文件

在下载的 sdk 包里面有一个 speechConfig.json 文件，里面是用于认证的信息

- KEY ： 用于认证设备
- Secret：用于认证设备
- device_type_id：此 ID 用于标识这一类型的设备，由 Rokid 开放平台生成
- device_id：用户为每个设备指明的设备 ID

将这些信息依次填入 /speech/demo/demo_tts.cc 和 /speech/demo/demo_speech.cc 中

```
$ cd demo/
```

```
int main(int argc, char** argv) {
	PrepareOptions opts;
	opts.host = "apigwws.open.rokid.com";
	opts.port = 443;
	opts.branch = "/api";
	opts.key = "rokid_test_key";                       // key 
	opts.device_type_id = "rokid_test_device_type_id"; // device_type_id
	opts.device_id = "ming.qiwo";                      // device_id
	opts.secret = "rokid_test_secret";                 // secret
	.
	.
	.
	return 0;
}

```

## 4. 编译生成 demo

上述操作完成之后就可以生成 demo 直接运行了，方法如下：

```
$ cd build/
$ make
```

编译完成后会生成 demo_tts，d	emo_speech 等可执行程序

## 5. 运行

tts 运行方法

```
$ ./demo_tts "文本信息"
```

执行完之后在同级目录下生成经过 tts 处理后的 data1.wav 的音频文件

speech 运行方法

```
$ ./demo_speech xxx.wav（音频文件）
```

执行完之后会识别语音信息，并且解析 nlp（自然语言处理）

