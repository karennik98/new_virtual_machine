#pragma once
#include "Common.h"
#include "Commands.h"

#include <vector>
#include <string>
#include <fstream>

namespace virtual_machine {

	class Compiler
	{
	public:
		//................................... general methods ...............................//
		void parse();
		bool open(std::string file);
		void delete_comment(std::string& line);
		std::string delete_space(std::string line); // for add_data_node
		void delete_space_ref(std::string& line);
		void delete_garbage(std::string& line);
		bool is_comment(std::string line)const;
		std::string get_segment(std::string line);
		bool is_delim(char ch)const;
		bool is_segment(std::string line);
		//................................... data parsing methods ...............................//
		void add_data_node(std::string line);
		var_type get_variable_type(std::string type)const;
		size_t get_array_size(std::string line)const;
		std::vector<int> get_array_from_init_list(std::string line)const;
		//................................... functions parsing methods ...............................//

		bool is_start_function(std::string line);
		bool is_end_function(std::string line);
		bool is_func_decl(std::string line);
		void add_func_node(std::vector<std::unique_ptr<I_command>> commands);
		std::unique_ptr<I_command> add_cmd_node(std::string line);

		//................................... debug ...............................//
		void show_data();
	private:
		std::ifstream m_stream;

		// ....... output data ........ //
		std::vector<std::shared_ptr<I_data>> m_data;
		std::vector<std::unique_ptr<I_function>> m_code;
	};

}
