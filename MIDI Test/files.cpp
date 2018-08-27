#include "stdafx.h"
#include "files.h"
#include "messageSend.h"
#include "midiLib.h"

// start with a new midi file
midiFile* currentFile = NULL; // eventually make vector of open files


midiFile::midiFile(std::string fileAddress) // open existing file
{
	if (fileAddress == "") return;

	location = fileAddress;

	try {

		//open file here
		std::ifstream in;
		in.open(fileAddress, std::ios::binary | std::ios::in);

		if (in.is_open()) {

			// send file stream as reference to new MIDI object
			midi = Midi(&in);

			in.close();

		}
		else throw std::exception("Error opening file");

		hasChanged = false;

		sendMessage(MESSAGE_OPEN_FILE, fileAddress);

	}
	catch (std::exception &e) {

		isGood = false;
		sendMessage(MESSAGE_ERROR_OPENING_FILE, e.what(),MESSAGE_TYPE_CRITICAL_ERROR);

	}
	catch (...) {

		isGood = false;
		sendMessage(MESSAGE_ERROR_OPENING_FILE, "", MESSAGE_TYPE_CRITICAL_ERROR);

	}
}

midiFile::midiFile() // new file
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
		try {
			saveFile();

			sendMessage(MESSAGE_FILE_SAVED, location);
			hasChanged = false;
		}
		catch (std::exception &e) {

			sendMessage(MESSAGE_ERROR_SAVING_FILE, e.what(), MESSAGE_TYPE_CRITICAL_ERROR);

		}
		catch (...) {

			sendMessage(MESSAGE_ERROR_SAVING_FILE, "", MESSAGE_TYPE_CRITICAL_ERROR);

		}
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

bool midiFile::is_good()
{
	return (isGood && midi.is_good());
}

bool midiFile::has_changed()
{
	return (hasChanged && midi.has_changed());
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
		midi.save(&fileOut);

		fileOut.close();
	}
	else {

		// send an error about not being able to save the file
		sendMessage(MESSAGE_ERROR_SAVING_FILE, "", MESSAGE_TYPE_ERROR);

	}

}

void fileOpen(std::string location)
{
	//if file is open close it
	if (currentFile != NULL) {

		delete currentFile;

	}

	currentFile = new midiFile(location);
	if (!currentFile->is_good()) {
		delete currentFile;
		currentFile = NULL;
	}
	updateWindowTitle();
}

void fileClose()
{	
	delete currentFile;
	currentFile = NULL;

	updateWindowTitle();
}

void fileNew()
{
	//if file is open close it
	if (currentFile != NULL) {

		delete currentFile;

	}

	currentFile = new midiFile();
	updateWindowTitle();
}

bool fileIsOpen() {

	if (currentFile == NULL) return false;
	else return true;

}

