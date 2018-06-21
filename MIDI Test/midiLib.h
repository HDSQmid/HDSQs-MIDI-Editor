#pragma once

//define midi events
/*System*/
#define MIDI_TEMPO (1)
#define MIDI_TIME_SIGNATURE (2)
#define MIDI_KEY (3)
#define MIDI_MARK (4)
/*Channel*/
#define MIDI_INSTRUMENT (1001)
#define MIDI_EXPRESSION (1002)
#define MIDI_VOLUME (1003)
#define MIDI_PAN (1004)
#define MIDI_PITCH_BEND (1005)
/*Track*/
#define MIDI_NOTE (2001)

class MidiPosition {
public:
	unsigned int position; // position in ticks from start

	void setPosition(unsigned int value);

	void setPosition(unsigned int barNum, unsigned int tickNum);

	int getRawPosition();

	std::string getPosition();

	void increment(int numTicks); // increase or decrese position by ticks

};
// todo: add operators for this event

///
//Events
///

class MidiEvent { // most event types can be used directly from this
protected:
	
	int value;	// velocity for note, etc
				// 0 - 127 generally
	int type;
public:

	MidiPosition tick;

	MidiEvent(int type, int value);

	MidiEvent();

	virtual void setValue(int val);

	int getRawValue();

	virtual std::string getValueS(); //return as string

	virtual int getValue();

	void increment(int increment);

	

};

class MidiNote : public MidiEvent {
protected:
	int pitch;
	unsigned int gate;
	//velocity included in class MidiEvent
public:
	MidiNote(int pitch, int value, int gate);

	void setValue(int val);

	void setPitch(int val);

	void setGate(int val);

};

class MidiPitchBend : public MidiEvent {

	//value included in class MidiEvent
	//overload set value (value between -8191 and 8192)
	void setValue(int val);

};

class MidiTempo : public MidiEvent {

	//tempo value included in class MidiEvent
	//add different return function (return based on time signature)

	void setValue(int val);

	int getValue(); // return based on time signature

	std::string getValueS(); //return as string

};

class MidiKey : public MidiEvent {


	//key value included in class MidiEvent
	//add different return function (return as string)

};

class MidiMark : public MidiEvent {

	std::string value;
	//add different return function (return as string)

};



class MidiTrack {
public:
	//events in vector (sorted in order of position)

	//addEvent(MidiEvent event);

	std::string trackName;

	int TrackChannel;

};

class SystemTrack {
public:
	//events in vector (sorted in order of position)

	//addEvent(MidiEvent event);

	std::string trackName = "System";

};

class EventTrack {
public:
	//events in vector (sorted in order of position)

	//addEvent(MidiEvent event);

	std::string trackName = "Event Track";



};

class Track : public MidiTrack {
public:
	//events in vector (sorted in order of position)

	//addNote(MidiNote event);

	std::string trackName;

	int TrackChannel;

};

//
//class MIDI: container for MIDI files
//
class Midi {

		SystemTrack systemEvents; // system track contains all system-wide events eg tempo

		EventTrack channelEvents[16];

		// vector of tracks

		std::string name, copyright, description;
		int PPQN;



	};

