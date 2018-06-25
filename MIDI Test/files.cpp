#include "stdafx.h"
#include "files.h"
#include "messageSend.h"
#include "midiLib.h"

midiFile* currentFile = NULL; // eventually make vector of open files


midiFile::midiFile(std::string fileAddress)
{
	location = fileAddress;

	//open file here

	hasChanged = false;
	
	sendMessage(MESSAGE_OPEN_FILE, fileAddress);

}

midiFile::midiFile()
{
	hasChanged = false;
	sendMessage(MESSAGE_NEW_FILE);
}

midiFile::~midiFile()
{
	if (hasChanged) {

		if (
			 sendMessage(MESSAGE_FILE_UNSAVED, location, MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_YN) == "y"
			) save();

	}
	sendMessage(MESSAGE_CLOSE_FILE);
}

void midiFile::save()
{
	if (hasChanged) {

		if (location == "") {
			location = sendMessage(STRING_ENTER_SAVE_LOCATION,"" ,MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_STRING);
			//check filename is valid
		}

		saveFile();

		sendMessage(MESSAGE_FILE_SAVED, location);
	}
	else {

		sendMessage(STRING_NO_CHANGES_DIDNT_SAVE);

	}

}

void midiFile::saveAs(std::string newFileName)
{
	location = newFileName;
	saveFile();
	sendMessage(MESSAGE_FILE_SAVED_AS, location);

}

void midiFile::makeEdit()
{
	if (currentFile != NULL) { 
		hasChanged = true;
		sendMessage(MESSAGE_EDIT_MADE);
	}
	else sendMessage(MESSAGE_NO_FILE_OPEN, "",MESSAGE_TYPE_ERROR, MESSAGE_RESPONSE_OK);
}

//the one that actually saves the file
void midiFile::saveFile()
{
	

	//actually save the file here
}

void fileOpen(std::string location)
{
	//if file is open close it
	if (currentFile != NULL) {

		delete currentFile;

	}

	currentFile = new midiFile(location);

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

	currentFile = new midiFile();

}

bool fileIsOpen() {

	if (currentFile == NULL) return false;
	else return true;

}
