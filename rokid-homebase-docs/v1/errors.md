# 驱动错误代码

## 标准错误

- `E_DRIVER_ERROR`  通用错误
- `E_INVALID_AUTHORIZATION` 授权非法，并且不应该继续使用、刷新
- `E_DRIVER_SIGN_ERROR`  签名错误（Token 超时时使用）提醒用户去　App 授权
- `E_DRIVER_DEVICE_NO_FOUND`  设备不存在
- `E_DRIVER_TIMEOUT` 设备控制超时
- `E_DRIVER_WRONG_USERNAME_PASSWORD` 用户名密码错误（登录 command 内使用）
- `E_DRIVER_LOGIN_FAILED` 登录失败（登录 command 内使用）
- `E_CHANNEL_NOT_FOUND` 找不到该频道 (channel.channelName action 使用)
- `E_VALUE_OUT_OF_RANGE` 命令的值超出了阈值
- `E_ENDPOINT_BUSY` 终端正在处理请求（不一定是来自若琪的命令请求），无法处理当前命令请求
- `E_ENDPOINT_UNBOUND` 设备被解绑，无法控制。建议用户：重新对该设备配网
- `E_ENDPOINT_REVOKED_AUTHORIZATION` 取消了该终端对若琪的授权
- `E_ENDPOINT_NEEDS_UPGRADE` 设备固件需要升级
- `E_ENDPOINT_UNREACHABLE` 无法访问到终端
- `E_GATEWAY_UNREACHABLE` 无法访问到终端网关
- `E_SERVER_UNREACHABLE` 无法访问到终端服务器

## 家庭音乐错误

- `E_MEDIA_RESOURCE_NOT_FOUND` 找不到点播歌曲
- `E_DRIVER_FAVORITE_NOT_FOUND`: 找不到收藏夹中的点播歌曲
- `E_DRIVER_MEDIA_NO_PREV` 没有上一首了
- `E_DRIVER_MEDIA_NO_NEXT` 没有下一首了
- `E_DRIVER_MEDIA_NOT_PLAYING` 当前没有在播放状态