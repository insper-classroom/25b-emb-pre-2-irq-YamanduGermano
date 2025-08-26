#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_R = 28;
const int BTN_G = 26;
const int LED_R = 4;
const int LED_G = 6;

volatile int press_r = 0;
volatile int press_g = 0;

void btn_callback(uint gpio, uint32_t events){
  if (gpio == BTN_R && events == 0x4){
    press_r = 1;
  }
  if (gpio == BTN_G && events == 0x4){
    press_g = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_G);
  gpio_set_dir(BTN_G,GPIO_IN);
  gpio_pull_up(BTN_G);

  gpio_init(BTN_R);
  gpio_set_dir(BTN_R,GPIO_IN);
  gpio_pull_up(BTN_R);

  gpio_init(LED_G);
  gpio_set_dir(LED_G,GPIO_OUT);

  gpio_init(LED_R);
  gpio_set_dir(LED_R,GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_R,GPIO_IRQ_EDGE_FALL,true,&btn_callback);
  gpio_set_irq_enabled_with_callback(BTN_G,GPIO_IRQ_EDGE_FALL,true,&btn_callback);

  int status_led_r = 0, status_led_g = 0;
  while (true) {
    if (press_g){
      press_g = 0;
      status_led_g = !status_led_g;
      gpio_put(LED_G,status_led_g);
    }

    if (press_r){
      press_r = 0;
      status_led_r = !status_led_r;
      gpio_put(LED_R,status_led_r);
    }
  }
}
