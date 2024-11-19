#include <Bounce2.h>

const int buttonPin = 2;
const int ledPin = 3;

int buttonState = 0;
Bounce debouncer = Bounce(); // 防跳動

unsigned long previousMillis = 0;
int blinkInterval; // 閃爍間隔

int lightMode = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  debouncer.attach(buttonPin);
  debouncer.interval(50);      // 設定防跳動間隔50毫秒
}

void loop() {
  debouncer.update(); // 更新按鈕狀態
  if (debouncer.fell()) {
    changeState();
  }

  switch (lightMode) {
    case 0: // 恆亮
      StateAlwaysLight();
      break;

    case 1: // 慢閃爍
      blinkInterval = 1000;
      blinkLED();
      break;

    case 2: // 中等速度閃爍
      blinkInterval = 500;
      blinkLED();
      break;

    case 3: // 快閃爍
      blinkInterval = 200;
      blinkLED();
      break;
  }
}

void changeState() {
  lightMode = (lightMode + 1) % 4;
}

void StateAlwaysLight() {
  digitalWrite(ledPin, LOW);
}

void blinkLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    
    int ledState = digitalRead(ledPin);
    digitalWrite(ledPin, !ledState);
  }
}

