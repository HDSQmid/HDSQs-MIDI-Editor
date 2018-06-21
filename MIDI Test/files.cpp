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
	std::string str = "Openned " + fileAddress;
	sendMessage(str);

}

file::file()
{
	hasChanged = false;
	std::string str = "Created new file";
	sendMessage(str);
}

file::~file()
{
	if (hasChanged) {

		if (
			 sendMessage("The file has unsaved changes. Would you like to save it?", MESSAGE_QUESTION, RESPONSE_YN) == "y"
			) save();

	}
	sendMessage("File closed successfully");
}

void file::save()
{
	if (hasChanged) {

		if (location == "") {
			location = sendMessage("Where would you like to save?", MESSAGE_QUESTION, RESPONSE_STRING);
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
	else sendMessage("Can't make edit unless there is a file open", MESSAGE_ERROR, RESPONSE_OK);
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
