#include "stdafx.h"
#include "midiLib.h"
#include "multiLingual.h"

// midi events



MidiPosition::MidiPosition()
{
	position = 0;
}

MidiPosition::MidiPosition(int tick)
{
	position = tick;
}

void MidiPosition::setPosition(unsigned int value)
{
	position = value;
}

void MidiPosition::setPosition(unsigned int barNum, unsigned int tickNum)
{
	//calculate from ppqn and time signatures
}

int MidiPosition::getRawPosition()
{
	return position;
}

std::string MidiPosition::getPosition()
{
	//calculate position from ppqn and time signatures then convert to string

	return std::string();
}

void MidiPosition::increment(int numTicks)
{
	setPosition(position + numTicks);
}



//midi object

Midi::Midi()
{
	name = translate(DEFAULT_MIDI_NAME);
	copyright = translate(DEFAULT_COPYRIGHT_INFO);
	description = translate(STRING_MIDI_MADE_IN) + " " APP_NAME;
}

Midi::Midi(std::ifstream * in)
{
	// read name of midi
	{
		size_t size;
		in->read(reinterpret_cast<char*>(&size), sizeof size_t);
		
		char * str = new char[size];
		in->read(str, size);
		
		name = std::string(str);

	}

	// read copyright of midi
	{
		size_t size;
		in->read(reinterpret_cast<char*>(&size), sizeof size_t);

		char * str = new char[size];
		in->read(str, size);

		copyright = std::string(str);

	}

	// read description of midi
	{
		size_t size;
		in->read(reinterpret_cast<char*>(&size), sizeof size_t);

		char * str = new char[size];
		in->read(str, size);

		description = std::string(str);

	}

	in->read(reinterpret_cast<char*>(&ppqn), sizeof (int));

}

void Midi::save(std::ofstream * out)
{
	
	//write name of midi
	{
		size_t size = name.size();
		out->write(reinterpret_cast<char*>(&size), sizeof(size_t));
		out->write(name.c_str(), size);
	}

	//write copyright info of midi
	{
		size_t size = copyright.size();
		out->write(reinterpret_cast<char*>(&size), sizeof(size_t));
		out->write(copyright.c_str(), size);
	}

	// write description of midi
	{
		size_t size = description.size();
		out->write(reinterpret_cast<char*>(&size), sizeof(size_t));
		out->write(description.c_str(), size);
	}

	// write ppqn
	out->write(reinterpret_cast<char*>(&ppqn), sizeof(int));

	// write system track
	systemEvents.save(out);

	// for each pattern, call function to get array of bytes for pattern
	// including unique int id for pattern to be used later?

	// for each pattern impl, call function to get array of bytes
	// including unique int id of pattern used

}

bool Midi::is_good()
{
	return isGood;
}

bool Midi::has_changed()
{
	return hasChanged;
}

void Midi::setName(std::string newName)
{
	name = newName;
}

std::string Midi::getName()
{
	return name;
}

void Midi::setCopyright(std::string str)
{
	copyright = str;
}

std::string Midi::getCopyright()
{
	return copyright;
}

void Midi::setDescription(std::string str)
{
	description = str;
}

std::string Midi::getDescription()
{
	return description;
}

std::string Midi::getInfo(std::string style)
{
	std::string ret;

	if (style == "standard") {

		ret = name + "\n\n" + description + "\n" + copyright;

	}

	if (style == "blackMidi") {

		ret = name + " - " + std::to_string(getNoteCount()) + " Notes" + "\n\n" + description + "\n" + copyright;

	}

	return ret;
}

unsigned long int Midi::getNoteCount()
{
	// calculate number of notes in midi

	return 0;
}

//patterns
Pattern * currentPattern = NULL;

void Midi::newPattern()
{
	Patterns.push_back(Pattern());
}

void Midi::removePattern(int patternNum)
{
	Patterns.erase(Patterns.begin() + patternNum);
}

void Midi::renamePattern(int patternNum, std::string newName)
{
	Patterns[patternNum].setName(newName);
}

void Midi::openPattern(int patternNum)
{
	Patterns[patternNum].open();
}

void Midi::closePattern()
{
	currentPattern = NULL;
}

void Midi::implementPattern(int patternNum, int trackNum, int tick)
{
	PatternImpls.push_back(PatternImpl(&(Patterns[patternNum]), trackNum, MidiPosition(tick)));
}

Pattern::Pattern()
{
	name = translate(DEFAULT_PATTERN_NAME);
}

Pattern::Pattern(std::string name)
{
	this->name = name;
}

void Pattern::setName(std::string newName)
{
	name = newName;
}

void Pattern::open()
{
	currentPattern = this;
}

void Pattern::openTrack(int trackNumber)
{
	currentTrack = &tracks[trackNumber];
}

void Pattern::closeTrack()
{
	currentTrack = NULL;
}

void Pattern::newTrack()
{
	tracks.push_back(Track());
}

void Pattern::removeTrack(int patternNum)
{
	tracks.erase(tracks.begin() + patternNum);
}

void Pattern::renameTrack(int patternNum, std::string newName)
{
	tracks[patternNum].setName(newName);
}

//tracks
Track * currentTrack = NULL;

void Track::setName(std::string newName)
{
	trackName = newName;
}

patternSize::patternSize(int nlength, int nheight)
{
	length = nlength;
	height = nheight;
}

patternSize::patternSize(MidiPosition startPos, MidiPosition endPos, int nheight)
{
	length = 0;// endPos - startPos; // use overloaded operator to calculate the length of the midi in ticks
	height = nheight;
}

void patternSize::setData(int nlength, int nheight)
{
	length = nlength;
	height = nheight;
}

void patternSize::setData(MidiPosition startPos, MidiPosition endPos, int nheight)
{
	length = endPos.getRawPosition() - startPos.getRawPosition();
	height = nheight;
}

int patternSize::getLength()
{
	return length;
}

int patternSize::getHeight()
{
	return height;
}

PatternImpl::PatternImpl(Pattern * pat, int trackNum, MidiPosition tick)
{
	pattern = pat;
	topTrackNum = trackNum;
	startLocation = tick;
}

void PatternImpl::open()
{
	pattern->open();
}

SystemTrack::SystemTrack()
{
	trackName = std::string("System");
}

void SystemTrack::save(std::ofstream * out)
{
	//write name of track
	{
		size_t size = trackName.size();
		out->write(reinterpret_cast<char*>(&size), sizeof(size_t));
		out->write(trackName.c_str(), size);
	}

	// write  events
	{
		// get number of events
		size_t s = events.size();

		// write number of events
		out->write(reinterpret_cast<char*>(&s), sizeof(size_t));

		for (int i = 0; i < s; i++) 
		{
			events[i].save(out);
		}

	}



}

