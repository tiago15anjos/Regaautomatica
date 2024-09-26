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
