#pragma once

//message types
//
//

#define MESSAGE_TYPE_MESSAGE (1)
#define MESSAGE_TYPE_ERROR (2)
#define MESSAGE_TYPE_HELP (3)
#define MESSAGE_TYPE_TIP (4)
#define MESSAGE_TYPE_QUESTION (5)

//message response types
//
//

#define MESSAGE_RESPONSE_OK (1001)
#define MESSAGE_RESPONSE_YN (1002)
#define MESSAGE_RESPONSE_RETRYCANCEL (1003)
#define MESSAGE_RESPONSE_STRING (1004)

//message contents
//
//

//console io
#define MESSAGE_NO_MATCHING_COMMAND (10000)

//midi file open/close
#define MESSAGE_OPEN_FILE (11000) // add file name
#define MESSAGE_NEW_FILE (11001)
#define MESSAGE_CLOSE_FILE (1102)
#define MESSAGE_NO_FILE_OPEN (1103)
#define MESSAGE_NOT_VALID_FILENAME (1104) // not a file name
#define MESSAGE_FILE_UNSAVED (1105) // file has unsaved changes