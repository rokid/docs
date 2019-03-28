## 酷狗音乐 Skill 接入流程

本文旨在介绍酷狗音乐技能的接入流程，方便B端厂商快速接入酷狗音乐优质的资源内容。

* [一、酷狗音乐skill介绍](#一、叮当音乐skill介绍)
* [二、酷狗音乐skill通用流程](#二、叮当音乐skill接入通用流程介绍)

  
### 酷狗音乐skill介绍

#### 酷狗音乐skill内容介绍

<table><tbody>
<tr style="font-weight:bold">  <td style="width: 100px">技能名称</td>  <td style="width: 180px">介绍</td>  <td style="width: 180px">价格</td> <td style="width: 180px">>头部内容</td><td>内容数量</td></tr>
<tr>  <td>酷狗音乐</td>  <td>容来自腾讯酷狗音乐，API方式接入</td>  <td>需与商务沟通</td> <td>歌手：周杰伦、陈奕迅、王菲、张学友、刘德华、林俊杰、李荣浩、邓紫棋、艾伦.沃克、张杰、杨宗纬、李宇春、陈粒、赵雷、张靓颖、吴亦凡、金志文、胡彦斌、TFboys、胡66、华晨宇、周笔畅等
音乐标签：流行、民谣、摇滚、英文、粤语、日语、伤感、睡前等</td> <td>歌曲数2100W
腾讯酷狗音乐音箱端版权所有歌曲</td> </tr>
</tbody></table>

#### 酷狗音乐skill功能列表

<table>
    <tr>
        <td>功能</td> 
        <td>示例</td> 
        <td>备注</td> 
   </tr>
    <tr>
        <td >歌手点播</td>    
        <td >我要听刘德华的歌</td>  
        <td></td>
    </tr>
    <tr>
        <td >歌曲点播</td> 
        <td >我要听冰雨</td> 
         <td></td> 
    </tr>
     <tr>
        <td >歌手+歌曲点播</td> 
        <td >我要听刘德华的冰雨</td>  
          <td></td> 
    </tr>
     <tr>
        <td >播放我的收藏</td> 
        <td >播放我的收藏歌曲</td>
          <td></td>  
    </tr>
     <tr>
        <td >点播专辑</td> 
        <td >播放周杰伦的专辑范特西</td> 
          <td></td> 
    </tr>
     <tr>
        <td >播放榜单歌曲</td> 
        <td >我要听新歌榜</td> 
          <td></td>
    </tr>
     <tr>
        <td >若琪推荐</td> 
        <td >播放音乐</td> 
          <td></td>
    </tr>
     <tr>
        <td >年代、场景、情绪点播</td> 
        <td >播放睡前音乐</td> 
        <td></td>
    </tr>
     <tr>
        <td >语言点播</td> 
        <td >我要听中文歌</td> 
         <td></td>
    </tr>
     <tr>
        <td >点播播放历史</td> 
        <td >播放我最近听过的歌</td> 
         <td></td>
    </tr>
     <tr>
        <td >歌手类别点播</td> 
        <td >我要听华语歌手的歌 / 我要听男歌手的歌</td> 
         <td></td>
    </tr>
     <tr>
        <td >下一首/td> 
        <td >下一首</td> 
        <td></td>
    </tr>
     <tr>
        <td >上一首</td> 
        <td >上一首</td> 
        <td></td>
    </tr>
     <tr>
        <td >停止播放</td> 
        <td >别放了</td> 
        <td></td>
    </tr>
     <tr>
        <td >继续播放</td> 
        <td >继续播放</td> 
         <td></td>
    </tr>
     <tr>
        <td >暂停</td> 
        <td >暂停播放</td> 
         <td></td>
    </tr>
     <tr>
        <td >取消循环</td> 
        <td >取消单曲循环</td> 
        <td></td>
    </tr>
     <tr>
        <td >单曲循环</td> 
        <td >单曲循环</td> 
        <td></td>
    </tr>
     <tr>
        <td >从头播放</td> 
        <td >再放一遍</td> 
        <td></td>
    </tr>
     <tr>
        <td >收藏/我喜欢</td> 
        <td >我喜欢这首歌 / 收藏</td> 
        <td>需要接入账号绑定才支持收藏</td>
    </tr>
    <tr>
        <td >歌曲黑名单</td>    
        <td >我不喜欢这首歌</td>  
        <td></td>
    </tr>
    <tr>
        <td >不取消收藏</td> 
        <td >取消收藏</td>  
        <td></td>
    </tr>
     <tr>
        <td >帮助</td>    
        <td >介绍下音乐功能</td>  
        <td></td>
    </tr>
     <tr>
        <td >取消订阅专辑</td> 
        <td >取消订阅</td> 
    </tr>
     <tr>
        <td rowspan="2">喜欢</td>    
        <td >喜欢某个声音</td>  
        <td>喜欢</td>
    </tr>
     <tr>
        <td >询问歌曲信息</td> 
        <td >这是什么歌/这首歌谁唱的</td> 
    </tr>
</table>

### 酷狗音乐skill接入通用流程介绍

需要合作方和若琪商务（rokidopen@rokid.com）确定合作，确定商务协议后，进行酷狗音乐skill的接入，需要进行的步骤: 

- 若琪开放平台授权酷狗音乐 skill

在开放平台将酷狗音乐技能授权给合作方设备，合作方接受授权

- 酷狗音乐账号oauth流程

腾讯牛音乐必须在登录酷狗音乐账号后才可以收听音乐。

- 公版APP的方式接入：

公版APP已包含oauth鉴权的流程和页面，只需在开放平台创建一个APP即可，详见[开放平台APP配置](https://developer.rokid.com/docs/8-app/alliance/web/gongban.html)。

备注：目前仅支持公版APP方式接入，如需要APP SDK，需与对接的商务进行沟通。

- 目前酷狗音乐只支持 Android 和 linux 系统的设备。
