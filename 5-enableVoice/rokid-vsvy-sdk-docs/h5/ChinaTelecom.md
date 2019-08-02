# 电信 H5 接入文档

### 介绍：
电信 H5 页面开发采用的是 vue.js，代码编译使用 npm 和 webpack。

### 代码目录结构

```
apps --- 业务文件
    |  --- assets --- 静态资源等
    | --- | --- pc
    | --- | --- h5
    |  --- components --- 通用组件
    | --- |  --- pc --- pc组件
    | --- | --- h5 --- h5组件
    | --- modules  --- 页面目录
    | --- |  ---  program1
    | --- | --- | --- pc
    | --- | --- | --- h5
    | --- |  ---  program2
    | --- | --- | --- pc
    | --- | --- | --- h5
    |
build --- 本地服务、webpack配置文件等
    |
dist  ---   压缩
    |
mock --- 接口数据模拟
    |
node_modules --- 第三方包
```

下面是具体的操作流程

### Step1: 下载代码包
代码包地址：https://p.rokidcdn.com/web/telecom/rokid-h5.tar

下载完成后解压代码到本地

**代码更新：代码更新只需要把本地的 config 文件复制出来，放到新的代码包中就可以，但是如果本身有对 H5 的其他定制化修改，则需要自己去做代码合并**

### Step2: 安装 npm 包
如果你本地没有安装 node， 请先到 node 官网安装。成功安装 node 之后执行如下命令：

```
cd rokid-h5
npm install
```

### Step3: 运行本地代码
你可以在本地开发多个项目，代码包中默认会有`telecom/h5`相关的页面，如果你想开发多个设备的H5页面，复制 `apps/modules/cmcc` 文件到 `apps/modules` 并修改 `telecom` 文件夹的名字为对应项目名称[name]即可（**文档中的[name]均表示项目名称**）。然后执行如下的命令运行本地代码：

```
npm run dev [name]-h5
```
该命令会生成一个 http 链接的地址和一个 https 链接的地址，会默认在浏览器中打开 http 链接的页面。

### Step4: 修改页面内容
现在生成的H5页面的内容是针对 若琪-繁星 设备的，因此页面中的部分文案需要做修改，具体页面中需要做修改的地方都在config文件中。

* basic 文件，basic文件中主要管理基本信息，具体字段说明：

```
deviceName: 设备名称,
deviceImgName: 图片名称，所有的图片都放在对应项目的 img 文件夹下面
key: 电信会为每个厂商生成一个单独的密钥用于解析链接中的参数
```
* help 文件，所有帮助页面的内容，如果不需要某个帮助页面只要把help文件中对应的那一项删除即可。下面是 help 文件中字段的说明，为了帮助理解，后面会有对应的图文说明。

```
 // 这里我们以开关机这一项来举例，每一项在文件中都有注释说明其对应的帮助页面
  startup: {
    title: '开/关机',
    pageName: '开/关机', // 如果 pageName 与 title 相同则不需要写
    steps: [            // 帮助页面一级子元素
      {
        title: 'Mini连接电源线并通电后，将自动开机。'
      },
      {
        title: '开机后，Mini灯光亮起，主动向你打招呼。 ',
        customers: [   // 帮助页面二级子元素
          {
            title: '无法自动开机？ ',
            items: [{     // 帮助页面三级子元素，最多只支持三级
              title: '请先确认插头和电源线已接入电源，没有损坏。',
              imgName: 'mini.png'
            }, {
              title: '排除电源连接问题后，可联系客服。',
              children: ['微信公众号：Rokidservice', '客服电话：400-113-0099']
            }]
          },
          {
            title: '需要关机？',
            items: [{
              title: '如需关闭Mini，请直接断开电源连接。'
            }, {
              title: '重新接入电源，即可再次启动Mini。'
            }]
          }
        ]
      }
    ]
  },
```
图文描述：
![](images/intro.jpg)

### Step5: 页面打包上传

本地打包命令：

```
// 测试环境打包，支持同时打包多个项目文件
npm run publish-dev [name]-h5

// 线上打包，支持同时打包多个项目文件
npm run publish-online [name]-h5
```
打包成功后会在 `dist/app/[name]/h5` 目录下生成：

* index.html:  html 文件
* static 文件夹: 存放所有js、css 和 图片
* [name].zip: 代码压缩包

### Step6: nginx 配置

电信那边要求页面的链接必须符合一定的规范，页面链接里必须包含：/CTCC-JS/1.0/detail/ 的地址，所以部署的时候需要注意：

1. 新建一个 /CTCC-JS/1.0/detail/ 的文件夹，然后在文件夹里新建一个[name]文件夹，把打包好的 `/dist/app/[name]/h5` 文件夹下的文件放到[name]文件夹下，然后部署前端代码

2. 用 nginx 配置来代理 /CTCC-JS/1.0/detail/ 文件夹下的内容。