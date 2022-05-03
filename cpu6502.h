#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define LO_BYTE_MASK	0x00FF
#define HI_BYTE_MASK	0xFF00

#define SIGBIT_MASK_8	0x80
#define SIGBIT_MASK_16	0x0080

#define ZERO_8			0x00
#define ZERO_16			0x0000

#define STACK_BASE		0x0100
#define STACK_RESET		0xFD;
#define RESET_ADDRESS	0xFFFC

typedef uint8_t		reg8;
typedef uint16_t	reg16;

class bus;

class _6502
{
public:
	_6502();
	~_6502();

public:
	enum FLAG6502
	{
		C = (1 << 0),
		Z = (1 << 1),
		I = (1 << 2),
		D = (1 << 3),
		B = (1 << 4),
		U = (1 << 5),
		V = (1 << 6),
		N = (1 << 7),
	};

	void ConnectBus(bus* bus) { this->bus = bus; }

	// Addressing modes
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZPG();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

	// Opcodes
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX();

	void clock();
	void reset();
	void irq();
	void nmi();

	uint8_t fetch();
	uint8_t fetched = 0x00;

	uint16_t addr_abs = 0x0000;
	uint16_t addr_rel = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t cycles = 0;

	reg8 a, x, y = 0x00;
	reg8 sp = 0x00;
	reg16 pc = 0x0000;
	reg8 status = 0x00;

private:
	bus* bus = nullptr;
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);

	void stackPush(uint8_t data);
	uint8_t stackPop();

	uint8_t GetFlag(FLAG6502 f);
	void	SetFlag(FLAG6502 f, bool v);

	struct Inst
	{
		std::string name;
		uint8_t(_6502::* opcode)(void) = nullptr;
		uint8_t(_6502::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};

	std::vector<Inst> opLookup;
};