#include <PJON.h>

// <Strategy name> bus(selected device id)
PJON<SoftwareBitBang> bus(45);

unsigned long time = millis();

void setup() {
  bus.strategy.set_pin(12);
  bus.begin();

  bus.set_error(error_handler);

  Serial.begin(115200);
}

void error_handler(uint8_t code, uint8_t data) {
  if(code == CONNECTION_LOST) {
    Serial.print("Connection lost with device id ");
    Serial.println(data);
  }
}

void loop() {

  if(millis() - time > 1000) {
    time = millis();
    int temperature = analogRead(A0);

    //Send a "T", break the int in two bytes
    char content[3] = {'T', temperature >> 8, temperature & 0xFF};

    bus.send(44, content, 3);
  }

  bus.update();
};
