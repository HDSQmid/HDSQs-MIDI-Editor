#include "stdafx.h"
#include "files.h"
#include "messageSend.h"
#include "midiLib.h"

file* currentFile = NULL; // eventually make vector of open files


file::file(std::string fileAddress)
{
	location = fileAddress;

	//open file here

	hasChanged = false;
	std::string str = MESSAGE_OPEN_FILE + fileAddress;
	sendMessage(str);

}

file::file()
{
	hasChanged = false;
	std::string str = MESSAGE_NEW_FILE;
	sendMessage(str);
}

file::~file()
{
	if (hasChanged) {

		if (
			 sendMessage(MESSAGE_FILE_UNSAVED, MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_YN) == "y"
			) save();

	}
	sendMessage(MESSAGE_CLOSE_FILE);
}

void file::save()
{
	if (hasChanged) {

		if (location == "") {
			location = sendMessage("Where would you like to save?", MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_STRING);
			//check filename is valid
		}

		saveFile();

		std::string str = "Saved " + location;
		sendMessage(str);
	}
	else {

		sendMessage("Didn't save file. There were no changes");

	}

}

void file::saveAs(std::string newFileName)
{
	location = newFileName;
	saveFile();
	std::string str = "Saved as " + location;
	sendMessage(str);

}

void file::makeEdit()
{
	if (currentFile != NULL) { 
		hasChanged = true;
		sendMessage("Edit made");
	}
	else sendMessage(MESSAGE_NO_FILE_OPEN, MESSAGE_TYPE_ERROR, MESSAGE_RESPONSE_OK);
}

//the one that actually saves the file
void file::saveFile()
{
	

	//actually save the file here
}

void fileOpen(std::string location)
{
	//if file is open close it
	if (currentFile != NULL) {

		delete currentFile;

	}

	currentFile = new file(location);

}

void fileClose()
{
	
	delete currentFile;
	currentFile = NULL;
}

void fileNew()
{
	//if file is open close it
	if (currentFile != NULL) {

		delete currentFile;

	}

	currentFile = new file();

}

bool fileIsOpen() {

	if (currentFile == NULL) return false;
	else return true;

}
