#include "stdafx.h"
#include "Debug.h"

void printVariableSizes()
{
	std::cout << "Size of Midi Object: " << sizeof Midi << " bytes\n";
	std::cout << "Size of System Track Object: " << sizeof SystemTrack << " bytes\n";
	std::cout << "Size of Event Track Object: " << sizeof EventTrack << " bytes\n";
	std::cout << "\n";

	std::cout << "Size of Pattern Object: " << sizeof Pattern << " bytes\n";
	std::cout << "Size of Track Object: " << sizeof Track << " bytes\n";
	std::cout << "Size of Note: " << sizeof MidiNote << " bytes\n";
	std::cout << "\n";

	std::cout << "Size of Pattern Impl Object: " << sizeof PatternImpl << " bytes\n";
	std::cout << "Size of TrackImpl Object: " << sizeof TrackImpl << " bytes\n";
	std::cout << "\n";
	
}

void printStdVarSizes()
{
	std::cout << "int: " << sizeof(int) << "\n" <<
		"long int: " << sizeof(long int) << "\n" <<
		"double: " << sizeof(double) << "\n" <<
		"long long int: " << sizeof(long long int) << "\n" << std::endl;
}
