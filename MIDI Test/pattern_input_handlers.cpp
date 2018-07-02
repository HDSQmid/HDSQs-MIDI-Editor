#include "stdafx.h"
#include "pattern_input_handlers.h"

ConsolePatternAdd addPattern;

ConsoleInputHandler * handlers_Pattern[NUM_PATTERN_HANDLERS] = {
	&addPattern
};

// parent handler

ConsoleMidiPattern::ConsoleMidiPattern()
{
	identifier = "pattern";
	description = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_MIDI_PATTERN_EXAMPLE_USAGE;
}

void ConsoleMidiPattern::call(std::string args)
{
	// use handle console input function to handle the console input
	handleConsoleInput(args, handlers_Pattern, NUM_PATTERN_HANDLERS);
}

// child handlers (don't take that the wrong way)

ConsolePatternAdd::ConsolePatternAdd()
{
	identifier = "add";
	description = CONSOLE_INPUT_HANDLER_PATTERN_NEW_DESCRIPTION;
	arguments = CONSOLE_INPUT_HANDLER_PATTERN_NEW_ARGUMENTS;
	exampleUsage = CONSOLE_INPUT_HANDLER_PATTERN_NEW_EXAMPLE_USAGE;
}

void ConsolePatternAdd::call(std::string args)
{
	currentFile->midi.newPattern();
}
