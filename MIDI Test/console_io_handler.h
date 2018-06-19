#pragma once
#include "stdafx.h"
#include "files.h"

class consoleInputHandler {
protected:
	std::string identifier;

	std::string description;
	std::string help;

public:
	virtual void call(std::string args);

	std::string getIdentifier();

	std::string getDescription();

	std::string getHelp();

	consoleInputHandler();

};

class ConsoleFileOpen : public consoleInputHandler {
public:
	ConsoleFileOpen();

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

void handleConsoleInput(std::string input);