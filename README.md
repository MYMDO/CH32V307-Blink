 # [CH32V307-Blink](https://wch-ic.com/products/CH32V307.html) 

 ## [32-bit Interconnected RISC-V MCU CH32V307](https://github.com/openwch/ch32v307)
 ## [CH32V307VCT6 RISC-V based development board](https://github.com/yym36100/RISC-V_CH32V307VCT6)
 
 ---

The code configures a microcontroller to control two LEDs and one push-button. Here's a simple breakdown:

- **Initialization:**  
  - Two output pins are set up for the LEDs (one on PA15 and one on PB4).  
  - An input pin is set up for a push-button (on PB3) using an internal pull-up, so the button is active low.

- **Main Loop Behavior:**  
  - The program continuously checks if the button is pressed. It uses a small delay (debounce) to ignore any false triggers.  
  - When the button is detected as pressed, it toggles a flag (`blinkingEnabled`) that controls whether the LEDs blink or not.
  
- **LED Blinking:**  
  - If blinking is enabled, the code alternates which LED is on: when PA15 is on, PB4 is off and vice versa.
  - A delay of 500 milliseconds is used between toggles.
  
- **Button Effect:**  
  - If blinking is disabled, both LEDs are turned off regardless of their previous state.

Overall, the program lets you control whether two LEDs blink alternately or stay off by pressing a button.

 ---
 
This code makes two LEDs blink in a cycle.

Here's what it does:

 1. It turns on one LED (PA15) and turns off the other LED (PB4).
 2. Then, it waits for a short time (500 milliseconds).
 3. Next, it turns off the first LED (PA15) and turns on the second LED (PB4).
 4. It waits again for a short time (500 milliseconds).
 5. It keeps repeating steps 1-4, so the LEDs keep blinking in a cycle.

Think of it like a seesaw: when one LED is on, the other is off, and they keep switching back and forth.

---

## Features

  -  Qingke V4F processor, up to 144MHz system clock frequency.
  -  Single-cycle multiplication and hardware division. Hardware float point unit (FPU).
  -  64KB SRAM, 256KB Flash.
  -  Supply voltage: 2.5V/3.3V. GPIO unit is supplied independently.
  -  Low-power modes: sleep/stop/standby.
  -  Power-on/power-down reset (POR/PDR), programmable voltage detector (PVD).
  -  2 general DMA controllers, 18 channels in total.
  -  4 amplifiers.
  -  One true random number generator (TRNG).
  -  2 x 12-bit DAC.
  -  2-unit 16-channel 12-bit ADC, 16-channel TouchKey.
  -  10 timers.
  -  USB2.0 full-speed OTG interface.
  -  USB2.0 high-speed host/device interface (built-in 480Mbps PHY).
  -  3 USARTs, 5 UARTs.
  -  2 CAN interfaces (2.0B active).
  -  SDIO interface, FSMC interface, DVP.
  -  2 IIC interfaces, 3 SPI interfaces, 2 IIS interfaces.
  -  Gigabit Ethernet controller ETH (built-in 10M PHY).
  -  80 I/O ports, can be mapped to 16 external interrupts;
  -  CRC calculation unit, 96-bit unique ID.
  -  Serial 2-wire debug interface.
  -  Packages: LQFP64M, LQFP100.
