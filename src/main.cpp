#include <Arduino.h>
#include <notification.h>
#include <notifier.h>
#include <rgb/simple.h>
#include <com_layer.h>

BasicRGBLed led = BasicRGBLed(6, 10, 11);
Notifier<BasicRGBLed> notifier = Notifier<BasicRGBLed>(led, 1000);
ComLayer com_layer = ComLayer(0x7e);

void setup() {
    led.init();
    Serial.begin(115200);
}

void loop() {
    if(com_layer.available(Serial)){
        notifier.addNotification(com_layer.getNotification());
    }  
    notifier.execute();
}
