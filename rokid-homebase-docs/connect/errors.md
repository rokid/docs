# 驱动错误代码
## 标准错误
- `E_DRIVER_ERROR`  通用错误
- `E_DRIVER_SIGN_ERROR`  签名错误（Token 超时时使用）提醒用户去　App 授权
- `E_DRIVER_DEVICE_NO_FOUND`  设备不存在
- `E_DRIVER_TIMEOUT` 设备控制超时
- `E_DRIVER_LOGIN_FAILED` 登录失败（登录 command 内使用）
- `E_DRIVER_WRONG_USERNAME_PASSWORD` 用户名密码错误（登录 command 内使用）
## 家庭音乐错误
- `E_DRIVER_RESOURCE_NOT_FOUND` 找不到点播歌曲
- `E_DRIVER_FAVORITE_NOT_FOUND`: 找不到收藏夹中的点播歌曲
- `E_DRIVER_MEDIA_NO_PREV` 没有上一首了
- `E_DRIVER_MEDIA_NO_NEXT` 没有下一首了
- `E_DRIVER_MEDIA_NOT_PLAYING` 当前没有在播放状态