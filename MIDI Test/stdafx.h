// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <exception>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

#include "AppMisc.h"
#include "languageDefinitions.h"

// general stuff

#define CONSOLE
#define APP_NAME "HDSQ's MIDI Editor"
#define APP_VERSION "0.0.1"
#define SAVE_FILE_EXTENSION ".hqm"
#define APP_SETTINGS_FILE_NAME "settings.bin"

// error codes
#define ERROR_CODE_MANUAL_CRASH (0x0001)
#define ERROR_CODE_BAD_LANGUAGE (0x0002)

// TODO: reference additional headers your program requires here
