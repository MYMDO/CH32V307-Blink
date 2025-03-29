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

void Delay_Init(void); // Initialize delay function
void Delay_Ms(uint32_t n); // Delay in milliseconds
 
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group
    SystemCoreClockUpdate(); // Update system clock
    Delay_Init(); // Initialize delay function
 
    GPIO_InitTypeDef GPIO_InitStructure = {0};  // Initialize the structure to zero
 
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
 
    uint8_t ledState_PA15 = 0; // Initialize LED state for PA15
    uint8_t ledState_PB4 = 0; // Initialize LED state for PB4
    
    while (1)
    {
        if (ledState_PA15 == 1)
        {
            GPIO_WriteBit(BLINKY_GPIO_PORT_PA15, BLINKY_GPIO_PIN_PA15, Bit_SET); // Turn on LED on PA15
            GPIO_WriteBit(BLINKY_GPIO_PORT_PB4, BLINKY_GPIO_PIN_PB4, Bit_RESET); // Turn off LED on PB4
        }
        else
        {
            GPIO_WriteBit(BLINKY_GPIO_PORT_PA15, BLINKY_GPIO_PIN_PA15, Bit_RESET); // Turn off LED on PA15
            GPIO_WriteBit(BLINKY_GPIO_PORT_PB4, BLINKY_GPIO_PIN_PB4, Bit_SET); // Turn on LED on PB4
        }
    
        ledState_PA15 ^= 1; // invert for the next run
        ledState_PB4 ^= 1; // invert for the next run
    
        Delay_Ms(500); // 500ms delay
    }
}
