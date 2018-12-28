<!----- Conversion time: 1.242 seconds.


Using this Markdown file:

1. Cut and paste this output into your source file.
2. See the notes and action items below regarding this conversion run.
3. Check the rendered output (headings, lists, code blocks, tables) for proper
   formatting and use a linkchecker before you publish this page.

Conversion notes:

* GD2md-html version 1.0β12
* Mon Oct 01 2018 06:59:25 GMT-0700 (PDT)
* Source doc: https://docs.google.com/open?id=1TMLe1x6TtPucHfD148havtVI9cKQTOCNS4bTTFegLWY
----->



# 智能家居接入 FAQ：


## 协议问题


### Q：v2 协议里面， 设备的 additional Info 含义是？

A：可以的， 在 Discover 接口返回的设备信息里面， 包含 endpointId 和 additional info， 我们在 Control 的时候会带上这些信息， 建议只存一些和设备定位相关的必要信息。


### Q：对于风速类操作，有自动、高档、中档、低挡的状态，该怎么设置？

A：目前还不支持


### Q: 授权回调地址是多少

A：我们在发起授权请求的时候会带上回调地址和必要信息， 具体地址是 https://homebase.rokid.com/oauth/callback


### Q：redirect_uri 地址，在测试时候填写成 [www.baidu.com](http://www.baidu.com/)，正式上线前能否修改？

A：redirect_uri 无法设置的， 而是在请求授权的时候会带上


### Q：在技能授权页面中，redirect_uri 回调地址是若琪提供？

A：是的


### Q： 添加场景时能为 "capabilities" 随便添加一个值还是设置为空？

A：场景如果能打开和关闭， 那么需要添加一个 打开和关闭的能力 Switch.On / Switch.off


### Q：OAuth2.0 H5页面，是若琪提供模版？

A：授权页面由提供授权服务的厂家提供


### Q: OAuth2.0 最下面有"预注册参数"这是什么意思

A：OAuth2.0 授权必要信息，包括接口地址， 注册信息等


### Q：酒店多个房间时某房间音箱发送的数据中是否包含该房间的相关信息？

A：通过智能家居的内部房间逻辑去处理， 在控制时不包含房间相关信息


## RHome/工具接入/调试问题


### Q：Rokid设备需要在什么情况下才会发出SSDP 报文？

A：若琪设备可以通过 "搜索智能设备"， 或者通过在App家庭首页下拉，发起局域网内的设备搜索


### Q：RHOME 提示返回内容错误，怎么办？

A：检查添加配置的时候，是否显示了正确的版本； 查看错误日志， 看下哪个字段有问题。


### Q：Rhome 搜索设备提示搜索成功，但无内容显示

A：检查字段名是否有问题, 设备是否按协议标准返回


### Q：现在 RHOME 调试正常，如何用音箱联调

A：若是V2协议， 服务部署好之后， 提交信息至表单中（http://cn.mikecrm.com/6LU3zsa）， 我们发布到开发者环境。

若是V1协议点击家庭 -> 添加品牌设备或者右上角的加号 -> 自定义接入 -> 绑定 详情文档： [https://developer.rokid.com/docs/rokid-homebase-docs/tools/developer-driver.html](https://developer.rokid.com/docs/rokid-homebase-docs/tools/developer-driver.html)


### Q：RHome 中添加远程驱动中驱动地址指的是什么？

A：按 homebase 协议提供的接口地址， 旧版 v1 协议， 地址是 list/execute/command 接口的根路径， v2 协议里面， 驱动地址=接口地址


### Q：厂家能否主动触发设备搜索？

A：目前还没有， 后续 v2 协议里面会加上，请关注


### Q：当使用 SDK 接入时，需要用户注册若琪 APP 的账号吗？

A：不需要，使用SDK可以绑定厂商的自有账户和自动创建的若琪的虚拟账户


### Q：请问你们有提供java版本的ssdp例子吗？

A：目前没有


### Q：通过测试程序RHOME测试没问题，自定义接入无法配置？

A: 自定义接入只支持V1协议， 不支持V2协议调试


## 酒店相关


### Q：我们当前是酒店智能家居对接，加载时如何判断那个音箱对应那个客房;

A：只要把音箱和设备放入同一个房间即可， 目前可以联系商户， 开通酒店模式。 smarthomeconnect@rokid.com


### Q：酒店多个客房用什么字段区分音箱属于那个客房？

A： 可用 recommendRoomName， 房间来区分。使用roomName字段进行灯设备的区分，音箱暂时不支持批量分配房间的字段。

关于酒店的情况，在调试成功后。将预期的音响设备号与放置的房间名提供给我们，我们将进行设备批量分配


<!-- GD2md-html version 1.0β12 -->
