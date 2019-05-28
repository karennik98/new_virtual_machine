#pragma once

#include <regex>

namespace virtual_machine {

// ............................ for data parsing ......................... //

	// supports forward declaration
	// CHAR var; 
	// BYTE _var2;
	// WORD _var2var_;
	std::regex var_forward_decl{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*);"
	};

	// support variable defin. with init statement
	// CHAR var = 'A'; 
	// BYTE _var2 = 342; 
	// WORD _var2var_=234;
	std::regex var_defin_init{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"([ \t]*=[ \t]*)"
		"('.'|\\d*);"
	};

	// support array decl.
	// CHAR arr1[20]; || BYTE arr2_[];
	std::regex array_decl{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\d*\\]|\\[\\]);"
	};

	// support string array decl. & init.
	//CHAR str1[] = "Hello World!";
	std::regex string_array_decl_init{
		"(CHAR)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\])"
		"([ \t]*=[ \t]*)"
		"(\".*\");"
	};

	// support array decl. & init.
	//DWORD adwVal7[5] = {10,20,30,-40,};
	std::regex array_decl_init{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\d*\\]|\\[\\])"
		"([ \t]*=[ \t]*)"
		"(\\{(-?\\d*,[ \t]*)*\\};)"
	};

// ............................ for code parsing ......................... //

	//RET, PUSHSF, POPSF
	std::regex null_arg_cmd{
		"(RET|PUSHSF|POPSF)[ \t]*"
	};

	//CALL A5
	//Label1: POPSF
	std::regex one_arg_cmd{
		"(CALL|Label[0-9]*:|PUSH|POP|JUMP)"
		"([ \t]*|[ \t]*[B|W|D|Q][ \t]*)" //TODO for DW&QW
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]*)"
	};

	//ASSIGN DW A5, str1
	//ADD R1, R2
	std::regex two_arg_cmd{
		"(ASSIGN|ADD|SUB|MUL|DIV|CMP|AND|MOV|OR|SWAP|XOR|NAND)" // add new cmd-s
		"([ \t]*|[ \t]*[B|W|D|Q][ \t]*)" //TODO for DW&QW
		"([ \t]*[A|R][0-9]*,)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]*)"
	};
}