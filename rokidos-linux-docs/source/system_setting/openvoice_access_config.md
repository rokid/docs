# 语音接入配置

这里介绍如何获得 Rokid 语音服务。如果您是个人开发者，或许您不需要过多关注这个章节。
该章节针对需要定义新的机型的需求而整理了如下的指导方式。随着 Rokid 后台服务各项基础设施的逐步完善，这些配置在将来并不需要手动接入，或者更简单，目前是一个暂时的修改设备类型的方式。
 

## 手动配置
首先需要登录 [Rokid 开放平台](https://developer.rokid.com)，之后按照如下步骤执行：
1. 进入 [Rokid 开放平台](https://developer.rokid.com) 申请 Rokid 账号，若您已经申请了 Rokid 账号，可直接登录(但需进行部分信息补全)。
2. 登录后点选「语音接入」进行设备认证信息申请。
3. 具体做法：语音接入 >> 创建新设备 >> 填写设备名称 >> 创建认证文件。之后您将获得：

	```
	account_id、device_type_id、secret、key

	```
4. adb shell 登录 RokidOS，将上面获得的 key 等写入到 openvoice_profile.json 中

	vi /data/system/openvoice_profile.json 
 
	```
	{
	    "host": "apigwws.open.rokid.com",
	    "event_req_host": "apigwrest.open.rokid.com",
	    "port": "443",
	    "branch": "/api",
	    "key": "your key",
	    "device_type_id": "your device_type_id",
	    "device_id": "your account_id",
	    "secret": "your secret",
	    "api_version":"1",
	    "lang": "zh",
	    "codec": "opu",
	    "vad_mode": "cloud",
	    "vend_timeout": 500
	}	

	```
5. sync 同步
6. reboot 后即获得语音接入


