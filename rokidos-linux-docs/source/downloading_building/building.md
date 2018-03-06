# 准备编译

现在您已经获取了 RokidOS 源代码树，做好了编译环境配置。大致编译步骤请参考如下示例操作。

**以下操作仅保证 Amlogic/A113 开发板有效。** 不同的开发板或有些许差别，请您在编译时根据您所使用的开发板来参考，详情（905D等其他开发板）可到[开发板用户手册](../../reference/dev_board/board_list.html)章节查询参考。


## 设置编译环境

使用 ```envsetup.sh``` 脚本初始化环境。
```
source rokid_br_external/build/envsetup.sh
```
或
```
. rokid_br_external/build/envsetup.sh
```

## 选择目标

使用 ```lunch``` 选择要编译的目标。
```
lunch banban_m_a113_release
```
或
```
lunch 

You are building on Linux
echo Lunch menu... pick a combo:
1. nana_t_s905d_release
2. nana_l_a112_release
3. rm101_s905d_release
4. rp102_s905d_release
5. banban_m_a113_release
6. nana_t2_s905d_release
7. banban_m2_a113_release
8. banban_m3_a113_release
Which would you like? [2]5
```
其中
```
banban_m_a113_release:  为 A113 6mic v1.0 麦克风板，版本号 v1.0 在麦克风板正中央丝印上
banban_m2_a113_release: 为 A113 4mic 麦克风板
banban_m3_a113_release: 为 A113 6mic v1.1 麦克风板，版本号 v1.1 在麦克风板正中央丝印上
```
**请根据开发板型号选择相应软件版本**

## 编译代码
```
make 
```
