#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	const char* what() const throw() = 0;
	Exception(std::string file, std::string func, unsigned line) : m_file(file), m_func(func), m_line(line)
	{
	}
	//virtual void info() = 0; //TO DO
protected:
	std::string m_file;
	unsigned m_line;
	std::string m_func;
};

class wrong_func :public Exception {
public:
	wrong_func(std::string file, std::string func, unsigned line) : Exception(file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("Wrong function call : File: " + m_file = "\nFunction: " + m_func + "\nLine: " + std::to_string(m_line)).c_str();
	}
};

class bad_type :public Exception {
public:
	bad_type(std::string file, std::string func, unsigned line) : Exception(file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("Wrong data type : File: " + m_file = "\nFunction: " + m_func + "\nLine: " + std::to_string(m_line)).c_str();
	}
};

class wrong_file_path :public Exception {
public:
	wrong_file_path(std::string file, std::string func, unsigned line) : Exception(file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("Wrong function path : File: " + m_file = "\nFunction: " + m_func + "\nLine: " + std::to_string(m_line)).c_str();
	}
};

class incomplete_expression :public Exception {
public:
	incomplete_expression(std::string file, std::string func, unsigned line) : Exception(file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("incomplete_expression : File: " + m_file = "\nFunction: " + m_func + "\nLine: " + std::to_string(m_line)).c_str();
	}
};

class invalid_data_type :public Exception {
public:
	invalid_data_type(std::string file, std::string func, unsigned line) : Exception(file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("invalid data type or wrong line : File: " + m_file = "\nFunction: " + m_func + "\nLine: " + std::to_string(m_line)).c_str();
	}
};

#endif