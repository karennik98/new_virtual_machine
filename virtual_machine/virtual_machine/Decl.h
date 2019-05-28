#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <regex>

namespace virtual_machine {

	std::unordered_set<std::string> segments({ "STACK", "DATA", "CODE", "MAIN" });

	std::unordered_map<std::string, var_type> var_types
	{
		{"CHAR",  CHAR},
		{"BYTE",  BYTE},
		{"WORD",  WORD},
		{"DWORD", DWORD},
		{"QWORD", QWORD},
	};

	using u_char = unsigned char;

}