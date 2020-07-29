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
    if(com_layer.available(Serial)) {
        uint8_t command = com_layer.getCommand();
        uint8_t len = com_layer.getLength();
        uint8_t payload[len];
        com_layer.getPayload(payload);
        switch (command) {
            case ADD:
                notifier.addNotification(
                    Notification(payload[0], uint32_t(uint32_t(payload[1]) << 16 | uint32_t(payload[2]) << 8 | payload[3]))
                );
                break;
            case REMOVE:
                Serial.println("delete");
                Serial.write(payload[0]);
                notifier.cleanNotification(payload[0]);
                break;
            default:
                break;
        }
    }  
    notifier.execute();
}
