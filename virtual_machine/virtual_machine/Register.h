#pragma once
#include "Common.h"

#include <memory>
#include <string>
#include <map>



namespace virtual_machine {

	struct I_register {
		virtual ~I_register() = 0;
	};
	I_register::~I_register() {}

	struct addres_register : public I_register {
		addres_register(std::unique_ptr<I_node> ptr)
			: addres_(ptr.get())
		{

		}
		std::unique_ptr<I_node> addres_;
	};
	

	struct gen_register : public I_register {
		gen_register(std::string name, int64_t value)
			: name_(name)
			, value_(value)
		{
		}
		std::string name_;
		int64_t value_;
	};
	
	struct status_regs {
		bool ZF : 1;
		bool OF : 1;
		bool SF : 1;
		bool CF : 1;
	};
}