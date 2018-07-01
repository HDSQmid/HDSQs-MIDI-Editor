#pragma once
#include "stdafx.h"
#include "files.h"

class consoleInputHandler {
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

	consoleInputHandler();

};

// program stuff

class ConsoleQuit : public consoleInputHandler {
public:
	ConsoleQuit();

	void call(std::string args);

};

class ConsoleHelp : public consoleInputHandler {
public:
	ConsoleHelp();

	void call(std::string args);

};

class ConsoleCrash : public consoleInputHandler {
public:
	ConsoleCrash();

	void call(std::string args);

};

class ConsoleInfo : public consoleInputHandler {
public:
	ConsoleInfo();

	void call(std::string args);

};

// application settings

class ConsoleSettingsAddLanguage : public consoleInputHandler {
public:
	ConsoleSettingsAddLanguage();

	void call(std::string args);

};

// files

class ConsoleFileOpen : public consoleInputHandler {
public:
	ConsoleFileOpen();

	void call(std::string args);

};

class ConsoleFileNew : public consoleInputHandler {
public:
	ConsoleFileNew();

	void call(std::string args);

};

class ConsoleFileClose : public consoleInputHandler {
public:
	ConsoleFileClose();

	void call(std::string args);

};

class ConsoleFileSave : public consoleInputHandler {
public:
	ConsoleFileSave();

	void call(std::string args);

};

class ConsoleFileSaveAs : public consoleInputHandler {
public:
	ConsoleFileSaveAs();

	void call(std::string args);

};


// midi editing stuff

class ConsoleMidiMakeEdit : public consoleInputHandler { // for debug purposes
public:
	ConsoleMidiMakeEdit();

	void call(std::string args);

};

class ConsoleMidiPattern : public consoleInputHandler { // make edits to patterns
public:
	ConsoleMidiPattern();

	void call(std::string args);

};

class ConsoleMidiTrack : public consoleInputHandler { // make edits to tracks
public:
	ConsoleMidiTrack();

	void call(std::string args);

};

class ConsoleMidiSelect : public consoleInputHandler { // select midi objects
public:
	ConsoleMidiSelect();

	void call(std::string args);

};

class ConsoleMidiSelection : public consoleInputHandler { // performs actions on selected midi objects

	ConsoleMidiSelection();

	void call(std::string args);

};

void handleConsoleInput(std::string input);