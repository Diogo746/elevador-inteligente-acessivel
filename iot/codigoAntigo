#include <WiFi.h>
#include <PubSubClient.h>

// ================= WIFI =================
const char* ssid = "Nome_Wifi";
const char* password = "senha";

// ================= MQTT =================
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ================= PINOS =================
#define BOTAO 4
#define LED   2

// ================= CONTROLE =================
bool modoAtivo = false;
unsigned long ultimoClique = 0;
const unsigned long debounce = 300;

// ================= WIFI SETUP =================
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ================= MQTT RECONNECT =================
void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP32_Elevador_" + String(random(0xffff));

    Serial.print("Conectando ao MQTT...");

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      client.publish("elevador/status", "online");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s...");
      delay(2000);
    }
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

// ================= LOOP =================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  bool leituraBotao = digitalRead(BOTAO);

  // debounce simples
  if (leituraBotao == LOW && millis() - ultimoClique > debounce && !modoAtivo) {
    ultimoClique = millis();
    modoAtivo = true;

    Serial.println("Modo acessível ativado");

    client.publish("elevador/evento", "modo_acessivel_ativado");

    digitalWrite(LED, HIGH);

    delay(20000); // segura a porta do elevador por 20 segundos

    digitalWrite(LED, LOW);

    client.publish("elevador/evento", "modo_acessivel_finalizado");

    modoAtivo = false;
  }
}
