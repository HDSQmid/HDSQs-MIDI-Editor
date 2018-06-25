#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"
#include "multiLingual.h"

#define NUM_HANDLERS 10
ConsoleQuit quit;
ConsoleHelp help;
ConsoleFileNew newFile;
ConsoleFileOpen openFile;
ConsoleFileClose closeFile;
ConsoleFileSave saveFile;
ConsoleFileSaveAs saveFileAs;
ConsoleFileMakeEdit makeEdit;
ConsoleCrash crash;
ConsoleInfo info;

consoleInputHandler* input_handlers[NUM_HANDLERS] = { &help, &quit, &openFile, &newFile, &closeFile, &saveFile, &saveFileAs, &crash, &info, &makeEdit };

void handleConsoleInput(std::string input)
{

	std::string test;
	std::istringstream iss{ input };
	iss >> test;

	std::ostringstream oss;
	oss << iss.rdbuf();

	std::string args = oss.str();
	if(args != "") args = args.substr(1);

	//reverse translate std::string test

	//remove command from rest of arguments for easier processing

	bool foundCall = false; // bool for whether a handler was found
	for (int i = 0; i < NUM_HANDLERS; i++) {
		if (input_handlers[i]->getIdentifier() == test) {
			input_handlers[i]->call(args);
			foundCall = 1;
			break;
		}
	}

	if (!foundCall) sendMessage(MESSAGE_NO_MATCHING_COMMAND, "", MESSAGE_TYPE_ERROR);

}

/***************************************/


consoleInputHandler::consoleInputHandler()
{
	identifier = CONSOLE_INPUT_HANDLER_DEFAULT_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_DEFAULT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_DEFAULT_ARGUMENTS;
}

void consoleInputHandler::call(std::string args)
{

	std::cout << "Test" << std::endl;

}

std::string consoleInputHandler::getIdentifier()
{
	return translate(identifier);
}

std::string consoleInputHandler::getDescription()
{
	return translate(description);
}

std::string consoleInputHandler::getArguments()
{
	return translate(arguments);
}

std::string consoleInputHandler::getExampleUsage()
{
	return translate(exampleUsage);
}

/***************************************/

ConsoleFileOpen::ConsoleFileOpen()
{
	identifier = CONSOLE_INPUT_HANDLER_FILE_OPEN_IDENTIFIER; 
	description = CONSOLE_INPUT_HANDLER_FILE_OPEN_DESCRIPTION; 
	arguments = CONSOLE_INPUT_HANDLER_FILE_OPEN_ARGUMENTS; 
	exampleUsage = CONSOLE_INPUT_HANDLER_DEFAULT_EXAMPLE_USAGE;
}

void ConsoleFileOpen::call(std::string args)
{
	if (args == "") {

		sendMessage(MESSAGE_NOT_VALID_FILENAME, "", MESSAGE_TYPE_ERROR);
		return;

	}
	
	fileOpen(args);

	return;
}

ConsoleFileClose::ConsoleFileClose()
{
	identifier = CONSOLE_INPUT_HANDLER_FILE_CLOSE_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_FILE_CLOSE_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_FILE_CLOSE_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_CLOSE_EXAMPLE_USAGE;
}

void ConsoleFileClose::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage(MESSAGE_NO_FILE_OPEN, "",MESSAGE_TYPE_ERROR);
		return;

	}
	
	fileClose();
}

ConsoleFileSave::ConsoleFileSave()
{
	identifier = CONSOLE_INPUT_HANDLER_FILE_SAVE_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_FILE_SAVE_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_FILE_SAVE_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_SAVE_EXAMPLE_USAGE;
}

void ConsoleFileSave::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage(MESSAGE_NO_FILE_OPEN, "", MESSAGE_TYPE_ERROR);
		return;

	}

	if (args != "") currentFile->saveAs(args);

	else currentFile->save();
}

ConsoleFileSaveAs::ConsoleFileSaveAs()
{
	identifier = CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_EXAMPLE_USAGE;
}

void ConsoleFileSaveAs::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage(MESSAGE_NO_FILE_OPEN, "",MESSAGE_TYPE_ERROR);
		return;

	}

	if (args == "") { // if no file name provided

		sendMessage(MESSAGE_NOT_VALID_FILENAME, "", MESSAGE_TYPE_ERROR);
		return;

	}

	currentFile->saveAs(args);
}

ConsoleQuit::ConsoleQuit()
{
	identifier = CONSOLE_INPUT_HANDLER_QUIT_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_QUIT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_QUIT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_QUIT_EXAMPLE_USAGE;
}

void ConsoleQuit::call(std::string args)
{
	if( fileIsOpen()) fileClose();
	exit(0);
}

ConsoleHelp::ConsoleHelp()
{
	identifier = CONSOLE_INPUT_HANDLER_HELP_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_HELP_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_HELP_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_HELP_EXAMPLE_USAGE;
}

void ConsoleHelp::call(std::string args)
{
	//set colour to green
	HANDLE hConsole;
	int colour = 2;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);

	//if no argument
	if (args == "") {
		

		std::cout << "Help:" << std::endl;
		for (int i = 0; i < NUM_HANDLERS; i++) {			
			std::cout << input_handlers[i]->getIdentifier() << ": "
				<< input_handlers[i]->getDescription() << std::endl;
		}
	}
	//if argument provided
	else {

		bool foundCall = false; // bool for whether a handler was found
		for (int i = 0; i < NUM_HANDLERS; i++) {
			if (input_handlers[i]->getIdentifier() == args) {
				std::cout << "help for " << input_handlers[i]->getIdentifier() << "\n" 
					<< input_handlers[i]->getDescription() << "\n" 
					<< input_handlers[i]->getArguments() << std::endl;
				foundCall = 1;
				break;
			}			
		}
		if (!foundCall) sendMessage(MESSAGE_NO_MATCHING_COMMAND, "", MESSAGE_TYPE_ERROR);
	}

	SetConsoleTextAttribute(hConsole, 15);

}

ConsoleCrash::ConsoleCrash()
{
	identifier = CONSOLE_INPUT_HANDLER_CRASH_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_CRASH_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_CRASH_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_CRASH_EXAMPLE_USAGE;
}

void ConsoleCrash::call(std::string args)
{
	throw new std::exception("ForceQuit");
}

ConsoleInfo::ConsoleInfo()
{
	identifier = CONSOLE_INPUT_HANDLER_INFO_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_INFO_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_INFO_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_INFO_EXAMPLE_USAGE;
}


void ConsoleInfo::call(std::string args)
{
	sendGreeting();
}

ConsoleFileNew::ConsoleFileNew()
{
	identifier = CONSOLE_INPUT_HANDLER_FILE_NEW_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_FILE_NEW_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_FILE_NEW_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_NEW_EXAMPLE_USAGE;
}

void ConsoleFileNew::call(std::string args)
{
	fileNew();
}

ConsoleFileMakeEdit::ConsoleFileMakeEdit()
{
	identifier = CONSOLE_INPUT_HANDLER_MAKE_EDIT_IDENTIFIER;
	description = CONSOLE_INPUT_HANDLER_MAKE_EDIT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MAKE_EDIT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MAKE_EDIT_EXAMPLE_USAGE;
}

void ConsoleFileMakeEdit::call(std::string args)
{
	currentFile->makeEdit();
}
