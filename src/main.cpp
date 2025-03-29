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
 
#define BLINKY_GPIO_PORT GPIOA
#define BLINKY_GPIO_PIN GPIO_Pin_15
#define BLINKY_CLOCK_ENABLE RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define BLINKY_GPIO_PORT_PB4 GPIOB
#define BLINKY_GPIO_PIN_PB4 GPIO_Pin_4
#define BLINKY_CLOCK_ENABLE_PB4 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)

void Delay_Init(void);
void Delay_Ms(uint32_t n);
 
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
 
    GPIO_InitTypeDef GPIO_InitStructure = {0};
 
    BLINKY_CLOCK_ENABLE;
    GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BLINKY_GPIO_PORT, &GPIO_InitStructure);

    BLINKY_CLOCK_ENABLE_PB4;
    GPIO_InitStructure.GPIO_Pin = BLINKY_GPIO_PIN_PB4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BLINKY_GPIO_PORT_PB4, &GPIO_InitStructure);
 
    uint8_t ledState_PA15 = 0;
    uint8_t ledState_PB4 = 0;
    
    while (1)
    {
        if (ledState_PA15 == 1)
        {
            GPIO_WriteBit(BLINKY_GPIO_PORT, BLINKY_GPIO_PIN, Bit_SET);
            GPIO_WriteBit(BLINKY_GPIO_PORT_PB4, BLINKY_GPIO_PIN_PB4, Bit_RESET);
        }
        else
        {
            GPIO_WriteBit(BLINKY_GPIO_PORT, BLINKY_GPIO_PIN, Bit_RESET);
            GPIO_WriteBit(BLINKY_GPIO_PORT_PB4, BLINKY_GPIO_PIN_PB4, Bit_SET);
        }
    
        ledState_PA15 ^= 1; // invert for the next run
        ledState_PB4 ^= 1; // invert for the next run
    
        Delay_Ms(500);
    }
}
