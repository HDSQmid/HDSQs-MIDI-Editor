#include "stdafx.h"
#include "messageSend.h"
#include "multiLingual.h"
#include "files.h"

bool echo = true;

std::string chooseYN() {

	std::cout << "type (y)es or (n)o" << std::endl;
	while (true) {

		char ch = getwchar();

		

		if (ch == 'y' || ch == 'Y') return "y";		

		if (ch == 'n' || ch == 'N') return "n";

		//continue until good input given

		std::cout << "bad input" << std::endl;

	}

}

std::string sendMessage(int message, std::string args, int title, int response)
{
#ifdef CONSOLE

	if (!echo) return std::string("Echo is off");

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
		colour = 4; // red
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
		std::cin.ignore(INT_MAX, '\n');
		std::cin.clear();
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

void printLogo()
{

	std::cout <<
		" 1         1   1111111111    11111111111   11111111111 \n" <<
		"101       101 100000000001  1000000000001 1000000000001\n" <<
		"101       101 1011111111101 101111111111  1011111111101\n" <<
		"101       101 101       101 101           101       101\n" <<
		"1011111111101 101       101 101111111111  101       101\n" <<
		"1000000000001 101       101 1000000000001 101       101\n" <<
		"1011111111101 101       101  111111111101 1011111111101\n" <<
		"101       101 101       101           101 1000000000001\n" <<
		"101       101 1011111111101  111111111101  1111111011  \n" <<
		"101       101 100000000001  1000000000001         101  \n" <<
		"1         1   1111111111    11111111111           1    \n" << std::endl;
		

}

void sendGreeting()
{
	std::cout << APP_NAME << " " << translate(STRING_VERSION) << " " << APP_VERSION << std::endl;
	std::cout << translate(STRING_GREETING_HELP) << std::endl;
}

void printAppInfo()
{
	std::cout << "\n\n";
	printLogo();
	std::cout << APP_NAME << " " << translate(STRING_VERSION) << " " << APP_VERSION << std::endl;
	std::cout << translate(STRING_BUILD_DATE) << " " << __DATE__ << " " << translate(STRING_AT) << " " << __TIME__ << std::endl;
}

void setOutputEcho(bool b)
{
	echo = b;
}

void updateWindowTitle()
{
	std::string t;

	if (currentFile) t = APP_NAME + (std::string) " - " + currentFile->midi.getName();
	else t = APP_NAME + (std::string) " - V" + APP_VERSION;


	SetConsoleTitleA(t.c_str());
}
