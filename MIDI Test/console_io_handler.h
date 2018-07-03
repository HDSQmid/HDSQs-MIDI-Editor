#pragma once
#include "stdafx.h"
#include "files.h"



#define NUM_HANDLERS 13

class ConsoleInputHandler {
protected:
	std::string identifier;
	int description;
	int arguments;
	int exampleUsage;

public:
	virtual void call(std::string args);

	std::string getIdentifier();

	std::string getDescription();

	std::string getArguments();

	std::string getExampleUsage();

	ConsoleInputHandler();

};

extern ConsoleInputHandler * input_handlers[];

// other input handlers here
#include "pattern_input_handlers.h"


// program stuff

class ConsoleQuit : public ConsoleInputHandler {
public:
	ConsoleQuit();

	void call(std::string args);

};

class ConsoleHelp : public ConsoleInputHandler {
public:
	ConsoleHelp();

	void call(std::string args);

};

class ConsoleCrash : public ConsoleInputHandler {
public:
	ConsoleCrash();

	void call(std::string args);

};

class ConsoleInfo : public ConsoleInputHandler {
public:
	ConsoleInfo();

	void call(std::string args);

};

class ConsolePrintTranslation : public ConsoleInputHandler {
public:
	ConsolePrintTranslation();

	void call(std::string args);


};


class ConsoleRunScript : public ConsoleInputHandler {
public:
	ConsoleRunScript();

	void call(std::string args);

};

// application settings

class ConsoleSettingsAddLanguage : public ConsoleInputHandler {
public:
	ConsoleSettingsAddLanguage();

	void call(std::string args);

};

// files

class ConsoleFileOpen : public ConsoleInputHandler {
public:
	ConsoleFileOpen();

	void call(std::string args);

};

class ConsoleFileNew : public ConsoleInputHandler {
public:
	ConsoleFileNew();

	void call(std::string args);

};

class ConsoleFileClose : public ConsoleInputHandler {
public:
	ConsoleFileClose();

	void call(std::string args);

};

class ConsoleFileSave : public ConsoleInputHandler {
public:
	ConsoleFileSave();

	void call(std::string args);

};

class ConsoleFileSaveAs : public ConsoleInputHandler {
public:
	ConsoleFileSaveAs();

	void call(std::string args);

};


// midi editing stuff

class ConsoleMidiMakeEdit : public ConsoleInputHandler { // for debug purposes
public:
	ConsoleMidiMakeEdit();

	void call(std::string args);

};

class ConsoleMidiTrack : public ConsoleInputHandler { // make edits to tracks
public:
	ConsoleMidiTrack();

	void call(std::string args);

};

class ConsoleMidiSelect : public ConsoleInputHandler { // select midi objects
public:
	ConsoleMidiSelect();

	void call(std::string args);

};

class ConsoleMidiSelection : public ConsoleInputHandler { // performs actions on selected midi objects

	ConsoleMidiSelection();

	void call(std::string args);

};

void handleConsoleInput(std::string input, ConsoleInputHandler ** handlerList = input_handlers, int numHandlers = NUM_HANDLERS);