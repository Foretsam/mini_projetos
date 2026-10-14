// Mapeamento de Pinos (Constantes evitam alterações acidentais)
const int S4R = 2,  S4G = 3;
const int S3R = 4,  S3Y = 5,  S3G = 6;
const int S2R = 7,  S2Y = 8,  S2G = 9;
const int S1R = 10, S1Y = 11, S1G = 12;

// Funções Auxiliares (Modularização)
void setS4(int r, int g) { 
  digitalWrite(S4R, r); digitalWrite(S4G, g); 
}
void setS3(int r, int y, int g) { 
  digitalWrite(S3R, r); digitalWrite(S3Y, y); digitalWrite(S3G, g); 
}
void setS2(int r, int y, int g) { 
  digitalWrite(S2R, r); digitalWrite(S2Y, y); digitalWrite(S2G, g); 
}
void setS1(int r, int y, int g) { 
  digitalWrite(S1R, r); digitalWrite(S1Y, y); digitalWrite(S1G, g); 
}

void setup() {
  // Configura todos os pinos (do 2 ao 12) como SAÍDA e desliga todos
  for (int i = 2; i <= 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  // TEMPO 1: S2 Direto + S4 Conversão à Esquerda ganham Verde
  setS1(1, 0, 0); // S1 Vermelho
  setS2(0, 0, 1); // S2 Verde
  setS3(1, 0, 0); // S3 Vermelho
  setS4(0, 1);    // S4 Verde
  delay(5000);    // Mantém por 5 segundos

  // CORTE DE CONVERSÃO: Fecha S4 para liberar o fluxo oposto (Regra do projeto)
  setS4(1, 0);    // S4 fica Vermelho (S2 continua Verde)
  delay(1000);    // Margem de segurança de 1 segundo

  // TEMPO 2: S1 Direto abre (Avenida inteira livre)
  setS1(0, 0, 1); // S1 Verde
  delay(5000);    // Mantém por 5 segundos

  // TRANSIÇÃO DA AVENIDA: Atenção
  setS1(0, 1, 0); // S1 Amarelo
  setS2(0, 1, 0); // S2 Amarelo
  delay(2000);    // Mantém por 2 segundos

  // CLEARANCE: Vermelho Total para esvaziar o cruzamento
  setS1(1, 0, 0); 
  setS2(1, 0, 0);
  delay(1000);

  // TEMPO 3: Via Transversal ganha Verde
  setS3(0, 0, 1); // S3 Verde
  delay(10000);   // Mantém por 10 segundos

  // TRANSIÇÃO DA TRANSVERSAL: Atenção
  setS3(0, 1, 0); // S3 Amarelo
  delay(2000);

  // CLEARANCE: Vermelho Total antes de recomeçar o ciclo
  setS3(1, 0, 0);
  delay(1000);
}