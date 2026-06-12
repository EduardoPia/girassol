#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

// Mapeamento dos pinos do Motor A (Saídas)
#define IN1A_PIN GPIO_NUM_21 
#define IN2A_PIN GPIO_NUM_22 // GPIO_NUM_19
#define IN3A_PIN GPIO_NUM_17 // GPIO_NUM_18
#define IN4A_PIN GPIO_NUM_16 // GPIO_NUM_5

// Mapeamento dos pinos do Motor B (Saídas)
#define IN1B_PIN GPIO_NUM_25 
#define IN2B_PIN GPIO_NUM_26 
#define IN3B_PIN GPIO_NUM_27 
#define IN4B_PIN GPIO_NUM_14 

// Pinos de acionamento (Entrada com Pull-Down)
#define BUTTON_PIN_A GPIO_NUM_33
#define BUTTON_PIN_B GPIO_NUM_32

// Função para configurar os pinos de entrada e saída
void setup(void)
{
    // 1. Configuração dos Pinos do Driver ULN2003 (Motor A)
    gpio_reset_pin(IN1A_PIN);
    gpio_reset_pin(IN2A_PIN);
    gpio_reset_pin(IN3A_PIN);
    gpio_reset_pin(IN4A_PIN);
    
    gpio_set_direction(IN1A_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN2A_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN3A_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN4A_PIN, GPIO_MODE_OUTPUT);

    // 2. Configuração dos Pinos do Driver ULN2003 (Motor B)
    gpio_reset_pin(IN1B_PIN);
    gpio_reset_pin(IN2B_PIN);
    gpio_reset_pin(IN3B_PIN);
    gpio_reset_pin(IN4B_PIN);
    
    gpio_set_direction(IN1B_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN2B_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN3B_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN4B_PIN, GPIO_MODE_OUTPUT);

    // 3. Configuração dos Pinos de Entrada (GPIO 13 e 16)
    gpio_reset_pin(BUTTON_PIN_A);
    gpio_set_direction(BUTTON_PIN_A, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN_A, GPIO_PULLDOWN_ONLY);

    gpio_reset_pin(BUTTON_PIN_B);
    gpio_set_direction(BUTTON_PIN_B, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN_B, GPIO_PULLDOWN_ONLY);

    printf("Setup dos motores e botoes concluido.\n");
}

// Função auxiliar para aplicar a sequência de MEIO PASSO no Motor A
void step_motor_A(int step)
{
    switch (step) {
        case 0: gpio_set_level(IN1A_PIN, 1); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 0); break;
        case 1: gpio_set_level(IN1A_PIN, 1); gpio_set_level(IN2A_PIN, 1); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 0); break;
        case 2: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 1); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 0); break;
        case 3: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 1); gpio_set_level(IN3A_PIN, 1); gpio_set_level(IN4A_PIN, 0); break;
        case 4: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 1); gpio_set_level(IN4A_PIN, 0); break;
        case 5: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 1); gpio_set_level(IN4A_PIN, 1); break;
        case 6: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 1); break;
        case 7: gpio_set_level(IN1A_PIN, 1); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 1); break;
        default: gpio_set_level(IN1A_PIN, 0); gpio_set_level(IN2A_PIN, 0); gpio_set_level(IN3A_PIN, 0); gpio_set_level(IN4A_PIN, 0); break;
    }
}

// Função auxiliar para aplicar a sequência de MEIO PASSO no Motor B
void step_motor_B(int step)
{
    switch (step) {
        case 0: gpio_set_level(IN1B_PIN, 1); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 0); break;
        case 1: gpio_set_level(IN1B_PIN, 1); gpio_set_level(IN2B_PIN, 1); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 0); break;
        case 2: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 1); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 0); break;
        case 3: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 1); gpio_set_level(IN3B_PIN, 1); gpio_set_level(IN4B_PIN, 0); break;
        case 4: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 1); gpio_set_level(IN4B_PIN, 0); break;
        case 5: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 1); gpio_set_level(IN4B_PIN, 1); break;
        case 6: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 1); break;
        case 7: gpio_set_level(IN1B_PIN, 1); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 1); break;
        default: gpio_set_level(IN1B_PIN, 0); gpio_set_level(IN2B_PIN, 0); gpio_set_level(IN3B_PIN, 0); gpio_set_level(IN4B_PIN, 0); break;
    }
}

void app_main(void)
{
    // Executa a inicialização
    setup();

    int current_step_A = 0;
    int current_step_B = 0;

    printf("Sistema pronto. Envie nivel ALTO na GPIO 33 ou 32 para girar os motores.\n");

    while (1) {
        // Lê o estado de ambos os botões no início do ciclo
        int state_A = gpio_get_level(BUTTON_PIN_A);
        int state_B = gpio_get_level(BUTTON_PIN_B);

        // --- Lógica do Motor A ---
        if (state_A == 1) {
            step_motor_A(current_step_A);
            current_step_A = (current_step_A + 1) % 8; // Agora divide por 8
        } else {
            // Desliga bobinas do Motor A se não estiver acionado
            gpio_set_level(IN1A_PIN, 0);
            gpio_set_level(IN2A_PIN, 0);
            gpio_set_level(IN3A_PIN, 0);
            gpio_set_level(IN4A_PIN, 0);
        }

        // --- Lógica do Motor B ---
        if (state_B == 1) {
            step_motor_B(current_step_B);
            current_step_B = (current_step_B + 1) % 8; // Agora divide por 8
        } else {
            // Desliga bobinas do Motor B se não estiver acionado
            gpio_set_level(IN1B_PIN, 0);
            gpio_set_level(IN2B_PIN, 0);
            gpio_set_level(IN3B_PIN, 0);
            gpio_set_level(IN4B_PIN, 0);
        }

        // --- Gerenciamento de Delay ---
        if (state_A == 1 || state_B == 1) {
            // Delay reduzido para 10ms, já que a quantidade de passos dobrou
            vTaskDelay(10 / portTICK_PERIOD_MS);
        } else {
            // Se NENHUM motor estiver rodando, mantemos o delay maior (50ms) para aliviar a CPU
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}