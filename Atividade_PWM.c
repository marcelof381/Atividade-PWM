#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint SERVO = 22;            // Pino do SERVO conectado
const uint16_t PERIOD = 20000;   // Período do PWM (valor máximo do contador)
const float DIVIDER_PWM = 125.0; // Divisor fracional do clock para o PWM
uint16_t pwm_level = 500;       // Nível inicial do PWM (duty cycle)

void setup_pwm()
{
    uint slice;
    gpio_set_function(SERVO, GPIO_FUNC_PWM); // Configura o pino do SERVO para função PWM
    slice = pwm_gpio_to_slice_num(SERVO);    // Obtém o slice do PWM associado ao pino do SERVO
    pwm_set_clkdiv(slice, DIVIDER_PWM);    // Define o divisor de clock do PWM
    pwm_set_wrap(slice, PERIOD);           // Configura o valor máximo do contador (período do PWM)
    pwm_set_gpio_level(SERVO, pwm_level);    // Define o nível inicial do PWM para o pino do SERVO
    pwm_set_enabled(slice, true);          // Habilita o PWM no slice correspondente

    pwm_set_gpio_level(SERVO, 2400); // Define o nível atual do PWM (duty cycle)
    sleep_ms(5000); 

    pwm_set_gpio_level(SERVO, 1470); // Define o nível atual do PWM (duty cycle)
    sleep_ms(5000);

    pwm_set_gpio_level(SERVO, 500); // Define o nível atual do PWM (duty cycle)
    sleep_ms(5000);
}

int main()
{
    stdio_init_all(); // Inicializa o sistema padrão de I/O
    setup_pwm();      // Configura o PWM
    while (true)
    {
        for (int pulse = 500; pulse <= 2400; pulse += 5) {
            pwm_set_gpio_level(SERVO, pwm_level); // Define o nível atual do PWM (duty cycle)
            sleep_ms(10);
        }

        for (int pulse = 2400; pulse >= 500; pulse -= 5) {
            pwm_set_gpio_level(SERVO, pwm_level); // Define o nível atual do PWM (duty cycle)
            sleep_ms(10);
        }// Atraso de 1 segundo
    }
}