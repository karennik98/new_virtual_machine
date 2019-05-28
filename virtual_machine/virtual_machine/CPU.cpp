#include "pch.h"
#include "CPU.h"

namespace virtual_machine {

	CPU::CPU()
	{

	}
	void CPU::set_IP(size_t ip)
	{

	}
	size_t CPU::get_IP()const
	{

	}
	void CPU::execute()
	{

	}
	void CPU::set_addres_reg(std::string name, addres_register reg)
	{
		//add_regs_map.insert({ name,reg });//TODO
	}
	void CPU::set_general_reg(std::string name, gen_register reg)
	{
		gen_regs_map.insert({ name,reg });
	}
}