#ifndef COM_LAYER_H
#define COM_LAYER_H

#include <Arduino.h>
#include <notification.h>

// Sample: 7E040A00006491
// Sample: 7E040B6400642C


class ComLayer {
    private:
        uint8_t header;
        Notification notification;
    public:
        ComLayer(uint8_t header);
        bool available(Stream &uart);
        Notification getNotification();
};

ComLayer::ComLayer(uint8_t header) {
    this->header = header;
};

bool ComLayer::available(Stream &uart){
    if(uart.available() >= 2){
        if(uart.read() == this->header){
            uint8_t len = uart.read();
            uint8_t input_buffer[len];
            uart.readBytes(input_buffer, len+1);
            uint8_t recived_chk = input_buffer[len];
            uint8_t calculated_chk = 0;
            for(int i=0; i<len; i++){
                calculated_chk+=input_buffer[i];
            }
            if(uint8_t(0xFF-calculated_chk) == recived_chk){
                this->notification = Notification(
                    input_buffer[0], 
                    uint32_t(uint32_t(input_buffer[1]) << 16 | uint16_t(input_buffer[2]) << 8 | input_buffer[3])
                );
                return true;
            }
        }
    }
    return false;
}

Notification ComLayer::getNotification(){
    return this->notification;
}

#endif