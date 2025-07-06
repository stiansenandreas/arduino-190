#pragma once

namespace Transmission {
enum TransmissionMode : uint8_t { AUTOMATIC = 1, MANUAL = 2 };
enum TransmissionGear : uint8_t {
    N = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
    _5 = 5,
};

template <typename E>
struct Base {
    E value{};

    explicit Base(E v) : value(v) {}

    Base& operator=(const uint8_t val) {
        value = static_cast<E>(val);
        return *this;
    }

    [[nodiscard]] virtual const char* to_str() = 0;

protected:
    ~Base() = default;
};


struct Mode final : Base<TransmissionMode> {
    using Base::operator=;
    explicit Mode() : Base(AUTOMATIC) {}

    [[nodiscard]] const char* to_str() override {
        switch (value) {
            case AUTOMATIC:
                return "A";
            case MANUAL:
                return "M";
            default:
                return "";
        }
    }
};

struct Gear final : Base<TransmissionGear> {
    using Base::operator=;
    explicit Gear() : Base(N) {}

    [[nodiscard]] const char* to_str() override {
        switch (value) {
            case N:
                return "N";
            case _1:
                return "1";
            case _2:
                return "2";
            case _3:
                return "3";
            case _4:
                return "4";
            case _5:
                return "5";
            default:
                return "";
        }
    }
};

struct Temp final : Base<uint8_t> {
    using Base::operator=;
    explicit Temp() : Base(0) {}

    [[nodiscard]] const char* to_str() override {
        static char str[4] = "00C";
        utoa(value, str, 10);
        str[2] = 'C';
        str[3] = '\0';
        return str;
    }
};
}
