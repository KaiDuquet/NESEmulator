#include "cpu6502.h"

cpu6502::cpu6502() {

}

cpu6502::~cpu6502() {

}

void cpu6502::write(uint16_t addr, uint8_t data) {
	bus->write(addr, data);
}

uint8_t cpu6502::read(uint16_t addr) {
	return bus->read(addr);
}