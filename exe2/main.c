#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED = 4;
const int BTN = 28;
volatile int pressed = 0;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4) {
    pressed = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(LED);
  gpio_set_dir(LED,GPIO_OUT);
  
  gpio_init(BTN);
  gpio_set_dir(BTN,GPIO_IN);
  gpio_pull_up(BTN);

  gpio_set_irq_enabled_with_callback(BTN,GPIO_IRQ_EDGE_FALL,true , &btn_callback);
  int led_state = 0;
  while(true){
    if(pressed){
      led_state = !led_state;
      gpio_put(LED,led_state);
      pressed = 0;
    }
  }
}
