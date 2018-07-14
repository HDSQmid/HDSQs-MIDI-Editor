#include "scripting.h"
#include "stdafx.h"

void quickRunScript(std::string fileName)
{
	script temp(fileName);

	temp.run();
}
