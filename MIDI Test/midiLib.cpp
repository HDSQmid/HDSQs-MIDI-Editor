#include "stdafx.h"
#include "midiLib.h"
#include "multiLingual.h"

// midi events

ShortValueMidiEvent::ShortValueMidiEvent(int type, byte value)
{
	this->type = type;

	setValue(value);

}

ShortValueMidiEvent::ShortValueMidiEvent()
{
	type = 0;
	value = 0;
}

void ShortValueMidiEvent::setValue(byte val)
{
	if (val < 0) value = 0;
	else {
		if (val > 127) value = 127;
		else value = val;
	}
}

byte ShortValueMidiEvent::getRawValue()
{
	return value;
}

std::string ShortValueMidiEvent::getValueS()
{
	

	return std::string((char*) value);
}

byte ShortValueMidiEvent::getValue()
{
	return getRawValue();
}

void ShortValueMidiEvent::increment(byte increment)
{
	setValue(value + increment);
}

MidiNote::MidiNote(int pitch, int value, int gate)
{
	setValue(value);
	setPitch(pitch);
	setGate(gate);
}

void MidiNote::setValue(int val)
{
	if (val < 1) value = 1;
	else {
		if (val > 127) value = 127;
		else value = val;
	}
}

void MidiNote::setPitch(int val)
{
	if (val < 0) value = 0;
	else {
		if (val > 127) value = 127;
		else value = val;
	}
}

void MidiNote::setGate(int val)
{
	if (val <= 0) val = 1;
	gate = val;
}

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

void MidiPitchBend::setValue(int val)
{
	if (val < -8191) longValue = -8191;
	else {
		if (val > 8192) longValue = 8192;
		else longValue = val;
	}
}

void MidiTempo::setValue(int val)
{
	if (val < 1) value = 1;
	else {
		value = val; // no upper limit
	}
}

//midi object

Midi::Midi()
{
	name = translate(DEFAULT_MIDI_NAME);
	copyright = translate(DEFAULT_COPYRIGHT_INFO);
	description = translate(STRING_MIDI_MADE_IN) + " " APP_NAME;
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
