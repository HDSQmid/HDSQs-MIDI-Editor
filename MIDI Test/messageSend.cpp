#include "stdafx.h"
#include "messageSend.h"


void sendMessage(std::string message, int title)
{
#ifdef CONSOLE
	HANDLE hConsole;
	int colour;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string titleS;

	switch (title) {
	case MESSAGE_ERROR:
			colour = 6; // orange
			titleS = "Error";
			break; 
	case MESSAGE_MESSAGE: 
			colour = 1; // blue
			titleS = "Message";
			break; 
	case MESSAGE_HELP:
			colour = 2; // green
			titleS = "Help";
			break;
	case MESSAGE_TIP:
			colour = 2; // green
			titleS = "Tip";
			break; 
	default: 
			colour = 4; // red
			SetConsoleTextAttribute(hConsole, colour);
			std::cout << "System Error: Unknown message title" << std::endl;
			SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning
			return;

	} 

	SetConsoleTextAttribute(hConsole, colour);
	std::cout << titleS << ": \t\t" << message << std::endl;
	SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning
#endif // 


}

void sendGreeting()
{
	std::cout << APP_NAME << " Version " << APP_VERSION << std::endl;
	std::cout << "Type \"help\" for help\n\n" << std::endl;
}
