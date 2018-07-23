#pragma once

// MIDI Library
// 
// midi events are stored on tracks.
// events that affect the entire midi (eg tempo) are stored on system track.
// events that affect entire channels are stored in their relaive channel tracks (0-15).
// notes are stored in patterns.
// patterns contain multiple midi tracks all with notes.
// the midi object has tracks which references to patterns are placed on.
// in the gui, patterns will be shown taking up their relative number of tracks, and length.
// a pattern can be used as many times as neccisary, and will not consume much more RAM because duplicating it only creates a reference to the pattern.
// This means a change in one instance of the pattern affects all instances.
// there will be an option to create a derived pattern (eg pattern A could have a derived pattern A1. These patterns have seperate memory, so a change in one does not affect the other.
// by using references, memory consumption could be minimised, although it will increase the exporting time.
// when a midi is imported, it is all imported to the one pattern (unless someone wants to write an intelligent script to sort tracks into patterns, any volenteers? I didn't think so.)
// 


//define midi events
/*System*/
#define MIDI_TEMPO (-1)
#define MIDI_TIME_SIGNATURE (-2)
#define MIDI_KEY (-3)
#define MIDI_MARK (-4)
/*Channel*/
#define MIDI_INSTRUMENT (-1001)
#define MIDI_EXPRESSION (-1002)
#define MIDI_VOLUME (-1003)
#define MIDI_PAN (-1004)
#define MIDI_PITCH_BEND (-1005)
/*Track*/
#define MIDI_NOTE (-2001)

class MidiPosition;

// class patternSize for returning length 
class patternSize {
protected:
	int length, height;

public:
	patternSize(int nlength, int nheight);

	patternSize(MidiPosition startPos, MidiPosition endPos, int nheight);

	void setData(int nlength, int nheight);

	void setData(MidiPosition startPos, MidiPosition endPos, int nheight);

	int getLength();

	int getHeight();

};

class MidiPosition {
public:

	MidiPosition();

	MidiPosition(int tick);

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

class MidiEvent {
protected:
	int type;
public:

	MidiPosition tick;


};

class ShortValueMidiEvent : public MidiEvent { // most event types can be used directly from this
protected:
	
	byte value;	// velocity for note, etc
				// 0 - 127 generally
public:


	ShortValueMidiEvent(int type, byte value);

	ShortValueMidiEvent();

	virtual void setValue(byte val);

	byte getRawValue();

	virtual std::string getValueS(); //return as string

	virtual byte getValue();

	void increment(byte increment);

	

};

class LongValueMidiEvent : public MidiEvent { // most event types can be used directly from this
protected:

	int value;	// velocity for note, etc
				// 0 - 127 generally
public:


	LongValueMidiEvent(int type, int value);

	LongValueMidiEvent();

	virtual void setValue(int val);

	int getRawValue();

	virtual std::string getValueS(); //return as string

	virtual int getValue();

	void increment(int increment);



};

class MidiNote : public ShortValueMidiEvent {
protected:
	byte pitch;
	unsigned int gate;
	//velocity included in class MidiEvent
public:
	MidiNote(int pitch, int value, int gate);

	void setValue(int val);

	void setPitch(int val);

	void setGate(int val);

};

class MidiPitchBend : public LongValueMidiEvent {
	int longValue;
public:
	//value included in class MidiEvent
	//overload set value (value between -8191 and 8192)
	void setValue(int val);

};

class MidiTempo : public LongValueMidiEvent {

	//tempo value included in class MidiEvent
	//add different return function (return based on time signature)

	void setValue(int val);

	int getValue(); // return based on time signature

	std::string getValueS(); //return as string

};

class MidiKey : public ShortValueMidiEvent {


	//key value included in class MidiEvent
	//add different return function (return as string)

};

class MidiMark : public ShortValueMidiEvent {

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

public:

	void setName(std::string newName);

};

class TrackImpl {

	int channelNum;

};

//class pattern contains midi tracks
class Pattern {

	std::string name;

	std::vector<Track> tracks;

	int length = 0; // length of midi pattern in ticks

public:
	Pattern();

	Pattern(std::string name);

	void setName(std::string newName);

	void open(); // select this pattern

	//functions for editing
	void openTrack(int trackNumber);

	void closeTrack();

	void newTrack();

	void removeTrack(int trackNum);

	void renameTrack(int trackNum, std::string newName);


};

//class patternImplement is used by Midi object to add patterns to the midi
class PatternImpl {
protected:

	double magnification = 1; // magnification of track

	int startTrim = 0; // length in ticks of trim of the pattern from the start in ticks
	int endTrim = 0; // length in ticks of trim of the pattern from the end in ticks

	MidiPosition startLocation;

	int topTrackNum;

public:


	PatternImpl(Pattern *pat, int trackNum, MidiPosition tick);

	Pattern * pattern;

	

	void open(); // selects this pattern

};

//
//class MIDI: container for MIDI files
//
class Midi {

		SystemTrack systemEvents; // system track contains all system-wide events eg tempo

		EventTrack channelEvents[16];

		std::vector<TrackImpl> tracks;

		std::vector<PatternImpl> PatternImpls; // the actual song

		std::vector<Pattern> Patterns; // store of patterns ready for use:tm:
		
		std::string name, copyright, description;
		int PPQN = 960;

public:

		Midi();


		//functions for getting/setting midi details
		void setName(std::string newName);	// set song name
		std::string getName();				// get song name

		void setCopyright(std::string str);	// set copyright info
		std::string getCopyright();

		void setDescription(std::string str);	// set song description
		std::string getDescription();

		std::string getInfo(std::string style = "standard");	// gets info about song

		unsigned long int getNoteCount();

		//functions for patterns
		void newPattern(); // add pattern to pattern list

		void removePattern(int patternNum); // remove pattern from pattern list

		void renamePattern(int patternNum, std::string newName); // renames a pattern

		void openPattern(int patternNum); // selects a pattern as the current pattern for editing

		void closePattern();

		// functions for using patterns in midi
		void implementPattern(int patternNum, int trackNum, int tick); // include pattern in the midi


	};

extern Pattern * currentPattern;
extern Track * currentTrack;

