#pragma once
#include "stdafx.h"
#include "console_io_handler.h"
#include "files.h"

#define NUM_PATTERN_HANDLERS 1


extern ConsoleInputHandler * handlers_Pattern[];

// parent handler
class ConsoleMidiPattern : public ConsoleInputHandler { // make edits to patterns
public:
	ConsoleMidiPattern();

	void call(std::string args);

};

// child handlers

class ConsolePatternAdd : public ConsoleInputHandler { // make edits to patterns
public:
	ConsolePatternAdd();

	void call(std::string args);

};

class ConsolePatternRemove : public ConsoleInputHandler { // make edits to patterns
public:
	ConsolePatternRemove();

	void call(std::string args);

};
