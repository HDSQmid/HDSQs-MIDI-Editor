#pragma once

//define midi events
/*System*/
#define MIDI_TEMPO (1)
#define MIDI_TIME_SIGNATURE (2)
#define MIDI_KEY (3)
/*Channel*/
#define MIDI_INSTRUMENT (1001)
#define MIDI_EXPRESSION (1002)
#define MIDI_VOLUME (1003)
#define MIDI_PAN (1004)
#define MIDI_PITCH_BEND (1005)
/*Track*/
#define MIDI_NOTE (2001)

class Midi {

	MidiTrack systemTrack; // system track contains all system-wide events eg tempo

	// channel event tracks which contain channel-wide events eg instrument, 1-16

	// other tracks stored in array or vector

	std::string name, copyright, description;
	int PPQN;


};

class MidiTrack {
public:
	//events in vector (sorted in order of position)
	
	//addEvent(MidiEvent event);

	//std:string trackName;

	int trackPort, TrackChannel;

};

class MidiPosition {
public:
	unsigned int
		position, // position in ticks from start
		barNum, // bar number
		tickNum; // number of ticks from start of bar

				 //setPosition(unsigned int position);

				 //setPosition(unsigned int barNum, unsigned int tickNum);

};
// todo: add operators for this event

class MidiEvent {

	MidiPosition position;

	int type;

	int value;

};

class MidiEventWithVolume : public MidiEvent {

	unsigned int volume;

};

class MidiNote : public MidiEventWithVolume {

	int pitch;
	int gate;

};

class MidiExpression : public MidiEventWithVolume {

	int pitch;
	int gate;

};

