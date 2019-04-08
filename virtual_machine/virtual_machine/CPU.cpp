#include "pch.h"
#include "CPU.h"

namespace virtual_machine {

	CPU::CPU()
	{
	}

	void CPU::execute() {
		m_interpreter.open();
	}

	CPU::~CPU()
	{
	}
}