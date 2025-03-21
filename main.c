/*
*   Example program for blinking led in STM32F7
*   May be used as a template
*/

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void clock_setup() {
    rcc_clock_setup_hse(&rcc_3v3[RCC_CLOCK_3V3_216MHZ], 8);
    rcc_periph_clock_enable(RCC_GPIOB);
}

static void gpio_setup() {
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
    gpio_set_output_options(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO7);
}

int main() {
    clock_setup();
    gpio_setup();

    while (1) {
        gpio_toggle(GPIOB, GPIO7);
    }
}