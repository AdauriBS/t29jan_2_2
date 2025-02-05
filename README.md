# Controle de LEDs com Raspberry Pi Pico

Este projeto utiliza uma Raspberry Pi Pico para controlar três LEDs (vermelho, azul e verde) e um botão. O comportamento dos LEDs é gerenciado por um temporizador e o estado do botão, com implementação de debouncing para evitar leituras falsas.

## Funcionalidades

- Controle de três LEDs conectados aos pinos GPIO 11, 12 e 13.
- Sequência de desligamento dos LEDs em etapas, controlada por um temporizador de 3 segundos.
- O botão só reinicia a sequência após o último LED ser desligado.
- Implementação de debouncing para evitar falsos acionamentos do botão.
- Exibição do estado atual e do pino dos LEDs desligados no console.

## Requisitos de Hardware

- Raspberry Pi Pico
- 3 LEDs (vermelho, azul e verde)
- 3 resistores de 220Ω (para os LEDs)
- 1 botão push
- 1 resistor de 10kΩ (para pull-up do botão)
- Jumpers e protoboard

## Conexões

- **LED Azul:** GPIO 11
- **LED Vermelho:** GPIO 12
- **LED Verde:** GPIO 13
- **Botão:** GPIO 5 (com resistor de pull-up)

## Lógica de Funcionamento

1. **Estado 0:** Todos os LEDs ligados.
2. **Estado 1:** LED Azul apagado (Pino 11), LEDs Vermelho e Verde ligados.
3. **Estado 2:** LED Vermelho apagado (Pino 12), LED Verde ligado.
4. **Estado 3:** LED Verde apagado (Pino 13), todos os LEDs desligados.
5. O botão só reinicia a sequência quando o Estado 3 for alcançado.

## Compilação e Execução

1. Instale o SDK do Raspberry Pi Pico.
2. Compile o código com o CMake.
3. Carregue o arquivo UF2 na placa.
4. Monitore a saída serial para visualizar os estados dos LEDs.

## Exemplo de Saída no Console

```
Estado 0: Todos os LEDs ligados
Estado 1: LED Azul apagado (Pino 11), LEDs Vermelho e Verde ligados
Estado 2: LED Vermelho apagado (Pino 12), LED Verde ligado
Estado 3: LED Verde apagado (Pino 13), todos os LEDs desligados
Botão pressionado, reiniciando a sequência...
```

## Licença

Este projeto é de uso livre para fins educacionais e de aprendizado.

