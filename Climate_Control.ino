const int tempPin = A0;
const int fanPin  = 5;

unsigned long lastPrint = 0;
const unsigned long interval = 500;

float readTemperature() {
  int value = analogRead(tempPin);
  float voltage = value * (5.0 / 1023.0);

  float tempC = (voltage - 0.5) * 100.0; // TMP36

  return tempC;
}

int getPWM(float temp) {
  if (temp < 27.0) return 0;
  if (temp >= 40.0) return 255;

  return (temp - 27.0) * 255 / (40.0 - 27.0);
}

void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp = readTemperature();
  int pwm = getPWM(temp);

  analogWrite(fanPin, pwm);

  if (millis() - lastPrint >= interval) {
    lastPrint = millis();

    Serial.print("Temp: ");
    Serial.print((int)(temp + 0.5));
    Serial.print(" C, PWM: ");
    Serial.println(pwm);
  }
}