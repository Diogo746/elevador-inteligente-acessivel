/*

* ================================================================

*  ESTRUTURA IoT — ELEVADOR INTELIGENTE ACESSÍVEL (EIA)

*  Tecnologias: ESP32 + Botão/Sensor + LED + MQTT

* ================================================================

*

*  BLOCO 1 — BIBLIOTECAS E DEPENDÊNCIAS

*  - WiFi.h: ensina o ESP32 a usar a internet.

*  - PubSubClient.h: ensina o ESP32 a mandar mensagens em tempo real (MQTT).

*  - ArduinoJson.h: ensina o ESP32 a ler e escrever dados em JSON.

* ================================================================

*/

#include <WiFi.h>

#include <PubSubClient.h>   // Biblioteca para o MQTT

#include <ArduinoJson.h>

#include <Arduino.h>
 
/*

* ================================================================

*  BLOCO 2 — PARÂMETROS DO ALUNO E VARIÁVEIS GLOBAIS

* ================================================================

*/
 
// ── Identificação ─────────────────────────────────────────────

const char* ID_ELEVADOR = "ELEVADOR-SENAC-01";
 
// ── Credenciais de Rede (WiFi) ────────────────────────────────

const char* WIFI_SSID      = "SENAC-Mesh";

const char* WIFI_SENHA     = "09080706";
 
// ── Integração com a Nuvem (MQTT) ─────────────────────────────

const char* MQTT_SERVIDOR  = "test.mosquitto.org"; // Broker MQTT de teste

const int   MQTT_PORTA     = 1883;

const char* TOPICO_ENVIO   = "senac/elevador/acessibilidade";
 
// ── Hardware e Pinos (Esquemático) ────────────────────────────

const int PINO_BOTAO = 4; // Pino onde o botão ou sensor está ligado

const int PINO_LED   = 2; // LED azul da placa (simula a porta abrindo)
 
// ── Lógica e Regras de Negócio ────────────────────────────────

const unsigned long TEMPO_PORTA = 10000; // 10000 ms = 10 segundos de porta aberta
 
// ── Variáveis de Estado do Sistema (Memória) ──────────────────

unsigned long tempoAbertura = 0;     // Guarda a hora que a porta abriu

bool portaAberta            = false; // Lembra se a porta está aberta ou fechada

bool statusMudou            = false; // Avisa se precisamos mandar mensagem pra nuvem
 
WiFiClient clienteWiFi;

PubSubClient clienteMQTT(clienteWiFi);
 
/*

* ================================================================

*  BLOCO 3 — PROTÓTIPOS DE FUNÇÕES (O "ÍNDICE" DO CÓDIGO)

* ================================================================

*/

void conectarWiFi();

void verificarConexoes(); // Checa o WiFi e o MQTT

bool lerSensorBotao();

void acionarPorta();

bool enviarParaNuvem(String evento);
 
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

  Serial.println("================================================");
 
  // Configura os pinos

  pinMode(PINO_LED, OUTPUT);

  pinMode(PINO_BOTAO, INPUT_PULLUP); // Usa o resistor interno da placa para o botão

  digitalWrite(PINO_LED, LOW);       // Começa com a porta fechada
 
  // Conecta na internet e configura o MQTT

  conectarWiFi();

  clienteMQTT.setServer(MQTT_SERVIDOR, MQTT_PORTA);
 
  Serial.println("[OK] Setup concluído. Monitorando botão...\n");

}
 
/*

* ================================================================

*  BLOCO 5 — LOOP PRINCIPAL (O CORAÇÃO DO PROGRAMA)

*  Fica girando sem parar, vigiando o botão e o relógio.

* ================================================================

*/

void loop() {

  // Passo 1: Garantir que a internet e o MQTT continuam funcionando

  verificarConexoes();

  clienteMQTT.loop(); // Mantém o MQTT vivo
 
  // Passo 2: Ler o botão de acessibilidade

  // Se a função lerSensorBotao() disser que foi apertado, ativamos o modo!

  if (lerSensorBotao()) {

    portaAberta = true;

    statusMudou = true;

    tempoAbertura = millis(); // Marca no relógio a hora que ativou

  }
 
  // Passo 3: Executar a regra de negócio (Atuar na porta)

  acionarPorta();
 
  // Passo 4: Enviar os dados para a Nuvem apenas quando algo mudar

  if (statusMudou) {

    String mensagem = portaAberta ? "Modo Acessível: Porta Aberta" : "Modo Normal: Porta Fechada";

    enviarParaNuvem(mensagem);

    statusMudou = false; // Reseta o aviso de mudança

  }

}
 
/*

* ================================================================

*  BLOCO 6 — FUNÇÕES DE INTERNET (WIFI E MQTT)

* ================================================================

*/

void conectarWiFi() {

  Serial.print("[WiFi] Conectando a rede: ");

  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_SENHA);
 
  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("\n[WiFi] Sucesso! Estamos online.");

}
 
void verificarConexoes() {

  // Se o WiFi cair, reconecta

  if (WiFi.status() != WL_CONNECTED) {

    conectarWiFi();

  }

  // Se o MQTT cair, reconecta

  while (!clienteMQTT.connected()) {

    Serial.print("[MQTT] Tentando conectar...");

    String clientId = "EIA-" + String(random(0xffff), HEX);

    if (clienteMQTT.connect(clientId.c_str())) {

      Serial.println(" Conectado!");

    } else {

      delay(2000);

    }

  }

}
 
/*

* ================================================================

*  BLOCO 7 — LEITURA DO SENSOR E VALIDAÇÃO

* ================================================================

*/

bool lerSensorBotao() {

  // O INPUT_PULLUP inverte a lógica: LOW significa que o botão foi apertado

  bool botaoApertado = (digitalRead(PINO_BOTAO) == LOW);
 
  // Só retorna verdadeiro se o botão for apertado E a porta já estiver fechada

  if (botaoApertado && !portaAberta) {

    Serial.println("[SENSOR] Botão de acessibilidade acionado!");

    delay(200); // Pausa rápida para evitar "clique duplo" sem querer

    return true;

  }

  return false;

}
 
/*

* ================================================================

*  BLOCO 8 — ATUADOR (AGINDO NO MUNDO FÍSICO)

* ================================================================

*/

void acionarPorta() {

  // Se a porta está aberta, precisamos checar se já deu o tempo de fechar

  if (portaAberta) {

    digitalWrite(PINO_LED, HIGH); // Mantém o LED aceso (Porta aberta)
 
    unsigned long tempoPassado = millis() - tempoAbertura;

    // Se passou dos 10 segundos (TEMPO_PORTA)...

    if (tempoPassado >= TEMPO_PORTA) {

      digitalWrite(PINO_LED, LOW); // Apaga o LED (Fecha a porta)

      portaAberta = false;

      statusMudou = true; // Avisa que a porta fechou para mandar pra nuvem

      Serial.println("[ATUADOR] Tempo esgotado. Porta fechada.");

    }

  }

}
 
/*

* ================================================================

*  BLOCO 9 — ENVIO PARA A API (A NUVEM VIA MQTT)

* ================================================================

*/

bool enviarParaNuvem(String evento) {

  // 1. Cria o objeto JSON

  StaticJsonDocument<200> doc;

  doc["dispositivo"] = ID_ELEVADOR;

  doc["evento"]      = evento;

  doc["porta_aberta"]= portaAberta;

  doc["timestamp"]   = millis();
 
  // 2. Transforma em texto (String)

  String pacoteJSON;

  serializeJson(doc, pacoteJSON);

  Serial.println("[NUVEM] Enviando pacote: " + pacoteJSON);
 
  // 3. Envia pelo MQTT (Publica no tópico)

  bool sucesso = clienteMQTT.publish(TOPICO_ENVIO, pacoteJSON.c_str());
 
  if (sucesso) {

    Serial.println("[NUVEM] Sucesso! Aplicativo notificado.");

  } else {

    Serial.println("[NUVEM] Falha ao enviar a mensagem.");

  }
 
  return sucesso;

}
