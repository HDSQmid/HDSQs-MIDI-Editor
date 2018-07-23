#include "stdafx.h"
#include "files.h"
#include "messageSend.h"
#include "midiLib.h"

// start with a new midi file
midiFile* currentFile = NULL; // eventually make vector of open files


midiFile::midiFile(std::string fileAddress)
{
	if (fileAddress == "") return;

	location = fileAddress;

	//open file here

	hasChanged = false;
	
	sendMessage(MESSAGE_OPEN_FILE, fileAddress);

}

midiFile::midiFile()
{
	hasChanged = false;
	sendMessage(MESSAGE_NEW_FILE);
	location = "";
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
			location = sendMessage(STRING_ENTER_SAVE_LOCATION, "",MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_STRING);
			//check filename is valid
		}

		saveFile();

		sendMessage(MESSAGE_FILE_SAVED, location);
		hasChanged = false;
	}
	else {

		sendMessage(STRING_NO_CHANGES_DIDNT_SAVE);

	}

}

void midiFile::saveAs(std::string newFileName)
{
	location = newFileName;
	if (location == "") {
		location = sendMessage(STRING_ENTER_SAVE_LOCATION, "", MESSAGE_TYPE_QUESTION, MESSAGE_RESPONSE_STRING);
		//check filename is valid
	}
	saveFile();
	sendMessage(MESSAGE_FILE_SAVED_AS, location);
	hasChanged = false;
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
	
	// make file stram for saving
	std::ofstream fileOut;
	// open file in binary out mode
	fileOut.open(location, std::ios::binary | std::ios::out);

	if (fileOut.is_open()) {

		//save file


		fileOut.close();
	}

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
