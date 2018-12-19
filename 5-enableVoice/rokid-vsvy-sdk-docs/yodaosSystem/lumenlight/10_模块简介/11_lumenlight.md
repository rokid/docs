## LumenLight

&ensp;&ensp;&ensp;&ensp;LumenLight模块为应用层提供灯光绘制方法和LED信息。

<br>

**位置** ：frameworks/native/libs/lumenlight

### Method

#### void lumen_set_enable(bool cmd)

&ensp;&ensp;&ensp;&ensp;设置 *lumen_draw* 是否生效.

#### int lumen_draw(unsigned char* buf, int len)

&ensp;&ensp;&ensp;&ensp;写入LED像素值.


### Variable

#### int m_ledCount

&ensp;&ensp;&ensp;&ensp;LED数量。

#### int m_pixelFormat

&ensp;&ensp;&ensp;&ensp;像素格式，3代表RGB格式。

#### int m_frameSize

&ensp;&ensp;&ensp;&ensp;像素值总长度，*m_frameSzie =  m_ledCount *  m_pixelFormat*。

#### int m_fps

&ensp;&ensp;&ensp;&ensp;建议使用的最大帧率，实际帧率大于该值时可能导致丢帧。