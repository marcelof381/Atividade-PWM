#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint SERVO = 12;            // Pino GPIO conectado ao servo motor
const uint16_t PERIOD = 20000;    // Período do PWM (20ms para 50Hz)
const float DIVIDER_PWM = 125.0;  // Divisor de clock para o PWM
uint16_t pwm_level = 500;         // Valor inicial do ciclo de trabalho (duty cycle)

// Função para configurar o PWM no pino do servo
void setup_pwm()
{
    uint slice;
    gpio_set_function(SERVO, GPIO_FUNC_PWM); // Configura o pino do servo como saída PWM
    slice = pwm_gpio_to_slice_num(SERVO);    // Obtém o slice do PWM correspondente ao pino do servo
    pwm_set_clkdiv(slice, DIVIDER_PWM);      // Define o divisor de clock do PWM
    pwm_set_wrap(slice, PERIOD);             // Define o período do PWM (duração do ciclo)
    pwm_set_gpio_level(SERVO, pwm_level);    // Define o nível inicial do PWM (posição inicial do servo)
    pwm_set_enabled(slice, true);            // Habilita o PWM no slice correspondente

    // Define a posição do servo para 180° e aguarda 5 segundos
    pwm_set_gpio_level(SERVO, 2400);
    sleep_ms(5000);

    // Define a posição do servo para 90° e aguarda 5 segundos
    pwm_set_gpio_level(SERVO, 1470);
    sleep_ms(5000);

    // Define a posição do servo para 0° e aguarda 5 segundos
    pwm_set_gpio_level(SERVO, 500);
    sleep_ms(5000);
}

int main()
{
    stdio_init_all(); // Inicializa a interface padrão de entrada e saída
    setup_pwm();      // Configura o PWM e posiciona o servo em diferentes ângulos

    while (true)
    {
        // Movimenta o servo suavemente de 0° para 180° (incremento de 5µs a cada 10ms)
        for (int pwm_level = 500; pwm_level <= 2400; pwm_level += 5) {
            pwm_set_gpio_level(SERVO, pwm_level); // Ajusta o PWM para o novo valor
            sleep_ms(10);
        }

        // Movimenta o servo suavemente de 180° para 0° (decremento de 5µs a cada 10ms)
        for (int pwm_level = 2400; pwm_level >= 500; pwm_level -= 5) {
            pwm_set_gpio_level(SERVO, pwm_level); // Ajusta o PWM para o novo valor
            sleep_ms(10);
        }
    }
}
