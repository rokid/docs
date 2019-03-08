Rokid Plate Recognition SDK and demo project.

***	
|Author|Email|
|---|---|
|cmxnono|cmxnono@rokid.com|
***

## cirtus_lpr_sdk

Version：1.0

### SDK接口说明

* 初始化

```
public long init(Context context)
```

* 相机预览识别

```
public int[] detect(byte[] data, int w, int h, int method, long  object)
public String recogAll(byte[] data, int w, int h, int method, int[] rects, long  object)
```

* BGR数据输入识别

```
public String recognizationBGR(byte[] data, int w, int h, int method, long  object)
```

* 模型更新

```
public String updateModel(Context context)

会将assets下的Citrus文件夹中的文件拷贝到应用程序的内部存储路径/data/data/<application package>/files/Citrus下
```

## android_demo

demo功能：触摸屏幕，对车牌进行对焦，触发一次车牌识别。

	
