/*
 * ================================================================
 *  PROJETO IoT — ESP32 + BOTAO ACESSIVEL + LED + MQTT
 *  SENAC — Disciplina: IoT Aplicado | Versao Estruturada 1.0
 * ================================================================
 *
 *  BLOCO 1 — BIBLIOTECAS E DEPENDENCIAS
 *  --------------------------------------------------
 *  WiFi.h         -> Permite conectar o ESP32 à internet
 *  PubSubClient.h -> Permite comunicação MQTT
 * ================================================================
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

/*
 * ================================================================
 *  BLOCO 2 — PARAMETROS DO ALUNO E VARIAVEIS GLOBAIS
 *  --------------------------------------------------
 *  Configure aqui sua rede, broker MQTT e hardware.
 * ================================================================
 */

// ================================================================
//  1. CONFIGURACOES DE REDE
// ================================================================
const char* WIFI_SSID       = "Nome_Wifi";
const char* WIFI_SENHA      = "senha";

// ================================================================
//  2. CONFIGURACOES MQTT
// ================================================================
const char* MQTT_SERVER     = "broker.hivemq.com";
const int   MQTT_PORT       = 1883;

// Topicos MQTT
const char* TOPICO_STATUS   = "elevador/status";
const char* TOPICO_EVENTO   = "elevador/evento";

// ================================================================
//  3. HARDWARE E PINOS
// ================================================================
const int PINO_BOTAO        = 4;
const int PINO_LED          = 2;

// ================================================================
//  4. REGRAS DE NEGOCIO
// ================================================================
const unsigned long DEBOUNCE_MS      = 300;
const unsigned long TEMPO_ACESSIVEL  = 20000; // 20 segundos segurando a porta do elevador

// ================================================================
//  5. VARIAVEIS DE ESTADO DO SISTEMA
// ================================================================
bool modoAtivo              = false;
bool estadoLED              = false;
unsigned long ultimoClique  = 0;
unsigned long inicioModo    = 0;

// Objetos principais
WiFiClient espClient;
PubSubClient client(espClient);

/*
 * ================================================================
 *  BLOCO 3 — PROTOTIPOS DE FUNCOES
 * ================================================================
 */
void conectarWiFi();
void verificarWiFi();
void conectarMQTT();
void verificarMQTT();
void verificarBotao();
void ativarModoAcessivel();
void finalizarModoAcessivel();

/*
 * ================================================================
 *  BLOCO 4 — SETUP (INICIALIZACAO)
 * ================================================================
 */
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n================================================");
  Serial.println(" Sistema IoT — Elevador Acessivel");
  Serial.println("================================================");

  // Configura pinos
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  Serial.println("[OK] Hardware configurado.");

  // WiFi
  conectarWiFi();

  // MQTT
  client.setServer(MQTT_SERVER, MQTT_PORT);

  Serial.println("[OK] Sistema inicializado com sucesso.\n");
}

/*
 * ================================================================
 *  BLOCO 5 — LOOP PRINCIPAL
 * ================================================================
 */
void loop() {
  
  verificarWiFi();
  verificarMQTT();

  client.loop();

  verificarBotao();

  // Verifica se o modo acessível deve ser finalizado
  if (modoAtivo && millis() - inicioModo >= TEMPO_ACESSIVEL) {
    finalizarModoAcessivel();
  }
}

/*
 * ================================================================
 *  BLOCO 6 — FUNCOES WIFI
 * ================================================================
 */
void conectarWiFi() {
  Serial.print("[WiFi] Conectando em: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  int tentativas = 0;

  while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
    digitalWrite(PINO_LED, !digitalRead(PINO_LED));
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[WiFi] Conectado com sucesso!");
    Serial.print("[WiFi] IP local: ");
    Serial.println(WiFi.localIP());
    digitalWrite(PINO_LED, LOW);
  } else {
    Serial.println("[WiFi] Falha na conexao.");
  }
}

void verificarWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Conexao perdida. Reconectando...");
    WiFi.disconnect();
    delay(1000);
    conectarWiFi();
  }
}

/*
 * ================================================================
 *  BLOCO 7 — FUNCOES MQTT
 * ================================================================
 */
void conectarMQTT() {
  while (!client.connected()) {

    String clientId = "ESP32_Elevador_" + String(random(0xffff));

    Serial.print("[MQTT] Conectando...");

    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
      client.publish(TOPICO_STATUS, "online");

    } else {
      Serial.print(" falhou. rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

void verificarMQTT() {
  if (!client.connected()) {
    conectarMQTT();
  }
}

/*
 * ================================================================
 *  BLOCO 8 — LEITURA DO BOTAO + DEBOUNCE
 * ================================================================
 */
void verificarBotao() {
  
  bool leituraBotao = digitalRead(PINO_BOTAO);

  // Botao pressionado = LOW
  if (leituraBotao == LOW &&
      millis() - ultimoClique > DEBOUNCE_MS &&
      !modoAtivo) {

    ultimoClique = millis();

    ativarModoAcessivel();
  }
}

/*
 * ================================================================
 *  BLOCO 9 — LOGICA DO MODO ACESSIVEL
 * ================================================================
 */
void ativarModoAcessivel() {

  modoAtivo = true;
  inicioModo = millis();

  Serial.println("[ELEVADOR] Modo acessivel ativado.");

  // Acende LED
  digitalWrite(PINO_LED, HIGH);
  estadoLED = true;

  // Publica evento MQTT
  client.publish(TOPICO_EVENTO, "modo_acessivel_ativado");
}

void finalizarModoAcessivel() {

  modoAtivo = false;

  // Apaga LED
  digitalWrite(PINO_LED, LOW);
  estadoLED = false;

  Serial.println("[ELEVADOR] Modo acessivel finalizado.");

  // Publica evento MQTT
  client.publish(TOPICO_EVENTO, "modo_acessivel_finalizado");
}
