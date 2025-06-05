# 🌊 Sistema de Monitoramento de Nível de Água

Um sistema completo de monitoramento de nível de água usando Arduino, sensor ultrassônico HC-SR04 e alarmes visuais/sonoros profissionais.


## 📋 Índice

- [Visão Geral](#-visão-geral)
- [Características](#-características)
- [Componentes](#-componentes)
- [Esquema de Ligação](#-esquema-de-ligação)
- [Instalação](#-instalação)
- [Como Usar](#-como-usar)
- [Comandos](#-comandos)
- [Níveis de Monitoramento](#-níveis-de-monitoramento)
- [Alarmes](#-alarmes)
- [Simulação no Tinkercad](#-simulação-no-tinkercad)
- [Troubleshooting](#-troubleshooting)
- [Contribuição](#-contribuição)
- [Licença](#-licença)

## 🎯 Visão Geral

Este projeto implementa um sistema de monitoramento de nível de água em tempo real, ideal para:

- 🏠 **Residencial**: Monitoramento de caixas d'água
- 🏭 **Industrial**: Controle de tanques e reservatórios  
- 🌱 **Agrícola**: Sistemas de irrigação
- 🔬 **Educacional**: Projetos de automação e IoT

### Principais Funcionalidades

- ✅ **Monitoramento contínuo** do nível de água
- ✅ **4 níveis de alerta** com indicação visual e sonora
- ✅ **Alarmes profissionais** diferenciados por urgência
- ✅ **Interface serial** para monitoramento remoto
- ✅ **Modo manual** para testes e calibração
- ✅ **Sistema de simulação** para demonstrações

## 🚀 Características

### 📊 Monitoramento Inteligente
- **Sensor ultrassônico** HC-SR04 para medição precisa
- **Atualização em tempo real** (1 segundo)
- **Filtros de ruído** para leituras estáveis
- **Calibração automática** do sistema

### 🚨 Sistema de Alarmes
- **4 tipos de alarme** sonoro diferenciados
- **Indicação visual** com LEDs coloridos
- **Padrões profissionais** de alerta
- **Controle de volume** e frequência

### 🎛️ Interface Completa
- **Comandos via Serial Monitor**
- **Feedback visual** em tempo real
- **Modo de teste** integrado
- **Status detalhado** do sistema

## 🔧 Componentes

### Hardware Necessário

| Componente | Quantidade | Descrição |
|------------|------------|-----------|
| ![Arduino](https://via.placeholder.com/50x30/FF5722/FFFFFF?text=ARD) **Arduino Uno R3** | 1x | Microcontrolador principal |
| ![Sensor](https://via.placeholder.com/50x30/2196F3/FFFFFF?text=HC04) **HC-SR04** | 1x | Sensor ultrassônico |
| ![LED](https://via.placeholder.com/50x30/4CAF50/FFFFFF?text=LED) **LEDs** | 4x | Verde, Amarelo, Azul, Vermelho |
| ![Buzzer](https://via.placeholder.com/50x30/9C27B0/FFFFFF?text=BUZ) **Buzzer** | 1x | Alarme sonoro |
| ![Botão](https://via.placeholder.com/50x30/607D8B/FFFFFF?text=BTN) **Push Button** | 1x | Liga/desliga sistema |
| ![Pot](https://via.placeholder.com/50x30/FF9800/FFFFFF?text=POT) **Potenciômetro** | 1x | Controle manual (10kΩ) |
| ![Resistor](https://via.placeholder.com/50x30/795548/FFFFFF?text=220R) **Resistores** | 4x | 220Ω para LEDs |
| ![Protoboard](https://via.placeholder.com/50x30/FFC107/FFFFFF?text=PROTO) **Protoboard** | 1x | Montagem do circuito |
| ![Jumpers](https://via.placeholder.com/50x30/E91E63/FFFFFF?text=WIRE) **Jumpers** | 15x | Conexões |

### Especificações Técnicas

#### Sensor HC-SR04
- **Alcance**: 2cm - 400cm
- **Precisão**: ±3mm
- **Ângulo**: 15°
- **Frequência**: 40kHz
- **Alimentação**: 5V DC

#### Arduino Uno R3
- **Microcontrolador**: ATmega328P
- **Tensão**: 5V
- **Pinos Digitais**: 14 (6 PWM)
- **Pinos Analógicos**: 6
- **Memória Flash**: 32KB

## 🔌 Esquema de Ligação

### Diagrama de Conexões

\`\`\`
                    ARDUINO UNO R3
                   ┌─────────────────┐
                   │                 │
    HC-SR04        │  D7 ←─── TRIG   │
    ┌─────────┐    │  D6 ←─── ECHO   │
    │ VCC ────┼────┤  5V             │
    │ GND ────┼────┤  GND            │
    │ TRIG────┼────┤  D7             │
    │ ECHO────┼────┤  D6             │
    └─────────┘    │                 │
                   │  D13 ───→ LED Verde
                   │  D12 ───→ LED Vermelho
                   │  D11 ───→ LED Azul
    Buzzer         │  D10 ───→ LED Amarelo
    ┌─────┐        │  D8  ───→ Buzzer (+)
    │  +  ├────────┤  D8             │
    │  -  ├────────┤  GND            │
    └─────┘        │                 │
                   │  D2  ←─── Botão
    Potenciômetro  │  A0  ←─── Pot (centro)
    ┌─────────┐    │  5V  ←─── Pot (lateral)
    │ ┌─────┐ │    │  GND ←─── Pot (lateral)
    │ │  ○  │ ├────┤  A0             │
    │ └─────┘ │    │                 │
    └─────────┘    └─────────────────┘
\`\`\`

### Conexões Detalhadas

#### Sensor HC-SR04
\`\`\`
HC-SR04 VCC  → Arduino 5V
HC-SR04 GND  → Arduino GND
HC-SR04 TRIG → Arduino Pino 7
HC-SR04 ECHO → Arduino Pino 6
\`\`\`

#### LEDs Indicadores
\`\`\`
LED Verde:    Pino 13 → Resistor 220Ω → LED (+) → GND
LED Vermelho: Pino 12 → Resistor 220Ω → LED (+) → GND
LED Azul:     Pino 11 → Resistor 220Ω → LED (+) → GND
LED Amarelo:  Pino 10 → Resistor 220Ω → LED (+) → GND
\`\`\`

#### Controles
\`\`\`
Buzzer:        Pino 8 → Buzzer (+) → GND
Botão:         Pino 2 → Botão → GND
Potenciômetro: Pino A0 ← Centro, 5V ← Lateral, GND ← Lateral
\`\`\`

## 💾 Instalação

### 1. Preparação do Ambiente

#### Arduino IDE
1. Baixe o [Arduino IDE](https://www.arduino.cc/en/software)
2. Instale e configure para Arduino Uno
3. Conecte o Arduino via USB

#### Tinkercad (Simulação)
1. Acesse [Tinkercad Circuits](https://www.tinkercad.com)
2. Crie uma conta gratuita
3. Inicie um novo projeto de circuito

### 2. Montagem do Hardware

#### Passo a Passo
1. **Monte o circuito** seguindo o diagrama
2. **Verifique todas as conexões** antes de energizar
3. **Teste a continuidade** com multímetro
4. **Conecte o Arduino** ao computador

#### Checklist de Montagem
- [ ] HC-SR04 conectado (VCC, GND, TRIG=7, ECHO=6)
- [ ] 4 LEDs com resistores (pinos 13, 12, 11, 10)
- [ ] Buzzer conectado (pino 8)
- [ ] Botão conectado (pino 2)
- [ ] Potenciômetro conectado (A0)
- [ ] Alimentação da protoboard (5V e GND)

### 3. Upload do Código

#### Arduino IDE
\`\`\`bash
1. Abra o Arduino IDE
2. Copie o código do arquivo 'codigo_compacto_tinkercad.ino'
3. Cole no IDE
4. Selecione: Ferramentas → Placa → Arduino Uno
5. Selecione: Ferramentas → Porta → (sua porta COM)
6. Clique em Upload (→)
\`\`\`

#### Tinkercad
\`\`\`bash
1. Monte o circuito no Tinkercad
2. Clique no Arduino
3. Clique em "Code"
4. Apague o código existente
5. Cole o código fornecido
6. Clique em "Done & Back"
7. Inicie a simulação
\`\`\`

## 🎮 Como Usar

### Inicialização do Sistema

1. **Conecte o Arduino** à alimentação
2. **Abra o Serial Monitor** (115200 baud)
3. **Aguarde a mensagem** de inicialização
4. **Ouça o som** de confirmação

### Interface Serial

\`\`\`
=== MONITOR DE NIVEL ===
Sistema ativo!
Comandos: m(manual), 1-4(niveis), s(status), t(teste)

Nivel: 45.2% | Status: MEDIO | Sistema: ON
\`\`\`

### Operação Normal

#### Modo Automático (Padrão)
- Sistema lê o sensor HC-SR04 automaticamente
- Atualiza a cada 1 segundo
- Ativa alarmes conforme o nível

#### Modo Manual
- Digite `m` para alternar
- Use o potenciômetro para simular níveis
- Ideal para testes e demonstrações

## ⌨️ Comandos

### Comandos Principais

| Comando | Função | Exemplo |
|---------|--------|---------|
| `m` | Alternar modo manual/automático | `m` |
| `1` | Definir nível 25% | `1` |
| `2` | Definir nível 50% | `2` |
| `3` | Definir nível 75% | `3` |
| `4` | Definir nível 95% | `4` |
| `s` | Mostrar status detalhado | `s` |
| `t` | Executar teste completo | `t` |
| `p` | Parar todos os alarmes | `p` |

### Exemplos de Uso

#### Teste Rápido
\`\`\`
> t
=== TESTE ===
LEDs...
Sons...
Sensor...
Leitura 1: 23.4%
Leitura 2: 24.1%
Leitura 3: 23.8%
=== FIM TESTE ===
\`\`\`

#### Definir Nível Crítico
\`\`\`
> 4
>>> Nivel: 95% <<<
Nivel: 95.0% | Status: CRITICO | Sistema: ON
>>> ALARME NIVEL CRITICO <<<
\`\`\`

#### Status Detalhado
\`\`\`
> s
========== STATUS ==========
Sistema: LIGADO
Modo: AUTO
Nivel: 67.3%
Limites:
  Medio: 40
  Alto: 60
  Critico: 80
Alarme: 2
===========================
\`\`\`

## 📊 Níveis de Monitoramento

### Faixas de Nível

| Nível | Faixa | LED | Alarme | Descrição |
|-------|-------|-----|--------|-----------|
| 🟢 **Baixo** | 0-39% | Verde | Nenhum | Nível normal |
| 🟡 **Médio** | 40-59% | Amarelo | Beep lento | Atenção |
| 🔵 **Alto** | 60-79% | Azul | Beep médio | Cuidado |
| 🔴 **Crítico** | 80-100% | Vermelho | Alternado | Urgente |

### Comportamento dos LEDs

#### LED Verde (Sistema)
- **Sempre ligado** quando sistema ativo
- **Apagado** quando sistema desligado

#### LEDs de Nível
- **Acumulativo**: LEDs inferiores permanecem acesos
- **Vermelho pisca** no nível crítico
- **Atualização** em tempo real

### Exemplo Visual
\`\`\`
Nível 25%: 🟢 (apenas verde)
Nível 45%: 🟢🟡 (verde + amarelo)
Nível 65%: 🟢🟡🔵 (verde + amarelo + azul)
Nível 85%: 🟢🟡🔵🔴 (todos + vermelho piscando)
\`\`\`

## 🔊 Alarmes

### Tipos de Alarme

#### 🟡 Alarme Médio (40-59%)
- **Frequência**: 750 Hz
- **Padrão**: Beep a cada 3 segundos
- **Duração**: 200ms
- **Propósito**: Alerta preventivo

#### 🔵 Alarme Alto (60-79%)
- **Frequência**: 1000 Hz
- **Padrão**: Beep a cada 2 segundos
- **Duração**: 300ms
- **Propósito**: Atenção necessária

#### 🔴 Alarme Crítico (80-100%)
- **Frequências**: 1000Hz / 500Hz alternadas
- **Padrão**: Tom alternado rápido
- **Ciclo**: 800ms (200ms cada tom)
- **Propósito**: Ação imediata

### Controle de Alarmes

#### Silenciar Temporariamente
\`\`\`
> p
>>> Alarmes parados <<<
\`\`\`

#### Desligar Sistema
- Pressione o **botão físico**
- Ou use comando via serial
- Todos os alarmes param automaticamente

## 🖥️ Simulação no Tinkercad

### Montagem Virtual

#### 1. Componentes Necessários
- Arduino Uno R3
- Ultrasonic Distance Sensor (HC-SR04)
- 4x LED (cores diferentes)
- 1x Piezo (buzzer)
- 1x Pushbutton
- 1x Potentiometer
- 4x Resistor (220Ω)
- 1x Breadboard Full
- Jumper wires

#### 2. Passo a Passo
1. **Adicione o Arduino Uno** na área de trabalho
2. **Adicione a protoboard** ao lado
3. **Conecte a alimentação** (5V e GND)
4. **Adicione o HC-SR04** na parte superior
5. **Posicione os LEDs** em linha na protoboard
6. **Adicione buzzer e controles** na parte inferior
7. **Faça as conexões** conforme o diagrama

#### 3. Teste da Simulação
\`\`\`
1. Cole o código no Arduino
2. Inicie a simulação
3. Abra o Serial Monitor
4. Digite 't' para teste completo
5. Use comandos 1-4 para testar níveis
6. Observe LEDs e ouça alarmes
\`\`\`

### Dicas para Tinkercad

#### Testando o Sensor
- **Aproxime objetos** do HC-SR04
- **Quanto mais próximo** = maior nível
- **Use qualquer componente** como obstáculo

#### Modo Manual
- **Digite 'm'** para ativar
- **Gire o potenciômetro** para simular níveis
- **Mais fácil** para demonstrações

#### Visualização
- **LEDs acendem** conforme nível
- **Buzzer faz ruído** nos alarmes
- **Serial Monitor** mostra dados em tempo real

## 🔧 Troubleshooting

### Problemas Comuns

#### ❌ Sistema não inicializa
**Sintomas**: Nenhum LED acende, sem som
**Soluções**:
- Verifique alimentação do Arduino
- Confirme conexão USB
- Teste com LED simples no pino 13

#### ❌ Sensor não funciona
**Sintomas**: Leituras sempre 0% ou 100%
**Soluções**:
- Verifique conexões TRIG (7) e ECHO (6)
- Confirme alimentação 5V do HC-SR04
- Teste com objetos a diferentes distâncias

#### ❌ LEDs não acendem
**Sintomas**: Sistema funciona mas LEDs apagados
**Soluções**:
- Verifique polaridade dos LEDs
- Confirme resistores 220Ω
- Teste LEDs individualmente

#### ❌ Alarme não toca
**Sintomas**: LEDs funcionam mas sem som
**Soluções**:
- Verifique conexão do buzzer (pino 8)
- Confirme polaridade do buzzer
- Teste com comando 't'

#### ❌ Comandos não funcionam
**Sintomas**: Serial Monitor não responde
**Soluções**:
- Verifique velocidade (9600 baud)
- Confirme porta COM correta
- Reinicie o Arduino

### Códigos de Erro

#### Erro de Memória (Tinkercad)
\`\`\`
Erro: "data section exceeds available space"
Solução: Use o código compacto fornecido
\`\`\`

#### Erro de Compilação
\`\`\`
Erro: Variáveis não declaradas
Solução: Copie o código completo, incluindo #define
\`\`\`

### Diagnóstico Avançado

#### Teste Individual de Componentes
\`\`\`cpp
// Teste LED
digitalWrite(13, HIGH);
delay(1000);
digitalWrite(13, LOW);

// Teste Buzzer
tone(8, 1000, 500);

// Teste Sensor
long duration = pulseIn(6, HIGH);
Serial.println(duration);
\`\`\`

#### Monitoramento Serial
\`\`\`
> s
========== STATUS ==========
Sistema: LIGADO
Modo: AUTO
Nivel: 45.2%
Limites: 40/60/80
Alarme: 1
===========================
\`\`\`

## 🚀 Melhorias Futuras

### Versão 2.0 (Planejada)
- [ ] **Display LCD** para interface local
- [ ] **Conectividade WiFi** (ESP32)
- [ ] **App mobile** para monitoramento
- [ ] **Data logging** em SD card
- [ ] **Múltiplos sensores** redundantes

### Versão Industrial
- [ ] **Comunicação Modbus**
- [ ] **Relés para controle** de bombas
- [ ] **Proteção IP65**
- [ ] **Alimentação 24V**
- [ ] **Interface HMI**

### Versão IoT
- [ ] **Dashboard web** em tempo real
- [ ] **Alertas por email/SMS**
- [ ] **Histórico de dados**
- [ ] **API REST** para integração
- [ ] **Machine Learning** para predição

## 🤝 Contribuição

### Como Contribuir

1. **Fork** o repositório
2. **Crie uma branch** para sua feature
3. **Commit** suas mudanças
4. **Push** para a branch
5. **Abra um Pull Request**

### Diretrizes

#### Código
- Use **comentários claros** em português
- Siga o **padrão de nomenclatura** existente
- **Teste** todas as funcionalidades
- **Documente** mudanças no README

#### Issues
- **Descreva o problema** claramente
- **Inclua código** de exemplo se aplicável
- **Adicione screenshots** quando relevante
- **Especifique** versão do Arduino IDE

### Roadmap

#### Próximas Versões
- **v1.1**: Display LCD 16x2
- **v1.2**: Conectividade WiFi
- **v1.3**: App mobile
- **v2.0**: Sistema completo IoT

## 📄 Licença

Este projeto está licenciado sob a **MIT License** - veja o arquivo [LICENSE](LICENSE) para detalhes.

### Resumo da Licença
- ✅ **Uso comercial** permitido
- ✅ **Modificação** permitida
- ✅ **Distribuição** permitida
- ✅ **Uso privado** permitido
- ❌ **Sem garantia** ou responsabilidade


### FAQ

#### P: Funciona com Arduino Nano?
**R**: Sim, apenas ajuste os pinos conforme sua placa.

#### P: Posso usar sensor de pressão?
**R**: Sim, modifique a função \`lerSensor()\` para seu sensor.

#### P: Como calibrar o sistema?
**R**: Use o modo manual e compare com medições reais.

#### P: Funciona em 3.3V?
**R**: HC-SR04 precisa de 5V, use conversor de nível.

---

## 🏆 Créditos

### Desenvolvido por
- **Autores Principais**: Mateus Amaral Franze, Felipe Sumida

### Agradecimentos
- Comunidade Arduino
- Documentação do Tinkercad
- Fóruns de eletrônica

---

**⭐ Se este projeto foi útil, deixe uma estrela no GitHub!**

\`\`\`
Sistema de Monitoramento de Nível de Água v1.0
\`\`\`
