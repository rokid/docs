# display

## 1. 简介

* display模块为有屏设备提供图像绘制功能。

* display模块主要包括显示管理服务DMS、C++库、示例程序、说明文档。

## 2. API说明

### 2.1 常量说明

#### 2.1.1 enum ImageLayout

ImageLayout提供了图片与动图的显示布局选项。

```
	typedef enum
	{
	    IMAGE_TILED     = 1,
	    IMAGE_COVER     = 2,
	    IMAGE_CONTAIN   = 3,
	    IMAGE_STRETCH   = 4,
	} ImageLayout;
```

* IMAGE_TILED ： 以原像素大小显示
* IMAGE_COVER ： 保持原比例以填满窗口的方式显示
* IMAGE_CONTAIN ： 保持原比例以显示完整图片的方式显示
* IMAGE_STRETCH ：以填满窗口的方式显示

#### 2.1.2 enum TextAlign

TextAlign提供了文字的对齐方式选项。

```
	typedef enum {
	    TEXT_NONE           = 0x00000000,

	    TEXT_LEFT           = 0x00000000,
	    TEXT_CENTER         = 0x00000001,
	    TEXT_RIGHT          = 0x00000002,

	    TEXT_TOP            = 0x00000004,
	    TEXT_BOTTOM         = 0x00000008,

	    TEXT_OUTLINE        = 0x00000010,
	    TEXT_BLEND_FUNCS    = 0x00000020,

	    TEXT_TOPLEFT        = TEXT_TOP | TEXT_LEFT,
	    TEXT_TOPCENTER      = TEXT_TOP | TEXT_CENTER,
	    TEXT_TOPRIGHT       = TEXT_TOP | TEXT_RIGHT,

	    TEXT_BOTTOMLEFT     = TEXT_BOTTOM | TEXT_LEFT,
	    TEXT_BOTTOMCENTER   = TEXT_BOTTOM | TEXT_CENTER,
	    TEXT_BOTTOMRIGHT    = TEXT_BOTTOM | TEXT_RIGHT
	} TextAlign;
```

* TEXT_LEFT ： 左对齐
* TEXT_CENTER ：水平居中对齐
* TEXT_RIGHT ： 右对齐
* TEXT_TOP ： 文字位置的垂直坐标代表首行文字顶部的垂直坐标
* TEXT_BOTTOM ： 文字位置的垂直坐标代表末行文字底部的垂直坐标

#### 2.1.3 enum GIFPlayback

GIFPlayback提供了GIF动图的循环和顺序选项。

```
	typedef enum
	{
	    GIF_NOFX     = 0x00000000,
	    GIF_REWIND   = 0x00000001,
	    GIF_LOOPING  = 0x00000002
	} GIFPlayback;
```

* GIF_NOFX ：常规播放
* GIF_REWIND ：倒序播放
* GIF_LOOPING ： 循环播放

#### 2.1.4 enum DisplayDeviceType

DisplayDeviceType提供了屏幕类型描述。

```
	typedef enum
	{
	    DISPLAY_DEVICE_INVALID  = -1,
	    DISPLAY_DEVICE_PRIMARY  =  0
	} DisplayDeviceType;
```

* DISPLAY_DEVICE_INVALID ： 未知的屏幕类型，不合法
* DISPLAY_DEVICE_PRIMARY ： 主屏幕

#### 2.1.5 enum GraphType

GraphType提供了图形轮廓绘制和填充绘制的选项。

```
typedef enum
{
    GRAPH_OUTLINE   = 1,
    GRAPH_FILLED    = 2
} GraphType;
```

* GRAPH_OUTLINE ： 绘制图形轮廓
* GRAPH_FILLED ： 填充图形

#### 2.2 结构体说明

##### 2.2.1 struct ScreenDescription

ScreenDescription对屏幕属性进行描述。

```
	typedef struct
	{
	    int width;
	    int height;
	    DisplayDeviceType displayType;
	} ScreenDescription;
```
* width ： 屏幕宽度
* height ： 屏幕高度
* displayType ：屏幕类型

### 2.3 函数说明

#### 2.3.1 WindowID createWindow(int x, int y, int width, int height, int32_t opacity, DisplayDeviceType type = DISPLAY_DEVICE_PRIMARY);

在屏幕上创建一个窗口，同步接口，WindowID作为返回值返回。

* x ： 窗口左上角的水平坐标
* y ： 窗口左上角的垂直坐标
* width ： 窗口宽度
* height ： 窗口高度
* opacity ： 窗口透明度
* type ： 屏幕类型，指明窗口在哪块屏幕上创建
* 返回值 ： 窗口ID

#### 2.3.2 int createWindowAsync(std::function<void(WindowID)> cb, int x, int y, int width, int height, int32_t opacity, DisplayDeviceType type = DISPLAY_DEVICE_PRIMARY);

在屏幕上创建一个窗口，异步接口，WindowID通过回调函数返回。

* cb ： 回调函数
* x ： 窗口左上角的水平坐标
* y ： 窗口左上角的垂直坐标
* width ： 窗口宽度
* height ： 窗口高度
* opacity ： 窗口透明度
* type ： 屏幕类型，指明窗口在哪块屏幕上创建

#### 2.3.3 int destroyWindow(WindowID windowID, DisplayDeviceType deviceType = DISPLAY_DEVICE_PRIMARY);

销毁一个窗口。

* windowID ： 窗口ID
* deviceType ： 屏幕类型，指明销毁哪块屏幕上的窗口

#### 2.3.4 int getFBInfo(ScreenDescription &des);

获取屏幕信息，同步接口，屏幕信息存入des中。

* des ： 屏幕信息描述，函数结果会赋值给des

#### 2.3.5 int getFBInfoAsync(std::function<void(int ret, ScreenDescription&)> cb);

获取屏幕信息，异步接口，屏幕信息通过回调函数返回。

* cb ： 回调函数

#### 2.3.6 void prepareRender(WindowID id);

准备绘制，调用此接口后会清空指定窗口之前所有的绘制内容。

* id ： 窗口ID

#### 2.3.7 void drawString(WindowID id, const char *content, TextAlign alignment, int x, int y, int fontSize, uint32_t color, const char *fontPath = "", bool linefeed = false, int fontWidth = 0, int fontHeight = 0);

绘制文字。

* id ： 窗口ID
* content ：文本内容
* alignment ： 对齐方式
* x ： 文字水平坐标
* y ： 文字垂直坐标
* fontSize ： 文字大小
* color ： 文字颜色
* fontPath ： 字体路径
* linefeed ： 自动换行
* fontWidth ： 文字显示区域宽度
* fontHeight ： 文字显示区域高度

#### 2.3.8 void drawImage(WindowID id, const char *url, ImageLayout layout, int x = 0, int y = 0, int width = 0, int height = 0);

绘制图片。

* id ： 窗口ID
* url ： 图片位置
* layout ： 图片布局
* x ： 图片位置的水平坐标
* y ： 图片位置的垂直坐标
* width ： 图片所占区域的宽度
* height ：图片所占区域的高度

#### 2.3.9 void drawGif(WindowID id, const char *url, ImageLayout layout, GIFPlayback playbackFlag, double speed = 1);

播放GIF动图。

* id ： 窗口ID
* url ： 资源位置
* layout ： 显示布局
* playbackFlag ： 播放设置
* speed ： 播放速度

#### 2.3.10 void drawLine(WindowID id, int x1, int y1, int x2, int y2, uint32_t color);

绘制线段。

* id ： 窗口ID
* x1、y1 ： 线段一端坐标
* x2、y2 ： 线段另一端坐标
* color ： 颜色

#### 2.3.11 void drawRectangle(WindowID id, int x, int y, int width, int height, uint32_t color, GraphType type = GRAPH_FILLED);

绘制矩形。

* id ： 窗口ID
* x、y ： 矩形左上角坐标
* width ： 矩形宽度
* height ： 矩形高度
* color ： 矩形颜色
* type ： 绘制方式，指明以轮廓方式绘制还是填充方式

#### 2.3.12 void drawTriangle(WindowID id, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color, GraphType type = GRAPH_FILLED);

绘制三角形。

* id ： 窗口ID
* x1、y1 ： 点1坐标
* x2、y2 ： 点2坐标
* x3、y3 ： 点3坐标
* type ： 绘制方式，指明以轮廓方式绘制还是填充方式

#### 2.3.13 void drawCircle(WindowID id, int x, int y, int radius, uint32_t color, GraphType type = GRAPH_FILLED);

绘制圆。

* id ： 窗口ID
* x、y ： 圆心坐标
* radius ： 半径
* color ： 颜色
* type ： 绘制方式，指明以轮廓方式绘制还是填充方式

#### 2.3.14 void drawEllipse(WindowID id, int x, int y, int xRadius, int yRadius, uint32_t color, GraphType type = GRAPH_FILLED);

绘制椭圆。

* id ： 窗口ID
* x、y ： 中心坐标
* xRadius ： x轴半径
* yRadius ： y轴半径
* type ： 绘制方式，指明以轮廓方式绘制还是填充方式

#### 2.3.15 TaskID render(WindowID windowID);

执行绘制操作，在调用drawXXXX()接口后，需要调用该接口，才会进行真正的绘制，将图形绘制到屏幕上，同步接口，每次绘制会生成一个TaskID，该TaskID通过返回值返回。

* windowID ： 窗口ID
* 返回值 ： 生成的绘制任务ID

#### 2.3.16 int renderAsync(std::function<void(TaskID)> cb, WindowID windowID);

执行绘制操作，在调用drawXXXX()接口后，需要调用该接口，才会进行真正的绘制，将图形绘制到屏幕上，异步接口，每次绘制会生成一个TaskID，该TaskID通过回调函数返回。

* cb ： 回调函数
* windowID ： 窗口ID

#### 2.3.17 int windowMoveBy(WindowID id, int dx, int dy);

移动窗口，按照当前窗口位置进行相对移动。

* id ： 窗口ID
* dx ： 水平位移距离
* dy ： 垂直位移距离

#### 2.3.18 int windowMoveTo(WindowID id, int x, int y);

移动窗口至指定位置。

* id ： 窗口ID
* x、y ： 窗口新位置坐标

#### 2.3.19 int windowResize(WindowID id, int width, int height);

重置窗口大小，不改变窗口内任意图形大小。

* id ： 窗口ID
* width ： 窗口新宽度
* height ： 窗口新高度

#### 2.3.20 int windowScaled(WindowID id, int width, int height);

重置窗口大小，并对窗口内所有图形进行缩放

* id ： 窗口ID
* width ： 窗口新宽度
* height ： 窗口新高度

#### 2.3.21 int windowReset(WindowID id, int x, int y, int width, int height);

重置窗口位置和大小，不改变窗口内任意图形的大小

* id ： 窗口ID
* x、y ： 窗口新位置坐标
* width ： 窗口新宽度
* height ： 窗口新高度

#### 2.3.22 int windowResetScaled(WindowID id, int x, int y, int width, int height);

重置窗口位置和大小，并对窗口内所有图形进行缩放

* id ： 窗口ID
* x、y ： 窗口新位置坐标
* width ： 窗口新宽度
* height ： 窗口新高度

## 3. 使用说明

### 3.1 示例程序说明

示例程序代码位置在sample目录下，编译生成的程序默认不安装到镜像，如果需要运行示例，请通过adb push将程序推入设备，或者修改Makefile将示例程序安装到镜像中。

#### 3.1.1 display_demo

* 源文件 ： sample/Demo.cpp
* 资源文件目录 ：sample/res
* 对display库提供的所有接口进行调用测试

#### 3.1.2 display_demoClock

* 源文件 ： sample/DemoClock.cpp
* 资源文件目录 ：sample/res
* 模拟数字时钟，布局参考手机锁屏桌面

#### 3.1.3 display_demoJson

* 源文件 ： sample/DemoJson.cpp
* 从json文件中读取窗口信息和图形信息并进行绘制，json文件格式参考DemoConfig.json

### 3.2 使用注意事项和建议

1. 播放GIF动图需要独占一个窗口
2. 以IMAGE_TILED布局方式播放GIF，对系统性能影响最小
3. GIF尺寸越大，对系统性能影响越大