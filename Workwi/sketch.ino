#include <WiFi.h>
#include <PubSubClient.h>


#define TRIG_PIN 5
#define ECHO_PIN 18


#define LED_PIN 2


#define LDR_PIN 34

const float LIMITE_DISTANCIA = 100.0;    
const int LIMITE_LUMINOSIDADE = 1000;   

const char* ssid = "Wokwi-GUEST"; // nome do wifi
const char* password = ""; //senha do wifi


const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "smartguard/sensores";


WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  conectarWiFi();

  mqttClient.setServer(mqttServer, mqttPort);

  conectarMQTT();

  Serial.println("Sistema SmartGuard IoT iniciado...");
  Serial.println("-----------------------------------");
}

void loop() {
  if (!mqttClient.connected()) {
    conectarMQTT();
  }

  mqttClient.loop();

  float distancia = medirDistancia();
  int luminosidade = analogRead(LDR_PIN);

  bool aproximacaoDetectada = distancia <= LIMITE_DISTANCIA;
  bool ambienteEscuro = luminosidade < LIMITE_LUMINOSIDADE;

  String statusAproximacao;
  String statusLuminosidade;
  String statusGeral;

  if (aproximacaoDetectada) {
    statusAproximacao = "ALERTA";
  } else {
    statusAproximacao = "NORMAL";
  }

  if (ambienteEscuro) {
    statusLuminosidade = "ESCURO";
  } else {
    statusLuminosidade = "ADEQUADO";
  }

  if (aproximacaoDetectada && ambienteEscuro) {
    statusGeral = "CRITICO";
    digitalWrite(LED_PIN, HIGH);
  } else if (aproximacaoDetectada) {
    statusGeral = "ALERTA";
    digitalWrite(LED_PIN, HIGH);
  } else {
    statusGeral = "NORMAL";
    digitalWrite(LED_PIN, LOW);
  }

  String payload = montarJSON(
    distancia,
    luminosidade,
    statusAproximacao,
    statusLuminosidade,
    statusGeral
  );

  mqttClient.publish(mqttTopic, payload.c_str());

  Serial.println("Dados publicados no MQTT:");
  Serial.println(payload);
  Serial.println("-----------------------------------");

  delay(3000);
}

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao broker MQTT... ");

    String clientId = "SmartGuardESP32-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou. Codigo: ");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);

  float distancia = duracao * 0.034 / 2;

  return distancia;
}

String montarJSON(
  float distancia,
  int luminosidade,
  String statusAproximacao,
  String statusLuminosidade,
  String statusGeral
) {
  String payload = "{";

  payload += "\"distancia_cm\":";
  payload += String(distancia, 2);
  payload += ",";

  payload += "\"luminosidade\":";
  payload += String(luminosidade);
  payload += ",";

  payload += "\"status_aproximacao\":\"";
  payload += statusAproximacao;
  payload += "\",";

  payload += "\"status_luminosidade\":\"";
  payload += statusLuminosidade;
  payload += "\",";

  payload += "\"status_geral\":\"";
  payload += statusGeral;
  payload += "\"";

  payload += "}";

  return payload;
}