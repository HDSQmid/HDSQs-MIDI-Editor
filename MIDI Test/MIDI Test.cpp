// MIDI Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"

int main()
{
	sendGreeting();

	while (true) {
		std::string in;
		std::getline(std::cin, in);

		handleConsoleInput(in);
	}
	
    return 0;
}

