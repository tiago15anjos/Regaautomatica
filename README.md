# Projeto de Rega Automática com Arduino

Este projeto utiliza um Arduino para monitorar a umidade do solo usando um sensor de umidade e acionar uma bomba de água conectada a um relé quando o solo estiver seco. A bomba é ligada automaticamente sempre que a umidade do solo cai abaixo de um limite pré-estabelecido.

## Componentes Utilizados

- 1x Arduino (Uno, Nano, ou qualquer modelo compatível)
- 1x Sensor de umidade do solo (com módulo de amplificação)
- 1x Relé de 5V
- 1x Bomba de água de 5V (ou adequada à tensão e corrente do relé)
- Jumpers (cabos de conexão)
- Cabo para conectar ao PC
  
## Esquema de Conexão

1. **Sensor de Umidade**:
   - Pino **VCC** do módulo -> Pino **5V** do Arduino.
   - Pino **GND** do módulo -> Pino **GND** do Arduino.
   - Pino **A0** do módulo -> Pino **A0** (analógico) do Arduino.

2. **Relé**:
   - Pino **IN** do relé -> Pino **7** (digital) do Arduino.
   - Pino **VCC** do relé -> Pino **5V** do Arduino.
   - Pino **GND** do relé -> Pino **GND** do Arduino.
   - Fiação da bomba conectada ao relé (conforme a especificação do relé e da bomba).

## Funcionamento do Projeto

1. O sensor de umidade do solo lê continuamente o nível de umidade no solo.
2. O valor lido é convertido em uma porcentagem de umidade, onde 100% representa um solo completamente submerso em água e 0% representa um solo completamente seco. 
3. Quando a umidade do solo cai abaixo de 45%, o relé é acionado para ligar a bomba de água.
4. A bomba continua ligada até que a umidade do solo ultrapasse 45%, momento em que o relé desliga a bomba.
5. O sistema é configurado para atualizar a leitura de umidade a cada segundo.

## Código Arduino

Aqui está o código usado no projeto:

```cpp
// Definição dos pinos
const int sensorUmidadePin = A0;  // Pino analógico para o sensor de umidade
const int relePin = 7;            // Pino digital para o relé

// Variáveis
int valorUmidade;
int porcentagemUmidade;

void setup() {
  // Inicializa a comunicação serial para monitoramento
  Serial.begin(9600);
  Serial.println("Sistema de Monitoramento de Umidade");

  // Configuração dos pinos
  pinMode(sensorUmidadePin, INPUT);
  pinMode(relePin, OUTPUT);

  // Inicialmente, desligamos a bomba
  digitalWrite(relePin, HIGH);  // Desligado (assumindo que o relé é acionado em LOW)
}

void loop() {
  // Lê o valor do sensor de umidade
  valorUmidade = analogRead(sensorUmidadePin);
  
  // Converte o valor analógico em porcentagem (0-100%)
  porcentagemUmidade = map(valorUmidade, 1023, 400, 0, 100);

  // Exibe o valor de umidade no monitor serial
  Serial.print("Umidade do solo: ");
  Serial.print(porcentagemUmidade);
  Serial.println("%");

  // Verifica se o solo está seco (abaixo de 45% de umidade)
  if (porcentagemUmidade <= 45) {
    // Aciona a bomba de água (ativa o relé)
    digitalWrite(relePin, HIGH);  // Relé ativado
    Serial.println("Solo seco - bomba ligada.");
  } else {
    // Desliga a bomba de água (desativa o relé)
    digitalWrite(relePin, LOW); // Relé desativado
    Serial.println("Solo úmido - bomba desligada.");
  }

  // Aguarda 1 segundo antes de fazer a próxima leitura
  delay(1000);
}
