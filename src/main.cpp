#include <Arduino.h>
#include <rgb/simple.h>

BasicRGBLed led = BasicRGBLed(11, 10, 6);

void notifier(BaseLed &led) {
    led.setColor(0x00, 0x64, 0x00);
}

void setup() {
    led.init();
}

void loop() {
    led.setColor(0xFF, 0x00, 0xFF);
    delay(1000);
    notifier(led);
    delay(1000);
}
