#include "pch.h"
#include "CPU.h"

#include <iostream>

int main()
{
	virtual_machine::CPU core;
	core.execute("Assembly.txt");
}
