#pragma once
#define OLED_DISPLAY_128X32

#define MASTER_LEFT
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 6000


#define I2C1_SCL_PIN        GP1
#define I2C1_SDA_PIN        GP0
#define I2C_DRIVER I2CD0
#define OLED_BRIGHTNESS 128

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP16     // USART TX pin
#define SERIAL_USART_RX_PIN GP17    // USART RX pin
#define ENCODER_A_PINS { GP19 }
#define ENCODER_B_PINS { GP18 }