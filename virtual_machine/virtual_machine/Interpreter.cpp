#include "pch.h"
#include "Interpreter.h"
#include "Exception.h"

namespace virtual_machine {

	Interpreter::Interpreter()
	{
	}

	bool Interpreter::open(std::string file_name) 
	{
		m_stream.open(file_name);
		if (m_stream.is_open())
		{
			throw wrong_file_path("Interpreter.cpp", "open(std::string)", 16);
		}
		return true;
	}

	void Interpreter::set_data() 
	{
		std::string tmpStr;
		size_t idx = 0;
		while (std::getline(m_stream, tmpStr)) 
		{
			m_data[idx] = tmpStr;
			tmpStr.clear();
		}
	}

	void Interpreter::parse()
	{

	}

	Interpreter::~Interpreter()
	{
	}
}