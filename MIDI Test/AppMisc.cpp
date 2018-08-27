#include "stdafx.h"
#include "AppMisc.h"
#include "files.h"
#include "settings.h"

void quit()
{
	if (settings->getSaveBackup()) {
		if (fileIsOpen()) fileClose();
	}
	exit(0);
}
