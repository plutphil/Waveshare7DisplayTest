#pragma once
#include <Arduino.h>
#include <Wire.h>

class CH422G {
public:
    static constexpr uint8_t IO_COUNT = 12;
    static constexpr uint8_t REG_WR_SET = 0x24; // 0x48 >> 1
    static constexpr uint8_t REG_WR_OC  = 0x23; // 0x46 >> 1
    static constexpr uint8_t REG_WR_IO  = 0x38; // 0x70 >> 1
    static constexpr uint8_t REG_RD_IO  = 0x26; // 0x4D >> 1

    CH422G(TwoWire &wire = Wire, uint8_t address = 0x24)
        : _wire(wire), _addr(address), wr_oc(0x0F), wr_io(0xFF), wr_set(0x01) {}

    void begin() {
        writeReg(REG_WR_SET, wr_set);
        writeReg(REG_WR_OC, wr_oc);
        writeReg(REG_WR_IO, wr_io);
    }

    void setOutput(uint8_t pin) {
        if (pin >= IO_COUNT) return;
        wr_set |= 0x01; // IO_OE bit
        writeReg(REG_WR_SET, wr_set);
    }

    void setInput(uint8_t pin) {
        if (pin >= IO_COUNT) return;
        wr_set &= ~0x01;
        writeReg(REG_WR_SET, wr_set);
        delay(2);
    }

    void digitalWrite(uint8_t pin, bool level) {
        if (pin >= IO_COUNT) return;
        if (pin >= 8)
            wr_oc = (wr_oc & ~(1 << (pin - 8))) | ((level ? 1 : 0) << (pin - 8));
        else
            wr_io = (wr_io & ~(1 << pin)) | ((level ? 1 : 0) << pin);
        writeReg(REG_WR_OC, wr_oc);
        writeReg(REG_WR_IO, wr_io);
    }

    bool digitalRead(uint8_t pin) {
        if (pin >= IO_COUNT) return false;
        _wire.beginTransmission(_addr);
        _wire.write(REG_RD_IO);
        _wire.endTransmission(false);
        _wire.requestFrom((int)_addr, 1);
        uint8_t val = _wire.available() ? _wire.read() : 0;
        return (val >> pin) & 0x01;
    }

    void setAllInput() {
        wr_set &= ~0x01;
        writeReg(REG_WR_SET, wr_set);
        delay(2);
    }

    void setAllOutput() {
        wr_set |= 0x01;
        writeReg(REG_WR_SET, wr_set);
    }

    void setOpenDrain(bool enable) {
        if (enable)
            wr_set |= 0x04; // OD_EN bit
        else
            wr_set &= ~0x04;
        writeReg(REG_WR_SET, wr_set);
    }

    void pinMode(uint8_t pin, uint8_t mode) {
        if (pin >= IO_COUNT) return;
        if (mode == INPUT) {
            setInput(pin);
        } else if (mode == OUTPUT) {
            setOutput(pin);
        } else if (mode == INPUT_PULLUP) {
            setInput(pin);
            digitalWrite(pin, HIGH); // Emulate pull-up if circuit allows
        }
    }
    

private:
    TwoWire &_wire;
    uint8_t _addr;
    uint8_t wr_set, wr_oc, wr_io;

    void writeReg(uint8_t reg, uint8_t data) {
        _wire.beginTransmission(_addr);
        _wire.write(reg);
        _wire.write(data);
        _wire.endTransmission();
    }
};
