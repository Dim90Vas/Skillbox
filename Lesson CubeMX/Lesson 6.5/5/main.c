#include "stm32f1xx_hal.h"

// Настройки светодиода
#define LED_PIN         GPIO_PIN_10  // PA10 - TIM1_CH3
#define LED_PORT        GPIOA

// Настройки ШИМ
#define PWM_TIM         TIM1
#define PWM_CHANNEL     TIM_CHANNEL_3
#define PWM_FREQ        1000        // 1 kHz
#define PWM_RESOLUTION  100         // 100 ступеней (0-100%)

// Настройки таймера прерываний
#define INT_TIM         TIM2
#define INT_FREQ        1           // 1 Hz

// Уровни яркости
const uint8_t levels[] = {0, 20, 40, 60, 80, 100};
const uint8_t levels_count = sizeof(levels)/sizeof(levels[0]);

// Глобальные переменные
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
uint8_t current_brightness = 0;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void set_pwm_brightness(uint8_t percent);
void Error_Handler(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();

    HAL_TIM_PWM_Start(&htim1, PWM_CHANNEL); // Запуск ШИМ
    set_pwm_brightness(0);

    HAL_TIM_Base_Start_IT(&htim2); // Запуск таймера прерываний

    while (1) {
        // Основной цикл пустой - работа в прерываниях
    }
}

// обработчик прерывания таймера
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == INT_TIM) {
        current_brightness = (current_brightness + 1) % levels_count;
        set_pwm_brightness(levels[current_brightness]);
    }
}

// Установка яркости (0-100%)
void set_pwm_brightness(uint8_t percent) {
    if (percent > 100) percent = 100;
    uint32_t pulse = (htim1.Instance->ARR * percent) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, PWM_CHANNEL, pulse);
}

//TIM1 для ШИМ
void MX_TIM1_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim1.Instance = PWM_TIM;
    htim1.Init.Prescaler = (SystemCoreClock / (PWM_FREQ * PWM_RESOLUTION)) - 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = PWM_RESOLUTION - 1;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, PWM_CHANNEL) != HAL_OK) {
        Error_Handler();
    }

    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK) {
        Error_Handler();
    }
}

//TIM2 для прерываний
void MX_TIM2_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = INT_TIM;
    htim2.Init.Prescaler = SystemCoreClock / 10000 - 1;  // Деление до 10 кГц
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10000 / INT_FREQ - 1;           // Период для 1 Гц
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
}

// GPIO
void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();

    // Настройка PA10 как выход ШИМ
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

// конфигурация тактовой частоты 
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
