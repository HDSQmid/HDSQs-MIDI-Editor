#pragma once

#define MESSAGE_MESSAGE (1)
#define MESSAGE_ERROR (2)
#define MESSAGE_HELP (3)
#define MESSAGE_TIP (4)
#define MESSAGE_QUESTION (5)

#define RESPONSE_OK (1001)
#define RESPONSE_YN (1002)
#define RESPONSE_RETRYCANCEL (1003)
#define RESPONSE_STRING (1004)

std::string chooseYN();

std::string sendMessage(std::string message, int title = MESSAGE_MESSAGE, int response = RESPONSE_OK);

void sendGreeting();