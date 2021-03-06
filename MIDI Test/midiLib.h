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
	unsigned int length, height;

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

	unsigned int position; // position in ticks from start


	MidiPosition();
	MidiPosition(int tick);

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

class midiData {

public:
	unsigned int length;
	byte * data;

	// may lose data if not dynamically allocated
	// this should be managed by the constructor
	midiData(int lengthOfData, byte d);

};

class MidiEvent {
private:
	byte value;
protected:
	MidiPosition position;
public:
	// saves data to HQM format
	virtual void save(std::ofstream * o) = 0;
	// loads data from HQM format
	virtual void load(std::ifstream * i) = 0;
	// returns the midi data of the structure
	virtual midiData getMidiData() = 0;

};

class UnknownMidiEvent : public MidiEvent {
protected:
	byte type;
	byte param1, param2;
public:
	virtual midiData getMidiData();
	virtual void save(std::ofstream * o);
	virtual void load(std::ifstream * i);
};

class MidiNote {
protected:
	byte pitch, velocity, release;

public:
	midiData getNoteOn();
	midiData getNoteOff();
	void save(std::ofstream * o);
	void load(std::ifstream * i);

};

///
//Tracks
///

class MidiTrack {
public:
	//events in vector (sorted in order of position)

	//addEvent(MidiEvent event);

	std::string trackName;

	int TrackChannel;

};

class SystemTrack : public MidiTrack {
public:
	//events in vector (sorted in order of position)
	std::vector<MidiEvent> events;

	//addEvent(MidiEvent event);

	SystemTrack();

	void save(std::ofstream * out);

};

class EventTrack : public MidiTrack {
public:
	//events in vector (sorted in order of position)

	//addEvent(MidiEvent event);

	std::string trackName;



};

class Track : public MidiTrack {
public:
	//events in vector (sorted in order of position)
	std::vector<MidiNote> notes;

	std::string trackName;

public:


	void addNote(MidiNote event);
	void addNote(int start, int pitch, int duration, int velocity, int release);

	void setName(std::string newName);

};

class TrackImpl {

	std::string name;
	byte channelNum;

};

//class pattern contains midi tracks
class Pattern {

	std::string name;

	int length = 0; // length of midi pattern in ticks

	std::vector<Track> tracks;

	long long int patternNumber; // only use when saving MIDI
	

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

	unsigned int startTrim = 0; // length in ticks of trim of the pattern from the start in ticks
	unsigned int endTrim = 0; // length in ticks of trim of the pattern from the end in ticks

	MidiPosition startLocation;

	unsigned int topTrackNum;

public:


	PatternImpl(Pattern *pat, int trackNum, MidiPosition tick);

	Pattern * pattern;

	

	void open(); // selects this pattern

};

//
//class MIDI: container for MIDI files
//
class Midi {

	bool isGood = true;
	bool hasChanged = false;

	std::string name, copyright, description;

	int ppqn = 960;

	SystemTrack systemEvents; // system track contains all system-wide events eg tempo

	EventTrack channelEvents[16];

	std::vector<TrackImpl> tracks;

	std::vector<PatternImpl> PatternImpls; // the actual song

	std::vector<Pattern> Patterns; // store of patterns ready for use:tm:
		

public:

	Midi();
	Midi(std::ifstream * in);
		
	void save(std::ofstream * out); // serialise midi file and return as a vector of bytes
		
	bool is_good();
	bool has_changed();

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

