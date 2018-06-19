#pragma once


class file {
public:
	file(std::string fileAddress);

	~file();

	void save();

	void saveAs(std::string newFileName);

protected:
	std::string location;
	bool hasChanged;

	void saveFile();

};

extern file* currentFile;

void fileOpen(std::string location);

void fileClose();