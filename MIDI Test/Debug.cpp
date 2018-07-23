#include "stdafx.h"
#include "Debug.h"

void printVariableSizes()
{
	std::cout << "Size of Midi Object: " << sizeof(Midi) << " bytes\n";
	std::cout << "Size of Pattern Impl Object: " << sizeof(PatternImpl) << " bytes\n";
	std::cout << "Size of Pattern Object: " << sizeof(Pattern) << " bytes\n";
	std::cout << "Size of Track Object: " << sizeof(MidiTrack) << " bytes\n";
	std::cout << "Size of Note: " << sizeof(MidiNote) << " bytes\n";

	int numNotes, numTracks, numPatternImpls = 0;
	std::cout << "Enter numNotes, numTracks, numPatternImpls";
	std::cin >> numNotes >> numTracks, numPatternImpls;
	int size = sizeof(Midi) + sizeof(Pattern) + 
		sizeof(MidiTrack) * numTracks * (sizeof(MidiNote) * numNotes) + 
		numPatternImpls * sizeof(PatternImpl);

	std::cout << "Size of Midi with " << numPatternImpls 
		<< " implementations of a pattern with " << numTracks 
		<< " tracks containing " << numNotes 
		<< " notes: " << size << " bytes\n\n\n";
}
