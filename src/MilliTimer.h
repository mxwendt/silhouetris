#ifndef _MILLI_TIMER
#define _MILLI_TIMER

#include "ofMain.h"

class MilliTimer {
public:
	MilliTimer() : alarmMS(0), alarmstamp(0) { set(); }
	MilliTimer(const unsigned int aAlarmTime) { setAlarm(aAlarmTime); }
	virtual ~MilliTimer() {}

	inline void set() {
		// set timestamp to current time
		timestamp = ofGetElapsedTimeMillis();
	}

	inline void setAlarm(const unsigned int aAlarmTime) {
		alarmMS = aAlarmTime;
		timestamp = ofGetElapsedTimeMillis();
		alarmstamp = timestamp + aAlarmTime;
	}

	inline bool alarm() {
		return ofGetElapsedTimeMillis() >= alarmstamp;
	}

protected:
	unsigned int alarmMS; // length of alarm
	unsigned int timestamp; // current timestamp
	unsigned int alarmstamp; // future timestamp
};

#endif
