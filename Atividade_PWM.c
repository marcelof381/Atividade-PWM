#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_SERVO 7  // Pino GPIO conectado ao sinal PWM do servo

// Função para configurar o PWM para o servo
void setup_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(gpio); // Obtém o slice PWM correspondente
    pwm_set_clkdiv(slice, 64.0); // Define o divisor de clock para ajustar a frequência
    pwm_set_wrap(slice, 3906); // Define o período do PWM para 50Hz (20ms)
    pwm_set_enabled(slice, true); // Habilita o PWM no slice correspondente
}

// Função para definir o ângulo do servo (0° a 180°)
void set_servo_angle(uint gpio, int angle) {
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint duty = 195 + (angle * 10.8); // Mapeia 0°-180° para duty cycle entre 195-390
    pwm_set_gpio_level(gpio, duty); // Define o nível de PWM para o ângulo desejado
}

int main() {
    stdio_init_all();
    setup_pwm(PWM_SERVO);

    while (true) {
        for (int angle = 0; angle <= 180; angle += 10) {
            set_servo_angle(PWM_SERVO, angle);
            printf("Ângulo: %d°\n", angle);
            sleep_ms(500);
        }

        for (int angle = 180; angle >= 0; angle -= 10) {
            set_servo_angle(PWM_SERVO, angle);
            printf("Ângulo: %d°\n", angle);
            sleep_ms(500);
        }
    }
}
