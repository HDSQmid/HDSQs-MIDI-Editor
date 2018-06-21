#pragma once
#include "midiLib.h"


class file {
public:
	file(std::string fileAddress);

	file();

	~file();

	void save();

	void saveAs(std::string newFileName);

	Midi midi;

	void makeEdit();

protected:
	std::string location = "";
	bool hasChanged;

	void saveFile();

};

extern file* currentFile;

void fileOpen(std::string location);

void fileClose();

void fileNew();

bool fileIsOpen();
