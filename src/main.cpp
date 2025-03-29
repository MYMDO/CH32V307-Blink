#if defined(CH32V00X)
#include <ch32v00x.h>
// #elif defined(CH32V10X)
// #include <ch32v10x.h>
// #elif defined(CH32V20X)
// #include <ch32v20x.h>
#elif defined(CH32V30X)
#include <ch32v30x.h>
#endif
#include <debug.h>
 
#define BLINKY_GPIO_PORT_PA15 GPIOA
#define BLINKY_GPIO_PIN_PA15 GPIO_Pin_15
#define BLINKY_CLOCK_ENABLE_PA15 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define BLINKY_GPIO_PORT_PB4 GPIOB
#define BLINKY_GPIO_PIN_PB4 GPIO_Pin_4
#define BLINKY_CLOCK_ENABLE_PB4 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)

// --- New definitions for control button on PB3 ---
#define CONTROL_GPIO_PORT_PB3 GPIOB
#define CONTROL_GPIO_PIN_PB3 GPIO_Pin_3
#define CONTROL_CLOCK_ENABLE_PB3 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)

void Delay_Init(void); // Initialize delay function
void Delay_Ms(uint32_t n); // Delay in milliseconds
 
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group
    SystemCoreClockUpdate(); // Update system clock
    Delay_Init(); // Initialize delay function
 
    GPIO_InitTypeDef GPIO_InitStructure = {0};  // Initialize structure to zero
 
    BLINKY_CLOCK_ENABLE_PA15; // Enable clock for GPIOA
    GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN_PA15; // Pin 15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz speed
    GPIO_Init(BLINKY_GPIO_PORT_PA15, &GPIO_InitStructure); // Initialize GPIOA for pin 15

    BLINKY_CLOCK_ENABLE_PB4;
    GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN_PB4; // Pin 4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz speed
    GPIO_Init(BLINKY_GPIO_PORT_PB4, &GPIO_InitStructure); // Initialize GPIOB for pin 4
 
    // --- Initialize control button on PB3 ---
    CONTROL_CLOCK_ENABLE_PB3; // Enable clock for GPIOB for PB3
    GPIO_InitStructure.GPIO_Pin = CONTROL_GPIO_PIN_PB3; // Button on pin 3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-up
    GPIO_Init(CONTROL_GPIO_PORT_PB3, &GPIO_InitStructure);
 
    uint8_t ledState_PA15 = 0; // Initialize LED state for PA15
    uint8_t ledState_PB4  = 0; // Initialize LED state for PB4
    uint8_t blinkingEnabled = 1; // 1 = blinking enabled, 0 = LEDs off
 
    while (1)
    {
        // Poll control button on PB3 (active low)
        if(GPIO_ReadInputDataBit(CONTROL_GPIO_PORT_PB3, CONTROL_GPIO_PIN_PB3) == Bit_RESET)
        {
            Delay_Ms(10); // Debounce delay
            if(GPIO_ReadInputDataBit(CONTROL_GPIO_PORT_PB3, CONTROL_GPIO_PIN_PB3) == Bit_RESET)
            {
                blinkingEnabled = !blinkingEnabled; // Toggle blinking state
                // Wait until button is released
                while(GPIO_ReadInputDataBit(CONTROL_GPIO_PORT_PB3, CONTROL_GPIO_PIN_PB3) == Bit_RESET);
                Delay_Ms(10); // Debounce after release
            }
        }
 
        if(blinkingEnabled)
        {
            if (ledState_PA15 == 1)
            {
                GPIO_WriteBit(BLINKY_GPIO_PORT_PA15, BLINKY_GPIO_PIN_PA15, Bit_SET);   // Turn on LED on PA15
                GPIO_WriteBit(BLINKY_GPIO_PORT_PB4,  BLINKY_GPIO_PIN_PB4,  Bit_RESET);  // Turn off LED on PB4
            }
            else
            {
                GPIO_WriteBit(BLINKY_GPIO_PORT_PA15, BLINKY_GPIO_PIN_PA15, Bit_RESET);  // Turn off LED on PA15
                GPIO_WriteBit(BLINKY_GPIO_PORT_PB4,  BLINKY_GPIO_PIN_PB4,  Bit_SET);    // Turn on LED on PB4
            }
    
            ledState_PA15 ^= 1; // Invert LED state for PA15
            ledState_PB4  ^= 1; // Invert LED state for PB4
        }
        else
        {
            // When blinking is disabled, force both LEDs off
            GPIO_WriteBit(BLINKY_GPIO_PORT_PA15, BLINKY_GPIO_PIN_PA15, Bit_RESET); // Turn off LED on PA15
            GPIO_WriteBit(BLINKY_GPIO_PORT_PB4,  BLINKY_GPIO_PIN_PB4,  Bit_RESET); // Turn off LED on PB4
        }
 
        Delay_Ms(500); // 500ms delay
    }
}
