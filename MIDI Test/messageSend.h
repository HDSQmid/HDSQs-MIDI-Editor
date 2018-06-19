#pragma once

#define MESSAGE_MESSAGE (1)
#define MESSAGE_ERROR (2)
#define MESSAGE_HELP (3)
#define MESSAGE_TIP (4)

void sendMessage(std::string message, int title = MESSAGE_MESSAGE);

void sendGreeting();