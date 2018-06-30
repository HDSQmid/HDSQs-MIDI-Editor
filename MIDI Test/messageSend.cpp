#include "stdafx.h"
#include "messageSend.h"
#include "multiLingual.h"

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

std::string sendMessage(int message, std::string args, int title, int response)
{
#ifdef CONSOLE

	// print message

	HANDLE hConsole;
	int colour;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string titleS;

	// replace this with get translation function
	switch (title) {
	case MESSAGE_TYPE_ERROR:
			colour = 6; // orange
			titleS = translate(MESSAGE_TYPE_ERROR);
			break; 
	case MESSAGE_TYPE_MESSAGE: 
			colour = 1; // blue
			titleS = translate(MESSAGE_TYPE_MESSAGE);
			break; 
	case MESSAGE_TYPE_HELP:
			colour = 2; // green
			titleS = translate(MESSAGE_TYPE_HELP);
			break;
	case MESSAGE_TYPE_TIP:
			colour = 2; // green
			titleS = translate(MESSAGE_TYPE_TIP);
			break; 
	case MESSAGE_TYPE_QUESTION:
			colour = 5; // purple
			titleS = translate(MESSAGE_TYPE_QUESTION);
			break;
	case MESSAGE_TYPE_CRITICAL_ERROR:
		colour = 4; // orange
		titleS = translate(MESSAGE_TYPE_CRITICAL_ERROR);
		break;
	default: 
			colour = 15;
			SetConsoleTextAttribute(hConsole, colour);
			titleS = translate(MESSAGE_TYPE_UNKNOWN);
			SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning

	} 

	SetConsoleTextAttribute(hConsole, colour);
	std::cout << titleS << ": \t\t" << translate(message) << " " << args << std::endl;
	SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning

	std::string ret = "";

	// get response
	switch (response) {

	case MESSAGE_RESPONSE_OK:
		ret = "Ok";
		break;
	case MESSAGE_RESPONSE_YN:
		ret = chooseYN();
		break;
	case MESSAGE_RESPONSE_STRING:
		std::getline(std::cin, ret);
		break;
		
	default:
		colour = 4; // red
		SetConsoleTextAttribute(hConsole, colour);
		std::cout << translate(MESSAGE_RESPONSE_UNKNOWN) << std::endl;
		SetConsoleTextAttribute(hConsole, 15); // return text colour to normal before returning
		ret = "Error";
	}

	return ret;

#endif //  CONSOLE


}

void sendGreeting()
{
	std::cout << APP_NAME << " " << translate(STRING_VERSION) << " " << APP_VERSION << std::endl;
	std::cout << translate(STRING_GREETING_HELP) << std::endl;
}

void printAppInfo()
{
	std::cout << APP_NAME << " " << translate(STRING_VERSION) << " " << APP_VERSION << std::endl;
	std::cout << translate(STRING_BUILD_DATE) << " " << __DATE__ << " " << translate(STRING_AT) << " " << __TIME__ << std::endl;
}
