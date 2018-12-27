# 语音应用包管理

### 安装应用

使用 `rokidos-cli` 来完成应用的打包、安装，首先安装命令行工具：

```sh
$ npm install rokidos-cli -g
```

然后在应用目录下：

```sh
$ rokid build ./
```

上述命令会生成 `.rpp` 文件，然后通过：

```sh
$ rokid install example.rpp
```

安装到已连接的 RokidOS 设备。你也可以直接通过：

```shell
$ cd /path/to/your/app/directory
$ rokid install
```

来直接从应用目录安装。

> 注意：由于 AMS 目前还不支持在线重启应用，因此每次安装成功后，都需要手动重启。

### dbus 接口

```
service   : rokid.linux.pkgm
path      : /rokid/linux/pkgm
interface : rokid.linux.pkgm.IPackageManager
```

- `install(string name) => string` 通过包名安装
- `uninstall(string name) => string` 卸载包
- `getPackage(string name) => JSON` 获取当前包状态
