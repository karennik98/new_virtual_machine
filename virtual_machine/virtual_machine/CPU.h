#pragma once
#include "Decl.h"
#include "Interpreter.h"
#include "Register.h"

#include <vector>
#include <map>
#include <string>

namespace virtual_machine {

	class CPU
	{
	public:
		CPU();
		void set_IP(size_t ip);
		size_t get_IP()const;
		void execute();
		static void set_addres_reg(std::string name, addres_register reg);
		static void set_general_reg(std::string name, gen_register reg);
	private:
		static std::map<std::string, gen_register> gen_regs_map;
		static std::map<std::string, addres_register> add_regs_map;
		size_t m_IP;
	};
}