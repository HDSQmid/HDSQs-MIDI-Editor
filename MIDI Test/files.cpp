#include "stdafx.h"
#include "files.h"
#include "messageSend.h"

file* currentFile = NULL;


file::file(std::string fileAddress)
{
	location = fileAddress;

	//open file here

	hasChanged = false;
	std::string str = "Openned " + fileAddress;
	sendMessage(str);

}

file::~file()
{
	if (hasChanged) {

		//promptSave();

	}
	sendMessage("File closed successfully");
}

void file::save()
{
	saveFile();

	std::string str = "Saved " + location;
	sendMessage(str);
}

void file::saveAs(std::string newFileName)
{
	location = newFileName;
	saveFile();
	std::string str = "Saved as " + location;
	sendMessage(str);

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
