## GPIO Setting {#gpio-setting}

### GPIO Domain {#gpio-domain}

The ports beginning with PD1 are MCU domain ports. The ports beginning with PD2 are ARM domain ports. The gpio groups are as below：

*   PD2PORT0 - PD2PORT31 belong to gpa0 group
*   PD2PORT32 - PD2PORT51 belong to gpa1 group
*   PD1PORT0 - PD1PORT31 belong to ck_gpa0 group
*   PD1PORT32 - PD1PORT35 belong to ck_gpa1 group

MCU only can access the gpio in MCU domain, while ARM can access the gpio in both ARM domain and MCU domain. But the gpio in MCU domain can’t provide interrupt to ARM. The gpio number is the value “PDXPORTXX % 32”.

### GPIO Utilization Method in Linux Kernel {#gpio-utilization-method-in-linux-kernel}

The example to show how to control ARM domain gpio device tree node is as below:

test: test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

test1-gpio = &lt;&amp;gpa0 1 GPIO_ACTIVE_HIGH&gt;;

};

The example to show how to control MCU domain gpio device tree node is as below:

test: test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

test1-gpio = &lt;&amp;ck_gpa0 10 GPIO_ACTIVE_HIGH&gt;;

};

Note：

Here GPIO_ACTIVE_HIGH means gpio output1 stands for high level output and gpio output0 stands for low level output. While GPIO_ACTIVE_LOW means gpio output1 stands for low level output and gpio output0 stands for high level output.

The gpio APIs for Linux kernel driver calling are as below:

*   desc = devm_gpiod_get(&amp;pdev-&gt;dev, &quot;test1&quot;, GPIOD_OUT_LOW); //Get gpio descriptor for “test1-gpio” presented in dts accordingly and setup it as output low level.
*   gpiod_direction_input(desc); //Setup desc gpio as input mode.
*   gpiod_to_irq(desc) //Get the irq number according to desc gpio.
*   gpiod_direction_output(desc,1); //Setup desc gpio as output1.
*   gpiod_set_value(desc,0); //Set desc gpio as output0.
*   gpio_level = gpiod_get_value(desc); //Get desc gpio value.
*   devm_gpiod_put(&amp;test_pdev-&gt;dev, desc); //Release desc gpio.

For the gpio in ARM domain, kernel can setup it as pwm pin，while the gpio in MCU domain doesn’t support this function. pwm0 is for gpa0 group and pwm1 is for gpa1 group. The pwm number is the value “PDXPORTXX % 32”. The pwm APIs for Linux kernel driver calling are as below:

*   struct pwm_device *devm_pwm_get(struct device *dev, const char *con_id) //Get pwm handler.
*   int pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns) //Setup pwm
*   int pwm_enable(struct pwm_device *pwm) //Enable pwm
*   void pwm_disable(struct pwm_device *pwm) //Disable pwm

Device tree node example is as below：

Control PD2PORT26 pin

test:test{

compatible = &quot;nationalchip,LEO_A7-test&quot;;

pwms = &lt;&amp;pwm0 26 5000000&gt;;

};

### GPIO Utilization Method in MCU {#gpio-utilization-method-in-mcu}

For MCU side, K18 also provide gpio APIs as below：

*   GPIO_DIRECTION GpioGetDirection(unsigned int port);
*   int GpioSetDirection(unsigned int port, GPIO_DIRECTION direction);
*   GPIO_LEVEL GpioGetLevel(unsigned int port);
*   int GpioSetLevel(unsigned int port, GPIO_LEVEL level);
*   int GpioEnableTrigger(unsigned int port, GPIO_TRIGGER_EDGE edge, GPIO_CALLBACK callback, void *pdata);
*   int GpioDisableTrigger(unsigned int port);
*   int GpioEnablePWM(unsigned int port, unsigned int freq, unsigned int duty);
*   int GpioDisablePWM(unsigned int port);

For example：

*   GpioSetDirection(10, GPIO_DIRECTION_OUTPUT) //setup ck PD1PORT10 as output
*   GpioSetLevel(33, GPIO_LEVEL_HIGH) //setup ck PD1PORT33 as high level

### GPIO Utilization Method in User Space {#gpio-utilization-method-in-user-space}

For application layer, application use the sysfs node in/sys/class/gpio/ to control gpio.

echo pin number into /sys/class/gpio/export to generate gpioxx folder, the relation is as below：

*   For the port in ARM domain, the pin number echo into export is the port number(XX) for PD2PORTXX.
*   For the port in MCU domain, the pin number echo into export is the port number plus 64(XX+64) for PD1PORTXX.

For example：

To control PD2PORT42 pin:

echo 42 &gt; /sys/class/gpio/export

cd /sys/class/gpio/gpio42

cat direction //to check the input/output character of GPIO

echo out &gt; direction //to setup the pin as output

echo 1 &gt; value //to make the pin output high level

To control PD1PORT10 pin:

echo 74 &gt; /sys/class/gpio/export

cd /sys/class/gpio/gpio74

cat direction // to check the input/output character of GPIO

echo out &gt; direction // to setup the pin as output

echo 1 &gt; value // to make the pin output high level

pwmchip0 is for gpa0 group，pwmchip32 is for gpa1 group，the example for application layer to control pwm is as below:

To control PD2PORT26 pin:

echo 26 &gt; /sys/class/pwm/pwmchip0/export

cd /sys/class/pwm/pwmchip0/pwm26

echo 0 &gt; enable //disable pwm

echo 100000 &gt; period //setup the duration for pwm as 100 us

echo 50000 &gt; duty_cycle //setup the high level time for one cycle as 50 us

echo 1 &gt; enable //enable pwm

To control PD2PORT33 pin:

echo 1 &gt; /sys/class/pwm/pwmchip32/export

cd /sys/class/pwm/pwmchip32/pwm1

echo 0 &gt; enable // disable pwm

echo 100000 &gt; period // setup the duration for pwm as 100 us

echo 50000 &gt; duty_cycle // setup the high level time for one cycle as 50 us

echo 1 &gt; enable //enable pwm