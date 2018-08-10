#pragma once

//message types
//
//

#define MESSAGE_TYPE_MESSAGE (1)
#define MESSAGE_TYPE_ERROR (2)
#define MESSAGE_TYPE_HELP (3)
#define MESSAGE_TYPE_TIP (4)
#define MESSAGE_TYPE_QUESTION (5)
#define MESSAGE_TYPE_UNKNOWN (6)
#define MESSAGE_TYPE_CRITICAL_ERROR (7)

//message response types
//
//

#define MESSAGE_RESPONSE_OK (101)
#define MESSAGE_RESPONSE_YN (102)
#define MESSAGE_RESPONSE_RETRYCANCEL (103)
#define MESSAGE_RESPONSE_STRING (104)
#define MESSAGE_RESPONSE_UNKNOWN (105)

//message contents
//
//

//console io
#define MESSAGE_NO_MATCHING_COMMAND (1000)
#define MESSAGE_NO_COMMAND_PROVIDED (1001)

//midi file open/close
#define MESSAGE_OPEN_FILE (1100) // add file name
#define MESSAGE_NEW_FILE (1101) // created new file
#define MESSAGE_CLOSE_FILE (1102) // file closed
#define MESSAGE_NO_FILE_OPEN (1103) // open a file and try again
#define MESSAGE_NOT_VALID_FILENAME (1104) // not a file name
#define MESSAGE_FILE_UNSAVED (1105) // file has unsaved changes
#define MESSAGE_FILE_SAVED (1106) // saved <filename>
#define MESSAGE_FILE_SAVED_AS (1107) // saved as <filename>
#define MESSAGE_EDIT_MADE (1108) // made edit
#define MESSAGE_ADDED_LANGUAGE (1109) // added language to list of languages

#define MESSAGE_ERROR_OPENING_FILE (1201) // An error occurred when opening the file. Maybe it's Corrupted?
#define MESSAGE_ERROR_SAVING_FILE (1202) // An error occurred when saving the file.

//miscellaneous strings
#define MESSAGE_NO_TRANSLATION_FOUND (2000)
#define STRING_GREETING_HELP (2001)
#define STRING_ENTER_SAVE_LOCATION (2002)
#define STRING_NO_CHANGES_DIDNT_SAVE (2003)
#define STRING_ARGUMENTS (2004)
#define STRING_EXAMPLE_USAGE (2005)
#define STRING_CRITICAL_ERROR_CRASH (2006)
#define STRING_CRITICAL_ERROR_SAVE (2007)
#define STRING_MIDI_MADE_IN (2008)
#define STRING_BUILD_DATE (2009)
#define STRING_AT (2010)
#define STRING_VERSION (2011)
#define STRING_TRANSLATION (2012)
#define STRING_HELP_FOR (2013)

//default names for objects
#define DEFAULT_MIDI_NAME (3001)
#define DEFAULT_PATTERN_NAME (3002)
#define DEFAULT_TRACK_NAME (3003)
#define DEFAULT_COPYRIGHT_INFO (3011)

//console io handlers
//
//

//default
#define CONSOLE_INPUT_HANDLER_DEFAULT_DESCRIPTION (100012)
#define CONSOLE_INPUT_HANDLER_DEFAULT_ARGUMENTS (100013)
#define CONSOLE_INPUT_HANDLER_DEFAULT_EXAMPLE_USAGE (100014)

//file open
#define CONSOLE_INPUT_HANDLER_FILE_OPEN_DESCRIPTION (100022)
#define CONSOLE_INPUT_HANDLER_FILE_OPEN_ARGUMENTS (100023)
#define CONSOLE_INPUT_HANDLER_FILE_OPEN_EXAMPLE_USAGE (100024)

//file close
#define CONSOLE_INPUT_HANDLER_FILE_CLOSE_DESCRIPTION (100032)
#define CONSOLE_INPUT_HANDLER_FILE_CLOSE_ARGUMENTS (100033)
#define CONSOLE_INPUT_HANDLER_FILE_CLOSE_EXAMPLE_USAGE (100034)

//file save
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_DESCRIPTION (100042)
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_ARGUMENTS (100043)
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_EXAMPLE_USAGE (100044)

//file save as
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_DESCRIPTION (100052)
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_ARGUMENTS (100053)
#define CONSOLE_INPUT_HANDLER_FILE_SAVE_AS_EXAMPLE_USAGE (100054)

//quit application
#define CONSOLE_INPUT_HANDLER_QUIT_DESCRIPTION (100062)
#define CONSOLE_INPUT_HANDLER_QUIT_ARGUMENTS (100063)
#define CONSOLE_INPUT_HANDLER_QUIT_EXAMPLE_USAGE (100064)

//help
#define CONSOLE_INPUT_HANDLER_HELP_DESCRIPTION (100072)
#define CONSOLE_INPUT_HANDLER_HELP_ARGUMENTS (100073)
#define CONSOLE_INPUT_HANDLER_HELP_EXAMPLE_USAGE (100074)

//crash
#define CONSOLE_INPUT_HANDLER_CRASH_DESCRIPTION (100082)
#define CONSOLE_INPUT_HANDLER_CRASH_ARGUMENTS (100083)
#define CONSOLE_INPUT_HANDLER_CRASH_EXAMPLE_USAGE (100084)

//info
#define CONSOLE_INPUT_HANDLER_INFO_DESCRIPTION (100092)
#define CONSOLE_INPUT_HANDLER_INFO_ARGUMENTS (100093)
#define CONSOLE_INPUT_HANDLER_INFO_EXAMPLE_USAGE (100094)

//new file
#define CONSOLE_INPUT_HANDLER_FILE_NEW_DESCRIPTION (100102)
#define CONSOLE_INPUT_HANDLER_FILE_NEW_ARGUMENTS (100103)
#define CONSOLE_INPUT_HANDLER_FILE_NEW_EXAMPLE_USAGE (100104)

//make edit
#define CONSOLE_INPUT_HANDLER_MAKE_EDIT_DESCRIPTION (100112)
#define CONSOLE_INPUT_HANDLER_MAKE_EDIT_ARGUMENTS (100113)
#define CONSOLE_INPUT_HANDLER_MAKE_EDIT_EXAMPLE_USAGE (100114)

//midi pattern
#define CONSOLE_INPUT_HANDLER_MIDI_PATTERN_DESCRIPTION (100122)
#define CONSOLE_INPUT_HANDLER_MIDI_PATTERN_ARGUMENTS (100123)
#define CONSOLE_INPUT_HANDLER_MIDI_PATTERN_EXAMPLE_USAGE (100124)

//midi track
#define CONSOLE_INPUT_HANDLER_MIDI_TRACK_DESCRIPTION (100132)
#define CONSOLE_INPUT_HANDLER_MIDI_TRACK_ARGUMENTS (100132)
#define CONSOLE_INPUT_HANDLER_MIDI_TRACK_EXAMPLE_USAGE (100134)

//midi select
#define CONSOLE_INPUT_HANDLER_MIDI_SELECT_DESCRIPTION (100142)
#define CONSOLE_INPUT_HANDLER_MIDI_SELECT_ARGUMENTS (100142)
#define CONSOLE_INPUT_HANDLER_MIDI_SELECT_EXAMPLE_USAGE (100144)

//midi select
#define CONSOLE_INPUT_HANDLER_MIDI_SELECTION_DESCRIPTION (100152)
#define CONSOLE_INPUT_HANDLER_MIDI_SELECTION_ARGUMENTS (100152)
#define CONSOLE_INPUT_HANDLER_MIDI_SELECTION_EXAMPLE_USAGE (100154)

// settings add new language
#define CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_DESCRIPTION (100162)
#define CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_ARGUMENTS (100163)
#define CONSOLE_INPUT_HANDLER_SETTINGS_ADD_LANGUAGE_EXAMPLE_USAGE (100164)

// print the translation of an integer
#define CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_DESCRIPTION (100172)
#define CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_ARGUMENTS (100173)
#define CONSOLE_INPUT_HANDLER_PRINT_TRANSLATION_EXAMPLE_USAGE (100174)

// print the translation of an integer
#define CONSOLE_INPUT_HANDLER_PATTERN_NEW_DESCRIPTION (100172)
#define CONSOLE_INPUT_HANDLER_PATTERN_NEW_ARGUMENTS (100173)
#define CONSOLE_INPUT_HANDLER_PATTERN_NEW_EXAMPLE_USAGE (100174)

#define CONSOLE_INPUT_HANDLER_RUN_SCRIPT_DESCRIPTION (100182)
#define CONSOLE_INPUT_HANDLER_RUN_SCRIPT_ARGUMENTS (100183)
#define CONSOLE_INPUT_HANDLER_RUN_SCRIPT_EXAMPLE_USAGE (100184)
