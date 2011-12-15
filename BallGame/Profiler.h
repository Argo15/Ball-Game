#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <map>
using namespace std;

struct ProfilePoint {
	string name;
	string prev;
	string next;
	int totalTime;
	int numSamples;
	float avgTimeChange;
	float minTimeChange;
	float maxTimeChange;

	void addTimeChange(int time) {
		numSamples++;
		totalTime += time;
		if (time < minTimeChange) {
			minTimeChange = (float)time;
		}
		if (time > maxTimeChange) {
			maxTimeChange = (float)time;
		}
	}
};

class Profiler {
private:
	map<string, ProfilePoint> points;
	int lastTime;
	int currentTime;
	string lastpoint;
	bool initialized;
	long totalFps;
	long numFrames;

public:
	Profiler() {lastTime=0;currentTime=0; initialized = false; totalFps=0; numFrames=0;}
	~Profiler() {}

	void init();
	void profile(string name);
	void saveProfile(const char *filename);
	void update(int fps);
};

#endif