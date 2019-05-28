#pragma once
#include "Register.h"
#include "Memory.h"
#include "Enum_decl.h"
#include "CPU.h"

namespace virtual_machine {
	class I_command
	{
		virtual void execute() = 0;
	};

	class ASSIGN : public I_command
	{
	public:
		virtual void execute()
		{

			if (Memory::find_data(m_value)) {
				// set_addres_reg
				CPU::set_addres_reg(m_reg_name, addres_register(Memory::find_data(m_value)));
				//add_regs_map[m_reg_name] = addres_register(Memory::find_data(m_value));
			}
			else if (Memory::find_code(m_value)) {
				// set_addres_reg
				CPU::set_addres_reg(m_reg_name, addres_register(Memory::find_data(m_value)));
				//add_regs_map[m_reg_name] = addres_register(Memory::find_code(m_value));
			}
			else {
				// set_general_reg
				CPU::set_general_reg(m_reg_name, gen_register(m_reg_name, std::stoi(m_value)));
				//gen_regs_map[m_reg_name] = gen_register(m_reg_name, std::stoi(m_value));
			}
		}

		ASSIGN(std::string reg_name, std::string value, Extantion ex = Extantion::DW)
			: m_reg_name(reg_name)
			, m_value(value)
			, m_ex(ex)
		{

		}
	private:
		Extantion m_ex;
		std::string m_value;
		std::string m_reg_name;
	};

	class RET : public I_command
	{
	public:
		virtual void execute()
		{

		}
	};

	class PUSHSF : public I_command
	{
	public:
		virtual void execute()
		{

		}
	};
}

