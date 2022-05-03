#include "bus.h"
#include "cpu6502.h"

_6502::_6502() {
	using a = _6502;
	opLookup =
	{
		{"BRK", &a::BRK, &a::IMP, 7},{"ORA", &a::ORA, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ORA", &a::ORA, &a::ZPG, 3},{"ASL", &a::ASL, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"PHP", &a::PHP, &a::IMP, 3},{"ORA", &a::ORA, &a::IMM, 2},{"ASL", &a::ASL, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ORA", &a::ORA, &a::ABS, 4},{"ASL", &a::ASL, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BPL", &a::BPL, &a::REL, 2},{"ORA", &a::ORA, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ORA", &a::ORA, &a::ZPX, 4},{"ASL", &a::ASL, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"CLC", &a::CLC, &a::IMP, 2},{"ORA", &a::ORA, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ORA", &a::ORA, &a::ABX, 4},{"ASL", &a::ASL, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
		{"JSR", &a::JSR, &a::ABS, 6},{"AND", &a::AND, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"BIT", &a::BIT, &a::ZPG, 3},{"AND", &a::AND, &a::ZPG, 3},{"ROL", &a::ROL, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"PLP", &a::PLP, &a::IMP, 4},{"AND", &a::AND, &a::IMM, 2},{"ROL", &a::ROL, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"BIT", &a::BIT, &a::ABS, 4},{"AND", &a::AND, &a::ABS, 4},{"ROL", &a::ROL, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BMI", &a::BMI, &a::REL, 2},{"AND", &a::AND, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"AND", &a::AND, &a::ZPX, 4},{"ROL", &a::ROL, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"SEC", &a::SEC, &a::IMP, 2},{"AND", &a::AND, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"AND", &a::AND, &a::ABX, 4},{"ROL", &a::ROL, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
		{"RTI", &a::RTI, &a::IMP, 6},{"EOR", &a::EOR, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"EOR", &a::EOR, &a::ZPG, 3},{"LSR", &a::LSR, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"PHA", &a::PHA, &a::IMP, 3},{"EOR", &a::EOR, &a::IMM, 2},{"LSR", &a::LSR, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"JMP", &a::JMP, &a::ABS, 3},{"EOR", &a::EOR, &a::ABS, 4},{"LSR", &a::LSR, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BVC", &a::BVC, &a::REL, 2},{"EOR", &a::EOR, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"EOR", &a::EOR, &a::ZPX, 4},{"LSR", &a::LSR, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"CLI", &a::CLI, &a::IMP, 2},{"EOR", &a::EOR, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"EOR", &a::EOR, &a::ABX, 4},{"LSR", &a::LSR, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
		{"RTS", &a::RTS, &a::IMP, 6},{"ADC", &a::ADC, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ADC", &a::ADC, &a::ZPG, 3},{"ROR", &a::ROR, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"PLA", &a::PLA, &a::IMP, 4},{"ADC", &a::ADC, &a::IMP, 7},{"ROR", &a::ROR, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"JMP", &a::JMP, &a::IND, 5},{"ADC", &a::ADC, &a::ABS, 4},{"ROR", &a::ROR, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BVS", &a::BVS, &a::REL, 2},{"ADC", &a::ADC, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ADC", &a::ADC, &a::ZPX, 4},{"ROR", &a::ROR, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"SEI", &a::SEI, &a::IMP, 2},{"ADC", &a::ADC, &a::IMP, 7},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"ADC", &a::ADC, &a::ABX, 4},{"ROR", &a::ROR, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
		{"XXX", &a::XXX, &a::IMP, 2},{"STA", &a::STA, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"STY", &a::STY, &a::ZPG, 3},{"STA", &a::STA, &a::ZPG, 3},{"STX", &a::STX, &a::ZPG, 3},{"XXX", &a::XXX, &a::IMP, 2},{"DEY", &a::DEY, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"TXA", &a::TXA, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"STY", &a::STY, &a::ABS, 4},{"STA", &a::STA, &a::ABS, 4},{"STX", &a::STX, &a::ABS, 4},{"XXX", &a::XXX, &a::IMP, 2},
		{"BCC", &a::BCC, &a::REL, 2},{"STA", &a::STA, &a::IZY, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"STY", &a::STY, &a::ZPY, 4},{"STA", &a::STA, &a::ZPX, 4},{"STX", &a::STX, &a::ZPY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"TYA", &a::TYA, &a::IMP, 2},{"STA", &a::STA, &a::ABY, 5},{"TXS", &a::TXS, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"STA", &a::STA, &a::ABX, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},
		{"LDY", &a::LDY, &a::IMM, 2},{"LDA", &a::LDA, &a::IZX, 6},{"LDX", &a::LDX, &a::IMM, 2},{"XXX", &a::XXX, &a::IMP, 2},{"LDY", &a::LDY, &a::ZPG, 3},{"LDA", &a::LDA, &a::ZPG, 3},{"LDX", &a::LDX, &a::ZPG, 3},{"XXX", &a::XXX, &a::IMP, 2},{"TAY", &a::TAY, &a::IMP, 2},{"LDA", &a::LDA, &a::IMM, 2},{"TAX", &a::TAX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"LDY", &a::LDY, &a::ABS, 4},{"LDA", &a::LDA, &a::ABS, 4},{"LDX", &a::LDX, &a::ABS, 4},{"XXX", &a::XXX, &a::IMP, 2},
		{"BCS", &a::BCS, &a::REL, 2},{"LDA", &a::LDA, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"LDY", &a::LDY, &a::ZPY, 4},{"LDA", &a::LDA, &a::ZPX, 4},{"LDX", &a::LDX, &a::ZPY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"CLV", &a::CLV, &a::IMP, 2},{"LDA", &a::LDA, &a::ABY, 4},{"TSX", &a::TSX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"LDY", &a::LDY, &a::ABX, 4},{"LDA", &a::LDA, &a::ABX, 4},{"LDX", &a::LDX, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},
		{"CPY", &a::CPY, &a::IMM, 2},{"CMP", &a::CMP, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CPY", &a::CPY, &a::ZPG, 3},{"CMP", &a::CMP, &a::ZPG, 3},{"DEC", &a::DEC, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"INY", &a::INY, &a::IMP, 2},{"CMP", &a::CMP, &a::IMM, 2},{"DEX", &a::DEX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CPY", &a::CPY, &a::ABS, 4},{"CMP", &a::CMP, &a::ABS, 4},{"DEC", &a::DEC, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BNE", &a::BNE, &a::REL, 2},{"CMP", &a::CMP, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CMP", &a::CMP, &a::ZPX, 4},{"DEC", &a::DEC, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"CLD", &a::CLD, &a::IMP, 2},{"CMP", &a::CMP, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CMP", &a::CMP, &a::ABX, 4},{"DEC", &a::DEC, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
		{"CPX", &a::CPX, &a::IMM, 2},{"SBC", &a::SBC, &a::IZX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CPX", &a::CPX, &a::ZPG, 3},{"SBC", &a::SBC, &a::ZPG, 3},{"INC", &a::INC, &a::ZPG, 5},{"XXX", &a::XXX, &a::IMP, 2},{"INX", &a::INX, &a::IMP, 2},{"SBC", &a::SBC, &a::IMM, 2},{"NOP", &a::NOP, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"CPX", &a::CPX, &a::ABS, 4},{"SBC", &a::SBC, &a::ABS, 4},{"INC", &a::INC, &a::ABS, 6},{"XXX", &a::XXX, &a::IMP, 2},
		{"BEQ", &a::BEQ, &a::REL, 2},{"SBC", &a::SBC, &a::IZY, 5},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"SBC", &a::SBC, &a::ZPX, 4},{"INC", &a::INC, &a::ZPX, 6},{"XXX", &a::XXX, &a::IMP, 2},{"SED", &a::SED, &a::IMP, 2},{"SBC", &a::SBC, &a::ABY, 4},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"XXX", &a::XXX, &a::IMP, 2},{"SBC", &a::SBC, &a::ABX, 4},{"INC", &a::INC, &a::ABX, 7},{"XXX", &a::XXX, &a::IMP, 2},
	};
}

_6502::~_6502() {

}

void _6502::write(uint16_t addr, uint8_t data) {
	bus->write(addr, data);
}

uint8_t _6502::read(uint16_t addr) {
	return bus->read(addr);
}

void _6502::stackPush(uint8_t data) {
	write(STACK_BASE + sp, data);
	sp--;
}

uint8_t _6502::stackPop() {
	sp++;
	return read(STACK_BASE + sp);
}

void _6502::clock() {
	if (cycles == 0) {
		opcode = read(pc++);

		Inst inst = opLookup[opcode];
		cycles = inst.cycles;
		uint8_t c1 = (this->*inst.addrmode)();
		uint8_t c2 = (this->*inst.opcode)();
		cycles += (c1 & c2);
	}
	cycles--;
}

uint8_t _6502::GetFlag(FLAG6502 f) {
	return status & f;
}

void _6502::SetFlag(FLAG6502 f, bool v) {
	if (v)
		status |= f;
	else
		status &= ~f;
}

uint8_t _6502::IMP() {
	fetched = a;
	return 0;
}

uint8_t _6502::IMM() {
	addr_abs = pc++;
	return 0;
}

uint8_t _6502::ZPG() {
	addr_abs = read(pc++);
	addr_abs &= LO_BYTE_MASK;
	return 0;
}

uint8_t _6502::ZPX() {
	addr_abs = read(pc++) + x;
	addr_abs &= LO_BYTE_MASK;
	return 0;
}

uint8_t _6502::ZPY() {
	addr_abs = read(pc++) + y;
	addr_abs &= LO_BYTE_MASK;
	return 0;
}

uint8_t _6502::ABS() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t _6502::ABX() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = ((hi << 8) | lo) + x;

	return (addr_abs & HI_BYTE_MASK) != (hi << 8);
}

uint8_t _6502::ABY() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = ((hi << 8) | lo) + y;

	return (addr_abs & HI_BYTE_MASK) != (hi << 8);
}

uint8_t _6502::IND() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	uint16_t ptr = (hi << 8) | lo;

	if (lo == LO_BYTE_MASK)
		addr_abs = (read(ptr & HI_BYTE_MASK) << 8) | read(ptr);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

uint8_t _6502::IZX() {
	uint16_t t = read(pc++);

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & LO_BYTE_MASK);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & LO_BYTE_MASK);

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t _6502::IZY() {
	uint16_t t = read(pc++);

	uint16_t lo = read(t & LO_BYTE_MASK);
	uint16_t hi = read((t + 1) & LO_BYTE_MASK);

	addr_abs = ((hi << 8) | lo) + y;

	return (addr_abs & HI_BYTE_MASK) != (hi << 8);
}

uint8_t _6502::REL() {
	addr_rel = read(pc++);
	if (addr_rel & SIGBIT_MASK_8)
		addr_rel |= HI_BYTE_MASK;
	return 0;
}

// Instructions

uint8_t _6502::fetch() {
	if (!(opLookup[opcode].addrmode == &_6502::IMP))
		fetched = read(addr_abs);
	return fetched;
}

uint8_t _6502::AND() {
	fetch();
	a &= fetched;
	SetFlag(Z, a == ZERO_8);
	SetFlag(N, a & SIGBIT_MASK_8);
	return 1;
}

uint8_t _6502::BCS() {
	if (GetFlag(C)) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BCC() {
	if (GetFlag(C) == 0) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BEQ() {
	if (GetFlag(Z)) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BMI() {
	if (GetFlag(N)) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BNE() {
	if (GetFlag(Z) == 0) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BPL() {
	if (GetFlag(N) == 0) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BVC() {
	if (GetFlag(V) == 0) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::BVS() {
	if (GetFlag(V)) {
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & HI_BYTE_MASK) != (pc & HI_BYTE_MASK))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t _6502::CLC() {
	SetFlag(C, false);
	return 0;
}

uint8_t _6502::CLD() {
	SetFlag(D, false);
	return 0;
}

uint8_t _6502::CLI() {
	SetFlag(I, false);
	return 0;
}

uint8_t _6502::CLV() {
	SetFlag(V, false);
	return 0;
}

uint8_t _6502::ADC() {
	fetch();
	uint16_t temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);
	SetFlag(C, temp > 255);
	SetFlag(Z, (temp & LO_BYTE_MASK) == 0);
	SetFlag(N, temp & SIGBIT_MASK_8);
	SetFlag(V, (((uint16_t)a ^ temp) & ~((uint16_t)a ^ (uint16_t)fetched)) & ZERO_16);
	a = temp & LO_BYTE_MASK;
}

uint8_t _6502::SBC() {
	fetch();

	uint16_t inverted = ((uint16_t)fetched) ^ LO_BYTE_MASK;
	uint16_t temp = (uint16_t)a + inverted + (uint16_t)GetFlag(C);
	SetFlag(C, temp & HI_BYTE_MASK);
	SetFlag(Z, (temp & LO_BYTE_MASK) == 0);
	SetFlag(N, temp & ZERO_16);
	SetFlag(V, (((uint16_t)a ^ temp) & (temp ^ inverted) & ZERO_16));
	a = temp & LO_BYTE_MASK;
}

uint8_t _6502::PHA() {
	stackPush(a);
	return 0;
}

uint8_t _6502::PLA() {
	a = stackPop();
	SetFlag(Z, a == ZERO_8);
	SetFlag(N, a & SIGBIT_MASK_8);
	return 0;
}

void _6502::reset() {
	a = 0;
	x = 0;
	y = 0;
	sp = STACK_RESET;
	status = ZERO_8 | U;

	addr_abs = RESET_ADDRESS;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	addr_abs = ZERO_16;
	addr_rel = ZERO_16;
	fetched = ZERO_8;

	cycles = 8;
}

void _6502::irq() {
	if (GetFlag(I) == 0) {
		stackPush((pc >> 8) & LO_BYTE_MASK);
		stackPush(pc & LO_BYTE_MASK);
	}
}