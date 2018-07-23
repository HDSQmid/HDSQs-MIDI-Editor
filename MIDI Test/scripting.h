#pragma once
#include "stdafx.h"

class script {
public:
	std::string identifier;
	std::vector<std::string> lines;

	// script(std::string fileName);

	// void run();

};


// runs script from the disk
void quickRunScript(std::string fileName);

// void addScript(std::string fileName);

// void runScript(std::string identifier);
