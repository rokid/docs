# PINMUX and GPIO Setup {#pinmux-and-gpio-setup}

The PINMUX of Kamino18 is divided into MCU and ARM two domains. The PINMUX in ARM domain will be clear when system enter sleep state and it will be re-setup in u-boot-spl.bin when system resume from sleep state.（The detail will be illustrated in the chapter 4.1）