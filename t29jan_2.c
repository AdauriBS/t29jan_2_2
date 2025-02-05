#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos para os LEDs e botão
#define LED_RED 12   // Pino 12 para LED vermelho
#define LED_BLUE 11  // Pino 11 para LED azul
#define LED_GREEN 13 // Pino 13 para LED verde
#define BUTTON_PIN 5

// Variáveis globais para controlar o estado dos LEDs e o botão
int state = 4;  // Estado inicial com todos os LEDs apagados
bool button_pressed = false; // Estado do botão
bool last_button_state = false; // Estado anterior do botão para debouncing

// Função de callback chamada a cada 3 segundos
bool turn_off_callback(struct repeating_timer *t) {
    // Alterna os estados dos LEDs
    if (state == 0) {
        gpio_put(LED_BLUE, 0);
        printf("Estado 1: LED Azul apagado (Pino 11), LED Vermelho e Verde ligados\n");
        printf("GPIO 11 recebeu FALSE\n");
        state = 1;
    } else if (state == 1) {
        gpio_put(LED_RED, 0);
        printf("Estado 2: LED Vermelho apagado (Pino 12), azul apagado e verde aceso\n");
        printf("GPIO 12 recebeu FALSE\n");
        state = 2;
    } else if (state == 2) {
        gpio_put(LED_GREEN, 0);
        printf("Estado 3: LED Verde apagado (Pino 13), LED azul e vermelho apagados\n");
        printf("GPIO 13 recebeu FALSE\n");
        state = 3;
    } else if (state == 3) {
        printf("Estado 4: Todos os LEDs apagados\n");
        state = 4; // Fim do ciclo, aguardando botão
    }

    return true;  // Continua chamando o callback
}

// Função para verificar o estado do botão com debouncing
void check_button() {
    bool current_button_state = !gpio_get(BUTTON_PIN); // Botão ativo em nível baixo

    if (current_button_state && !last_button_state && state == 4) {
        // Transição de não pressionado para pressionado e LEDs apagados
        button_pressed = true;
        printf("Botão pressionado\n");
    }

    last_button_state = current_button_state; // Atualiza o estado anterior
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial

    // Inicializa os pinos dos LEDs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Inicializa o pino do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Ativa o resistor de pull-up para o botão

    // Configura o temporizador para alternar o estado dos LEDs a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, turn_off_callback, NULL, &timer);

    while (true) {
        check_button();  // Verifica o botão e faz o debouncing

        // Quando o botão for pressionado e os LEDs estiverem desligados, inicia a sequência
        if (button_pressed) {
            gpio_put(LED_RED, 1);
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_GREEN, 1);
            printf("Estado 0: Todos os LEDs ligados\n");
            state = 0;  // Reinicia a sequência
            button_pressed = false;  // Reseta o estado do botão
        }

        sleep_ms(100);  // Pausa para evitar alta carga de CPU
    }

    return 0;
}
