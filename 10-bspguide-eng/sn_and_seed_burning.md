# SN and Seed Burning {#sn-and-seed-burning}

In order to use Rokid cloud service normally，we need fuse SN and Seed number which are authorized by Rokid. The procedure is as below：

*   factory 0 0   --- reboot into ftm mode. After system reboot, run the below command for seed/sn/devicetypeid fusing.
*   factory 9 1 xxx   ---write seed，xxx is the seed number
*   factory 9 3 xxx  ---write sn，xxx is the serial number
*   factory 9 5 xxx  ---write devicetypeid，xxx is the devicetypeid number
*   factory 9 7 xxx  --- write factory_date，xxx is the factory_date number
*   factory 0 3 --- reboot into normal mode;