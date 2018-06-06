### 集成前准备

#### 获取SDK

 * 请登录[Rokid 开发者社区官网](https://developer.rokid.com/#/) （https://developer.rokid.com/#/）， 选择语音接入，创建产品，并根据网站提示进行配置，最后生成 SDK 后进行下载即可。

#### 复制文件

将```java-libraries```文件夹下的```rokid_speech.jar```复制到 Android 工程下的 ```app/libs``` 文件夹中，并设置为工程的依赖库

![](../img/init_jar.png)

将```shared-libraries```文件夹下的全部文件包含文件夹复制到 Android 工程下的```app/src/main/jniLibs``` 文件夹中

![](../img/init_jnilibs.png)

#### 添加权限

```xml
    <!--网络访问权限-->
    <uses-permission android:name="android.permission.INTERNET" />
```




