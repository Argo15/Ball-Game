#include "Profiler.h"
#include <stdlib.h>
#include <fstream>
#include <GL/freeglut.h>

void Profiler::init() 
{
	int time = glutGet( GLUT_ELAPSED_TIME );
	lastTime = time;
	currentTime = time;
	lastpoint = "init";
	if (points.find("init") == points.end()) {
		points["init"].name = "init";
		points["init"].prev = "";
		points["init"].next = "";
		points["init"].numSamples = 0;
		points["init"].totalTime = 0;
		points["init"].minTimeChange = 100;
		points["init"].maxTimeChange = 0;
	}
	points["init"].addTimeChange(0);
	initialized = true;
}

void Profiler::profile(string name) 
{
	if (!initialized) return;
	int time = glutGet( GLUT_ELAPSED_TIME );
	lastTime = currentTime;
	currentTime = time;
	if (points.find(name) == points.end()) {
		points[name].name = name;
		points[name].prev = lastpoint;
		points[name].numSamples = 0;
		points[name].avgTimeChange = 0;
		points[lastpoint].next = name;
		points[name].next = "";
		points[name].totalTime = 0;
		points[name].minTimeChange = 100;
		points[name].maxTimeChange = 0;
	}
	points[name].addTimeChange(currentTime-lastTime);
	lastpoint = name;
}

void Profiler::saveProfile(const char *filename)
{
	float averageFps = ((float)totalFps)/numFrames;
	ofstream file(filename);
	if (file.is_open()) {
		ProfilePoint current = points["init"];
		file << "init" << endl;
		do {
			current = points[current.next];
			float averageTime = (float)current.totalTime/current.numSamples;
			file << (int)(1000*(averageTime/(1000.0/averageFps)))/10.0 << "%" << endl;
			file << "Average Time: " << averageTime << endl;
			file << "Minimum Time: " << current.minTimeChange << endl;
			file << "Maximum Time: " << current.maxTimeChange << endl;
			file << current.name << endl;
		} while (current.next != "");
	}
	file << "Average Fps: " << averageFps << endl;
	file.close();
}

void Profiler::update(int fps) {
	totalFps += fps;
	numFrames++;
}