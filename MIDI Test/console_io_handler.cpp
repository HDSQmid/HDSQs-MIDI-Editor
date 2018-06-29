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
ConsoleMidiMakeEdit makeEdit;
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

//implement multi-layered console input handler


consoleInputHandler::consoleInputHandler()
{
	identifier = "NULL";
	description = CONSOLE_INPUT_HANDLER_DEFAULT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_DEFAULT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_DEFAULT_EXAMPLE_USAGE;
}

void consoleInputHandler::call(std::string args)
{

	std::cout << "Test" << std::endl;

}

std::string consoleInputHandler::getIdentifier()
{
	return identifier;
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

// files

ConsoleFileOpen::ConsoleFileOpen()
{
	identifier = "open"; 
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
	identifier = "close";
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
	identifier = "save";
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
	identifier = "saveAs";
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

ConsoleFileNew::ConsoleFileNew()
{
	identifier = "new";
	description = CONSOLE_INPUT_HANDLER_FILE_NEW_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_FILE_NEW_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_NEW_EXAMPLE_USAGE;
}

void ConsoleFileNew::call(std::string args)
{
	fileNew();
}

// program functions

ConsoleQuit::ConsoleQuit()
{
	identifier = "quit";
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
	identifier = "help";
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
	identifier = "crash";
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
	identifier = "info";
	description = CONSOLE_INPUT_HANDLER_INFO_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_INFO_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_INFO_EXAMPLE_USAGE;
}


void ConsoleInfo::call(std::string args)
{
	sendGreeting();
}

// midi functions

ConsoleMidiMakeEdit::ConsoleMidiMakeEdit()
{
	identifier = "makeEdit";
	description = CONSOLE_INPUT_HANDLER_MAKE_EDIT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MAKE_EDIT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MAKE_EDIT_EXAMPLE_USAGE;
}

void ConsoleMidiMakeEdit::call(std::string args)
{
	currentFile->makeEdit();
}

ConsoleMidiPattern::ConsoleMidiPattern()
{
	identifier = "pattern";
	description = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_EXAMPLE_USAGE;
}

void ConsoleMidiPattern::call(std::string args)
{
	// determine request type

	// based on request type perform different actions, parse remaining arguments

}

ConsoleMidiTrack::ConsoleMidiTrack()
{
	identifier = "track";
	description = CONSOLE_INPUT_HANDLER_MIDI_TRACK_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MIDI_TRACK_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MIDI_TRACK_EXAMPLE_USAGE;
}

void ConsoleMidiTrack::call(std::string args)
{
	// determine request type

	// based on request type, perform action
}

ConsoleMidiSelect::ConsoleMidiSelect()
{
	identifier = "select";
	description = CONSOLE_INPUT_HANDLER_MIDI_SELECT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MIDI_SELECT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MIDI_SELECT_EXAMPLE_USAGE;
}

void ConsoleMidiSelect::call(std::string args)
{
	// use arguments to determine what to select, then select it
}

ConsoleMidiSelection::ConsoleMidiSelection()
{
	identifier = "selection";
	description = CONSOLE_INPUT_HANDLER_MIDI_SELECTION_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MIDI_SELECTION_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MIDI_SELECTION_EXAMPLE_USAGE;
}

void ConsoleMidiSelection::call(std::string args)
{
	// determine action to perform based on arguments
}
