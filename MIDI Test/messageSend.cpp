#include "stdafx.h"
#include "messageSend.h"

std::string chooseYN() {

	std::cout << "type (y)es or (n)o" << std::endl;
	while (true) {

		char ch = getchar();

		

		if (ch == 'y' || ch == 'Y') return "y";		

		if (ch == 'n' || ch == 'N') return "n";

		//continue until good input given

		std::cout << "bad input" << std::endl;

	}

}

std::string sendMessage(std::string message, int title, int response)
{
#ifdef CONSOLE

	// print message

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
	case MESSAGE_QUESTION:
			colour = 5; // purple
			titleS = "Question";
			break;
	default: 
			colour = 4; // red
			SetConsoleTextAttribute(hConsole, colour);
			std::cout << "System Error: Unknown message title" << std::endl;
			SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning
			return  "Error";

	} 

	SetConsoleTextAttribute(hConsole, colour);
	std::cout << titleS << ": \t\t" << message << std::endl;
	SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning

	std::string ret = "";

	// get response
	switch (response) {

	case RESPONSE_OK:
		return "Ok";

	case RESPONSE_YN:
		return chooseYN();

	case RESPONSE_STRING:
		std::getline(std::cin, ret);
		return ret;
		
	default:
		colour = 4; // red
		SetConsoleTextAttribute(hConsole, colour);
		std::cout << "System Error: Unknown response type" << std::endl;
		SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning
		return "Error";
	}

#endif //  CONSOLE


}

void sendGreeting()
{
	std::cout << APP_NAME << " Version " << APP_VERSION << std::endl;
	std::cout << "Type \"help\" for help\n\n" << std::endl;
}
