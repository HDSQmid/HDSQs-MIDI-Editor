#pragma once
#include "midiLib.h"


class midiFile {
public:
	midiFile(std::string fileAddress);

	midiFile();

	~midiFile();

	void save();

	void saveAs(std::string newFileName);

	Midi midi;

	void makeEdit();

protected:
	std::string location = "";

	bool hasChanged;

	void saveFile();

};

extern midiFile* currentFile;

void fileOpen(std::string location);

void fileClose();

void fileNew();

bool fileIsOpen();
