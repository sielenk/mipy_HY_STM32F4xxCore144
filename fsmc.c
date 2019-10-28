#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc_ex.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "stm32f4xx_hal_sram.h"


void fsmc_sram_init() {
    __HAL_RCC_FSMC_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
        .Alternate = GPIO_AF12_FSMC
    };

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | 
               GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
               GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
               GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
               GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &gpio);    

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | 
               GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
               GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
               GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
               GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio);    

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
               GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
               GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &gpio);    

    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
               GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
               GPIO_PIN_6 | GPIO_PIN_9 | GPIO_PIN_10;
    HAL_GPIO_Init(GPIOG, &gpio);    

    SRAM_HandleTypeDef hsram = {
        .Instance = FSMC_NORSRAM_DEVICE,
        .Extended = FSMC_NORSRAM_EXTENDED_DEVICE,

        .Init = {
            .NSBank          = FSMC_NORSRAM_BANK2,
            .DataAddressMux  = FSMC_DATA_ADDRESS_MUX_DISABLE,
            .MemoryType      = FSMC_MEMORY_TYPE_PSRAM,
            .MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16,
        },
    };
    FSMC_NORSRAM_TimingTypeDef SRAM_Timing = {
        .AddressSetupTime = 3,
        .DataSetupTime = 8,
    };

    HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing);
}



void board_init() {
    fsmc_sram_init();
}
