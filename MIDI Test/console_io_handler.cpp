#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"
#include "multiLingual.h"
#include "settings.h"


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
ConsoleSettingsAddLanguage addLanguage;
ConsolePrintTranslation printTranslation;
ConsoleMidiPattern pattern;

ConsoleInputHandler* input_handlers[NUM_HANDLERS] =
{
	&help,
	&quit,
	&openFile,
	&newFile,
	&closeFile,
	&saveFile,
	&saveFileAs,
	&crash, &info,
	&makeEdit,
	&addLanguage,
	&printTranslation,
	&pattern
};


void handleConsoleInput(std::string input, ConsoleInputHandler ** handlerList, int numHandlers)
{

	std::string test;
	std::istringstream iss{ input };
	iss >> test;

	std::ostringstream oss;
	oss << iss.rdbuf();

	std::string args = oss.str();

	if (test == "") {
		sendMessage(MESSAGE_NO_COMMAND_PROVIDED, "", MESSAGE_TYPE_ERROR);
		return;
	}

	if(args != "") args = args.substr(1); // remove space from start of string

	//remove command from rest of arguments for easier processing

	bool foundCall = false; // bool for whether a handler was found
	for (int i = 0; i <numHandlers; i++) {
		if (handlerList[i]->getIdentifier() == test) {
			handlerList[i]->call(args);
			foundCall = 1;
			break;
		}
	}

	if (!foundCall) sendMessage(MESSAGE_NO_MATCHING_COMMAND, "", MESSAGE_TYPE_ERROR);

}

/***************************************/

//implement multi-layered console input handler


ConsoleInputHandler::ConsoleInputHandler()
{
	identifier = "NULL";
	description = CONSOLE_INPUT_HANDLER_DEFAULT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_DEFAULT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_DEFAULT_EXAMPLE_USAGE;
}

void ConsoleInputHandler::call(std::string args)
{

	std::cout << "Test" << std::endl;

}

std::string ConsoleInputHandler::getIdentifier()
{
	return identifier;
}

std::string ConsoleInputHandler::getDescription()
{
	return translate(description);
}

std::string ConsoleInputHandler::getArguments()
{
	return translate(arguments);
}

std::string ConsoleInputHandler::getExampleUsage()
{
	std::string str = identifier + " " + translate(exampleUsage);
	return str;
}

/***************************************/

// files

ConsoleFileOpen::ConsoleFileOpen()
{
	identifier = "open"; 
	description = CONSOLE_INPUT_HANDLER_FILE_OPEN_DESCRIPTION; 
	arguments = CONSOLE_INPUT_HANDLER_FILE_OPEN_ARGUMENTS; 
	exampleUsage = CONSOLE_INPUT_HANDLER_FILE_OPEN_EXAMPLE_USAGE;
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
				std::cout << translate(STRING_HELP_FOR) << " " << input_handlers[i]->getIdentifier() << "\n"
					<< input_handlers[i]->getDescription() << "\n"
					<< input_handlers[i]->getArguments() << "\n" << input_handlers[i]->getExampleUsage() << std::endl;
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
	throw std::exception("Manually initiated crash");
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
	printAppInfo();
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

ConsoleSettingsAddLanguage::ConsoleSettingsAddLanguage()
{
	identifier = "addLanguage";
	description = CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_EXAMPLE_USAGE;
}

void ConsoleSettingsAddLanguage::call(std::string args)
{
	settings->addLanguage(args);
}

ConsolePrintTranslation::ConsolePrintTranslation()
{
	identifier = "printTranslation";
	description = CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_EXAMPLE_USAGE;
}

void ConsolePrintTranslation::call(std::string args)
{
	std::stringstream ss(args);
	int i;
	ss >> i;
	sendMessage(STRING_TRANSLATION, translate(i));
}

ConsoleRunScript::ConsoleRunScript()
{
	identifier = "run";
	description = CONSOLE_INPUT_HANDLER_RUN_SCRIPT_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_RUN_SCRIPT_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_RUN_SCRIPT_EXAMPLE_USAGE;
}

void ConsoleRunScript::call(std::string args) {


}
