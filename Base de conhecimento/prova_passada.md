Você foi contratado para integrar a equipe de tecnologia da prefeitura de São Paulo e sua missão era criar um protótipo funcional de automação para a árvore de Natal do Parque Villa Lobos. A automação deveria ser controlada remotamente por uma dashboard baseada no protocolo MQTT, monitorando o estado dos LEDs que representavam os segmentos da árvore e utilizando um botão, um sensor de luz (LDR) e um relé.

## Objetivo Principal:

Desenvolver uma prova de conceito com as seguintes funcionalidades:
- Medição contínua do sinal analógico de um sensor LDR, sem travar o programa.
- Controle do estado dos LEDs com base no valor lido pelo LDR.
- Acionamento manual de um relé usando um botão de pressão.
- Publicação das leituras do LDR e do estado dos LEDs em uma dashboard via MQTT.
- Encapsulamento de partes do código em funções e classes para boa organização.

Etapas Realizadas:

- Medição do Sinal Analógico do LDR:
O sensor LDR foi configurado para medir a intensidade da luz ambiente. O valor analógico era lido a cada 1 segundo utilizando a função millis() para evitar o uso de delay() e garantir que o código permanecesse responsivo.

- Configuração do Circuito:
O LDR foi conectado a um pino analógico do ESP32 com um resistor em configuração pull-down para estabilizar o sinal.

- Controle dos LEDs Baseado no LDR:
Quando o valor lido no LDR ultrapassava 50% do range da entrada analógica:
O LED azul piscava a cada 500ms usando delay().
O LED vermelho permanecia apagado.
- Caso contrário:
O LED vermelho permanecia aceso continuamente.
O LED azul ficava apagado.

- Botão de Pressão para Controlar o Relé: 
Um botão em configuração pull-down foi usado para ativar um módulo relé apenas enquanto fosse pressionado. Quando ativado, uma mensagem era exibida no Monitor Serial.

- Publicação MQTT na Dashboard:
Os dados do LDR e o estado dos LEDs eram enviados a uma dashboard MQTT, que indicava se o LED azul e o LED vermelho estavam ligados ou desligados.
Estruturação do Código:
Funções: Criadas para encapsular as leituras do LDR e o controle dos LEDs.
Classe: Criada para encapsular o comportamento do relé e do botão, abstraindo a lógica de acionamento.

- Entrega Final:
O projeto foi entregue em formato ZIP contendo:
O código-fonte completo do projeto, organizado em funções e classes.
Capturas de tela do simulador, demonstrando:
A leitura analógica do LDR.
O controle dos LEDs (ligado/desligado) com base nos valores do LDR.
O acionamento do relé pelo botão.
O envio dos dados para a dashboard MQTT.
Além disso, foram incluídas capturas de tela da dashboard configurada para monitorar os valores e estados enviados pelo ESP32.
