#pragma once

#include <fstream>
#include <vector>

namespace virtual_machine {
	class Interpreter
	{
	public:
		Interpreter();
		bool open(std::string file_name);
		void parse();
		void set_data();

		~Interpreter();
	private:
		std::ifstream m_stream;
		std::vector<std::string> m_data;
		std::string   m_source;
	};
}
