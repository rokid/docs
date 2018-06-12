# 终端

 Rokid 智能家居协议的对接的基本单元为终端，终端可以是一个真实的终端，也可以表示一个虚拟场景、应用。每一个终端需要说明它们具备的能力接口（Interface），一个能力接口可代表终端的一个可问询状态值，如一个终端具有温度接口（Temperature Interface），我们可以对若琪说："若琪，现在的温度是多少？"，来获取终端提供的温度接口的值；也可以对若琪说："若琪，把温度调高一点"，来调用温度接口提供的控制温度能力。

字段名 | 类型 | 描述
--- | --- | ---
endpointId | `string`, 必需 | 终端 Id，只需要对于某一个用户来说是唯一的
displayType | `enum`，必需 | 终端的显示类型，可能会和实际类型不太类似
displayName | `string`，必需 | 若琪客户端显示的终端名称
recommendRoomName | `string` | 推荐若琪将这个终端划入与这个房间名相同的房间，便于用户命令
offline | `bool` | Skill 能否成功连接到设备，如果不能则为 `true`
additionalInfo | key-value pairs | 一组和终端关联的键值对，若琪每次会把这些键值对和终端 Id 一起发送给 Skill
capabilities | `Capability[]` | 一组终端能力描述符
states | `InterfaceState[]` | 一组终端能力接口状态描述符

## 能力描述 Capability

终端能力 Interface 代表终端具备的变化状态值。

当这个能力可以问询时（retrievable），除了可以通过若琪控制：“帮我把灯调为红色”，将 Color 设置为红色，还可以通过若琪问询：“这个灯现在是什么颜色”，播报“现在这个灯是红色”。

当这个能力会主动推送状态时（proactivelyReported），那么就可以将这个终端状态作为一个自动化操作的触发器，如一个自动化操作是“当在早上家门关闭时，关闭家里所有灯”，那么就需要有一个“家门”的 Switch 为 proactivelyReported，当在早上它的值设为 off 时，该自动化操作就会被触发。

终端能力的状态值可以是 number 与 enum 或者特殊描述符类型；
- Number 类型接口：可以具有 Set 和 Adjust 控制命令；Set 为设为绝对期望值，Adjust 为 delta 如 +1，-1 等相对值
  - Percentage: 取值 0 到 100，Adjust 默认步长为 10
  - RGB: 取值 0 到 0xFFFFFF
- Enum 类型接口：具体的 Enum 值即为命令（相当于 Set 但是枚举了所有值）
- 描述符类型接口：具体的取值无法枚举，如歌曲、电视频道，具有 Set 控制命令

字段名 | 类型 | 描述
--- | --- | ---
interface | `enum` | 终端能力类型
version | `enum` | 终端能力定义版本，当前只支持 `v1`
supportedOperations | `string[]` | 相应能力接口类型中支持的能力操作，如 `On`，`Off` 之类
isProactivelyReported | `bool`，默认 `false` | 是否支持由产商推送终端新状态，如果支持即可作为自动化的触发器
isRetrievable | `bool`，默认 `false` | 是否支持若琪发起状态查询请求，如果支持即可向若琪问询终端状态

## 能力状态 InterfaceState

字段名 | 类型 | 描述
--- | --- | ---
interface | `enum`，必需 | 终端能力的类型
value | `polymorphic`，必需 | 目前的能力状态，如 interface 为 Rokid.Switch 时，可以为 On，Off
timeOfSample | `Date` | 最后取样时间，若琪通过这个字段来判断多个同类型终端的状态可信度以决定播报哪一个终端的状态值
