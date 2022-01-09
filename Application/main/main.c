#include "boards.h"
#include "nrf_delay.h"
#include <stdbool.h>
#include <stdint.h>

int button1_state, button2_state, button4_state;

int main(void) {

  // Configure the buttons as inputs with pull-ups
  nrf_gpio_cfg_input(BUTTON_1, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_2, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_4, NRF_GPIO_PIN_PULLUP);

  // Configure the leds as outputs
  nrf_gpio_cfg_output(LED_1);
  nrf_gpio_cfg_output(LED_2);
  nrf_gpio_cfg_output(LED_4);

  while (true) {

    // Read the buttons states  
    button1_state = nrf_gpio_pin_read(BUTTON_1);
    button2_state = nrf_gpio_pin_read(BUTTON_2);
    button4_state = nrf_gpio_pin_read(BUTTON_4);

    if(button1_state == 0) nrf_gpio_pin_clear(LED_1);
    else nrf_gpio_pin_set(LED_1);                     

    if(button2_state == 0) nrf_gpio_pin_clear(LED_2);
    else nrf_gpio_pin_set(LED_2);

    if(button4_state == 0) nrf_gpio_pin_clear(LED_4);
    else nrf_gpio_pin_set(LED_4);
  }
}