#pragma once
namespace virtual_machine {

	template<typename data_value>
	class Register
	{
	public:
		Register();
		~Register();
	private:
		data_value data;
	};

}