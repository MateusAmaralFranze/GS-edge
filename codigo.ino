/*
 * SISTEMA DE MONITORAMENTO DE NIVEL - VERSAO COMPACTA
 * Otimizado para memoria limitada do Tinkercad
 */

// === PINOS ===
#define TRIG_PIN 7
#define ECHO_PIN 6
#define LED_VERDE 13
#define LED_VERMELHO 12
#define LED_AZUL 11
#define LED_AMARELO 10
#define BUZZER_PIN 8
#define BOTAO_PIN 2
#define POT_PIN A0

// === CONFIGURAÇÕES ===
#define ALTURA_TANQUE 20
#define NIVEL_CRITICO 80
#define NIVEL_ALTO 60
#define NIVEL_MEDIO 40

// === FREQUÊNCIAS ===
#define FREQ_ALTO 1000
#define FREQ_BAIXO 500
#define FREQ_MEDIO 750

// === VARIÁVEIS ===
float nivelAgua = 0.0;
bool sistemaLigado = true;
bool modoManual = false;
bool ultimoBotao = HIGH;
unsigned long ultimaLeitura = 0;
int alarmeAtual = 0;
unsigned long inicioAlarme = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== MONITOR DE NIVEL ===");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BOTAO_PIN, INPUT_PULLUP);
  
  digitalWrite(LED_VERDE, HIGH);
  
  // Som inicial
  tone(BUZZER_PIN, 800, 100);
  delay(150);
  tone(BUZZER_PIN, 1000, 100);
  delay(150);
  
  Serial.println("Sistema ativo!");
  Serial.println("Comandos: m(manual), 1-4(niveis), s(status), t(teste)");
}

void loop() {
  unsigned long agora = millis();
  
  verificarComandos();
  verificarBotao();
  
  if (sistemaLigado && (agora - ultimaLeitura >= 1000)) {
    if (modoManual) {
      lerManual();
    } else {
      lerSensor();
    }
    
    atualizarLeds();
    verificarAlarme();
    mostrarStatus();
    ultimaLeitura = agora;
  }
  
  processarAlarme();
}

void lerSensor() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duracao > 0) {
    float distancia = (duracao * 0.034) / 2;
    
    if (distancia <= ALTURA_TANQUE) {
      nivelAgua = ((ALTURA_TANQUE - distancia) / ALTURA_TANQUE) * 100.0;
      if (nivelAgua < 0) nivelAgua = 0;
      if (nivelAgua > 100) nivelAgua = 100;
    }
  }
}

void lerManual() {
  int pot = analogRead(POT_PIN);
  nivelAgua = map(pot, 0, 1023, 0, 100);
}

void atualizarLeds() {
  // Apagar todos
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);
  
  // Acender conforme nível
  if (nivelAgua >= NIVEL_CRITICO) {
    digitalWrite(LED_VERMELHO, (millis() / 300) % 2); // Piscar
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
  }
  else if (nivelAgua >= NIVEL_ALTO) {
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
  }
  else if (nivelAgua >= NIVEL_MEDIO) {
    digitalWrite(LED_AMARELO, HIGH);
  }
}

void verificarAlarme() {
  int novoAlarme = 0;
  
  if (nivelAgua >= NIVEL_CRITICO) novoAlarme = 3;
  else if (nivelAgua >= NIVEL_ALTO) novoAlarme = 2;
  else if (nivelAgua >= NIVEL_MEDIO) novoAlarme = 1;
  
  if (novoAlarme != alarmeAtual) {
    alarmeAtual = novoAlarme;
    inicioAlarme = millis();
    
    if (alarmeAtual > 0) {
      Serial.print(">>> ALARME NIVEL ");
      if (alarmeAtual == 1) Serial.println("MEDIO <<<");
      else if (alarmeAtual == 2) Serial.println("ALTO <<<");
      else Serial.println("CRITICO <<<");
    }
  }
}

void processarAlarme() {
  unsigned long tempo = millis() - inicioAlarme;
  
  if (alarmeAtual == 1) {
    // Médio: beep lento
    if (tempo % 3000 < 200) {
      tone(BUZZER_PIN, FREQ_MEDIO);
    } else {
      noTone(BUZZER_PIN);
    }
  }
  else if (alarmeAtual == 2) {
    // Alto: beep médio
    if (tempo % 2000 < 300) {
      tone(BUZZER_PIN, FREQ_ALTO);
    } else {
      noTone(BUZZER_PIN);
    }
  }
  else if (alarmeAtual == 3) {
    // Crítico: alternado
    unsigned long ciclo = tempo % 800;
    if (ciclo < 200) {
      tone(BUZZER_PIN, FREQ_ALTO);
    } else if (ciclo < 400) {
      tone(BUZZER_PIN, FREQ_BAIXO);
    } else if (ciclo < 600) {
      tone(BUZZER_PIN, FREQ_ALTO);
    } else {
      noTone(BUZZER_PIN);
    }
  }
  else {
    noTone(BUZZER_PIN);
  }
}

void verificarBotao() {
  bool estado = digitalRead(BOTAO_PIN);
  
  if (estado != ultimoBotao) {
    delay(50);
    
    if (digitalRead(BOTAO_PIN) == LOW && ultimoBotao == HIGH) {
      sistemaLigado = !sistemaLigado;
      
      if (!sistemaLigado) {
        alarmeAtual = 0;
        noTone(BUZZER_PIN);
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_AZUL, LOW);
        digitalWrite(LED_AMARELO, LOW);
        Serial.println(">>> SISTEMA OFF <<<");
      } else {
        Serial.println(">>> SISTEMA ON <<<");
      }
      
      // Beep confirmação
      tone(BUZZER_PIN, 1000, 100);
      delay(150);
      tone(BUZZER_PIN, 1000, 100);
    }
  }
  
  ultimoBotao = estado;
}

void verificarComandos() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch (cmd) {
      case 'm':
        modoManual = !modoManual;
        Serial.print("Modo: ");
        Serial.println(modoManual ? "MANUAL" : "AUTO");
        tone(BUZZER_PIN, 1000, 100);
        break;
        
      case '1':
        nivelAgua = 25;
        Serial.println(">>> Nivel: 25% <<<");
        tone(BUZZER_PIN, 800, 100);
        break;
        
      case '2':
        nivelAgua = 50;
        Serial.println(">>> Nivel: 50% <<<");
        tone(BUZZER_PIN, 900, 100);
        break;
        
      case '3':
        nivelAgua = 75;
        Serial.println(">>> Nivel: 75% <<<");
        tone(BUZZER_PIN, 1000, 100);
        break;
        
      case '4':
        nivelAgua = 95;
        Serial.println(">>> Nivel: 95% <<<");
        tone(BUZZER_PIN, 1200, 100);
        break;
        
      case 's':
        mostrarStatusCompleto();
        break;
        
      case 't':
        testarSistema();
        break;
        
      case 'p':
        alarmeAtual = 0;
        noTone(BUZZER_PIN);
        Serial.println(">>> Alarmes parados <<<");
        break;
        
      default:
        Serial.println("Comandos: m, 1-4, s, t, p");
        tone(BUZZER_PIN, 300, 200);
        break;
    }
  }
}

void mostrarStatus() {
  Serial.print("Nivel: ");
  Serial.print(nivelAgua, 1);
  Serial.print("% | Status: ");
  
  if (nivelAgua >= NIVEL_CRITICO) Serial.print("CRITICO");
  else if (nivelAgua >= NIVEL_ALTO) Serial.print("ALTO");
  else if (nivelAgua >= NIVEL_MEDIO) Serial.print("MEDIO");
  else Serial.print("BAIXO");
  
  Serial.print(" | Sistema: ");
  Serial.println(sistemaLigado ? "ON" : "OFF");
}

void mostrarStatusCompleto() {
  Serial.println("========== STATUS ==========");
  Serial.print("Sistema: ");
  Serial.println(sistemaLigado ? "LIGADO" : "DESLIGADO");
  Serial.print("Modo: ");
  Serial.println(modoManual ? "MANUAL" : "AUTO");
  Serial.print("Nivel: ");
  Serial.print(nivelAgua, 1);
  Serial.println("%");
  Serial.println("Limites:");
  Serial.print("  Medio: ");
  Serial.println(NIVEL_MEDIO);
  Serial.print("  Alto: ");
  Serial.println(NIVEL_ALTO);
  Serial.print("  Critico: ");
  Serial.println(NIVEL_CRITICO);
  Serial.print("Alarme: ");
  Serial.println(alarmeAtual);
  Serial.println("===========================");
}

void testarSistema() {
  Serial.println("=== TESTE ===");
  
  // Teste LEDs
  Serial.println("LEDs...");
  digitalWrite(LED_VERDE, HIGH);
  delay(300);
  digitalWrite(LED_AMARELO, HIGH);
  delay(300);
  digitalWrite(LED_AZUL, HIGH);
  delay(300);
  digitalWrite(LED_VERMELHO, HIGH);
  delay(500);
  
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  
  // Teste sons
  Serial.println("Sons...");
  tone(BUZZER_PIN, 500, 200);
  delay(300);
  tone(BUZZER_PIN, 750, 200);
  delay(300);
  tone(BUZZER_PIN, 1000, 200);
  delay(300);
  
  // Teste sensor
  Serial.println("Sensor...");
  for (int i = 0; i < 3; i++) {
    lerSensor();
    Serial.print("Leitura ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(nivelAgua, 1);
    Serial.println("%");
    delay(500);
  }
  
  Serial.println("=== FIM TESTE ===");
  tone(BUZZER_PIN, 1000, 100);
  delay(150);
  tone(BUZZER_PIN, 1200, 100);
}
