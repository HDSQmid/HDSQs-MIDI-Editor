#include "stdafx.h"
#include "midiLib.h"




MidiEvent::MidiEvent(int type, int value)
{
	this->type = type;

	setValue(value);

}

MidiEvent::MidiEvent()
{
	type = 0;
	value = 0;
}

void MidiEvent::setValue(int val)
{
	if (val < 0) value = 0;
	else {
		if (val > 127) value = 127;
		else value = val;
	}
}

int MidiEvent::getRawValue()
{
	return value;
}

std::string MidiEvent::getValueS()
{
	

	return std::string((char*) value);
}

int MidiEvent::getValue()
{
	return getRawValue();
}

void MidiEvent::increment(int increment)
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
	if (val < -8191) value = -8191;
	else {
		if (val > 8192) value = 8192;
		else value = val;
	}
}

void MidiTempo::setValue(int val)
{
	if (val < 1) value = 1;
	else {
		value = val; // no upper limit
	}
}
