#pragma once

#include "Enum_decl.h"
#include "Commands.h"

#include <iostream>
#include <string>
#include <vector>

namespace virtual_machine {
	// ............................................. data parsing node ...............................//
	struct I_node
	{
		virtual ~I_node() = 0;
	};
	I_node::~I_node() {}

	struct I_data :public I_node {
		virtual ~I_data() = 0;
		virtual void get() = 0;
		virtual std::string get_name() = 0;
	};
	I_data::~I_data() {}

	struct v_forward_decl :public I_data
	{
		v_forward_decl(var_type type, std::string name)
			: type_(type), name_(name)
		{
		}

		void get()
		{
			std::cout << "v_forward_decl" << std::endl;
			std::cout << "Type -> " << type_ << std::endl;
			std::cout << "Name -> " << name_ << std::endl;
		}

		std::string get_name() { return name_; }

		var_type type_;
		std::string name_;
	};

	struct v_defin_init : public I_data
	{
		v_defin_init(var_type type, std::string name, std::string value)
			: type_(type)
			, name_(name)
			, value_(value)
		{
		}

		void get()
		{
			std::cout << "v_defin_init" << std::endl;
			std::cout << "Type -> " << type_ << std::endl;
			std::cout << "Name -> " << name_ << std::endl;
			std::cout << "Value -> " << value_ << std::endl;
		}

		std::string get_name() { return name_; }

		var_type type_;
		std::string name_;
		std::string value_;
	};

	struct arr_decl : public I_data
	{
		arr_decl(var_type type, std::string name, size_t size)
			: type_(type)
			, name_(name)
			, size_(size)
		{
		}

		void get()
		{
			std::cout << "arr_decl" << std::endl;
			std::cout << "Type -> " << type_ << std::endl;
			std::cout << "Name -> " << name_ << std::endl;
			std::cout << "Size -> " << size_ << std::endl;
		}

		std::string get_name() { return name_; }

		var_type type_;
		std::string name_;
		size_t size_;
	};

	struct str_arr_decl_init : public I_data
	{
		str_arr_decl_init(std::string name, std::string value, var_type type = CHAR)
			: type_(type)
			, name_(name)
			, value_(value)
		{
		}

		void get()
		{
			std::cout << "str_arr_decl_init" << std::endl;
			std::cout << "Type -> " << type_ << std::endl;
			std::cout << "Name -> " << name_ << std::endl;
			std::cout << "Value -> " << value_ << std::endl;
		}

		std::string get_name() { return name_; }

		var_type type_;
		std::string name_;
		std::string value_;
	};

	struct arr_decl_init : public I_data
	{
		arr_decl_init(var_type type, std::string name, size_t size, std::vector<int> value)
			: type_(type)
			, name_(name)
			, size_(size)
			, value_(value)
		{
		}

		void get()
		{
			std::cout << "arr_decl_init" << std::endl;
			std::cout << "Type -> " << type_ << std::endl;
			std::cout << "Name -> " << name_ << std::endl;
			std::cout << "Size -> " << size_ << std::endl;
			std::cout << '{ ';
			for (const auto& it : value_)
			{
				std::cout << it << ', ';
			}
			std::cout << ' }' << std::endl;
		}

		std::string get_name() { return name_; }

		var_type type_;
		std::string name_;
		size_t size_;
		std::vector<int> value_;
	};

	// ............................................. function parsing node ...............................//
	struct I_function :public I_node
	{
		virtual ~I_function() = 0;
		virtual std::string get_name() = 0;
	};
	I_function::~I_function()
	{
	}

	struct function_node :public I_function
	{
		std::string get_name() { return name_; }

		std::string name_;
		std::vector<std::unique_ptr<I_command>> commands_;

	};
	struct function_decl_node : public I_function
	{
		std::string get_name() { return name_; }

		std::string name_;
	};
}