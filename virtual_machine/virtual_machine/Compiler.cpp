#include "pch.h"
#include "Compiler.h"
#include "Decl.h"
#include "Exception.h"
#include "Regex.h"

#include <iostream>
#include <regex>
#include <vector>
#include <string>


namespace virtual_machine {
	
//.......................................................... general methods  .......................................................//
	void Compiler::show_data()
	{
		for (auto& it : m_data)
		{
			it->get();
			std::cout << std::endl;
		}
	}

	bool Compiler::open(std::string file)
	{
		m_stream.open(file.c_str(), std::ios::in);
		return m_stream.is_open();
	}

	bool Compiler::is_delim(char ch)const
	{
		return (ch == ' ' || ch == '\t');
	}

	bool Compiler::is_comment(std::string line)const
	{
		for (const auto& it : line)
		{
			if (it == '#') {
				return true;
			}

			else if (it == ' ') {
				continue;
			}

			else {
				return false;
			}
		}
	}

	bool Compiler::is_segment(std::string line)
	{
		delete_garbage(line);
		delete_comment(line);
		if (line[0] == '.')
		{
			line.erase(0, 1);
			return segments.find(line) != segments.end();
		}
		else
		{
			return false;
		}
	}

	std::string Compiler::get_segment(std::string line)
	{
		delete_garbage(line);
		if (line[0] == '.')
		{
			line.erase(0, 1);
			return segments.find(line) != segments.end() ? line : "NOT_SEGMENT";
		}

		return "NOT_SEGMENT";
	}

	size_t Compiler::get_array_size(std::string line)const
	{
		line.erase(line.find('['), 1);
		line.erase(line.find(']'), 1);
		return std::stoi(line);
	}

	var_type Compiler::get_variable_type(std::string type)const
	{
		switch (hash_function(type.c_str()))
		{
		case CHAR:
			return CHAR;
		case BYTE:
			return BYTE;
		case WORD:
			return WORD;
		case DWORD:
			return DWORD;
		case QWORD:
			return QWORD;
		default:
			return UNKNOWN_TYPE;
		}
	}

	std::vector<int> Compiler::get_array_from_init_list(std::string line)const
	{
		std::vector<int> arr;
		std::string tmp;
		for (auto it = line.begin(); it != line.end(); ++it)
		{
			while ((*it != '{' && *it != '}' && *it != ',' && *it != ' ' && *it != ';') && it != line.end())
			{
				tmp += *it++;
			}

			if (!tmp.empty()) {
				arr.push_back(std::stoi(tmp));
				tmp.clear();
			}
		}

		return arr;
	}

	void Compiler::delete_comment(std::string& line)
	{
		for (std::string::iterator it = line.begin(); it != line.end(); ++it)
		{
			if (*it == '#')
			{
				line.erase(it, line.end());
				return;
			}
		}
	}

	std::string Compiler::delete_space(std::string line)
	{
		std::string::iterator it = line.begin();
		while (it != line.end())
		{
			if (*it != ' ') {
				break;
			}
			line.erase(it);
		}
		return line;
	}

	void Compiler::delete_space_ref(std::string& line)
	{
		std::string::iterator it = line.begin();
		while (it != line.end())
		{
			if (*it != ' ') {
				return;
			}
			line.erase(it);
		}
	}

	void Compiler::delete_garbage(std::string& line)
	{
		delete_space_ref(line);
		delete_comment(line);
	}

	void Compiler::add_data_node(std::string line)
	{
		std::cmatch result;

		if (std::regex_match(line.c_str(), result, var_forward_decl))
		{
			std::cmatch::iterator it = ++result.begin();
			m_data.push_back(std::make_unique<v_forward_decl>(get_variable_type(*it++), delete_space(it->str())));
		}
		else if (std::regex_match(line.c_str(), result, var_defin_init))
		{
			std::cmatch::iterator it = ++result.begin();
			m_data.push_back(std::make_unique<v_defin_init>(get_variable_type(*it++), delete_space(it->str()), (it + 2)->str()));
		}
		else if (std::regex_match(line.c_str(), result, array_decl))
		{
			std::cmatch::iterator it = ++result.begin();
			m_data.push_back(std::make_unique<arr_decl>(get_variable_type(*it++), delete_space(it++->str()), get_array_size(it->str())));
		}
		else if (std::regex_match(line.c_str(), result, string_array_decl_init))
		{
			std::cmatch::iterator it = ++result.begin();
			m_data.push_back(std::make_unique<str_arr_decl_init>(delete_space((it + 1)->str()), (it + 4)->str()));
		}
		else if (std::regex_match(line.c_str(), result, array_decl_init))
		{
			std::cmatch::iterator it = ++result.begin();

			var_type var = get_variable_type(it++->str());
			std::string name = delete_space(it++->str());
			size_t size = get_array_size(it->str());
			std::vector<int> vec = get_array_from_init_list((it + 2)->str());

			m_data.push_back(std::make_unique<arr_decl_init>(var, name, size, vec));
		}
		else if (!line.empty())
		{
			throw invalid_data_type("Compiler.cpp", "add_data_node", 205);
		}
	}

//.......................................................... function parsing methods  .......................................................//

	bool Compiler::is_start_function(std::string line)
	{
		delete_garbage(line);

		std::regex func_start_r{
			"(Func)"
			"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]*)"
		};

		return std::regex_match(line.c_str(), func_start_r);
	}

	bool Compiler::is_end_function(std::string line)
	{
		delete_garbage(line);
		return (line == "EndF");
	}

	bool Compiler::is_func_decl(std::string line)
	{
		delete_garbage(line);

		std::regex func_decl_r{
			"(Func)"
			"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*;[ \t]*)"
		};

		return std::regex_match(line.c_str(), func_decl_r);
	}

	void Compiler::add_func_node(std::vector<std::unique_ptr<I_command>> commands)
	{
		//TODO
	}

	std::unique_ptr<I_command> Compiler::add_cmd_node(std::string line)
	{
		std::cmatch result;

		if (std::regex_match(line.c_str(), result, null_arg_cmd))
		{
			std::cmatch::iterator it = ++result.begin();
			return;//TODO
		}
		else if (std::regex_match(line.c_str(), result, one_arg_cmd))
		{
			std::cmatch::iterator it = ++result.begin();
			//TODO
		}
		else if (std::regex_match(line.c_str(), result, two_arg_cmd))
		{
			std::cmatch::iterator it = ++result.begin();
			//TODO
		}
		else
		{

		}
	}
// ............ parser ...........//
	void Compiler::parse()
	{
		std::string line;

		while (!m_stream.eof())
		{
			std::getline(m_stream, line);
			if (is_comment(line)) {
				std::getline(m_stream, line);
				continue;
			}

			if (is_segment(line) && "DATA" == get_segment(line))
			{
				std::getline(m_stream, line);
				while (!m_stream.eof() && !is_segment(line))
				{
					delete_garbage(line);
					add_data_node(line);
					std::getline(m_stream, line);
				}
			}

			if (is_segment(line) && "CODE" == get_segment(line))
			{
				std::getline(m_stream, line);
				if (is_start_function(line))
				{
					if (is_func_decl(line))
					{
						// TODO add_func_decl_node
						std::getline(m_stream, line);
						continue;
					}

					std::getline(m_stream, line);
					std::vector<std::unique_ptr<I_command>> func_commands;
					while (!m_stream.eof() && !is_end_function(line))
					{
						func_commands.push_back(add_cmd_node(line));
						std::getline(m_stream, line);
					}
					add_func_node(func_commands);
				}
			}
		}
	}
}