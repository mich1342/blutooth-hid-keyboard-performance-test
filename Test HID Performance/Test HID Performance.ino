// Set 1 to use char by char sending data method
// Set 0 to blast full text at once

#define USE_CHAR_BY_CHAR 1

// Delay between each char (in milliseconds)
#define DELAY_CHAR 5

#include <BleKeyboard.h>

BleKeyboard bleKeyboard("KLS Test");
#define LED 2
char buf[50];
String dummyString = "123456789.987654321";

int payload = 0;
long lastMsg;

void setup() {
  // put your setup code here, to run once:
  bleKeyboard.begin();
  pinMode(LED, OUTPUT);
 
}

void loop() {
  if (bleKeyboard.isConnected()) {
    digitalWrite(LED, HIGH);


    digitalWrite(LED, LOW);
#if USE_CHAR_BY_CHAR
    payload = dummyString.length() + 1;
    dummyString.toCharArray(buf, payload);
    for (int i = 0; i < payload; i++) {
      bleKeyboard.print(buf[i]);
      Serial.print(buf[i]);
      delay(DELAY_CHAR);
    }
    bleKeyboard.println();
#else
  bleKeyboard.println(dummyString);
#endif

    delay(5000);
  } else {
    long now = millis();
    if (now - lastMsg > 500) {
      lastMsg = now;
      digitalWrite(LED, !digitalRead(LED));
    }
  }
}