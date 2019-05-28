#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Decl.h"
#include "Common.h"

namespace virtual_machine {

	struct Memory {
		static std::vector<std::unique_ptr<I_data>> m_data_segment;
		static std::vector<std::unique_ptr<I_function>> m_code_segment;

		static std::unique_ptr<I_data> find_data(std::string name)
		{
			for (const auto& it : m_data_segment)
			{
				if (it->get_name() == name)
				{
					return std::unique_ptr<I_data>(it.get());
				}
			}
			return nullptr;
		}

		static std::unique_ptr<I_function> find_code(std::string name)
		{
			for (const auto& it : m_code_segment)
			{
				if (it->get_name() == name)
				{
					return std::unique_ptr<I_function>(it.get());
				}
			}
			return nullptr;
		}
	};
}

