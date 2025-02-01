#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#define LED_PIN 15
#define BUTTON_PIN 16

// Função para inicializar o hardware
void init_hardware()
{
    stdio_init_all(); // Inicializa a comunicação serial
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o resistor de pull-up interno
}

// Função principal
int main()
{
    init_hardware();

    while (1)
    {
        // Aguarda um tempo aleatório antes de acender o LED
        int delay_time = rand() % 5000 + 1000; // Entre 1 e 6 segundos
        sleep_ms(delay_time);

        // Acende o LED
        gpio_put(LED_PIN, 1);

        // Marca o tempo inicial
        absolute_time_t start_time = get_absolute_time();

        // Aguarda o botão ser pressionado
        while (gpio_get(BUTTON_PIN) == 1)
        {
            // Espera...
        }

        // Marca o tempo final
        absolute_time_t end_time = get_absolute_time();

        // Apaga o LED
        gpio_put(LED_PIN, 0);

        // Calcula o tempo de reação
        int64_t reaction_time = absolute_time_diff_us(start_time, end_time);

        // Exibe o tempo de reação no console
        printf("Tempo de reacao: %lld ms\n", reaction_time / 1000);

        // Aguarda um pouco antes de reiniciar o jogo
        sleep_ms(2000);
    }

    return 0;
}