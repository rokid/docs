## MCU域PINMUX设置 {#mcu-pinmux}

MCU域中有34个pin（id）可以配置，每个pin对应的function如下表所示：

| **id** | **function0** | **function1** | **function2** | **function3** | **function4** |
| --- | --- | --- | --- | --- | --- |
| 1 | POWERDOWN | PD1PORT01 |  |  |  |
| 2 | UART0RX | PD1PORT02 |  |  |  |
| 3 | UART0TX | PD1PORT03 |  |  |  |
| 4 | OTPAVDDEN | PD1PORT04 |  |  |  |
| 5 | SDBGTDI | DDBGTDI | SNDBGTDI | PD1PORT05 |  |
| 6 | SDBGTDO | DDBGTDO | SNDBGTDO | PD1PORT06 |  |
| 7 | SDBGTMS | DDBGTMS | SNDBGTMS | PCM1INBCLK | PD1PORT07 |
| 8 | SDBGTCK | DDBGTCK | SNDBGTCK | PCM1INLRCK | PD1PORT08 |
| 9 | SDBGTRST | DDBGTRST | SNBGTRST | PCM1INDAT0 | PD1PORT09 |
| 11 | PCM1INBCLK | PD1PORT11 |  |  |  |
| 12 | PCM1INLRCK | PD1PORT12 |  |  |  |
| 13 | PCM1INDAT0 | PD1PORT13 |  |  |  |
| 14 | PCMOUTMCLK | DUARTTX | SNUARTTX | PD1PORT14 |  |
| 15 | PCMOUTDAT0 | SPDIF | PD1PORT15 |  |  |
| 16 | PCMOUTLRCK | PD1PORT16 |  |  |  |
| 17 | PCMOUTBCLK | PD1PORT17 |  |  |  |
| 18 | UART1RX | PD1PORT18 |  |  |  |
| 19 | UART1TX | PD1PORT19 |  |  |  |
| 20 | DDBGTDI | SNDBGTDI | PD1PORT20 |  |  |
| 21 | DDBGTDO | SNDBGTDO | PD1PORT21 |  |  |
| 22 | DDBGTMS | SNDBGTMS | PD1PORT22 |  |  |
| 23 | DDBGTCK | SNDBGTCK | PD1PORT23 |  |  |
| 24 | DDBGTRST | SNDBGTRST | PD1PORT24 |  |  |
| 25 | DUARTTX | SNUARTTX | PD1PORT25 |  |  |
| 26 | SDA0 | PD1PORT26 |  |  |  |
| 27 | SCL0 | PD1PORT27 |  |  |  |
| 28 | SDA1 | PD1PORT28 |  |  |  |
| 29 | SCL1 | PD1PORT29 |  |  |  |
| 30 | PCM0INDAT1 | PDMDAT3 | PD1PORT30 |  |  |
| 31 | PCM0INDAT0 | PDMDAT2 | PD1PORT31 |  |  |
| 32 | PCM0INMCLK | PDMDAT1 | PD1PORT32 |  |  |
| 33 | PCM0INLRCK | PDMDAT0 | PCM0OUTLRCK | PD1PORT33 |  |
| 34 | PCM0INBCLK | PDMCLK | PCM0OUTBCLK | PD1PORT34 |  |
| 35 | IR | PD1PORT35 |  |  |  |

MCU域的PINMUX设置统一在如下的数组中：

$(K18DIR)/vsp/mcu/board/nationalchip/leo_k18_universal/misc_board.c

static const PADMUX_PAD_CONFIG _pad_configs[] = {

/* id| func // function0 | function1 | function2 | function3 | function4 */

{ 1, 0}, // POWERDOWN | PD1PORT01 |

{ 2, 0}, // UART0RX | PD1PORT02 |

{ 3, 0}, // UART0TX | PD1PORT03 |

…

{33, 1}, // PCM0INLRCK | PDMDAT0 | PCM0OUTLRCK | PD1PORT33

{34, 1}, // PCM0INBCLK | PDMCLK | PCM0OUTBCLK | PD1PORT34

{35, 1}, // IR | PD1PORT35

};

配置表中的第一列表示芯片的port口，第二列表示port口的功能，根据硬件给出的管脚复用表，对应修改每个port口的功能即可。