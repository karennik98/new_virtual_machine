#pragma once
#include "Decl.h"
#include "Interpreter.h"

#include <vector>

namespace virtual_machine {

	class CPU
	{
	public:
		CPU();
		void set_IP(size_t ip);
		size_t get_IP()const;
		void execute();
		~CPU();
	private:
		std::vector<u_char> m_genRegisters;
		size_t              m_IP;
		status_regs         m_statusRegisters;
		Interpreter         m_interpreter;
	};
}
