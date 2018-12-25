# SN与Seed烧写 {#sn-seed}

为了能够正常配网并使用ROKID网络服务，需要正常烧写经ROKID授权的SN和Seed号，其步骤如下：

*   factory 0 0   ---进入ftm模式，系统会重启，待系统重启后再执行下面步骤；
*   factory 9 1 xxx   ---写入seed，xxx是具体seed number
*   factory 9 3 xxx  ---写入sn，xxx是具体sn number
*   factory 9 5 xxx  ---写入devicetypeid，xxx是具体devicetypeid number
*   factory 9 7 xxx  ---写入factory_date，xxx是具体factory_date number
*   factory 0 3 ---重启并进入正常模式；

上面步骤中，第2~5步，无所谓顺序，也可以只执行某几条。