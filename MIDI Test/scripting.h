#pragma once
#include "stdafx.h"

// runs script from the disk
void quickRunScript(std::string fileName);

void addScript(std::string fileName);

void runScript(std::string identifier);

class script {
public:
	std::string identifier;
	std::vector<std::string> lines;

	script(std::string fileName);

	void run();

};