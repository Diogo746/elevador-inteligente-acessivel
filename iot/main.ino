#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

#define PINO_SDA 8
#define PINO_SCL 9

// ===================== CONFIGURAÇÕES =====================
const char* WIFI_SSID     = "wifi";
const char* WIFI_PASSWORD = "senha_do_wifi";
const char* SERVER_URL    = "http://ip_da_maquina/api/iot/evento";

// ===================== PINOS =============================
const int BOTAO_PIN = 5;
const int LED_PIN   = 2;

// ===================== VARIÁVEIS =========================
bool estadoBotaoAnterior = HIGH;
int contadorBotao = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===================== SETUP =============================
void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.setPins(PINO_SDA, PINO_SCL);
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(BOTAO_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
      Serial.println("=== DESCONECTOU ===");
      Serial.print("Motivo: ");
      Serial.println(info.wifi_sta_disconnected.reason);
    }
  });

  conectarWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    sincronizarHora();
  } else {
    Serial.println("Pulando sincronização da hora.");
  }

  Serial.println("Sistema pronto. Aguardando botão...");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Esperando Botao");
}

// ===================== LOOP ==============================
void loop() {
  bool estadoBotaoAtual = digitalRead(BOTAO_PIN);

  if (estadoBotaoAnterior == HIGH && estadoBotaoAtual == LOW) {
    delay(50);
    contadorBotao++;

    Serial.println("\nBotão pressionado! Total: " + String(contadorBotao));
    digitalWrite(LED_PIN, LOW);

    int httpCode = enviarEvento("PORTA_ABERTA");

    if (httpCode == 200) {
      Serial.println("Servidor respondeu 200 — Acendendo LED!");
      acenderLED();
    } else {
      Serial.println("Erro — HTTP " + String(httpCode));
    }

    // Volta a tela de espera após a ação
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Esperando Botao");
  }

  estadoBotaoAnterior = estadoBotaoAtual;
  delay(50);
}

// ===================== WIFI ==============================
void conectarWiFi() {
  WiFi.disconnect(true);
  delay(1000);

  btStop();
  WiFi.mode(WIFI_STA);
  WiFi.setMinSecurity(WIFI_AUTH_WPA2_PSK);
  WiFi.setScanMethod(WIFI_ALL_CHANNEL_SCAN);
  WiFi.setSortMethod(WIFI_CONNECT_AP_BY_SIGNAL);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando em:");
  lcd.setCursor(0, 1);
  lcd.print(String(WIFI_SSID));

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 30) {
    Serial.print("Tentativa ");
    Serial.print(tentativas + 1);
    Serial.print(" | Status: ");
    Serial.println(WiFi.status());
    delay(1000);
    tentativas++;
  }

  Serial.println();
  int statusFinal = WiFi.status();

  if (statusFinal == WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi conectado!");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP().toString());
    delay(3000);
  } else if (statusFinal == WL_NO_SSID_AVAIL) {
    Serial.println("ERRO: SSID não encontrado.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SSID nao");
    lcd.setCursor(0, 1);
    lcd.print("encontrado");
  } else if (statusFinal == WL_CONNECT_FAILED) {
    Serial.println("ERRO: Senha incorreta.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha");
    lcd.setCursor(0, 1);
    lcd.print("incorreta");
  } else if (statusFinal == WL_DISCONNECTED) {
    Serial.println("ERRO: Dispositivo desconectado.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dispositivo");
    lcd.setCursor(0, 1);
    lcd.print("desconectado");
  } else {
    Serial.println("ERRO: Falha desconhecida. Status: " + String(statusFinal));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Falha WiFi");
    lcd.setCursor(0, 1);
    lcd.print("Status: " + String(statusFinal));
  }
}

// ===================== ENVIO HTTP ========================
int enviarEvento(String tipoEvento) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Reconectando...");
    conectarWiFi();
    return -1;
  }

  time_t agora    = time(nullptr);
  struct tm* info = localtime(&agora);

  char data[11];
  char hora[9];
  strftime(data, sizeof(data), "%Y-%m-%d", info);
  strftime(hora, sizeof(hora), "%H:%M:%S", info);

  StaticJsonDocument<256> json;
  json["tipo_evento"] = tipoEvento;
  json["data_evento"] = data;
  json["hora_evento"] = hora;

  String corpo;
  serializeJson(json, corpo);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enviando");
  lcd.setCursor(0, 1);
  lcd.print("Requisicao...");

  HTTPClient http;
  http.begin(String(SERVER_URL) + "/criar");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("idPlaca", WiFi.macAddress());
  http.setTimeout(10000);

  int httpCode = http.POST(corpo);

  if (httpCode > 0) {
    String body = http.getString();

    lcd.clear();
    lcd.setCursor(0, 0);
    if (httpCode == 200)      lcd.print("OK 200");
    else if (httpCode == 201) lcd.print("Criado 201");
    else if (httpCode == 400) lcd.print("Erro req 400");
    else if (httpCode == 401) lcd.print("Sem auth 401");
    else if (httpCode == 403) lcd.print("Proibido 403");
    else if (httpCode == 404) lcd.print("N encontrado");
    else if (httpCode == 500) lcd.print("Erro server");
    else                      lcd.print("HTTP: " + String(httpCode));

    lcd.setCursor(0, 1);
    if (body.length() > 16) lcd.print(body.substring(0, 16));
    else lcd.print(body);

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Falha HTTP");
    lcd.setCursor(0, 1);
    lcd.print(http.errorToString(httpCode).substring(0, 16));
  }

  delay(3000); // tempo para ler o resultado antes de voltar à tela de espera
  http.end();
  return httpCode;
}

// ===================== LED ===============================
void acenderLED() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED aceso por 5 segundos...");
  delay(5000);

  digitalWrite(LED_PIN, LOW);
  Serial.println("LED apagado.");
}

// ===================== HORA ==============================
void sincronizarHora() {
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sincronizando");
  lcd.setCursor(0, 1);
  lcd.print("hora...");

  int tentativas = 0;
  while (time(nullptr) < 100000 && tentativas < 30) {
    Serial.print(".");
    delay(500);
    tentativas++;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (time(nullptr) >= 100000) {
    lcd.print("Hora sincronizada");
    lcd.setCursor(0, 1);
    lcd.print("com sucesso!");
  } else {
    lcd.print("Falha ao");
    lcd.setCursor(0, 1);
    lcd.print("sincron. hora");
  }
  delay(2000);
}
