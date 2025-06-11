#define BLYNK_TEMPLATE_ID "TMPL3Amu_yc70"
#define BLYNK_TEMPLATE_NAME "SMART DEVICE"
#define BLYNK_AUTH_TOKEN "C6dYvQFzhFwbHiRuOrBtM4vKKSJ0H9Mg"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SVTECHNOLOGIES";
char pass[] = "Smart.23";

BlynkTimer timer;

#define LED_PIN D4     // Controlled from Blynk (V3)
#define BUZZER_PIN D5  // Output to buzzer

BLYNK_WRITE(V3) {
  int value = param.asInt();
  if (value == 1) {
    Serial.println("LED ON");
    digitalWrite(LED_PIN, LOW);  // LED ON (active low on NodeMCU)
  } else {
    Serial.println("LED OFF");
    digitalWrite(LED_PIN, HIGH); // LED OFF
  }
}

void buzzAlert(int times = 3, int delayTime = 300) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(delayTime);
    digitalWrite(BUZZER_PIN, LOW);
    delay(delayTime);
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(LED_PIN, OUTPUT);     // LED controlled from app
  pinMode(BUZZER_PIN, OUTPUT);  // Buzzer output

  digitalWrite(LED_PIN, HIGH);  // Turn LED off initially
  digitalWrite(BUZZER_PIN, LOW); // Buzzer off initially

  buzzAlert();  // Beep buzzer 3 times
}

void loop() {
  Blynk.run();
  timer.run();

  int ledState = digitalRead(LED_PIN); // Get LED state
  Blynk.virtualWrite(V7, ledState == LOW ? 0 : 1); // Send status to app

  // Optional buzzer logic (if needed in loop)
  if (ledState == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}
