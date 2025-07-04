#include <Arduino.h>
#include <mcp2515.h>


enum CANMessages : uint32_t { RPM = 0x00000042, GEAR = 0x00000043 };


MCP2515 mcp{10, 10000000};
can_frame frame;

void frame_data_to_string(const uint8_t data[], const uint8_t len, char* out) {
    for (int i = 0; i < len; i++) {
        out[i] = data[i];
    }
    out[len] = '\0';
}

void setup() {
    Serial.begin(115200);

    mcp.setBitrate(CAN_500KBPS);
}

void loop() {
    char buffer[CAN_MAX_DLEN + 1];
    buffer[CAN_MAX_DLEN] = '\0';
    if (mcp.readMessage(&frame) == MCP2515::ERROR_OK) {

        switch (frame.can_id) {
            case RPM:
                Serial.print("RPM: ");
                Serial.print(buffer);
        }
    }
    delay(15000);
}
