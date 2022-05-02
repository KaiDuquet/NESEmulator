#include "bus.h"

bus::bus() {
	for (auto& i : ram) i = 0x00;

	cpu.ConnectBus(this);
}

bus::~bus() {

}

void bus::write(uint16_t addr, uint8_t data) {
	ram[addr] = data;
}

uint8_t bus::read(uint16_t addr) {
	return ram[addr];
}