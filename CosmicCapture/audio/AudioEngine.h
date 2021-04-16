#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "AudioInstance.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring> 
#include <vector>
#include <memory>

namespace audioConstants
{
	// effects
	const int SOUND_FILE_ENGINE = 1;
	const int SOUND_FILE_COLLISION = 2;
	const int SOUND_FILE_PROJECTILE = 3;
	const int SOUND_FILE_FLAG_PICKUP = 4;
	const int SOUND_FILE_PROJECTILE_PICKUP = 5;
	const int SOUND_FILE_SPIKE_TRAP_PICKUP = 6;
	const int SOUND_FILE_SPEED_BOOST_PICKUP = 7;
	const int SOUND_FILE_FLAG_RETURN = 8;
	const int SOUND_FILE_SPEED_BOOST = 9;
	const int SOUND_FILE_CRASH = 10;
	const int SOUND_FILE_EXPLOSION = 11;
	const int SOUND_FILE_FLAG_LOST = 12;
	const int SOUND_FILE_GATE_SWITCH = 13;

	//music tracks
	const int SOUND_FILE_MAIN_TRACK = 0;

}

class AudioEngine
{
	public:
		AudioEngine();
		~AudioEngine();
		void initialize();
		void initializeBuffers();
		AudioInstance& createInstance(int soundFile);
		void killSources();

	private:
		void CheckError();
		bool _strcmp(const char* bse, const char* cp);
		bool loadWavFile(const char* filename, ALuint* buffer);

		static const int NUM_TOTAL = 14;
		static const int NUM_EFFECTS = 13;
		static const int NUM_TRACKS = 1;
		const char* soundEffects[NUM_EFFECTS];
		const char* musicTracks[NUM_TRACKS];

		ALuint bufferArray[NUM_TOTAL];
		ALuint sources[NUM_TOTAL];
		std::vector<std::unique_ptr<AudioInstance>> listOfSources;

		ALCdevice* device;
		ALCcontext* context;

};