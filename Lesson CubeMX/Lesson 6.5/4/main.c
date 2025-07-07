#include "stm32f1xx_hal.h"

// кнопка и светодиод
#define LED_PIN         GPIO_PIN_10  // PA10 - TIM1_CH3
#define LED_PORT        GPIOA
#define BUTTON_PIN      GPIO_PIN_12
#define BUTTON_PORT     GPIOB
#define DEBOUNCE_MS     50

// настройки ШИМ
#define PWM_TIMER       htim1
#define PWM_CHANNEL     TIM_CHANNEL_3
#define PWM_FREQ        1000        // 1 kHz
#define PWM_RESOLUTION  100         // 100 ступеней яркости (0-100%)

// уровни яркости (0-100%)
const uint8_t levels[] = {0, 20, 40, 60, 80, 100};
const uint8_t levels_count = sizeof(levels)/sizeof(levels[0]);

// глобальные переменные
TIM_HandleTypeDef htim1;
uint8_t current_brightness = 0;
uint32_t last_button_press = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
void set_pwm_brightness(uint8_t percent);
void Error_Handler(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM1_Init();

    HAL_TIM_PWM_Start(&PWM_TIMER, PWM_CHANNEL);
    set_pwm_brightness(0);
    
    while (1) {
        // Обработка кнопки с защитой от дребезга
        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET) {
            if (HAL_GetTick() - last_button_press > DEBOUNCE_MS) {
                last_button_press = HAL_GetTick();
                
                // Циклическое переключение уровней яркости
                current_brightness = (current_brightness + 1) % levels_count;
                set_pwm_brightness(levels[current_brightness]);
                
                // Ожидание отпускания кнопки
                while (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET);
            }
        }
    }
}

// Установка яркости (0-100%)
void set_pwm_brightness(uint8_t percent) {
    if (percent > 100) percent = 100;
    uint32_t pulse = (PWM_TIMER.Instance->ARR * percent) / 100;
    __HAL_TIM_SET_COMPARE(&PWM_TIMER, PWM_CHANNEL, pulse);
}

// Инициализация TIM1 для ШИМ
static void MX_TIM1_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    // настройки таймера
    PWM_TIMER.Instance = TIM1;
    PWM_TIMER.Init.Prescaler = (SystemCoreClock / (PWM_FREQ * PWM_RESOLUTION)) - 1;
    PWM_TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
    PWM_TIMER.Init.Period = PWM_RESOLUTION - 1;
    PWM_TIMER.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    PWM_TIMER.Init.RepetitionCounter = 0;
    PWM_TIMER.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_PWM_Init(&PWM_TIMER) != HAL_OK) {
        Error_Handler();
    }

    // Настройка канала ШИМ
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&PWM_TIMER, &sConfigOC, PWM_CHANNEL) != HAL_OK) {
        Error_Handler();
    }

    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&PWM_TIMER, &sBreakDeadTimeConfig) != HAL_OK) {
        Error_Handler();
    }
}

// Инициализация GPIO
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Включение тактирования
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();

    // Настройка вывода PA10
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    // Настройка кнопки PB12
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
}

// Конфигурация тактовой частоты
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Настройка HSI (внутренний генератор 8 MHz)
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Настройка делителей (без PLL)
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // 8 MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;   // 8 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;   // 8 MHz
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {
    while(1) {
        // Аварийная индикация - быстрое мигание
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
        HAL_Delay(100);
    }
}
