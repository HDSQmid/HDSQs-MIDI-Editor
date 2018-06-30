#pragma once
#include "languageDefinitions.h"

std::string chooseYN();

std::string sendMessage(int message, std::string args = "", int title = MESSAGE_TYPE_MESSAGE, int response = MESSAGE_RESPONSE_OK);

void sendGreeting();

void printAppInfo();
