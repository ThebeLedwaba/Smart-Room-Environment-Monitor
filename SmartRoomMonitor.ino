#include <DHT.h>

#define DHTPIN 2        // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11
#define PIRPIN 3        // PIR sensor connected to digital pin 3
#define LEDPIN 13       // Optional LED for alert

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(PIRPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  dht.begin();

  Serial.println("Smart Room Environment Monitor Initialized");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int motionDetected = digitalRead(PIRPIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  if (motionDetected == HIGH) {
    Serial.println("Motion detected! Alert triggered.");
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  delay(2000); // 2 seconds delay
}
