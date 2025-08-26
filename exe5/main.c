#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

const int BTN = 28;
volatile int fall = 0;
volatile int rise = 0;

void btn_callback(uint gpio, uint32_t events){
  if (gpio == BTN && events == 0x4){
    fall = 1;
  }
  if (gpio == BTN && events == 0x8){
    rise = 1;
  }
}

int main() {
    stdio_init_all();

    gpio_init(BTN);
    gpio_set_dir(BTN,GPIO_IN);
    gpio_pull_up(BTN);

    gpio_set_irq_enabled_with_callback(BTN,GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,true,&btn_callback);

    unsigned int start_ms = 0;
    while (true) {
        if (fall){
            start_ms = to_ms_since_boot(get_absolute_time());
            fall = 0;
        }
        if(rise){
            int now = to_ms_since_boot(get_absolute_time());
            if (now-start_ms>800){
                printf("Aperto longo\n");
            } else printf("Aperto curto\n");
            rise = 0;
        }
    }
}
