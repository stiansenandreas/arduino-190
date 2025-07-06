#include <mcp2515.h>
#include <U8g2lib.h>

#include "Transmission.hpp"


namespace {
enum MessageID : uint32_t { TRANSMISSION = 0x00000603 };

struct Static {
    inline static U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C U8G2{U8G2_R0, PIN_WIRE_SCL, PIN_WIRE_SDA, U8X8_PIN_NONE};
    inline static MCP2515 MCP{PIN_SPI_SS};
};

struct State {
    inline static volatile bool INTERRUPT = false;
    inline static can_frame FRAME;
    inline static Transmission::Mode MODE{};
    inline static Transmission::Gear GEAR{};
    inline static Transmission::Temp TEMP{};
};

void irqHandler() {
    State::INTERRUPT = true;
}

void draw() {
    constexpr uint8_t char_width = 18;
    constexpr uint8_t display_height = 32;
    Static::U8G2.clearBuffer();
    Static::U8G2.drawStr(0 * char_width, display_height - 1, State::GEAR.to_str());
    Static::U8G2.drawStr(2 * char_width, display_height - 1, State::MODE.to_str());
    Static::U8G2.drawStr(4 * char_width, display_height - 1, State::TEMP.to_str());
    Static::U8G2.sendBuffer();
}

void read(const MCP2515::RXBn rx) {
    if (Static::MCP.readMessage(rx, &State::FRAME) == MCP2515::ERROR_OK) {
        switch (State::FRAME.can_id) {
            case TRANSMISSION:
                State::GEAR = State::FRAME.data[0];
                State::MODE = State::FRAME.data[1];
                State::TEMP = State::FRAME.data[2];
                break;
            default:
                break;
        }
    }
}
} // namespace

void setup() {
    Static::MCP.setBitrate(CAN_500KBPS);
    Static::MCP.setListenOnlyMode();
    attachInterrupt(0, irqHandler, FALLING);

    Static::U8G2.begin();
    Static::U8G2.setFont(u8g2_font_logisoso28_tf);
}

void loop() {
    if (State::INTERRUPT) {
        State::INTERRUPT = false;

        const uint8_t irq = Static::MCP.getInterrupts();

        if (irq & MCP2515::CANINTF_RX0IF) {
            read(MCP2515::RXB0);
        }
        if (irq & MCP2515::CANINTF_RX1IF) {
            read(MCP2515::RXB1);
        }

        draw();
    }
}
