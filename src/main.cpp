#include <Arduino.h>
#include <notifier.h>
//#include <rgb/simple.h>

BasicRGBLed led = BasicRGBLed(6, 10, 11);
Notifier<BasicRGBLed> notifier = Notifier<BasicRGBLed>(led, 1000);

void setup() {
    led.init();
    notifier.addNotification(Notification(0x0A, 0x00640000));
    notifier.addNotification(Notification(0x0B, 0x00006400));
    notifier.addNotification(Notification(0x0C, 0x00000064));
}

void loop() {    
    notifier.execute();
}
