# 驱动错误代码
## 标准错误
- `10001 E_DRIVER_ERROR`  通用错误
- `10002 E_DRIVER_SIGN_ERROR`  签名错误（Token 超时时使用）提醒用户去　App 授权
- `10003 E_DRIVER_DEVICE_NO_FOUND`  设备不存在
- `10004 E_DRIVER_TIMEOUT` 设备控制超时
- `10005 E_DRIVER_WRONG_USERNAME_PASSWORD` 用户名密码错误（登录 command 内使用）
- `10006 E_DRIVER_LOGIN_FAILED` 登录失败（登录 command 内使用）
## 家庭音乐错误
- `10009 E_DRIVER_RESOURCE_NOT_FOUND` 找不到点播歌曲
- `10010 E_DRIVER_FAVORITE_NOT_FOUND`: 找不到收藏夹中的点播歌曲
- `10011 E_DRIVER_MEDIA_NO_PREV` 没有上一首了
- `10012 E_DRIVER_MEDIA_NO_NEXT` 没有下一首了
- `10020 E_DRIVER_MEDIA_NOT_PLAYING` 当前没有在播放状态