## GPIO设置 {#gpio}

### GPIO 规划 {#gpio-0}

PD1开头的port对应MCU域的port，PD2开头的port对应ARM域的port, 其对应的gpio组如下：

*   PD2PORT0 - PD2PORT31 对应 gpa0 组
*   PD2PORT32 - PD2PORT51 对应 gpa1 组
*   PD1PORT0 - PD1PORT31 对应ck_gpa0 组
*   PD1PORT32 - PD1PORT35 对应ck_gpa1 组

目前不提供ck的gpio中断在A7的支持，所有的GPIO都可以配置为中断模式，但要注意管脚复用配置正确，为GPIO模式。GPIO number的数字就是PDXPORTXX的数字 % 32。

### 内核层GPIO使用方法 {#gpio-1}

控制ARM域GPIO设备树节点例子如下：

test: test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

test1-gpio = &lt;&amp;gpa0 1 GPIO_ACTIVE_HIGH&gt;;

};

控制MCU域GPIO设备树节点例子如下：

test: test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

test1-gpio = &lt;&amp;ck_gpa0 10 GPIO_ACTIVE_HIGH&gt;;

};

Note：

这里GPIO_ACTIVE_HIGH代表gpio输出极性控制为正output1实际输出高电平，output0实际输出低电平），GPIO_ACTIVE_LOW代表gpio输出极性控制为负（output1实际输出低电平，output0实际输出高电平）

驱动代码调用gpio接口如下：

*   desc = devm_gpiod_get(&amp;pdev-&gt;dev, &quot;test1&quot;, GPIOD_OUT_LOW); //申请test1-gpio这个属性对应的GPIO口描述符，并设置为输出模式，输出低电平
*   gpiod_direction_input(desc); //设置desc描述符对应的GPIO口为输入模式
*   gpiod_to_irq(desc) //获取此gpio对应的中断号，中断号要注意检查，大于0为有效的
*   gpiod_direction_output(desc,1); //设置desc描述符对应的GPIO口为输出模式，输出高电平
*   gpiod_set_value(desc,0); //设置desc描述符对应的GPIO口输出值为0
*   gpio_level = gpiod_get_value(desc); //得到desc描述符对应的GPIO口的电平
*   devm_gpiod_put(&amp;test_pdev-&gt;dev, desc); //释放desc描述符对应的GPIO口，这样别人才能申请这个GPIO口

在kernel里只提供ARM gpio的pwm功能，MCU的gpio不支持。pwm0对应gpa0组,pwm1对应gpa1组, port换算关系为port 的数字就是PDXPORTXX的数字 % 32，驱动代码调用pwm接口如下：

*   struct pwm_device *devm_pwm_get(struct device *dev, const char *con_id) //获取pwm句柄
*   int pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns) //配置pwm
*   int pwm_enable(struct pwm_device *pwm) //开启pwm
*   void pwm_disable(struct pwm_device *pwm) //关闭pwm

设备树节点例子：

控制PD2PORT26脚为

test:test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

pwms = &lt;&amp;pwm0 26 5000000&gt;;

};

### MCU侧GPIO使用方法 {#mcu-gpio}

MCU端同样提供了gpio的支持方法，如下：

*   GPIO_DIRECTION GpioGetDirection(unsigned int port);
*   int GpioSetDirection(unsigned int port, GPIO_DIRECTION direction);
*   GPIO_LEVEL GpioGetLevel(unsigned int port);
*   int GpioSetLevel(unsigned int port, GPIO_LEVEL level);
*   int GpioEnableTrigger(unsigned int port, GPIO_TRIGGER_EDGE edge, GPIO_CALLBACK callback, void *pdata);
*   int GpioDisableTrigger(unsigned int port);
*   int GpioEnablePWM(unsigned int port, unsigned int freq, unsigned int duty);
*   int GpioDisablePWM(unsigned int port);

例子如下：

*   GpioSetDirection(10, GPIO_DIRECTION_OUTPUT) //设置ck的PD1PORT10为输出
*   GpioSetLevel(33, GPIO_LEVEL_HIGH) //设置ck的PD1PORT33为高电平

### 应用层GPIO使用方法 {#gpio-2}

应用层可以通过/sys/class/gpio/中的sysfs节点来控制gpio。

echo pin number进/sys/class/gpio/export 生成gpioxx目录，其换算关系如下：

*   ARM域的port echo进export的数字就是PD2PORTXX的数字
*   MCU域的port echo进export的数字是PD1PORTXX的数字加上64

例子如下：

控制PD2PORT42脚

echo 42 &gt; /sys/class/gpio/export

cd /sys/class/gpio/gpio42

cat direction //查看GPIO的输入输出属性

echo out &gt; direction //设置管脚为输出

echo 1 &gt; value //设置管脚为高电平

控制PD1PORT10脚

echo 74 &gt; /sys/class/gpio/export

cd /sys/class/gpio/gpio74

cat direction //查看GPIO的输入输出属性

echo out &gt; direction //设置管脚为输出

echo 1 &gt; value //设置管脚为高电平

pwmchip0对应gpa0组，pwmchip32对应gpa1组，应用层控制pwm输出例子如下:

控制PD2PORT26脚

echo 26 &gt; /sys/class/pwm/pwmchip0/export

cd /sys/class/pwm/pwmchip0/pwm26

echo 0 &gt; enable //关闭此port的pwm

echo 100000 &gt; period //周期设置为100 us

echo 50000 &gt; duty_cycle //高电平持续时间设置为50 us

echo 1 &gt; enable

控制PD2PORT33脚

echo 1 &gt; /sys/class/pwm/pwmchip32/export

cd /sys/class/pwm/pwmchip32/pwm1

echo 0 &gt; enable //关闭此port的pwm

echo 100000 &gt; period //周期设置为100 us

echo 50000 &gt; duty_cycle //高电平持续时间设置为50 us

echo 1 &gt; enable