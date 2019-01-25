## ARM Domain PINMUX Setup {#arm-domain-pinmux-setup}

ARM domain has 52 pins（id）which can be setup. Every pin has its own functions accordingly as the below table：

| **id** | **function0** | **function1** | **function2** | **function3** | **function4** | **function5** |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | BTDAT00 | PD2PORT00 |  |  |  |  |
| 1 | BTDAT01 | PD2PORT01 |  |  |  |  |
| 2 | BTDAT02 | PD2PORT02 |  |  |  |  |
| 3 | BTDAT03 | PD2PORT03 |  |  |  |  |
| 4 | BTCLKIN | PD2PORT04 |  |  |  |  |
| 5 | BTRESET | PD2PORT05 |  |  |  |  |
| 6 | BTCLKVSYNC | PD2PORT06 |  |  |  |  |
| 7 | BTCLKHREF | PD2PORT07 |  |  |  |  |
| 8 | BTCLKOUT | PD2PORT08 |  |  |  |  |
| 9 | BTDAT04 | SDA2 | SPI1SCK | PD2PORT09 |  |  |
| 10 | BTDAT05 | SCL2 | SPI1MOSI | PD2PORT10 |  |  |
| 11 | BTDAT06 | UART2RX | SPI1CSn | PD2PORT11 |  |  |
| 12 | BTDAT07 | UART2TX | SPI1MISO | NUARTTX | AUARTTX | PD2PORT12 |
| 13 | BTDAT08 | PD2PORT13 |  |  |  |  |
| 14 | BTDAT09 | PD2PORT14 |  |  |  |  |
| 15 | BTDAT10 | PD2PORT15 |  |  |  |  |
| 16 | BTDAT11 | PD2PORT16 |  |  |  |  |
| 17 | BTDAT12 | PD2PORT17 |  |  |  |  |
| 18 | BTDAT13 | PD2PORT18 |  |  |  |  |
| 19 | BTDAT14 | PD2PORT19 |  |  |  |  |
| 20 | BTDAT15 | PD2PORT20 |  |  |  |  |
| 21 | UART3RX | SD1CDn | SDA3 | PD2PORT21 |  |  |
| 22 | UART3TX | SD1DAT1 | SCL3 | PD2PORT22 |  |  |
| 23 | DBGTDI | SD1DAT0 | SPI2SCK | PD2PORT23 |  |  |
| 24 | DBGTDO | SD1CLK | SPI2MOSI | PD2PORT24 |  |  |
| 25 | DBGTMS | SD1CMD | SPI2CSn | PD2PORT25 |  |  |
| 26 | DBGTCK | SD1DAT3 | SPI2MISO | PD2PORT26 |  |  |
| 27 | DBGTRST | SD1DAT2 | PD2PORT27 |  |  |  |
| 28 | UART2RX | SDA2 | PD2PORT28 |  |  |  |
| 29 | UART2TX | SCL2 | PD2PORT29 |  |  |  |
| 30 | SPI1SCK | NDBGTDI | ADBGTDI | PD2PORT30 |  |  |
| 31 | SPI1MOSI | NDBGTDO | ADBGTDO | PD2PORT31 |  |  |
| 32 | SPI1CSn | NDBGTMS | ADBGTMS | PD2PORT32 |  |  |
| 33 | SPI1MISO | NDBGTCK | ADBGTCK | PD2PORT33 |  |  |
| 34 | SPI2SCK | NDBGTRST | ADBGTRST | PD2PORT34 |  |  |
| 35 | SPI2MOSI | PD2PORT35 |  |  |  |  |
| 36 | SPI2CSn | PD2PORT36 |  |  |  |  |
| 37 | SPI2MISO | PD2PORT37 |  |  |  |  |
| 38 | SD0CDn | PD2PORT38 |  |  |  |  |
| 39 | SD0DAT1 | PD2PORT39 |  |  |  |  |
| 40 | SD0DAT0 | PD2PORT40 |  |  |  |  |
| 41 | SD0CLK | PD2PORT41 |  |  |  |  |
| 42 | SD0CMD | PD2PORT42 |  |  |  |  |
| 43 | SD0DAT3 | PD2PORT43 |  |  |  |  |
| 44 | SD0DAT2 | PD2PORT44 |  |  |  |  |
| 45 | SD1CDn | PD2PORT45 |  |  |  |  |
| 46 | SD1DAT1 | PD2PORT46 |  |  |  |  |
| 47 | SD1DAT0 | PD2PORT47 |  |  |  |  |
| 48 | SD1CLK | PD2PORT48 |  |  |  |  |
| 49 | SD1CMD | PD2PORT49 |  |  |  |  |
| 50 | SD1DAT3 | PD2PORT50 |  |  |  |  |
| 51 | SD1DAT2 | PD2PORT51 |  |  |  |  |

The PINMUX in ARM domain is setup in the below code:

$(K18DIR)/uboot/board/nationalchip/leo_k18_universal/pinmux.c

static const struct pin_config pin_table[] = {

/* id |func function0 | function1 | function2 | function3 | function4 | function5 */

{ 0, 1}, // BTDAT00 | PD2PORT00

{ 1, 1}, // BTDAT01 | PD2PORT01

{ 2, 1}, // BTDAT02 | PD2PORT02

{ 3, 1}, // BTDAT03 | PD2PORT03

…

{49, 0}, // SD1CMD | PD2PORT49

{50, 0}, // SD1DAT3 | PD2PORT50

{51, 0}, // SD1DAT2 | PD2PORT51

};

The first column stands for K18 ARM port id. The other columns stand for the port functions. According to K18 spec, PINMUX table show every ARM port functions accordingly.