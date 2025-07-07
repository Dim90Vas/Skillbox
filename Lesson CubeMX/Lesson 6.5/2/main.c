#include "stm32f1xx_hal.h"

#define LED_PIN     GPIO_PIN_12
#define LED_PORT    GPIOB
#define TIM_HANDLE  htim1

TIM_HandleTypeDef htim1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
void Error_Handler(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM1_Init();
    
    // Настройка прерывания таймера
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
    
    // Запуск таймера
    HAL_TIM_Base_Start_IT(&TIM_HANDLE);
    
    while (1) {
        // Основной цикл
    }
}

// Обработчик прерывания TIM1
void TIM1_UP_IRQHandler(void) {
    if (__HAL_TIM_GET_FLAG(&TIM_HANDLE, TIM_FLAG_UPDATE) != RESET) {
        __HAL_TIM_CLEAR_FLAG(&TIM_HANDLE, TIM_FLAG_UPDATE);
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    }
}

// Инициализация таймера TIM1
static void MX_TIM1_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    TIM_HANDLE.Instance = TIM1;
    TIM_HANDLE.Init.Prescaler = 8000 - 1;    // 8 MHz / 8000 = 1 kHz
    TIM_HANDLE.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_HANDLE.Init.Period = 1000 - 1;       // 1 kHz / 1000 = 1 Hz
    TIM_HANDLE.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM_HANDLE.Init.RepetitionCounter = 0;
    TIM_HANDLE.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    
    if (HAL_TIM_Base_Init(&TIM_HANDLE) != HAL_OK) {
        Error_Handler();
    }
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&TIM_HANDLE, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&TIM_HANDLE, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

// Инициализация GPIO
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
    
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}

// Конфигурация тактовой частоты
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {
    while(1) {
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
        HAL_Delay(100);
    }
}



