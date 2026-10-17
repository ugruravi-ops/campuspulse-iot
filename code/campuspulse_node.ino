/*
 * CampusPulse — Smart Campus Environment Monitoring Node
 * Author : Ravi (ugruravi-ops) — for MARVEL R&D Lab membership project
 * Board  : ESP32 DevKit v1
 * Sensors: DHT11 (temp/humidity), MQ-135 (air quality), KY-037 (noise)
 * Cloud  : ThingSpeak (HTTP REST API)
 *
 * NOTE: Fill in WIFI_SSID, WIFI_PASS and TS_API_KEY before flashing.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ---------- User configuration ----------
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* TS_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY"; // ThingSpeak > Channels > API Keys
const char* TS_URL = "http://api.thingspeak.com/update";

// ---------- Pin mapping ----------
#define DHTPIN 4        // DHT11 data pin
#define DHTTYPE DHT11
#define MQ135_PIN 34    // Analog pin for MQ-135
#define NOISE_PIN 35    // Analog pin for KY-037 noise sensor
#define LED_GREEN 25
#define LED_RED 26

DHT dht(DHTPIN, DHTTYPE);

// ---------- Air quality thresholds (tune after calibration) ----------
const int AQ_GOOD = 1200;      // below this: acceptable air quality
const float TEMP_MAX = 35.0;   // alert if above
const float HUM_MIN = 20.0;    // alert if below

unsigned long lastUpload = 0;
const unsigned long UPLOAD_INTERVAL = 20000; // 20 s (ThingSpeak free tier: 15 s min)

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Warm-up for MQ-135 (it needs ~24h ideally; 30s minimum for demo)
  Serial.println("Warming up MQ-135, wait 30 s...");
  delay(30000);

  connectWiFi();
}

void loop() {
  if (millis() - lastUpload >= UPLOAD_INTERVAL) {
    lastUpload = millis();

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("DHT11 read failed, retrying next cycle.");
      digitalWrite(LED_RED, HIGH);
      delay(200);
      digitalWrite(LED_RED, LOW);
      return;
    }

    int airQuality = analogRead(MQ135_PIN);   // 0-4095 on ESP32
    int noiseLevel = analogRead(NOISE_PIN);

    // Simple smoothed noise estimate (peak over ~1 s)
    int noisePeak = 0;
    for (int i = 0; i < 20; i++) {
      int s = analogRead(NOISE_PIN);
      if (s > noisePeak) noisePeak = s;
      delay(50);
    }

    Serial.printf("T=%.1f C  H=%.1f %%  AQ=%d  Noise=%d\n",
                  temperature, humidity, airQuality, noisePeak);

    bool alert = (airQuality > AQ_GOOD) || (temperature > TEMP_MAX) || (humidity < HUM_MIN);

    if (WiFi.status() != WL_CONNECTED) connectWiFi();
    if (WiFi.status() == WL_CONNECTED) {
      uploadToThingSpeak(temperature, humidity, airQuality, noisePeak);
    }

    if (alert) {
      Serial.println("!! ALERT: threshold exceeded — poor environment detected");
      for (int i = 0; i < 3; i++) { digitalWrite(LED_RED, HIGH); delay(200); digitalWrite(LED_RED, LOW); delay(200); }
    } else {
      digitalWrite(LED_GREEN, HIGH); delay(500); digitalWrite(LED_GREEN, LOW);
    }
  }
}

void connectWiFi() {
  Serial.printf("Connecting to %s", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" WiFi connected. IP: " + WiFi.localIP().toString());
  } else {
    Serial.println(" WiFi connection failed, will retry.");
  }
}

void uploadToThingSpeak(float temp, float hum, int aq, int noise) {
  HTTPClient http;
  String url = String(TS_URL) + "?api_key=" + TS_API_KEY +
               "&field1=" + String(temp) +
               "&field2=" + String(hum) +
               "&field3=" + String(aq) +
               "&field4=" + String(noise);
  http.begin(url);
  int code = http.GET();
  if (code == 200) {
    Serial.println("Upload OK");
  } else {
    Serial.printf("Upload failed, HTTP code: %d\n", code);
  }
  http.end();
}
