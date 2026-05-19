/*
* ================================================================
*  ESTRUTURA IoT — ELEVADOR INTELIGENTE ACESSÍVEL (EIA)
*  Versão Local: Apenas Botão + LED (sem WiFi / MQTT)
* ================================================================
*
*  BLOCO 1 — BIBLIOTECAS E DEPENDÊNCIAS
*
*  ✅ Arduino.h: necessária para funções básicas do ESP32.
*
*  ❌ WiFi.h       — COMENTADA: não precisamos de internet agora.
*  ❌ PubSubClient.h — COMENTADA: é a biblioteca do MQTT (nuvem).
*  ❌ ArduinoJson.h  — COMENTADA: era usada só para montar o JSON
*                      do pacote enviado à nuvem.
* ================================================================
*/
#include <Arduino.h>

// #include <WiFi.h>          // ❌ Sem WiFi nesta versão, vamos colocar na proxima
// #include <PubSubClient.h>  // ❌ Sem MQTT nesta versão, vamos colocar na proxima
// #include <ArduinoJson.h>   // ❌ Sem JSON nesta versão, vamos colocar na proxima


/*
* ================================================================
*  BLOCO 2 — VARIÁVEIS GLOBAIS
* ================================================================
*/

// ── Identificação ─────────────────────────────────────────────
const char* ID_ELEVADOR = "ELEVADOR-SENAC-01"; // Apenas para o Serial Monitor

// ── Credenciais de Rede (WiFi) ────────────────────────────────
// ❌ COMENTADAS: sem conexão de rede nesta versão
// const char* WIFI_SSID     = "SENAC-Mesh";
// const char* WIFI_SENHA    = "09080706";

// ── Integração com a Nuvem (MQTT) ─────────────────────────────
// ❌ COMENTADAS: sem envio para a nuvem nesta versão
// const char* MQTT_SERVIDOR = "test.mosquitto.org";
// const int   MQTT_PORTA    = 1883;
// const char* TOPICO_ENVIO  = "senac/elevador/acessibilidade";

// ── Hardware e Pinos (Esquemático) ────────────────────────────
const int PINO_BOTAO = 4; // Pino onde o botão está ligado
const int PINO_LED   = 2; // LED azul da placa (simula a porta abrindo)
const int PINO_LED_LASER = 5;

// ── Lógica e Regras de Negócio ────────────────────────────────
const unsigned long TEMPO_PORTA  = 10000; // 10 segundos com a porta aberta
const unsigned long TEMPO_DEBOUNCE = 50;  // 50 ms para filtrar ruído do botão
const unsigned long TEMPO_PISCA = 300;

// ── Variáveis de Estado do Sistema (Memória) ──────────────────
unsigned long tempoAbertura   = 0;     // Momento em que a porta abriu
unsigned long ultimoDebounce  = 0;     // Momento do último acionamento do botão
unsigned long tempoPisca = 0;
bool estadoLaser = false;
bool portaAberta              = false; // Estado atual da porta

// ── Objetos de Rede ───────────────────────────────────────────
// ❌ COMENTADOS: dependem das bibliotecas WiFi e PubSubClient
// WiFiClient clienteWiFi;
// PubSubClient clienteMQTT(clienteWiFi);


/*
* ================================================================
*  BLOCO 3 — PROTÓTIPOS DE FUNÇÕES (O "ÍNDICE" DO CÓDIGO)
* ================================================================
*/
bool lerSensorBotao();
void acionarPorta();

// ❌ COMENTADOS: funções de internet não usadas nesta versão
// void conectarWiFi();
// void verificarConexoes();
// bool enviarParaNuvem(String evento);


/*
* ================================================================
*  BLOCO 4 — SETUP (INICIALIZAÇÃO)
* ================================================================
*/
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n================================================");
  Serial.println("  Sistema EIA — Elevador Inteligente Iniciando");
  Serial.println("  Modo: Local (sem conexão de rede)");
  Serial.println("================================================");

  // Configura os pinos
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP); // Resistor interno: LOW = botão pressionado
  pinMode(PINO_LED_LASER, OUTPUT);
  digitalWrite(PINO_LED, LOW);       // Começa com o LED apagado (porta fechada)
  digitalWrite(PINO_LED_LASER, LOW);

  // ❌ COMENTADOS: conexão com a internet não é necessária agora
  // conectarWiFi();
  // clienteMQTT.setServer(MQTT_SERVIDOR, MQTT_PORTA);

  Serial.println("[OK] Setup concluído. Monitorando botão...\n");
}


/*
* ================================================================
*  BLOCO 5 — LOOP PRINCIPAL (O CORAÇÃO DO PROGRAMA)
*  Fica repetindo sem parar, vigiando o botão e o relógio.
* ================================================================
*/
void loop() {

  // ❌ COMENTADOS: manutenção das conexões de rede
  // verificarConexoes();
  // clienteMQTT.loop();

  // Passo 1: Ler o botão — se foi pressionado E a porta está fechada, abre!
  if (lerSensorBotao()) {
    portaAberta   = true;
    tempoAbertura = millis(); // Marca o momento em que a porta abriu
    Serial.println("[AÇÃO] Porta aberta! Aguardando 10 segundos...");
  }

  // Passo 2: Controlar o LED e o tempo de porta aberta
  acionarPorta();

  // ❌ COMENTADO: envio para a nuvem não é necessário agora
  // if (statusMudou) {
  //   String mensagem = portaAberta ? "Modo Acessível: Porta Aberta"
  //                                 : "Modo Normal: Porta Fechada";
  //   enviarParaNuvem(mensagem);
  //   statusMudou = false;
  // }
}


/*
* ================================================================
*  BLOCO 6 — FUNÇÕES DE INTERNET (WIFI E MQTT)
*  ❌ COMENTADAS COMPLETAMENTE: não usadas nesta versão local.
*     Para reativar: descomente aqui e nos Blocos 2, 3, 4 e 5.
* ================================================================
*/

// void conectarWiFi() {
//   Serial.print("[WiFi] Conectando a rede: ");
//   Serial.println(WIFI_SSID);
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(WIFI_SSID, WIFI_SENHA);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\n[WiFi] Sucesso! Estamos online.");
// }

// void verificarConexoes() {
//   if (WiFi.status() != WL_CONNECTED) {
//     conectarWiFi();
//   }
//   while (!clienteMQTT.connected()) {
//     Serial.print("[MQTT] Tentando conectar...");
//     String clientId = "EIA-" + String(random(0xffff), HEX);
//     if (clienteMQTT.connect(clientId.c_str())) {
//       Serial.println(" Conectado!");
//     } else {
//       delay(2000);
//     }
//   }
// }


/*
* ================================================================
*  BLOCO 7 — LEITURA DO SENSOR E VALIDAÇÃO
*
*  CORREÇÃO: o delay(200) original foi substituído por debounce
*  por tempo (millis). O delay() trava o programa inteiro —
*  com millis() o loop continua rodando normalmente.
* ================================================================
*/
bool lerSensorBotao() {
  // INPUT_PULLUP inverte a lógica: LOW = botão pressionado
  bool botaoApertado = (digitalRead(PINO_BOTAO) == LOW);

  if (botaoApertado && !portaAberta) {
    // Debounce por tempo: só aceita o clique se passaram 50ms desde o último
    if ((millis() - ultimoDebounce) >= TEMPO_DEBOUNCE) {
      ultimoDebounce = millis();
      Serial.println("[SENSOR] Botão de acessibilidade acionado!");
      return true;
    }
  }
  return false;
}


/*
* ================================================================
*  BLOCO 8 — ATUADOR (AGINDO NO MUNDO FÍSICO)
* ================================================================
*/
void acionarPorta() {
  if (portaAberta) {
    digitalWrite(PINO_LED, HIGH); // Mantém LED aceso enquanto a porta está aberta

    // Pisca o laser enquanto a porta estiver aberta
    if ((millis() - tempoPisca) >= TEMPO_PISCA) {
      estadoLaser = !estadoLaser;
      digitalWrite(PINO_LED_LASER, estadoLaser ? HIGH : LOW);
      tempoPisca = millis();
    }

    // Verifica se os 10 segundos já passaram
    if ((millis() - tempoAbertura) >= TEMPO_PORTA) {
      digitalWrite(PINO_LED, LOW); // Apaga o LED (fecha a porta)
      portaAberta = false;
      Serial.println("[ATUADOR] 10 segundos encerrados. Porta fechada.\n");
    }
  }
}


/*
* ================================================================
*  BLOCO 9 — ENVIO PARA A NUVEM (MQTT)
*  ❌ COMENTADO COMPLETAMENTE: sem nuvem nesta versão local.
*     Para reativar: descomente aqui e nos Blocos 2, 3, 4 e 5.
* ================================================================
*/

// bool enviarParaNuvem(String evento) {
//   StaticJsonDocument<200> doc;
//   doc["dispositivo"]  = ID_ELEVADOR;
//   doc["evento"]       = evento;
//   doc["porta_aberta"] = portaAberta;
//   doc["timestamp"]    = millis();
//   String pacoteJSON;
//   serializeJson(doc, pacoteJSON);
//   Serial.println("[NUVEM] Enviando pacote: " + pacoteJSON);
//   bool sucesso = clienteMQTT.publish(TOPICO_ENVIO, pacoteJSON.c_str());
//   if (sucesso) {
//     Serial.println("[NUVEM] Sucesso! Aplicativo notificado.");
//   } else {
//     Serial.println("[NUVEM] Falha ao enviar a mensagem.");
//   }
//   return sucesso;
// }
