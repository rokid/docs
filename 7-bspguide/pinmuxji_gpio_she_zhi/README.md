# PINMUX及GPIO设置 {#pinmux-gpio}

Kamino18的PINMUX分为MCU和ARM两个域。其中ARM域中的PINMUX在系统深度休眠时状态会复位，系统从深度休眠唤醒时PINMUX会在u-boot-spl.bin中重置（具体在4.1中详述）。