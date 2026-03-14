#include "rpaudio.h"
#define RAUDIO_STANDALONE
#include <raudio.h>

#include <unordered_map>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

static int gSleepMs = 20;
static bool gAudioInit = false;
static std::unordered_map<int, Sound> gSounds;
static std::unordered_map<int, Music> gMusics;
static int gNextSound = 1;
static int gNextMusic = 1;

static std::thread* gUpdateThread = nullptr;
static std::atomic<bool> gThreadRunning(false);
static std::mutex gMusicMutex;

static void AutoUpdateThread()
{
	while (gThreadRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(gSleepMs));
		std::lock_guard<std::mutex> tLock(gMusicMutex);
		for (auto& tPair : gMusics)
		{
			UpdateMusicStream(tPair.second);
		}
	}
}

extern "C" double rp_init_audio(void)
{
	if (!gAudioInit)
	{
		InitAudioDevice();
		gAudioInit = IsAudioDeviceReady();
		if (gAudioInit && !gUpdateThread)
		{
			gThreadRunning = true;
			gUpdateThread = new std::thread(AutoUpdateThread);
		}
	}
	return gAudioInit ? 1.0 : 0.0;
}

extern "C" double rp_close_audio(void)
{
	if (gAudioInit)
	{
		gThreadRunning = false;
		if (gUpdateThread)
		{
			gUpdateThread->join();
			delete gUpdateThread;
			gUpdateThread = nullptr;
		}
		
		{
			std::lock_guard<std::mutex> tLock(gMusicMutex);
			for (auto& tPair : gMusics)
			{
				UnloadMusicStream(tPair.second);
			}
			gMusics.clear();
		}
		
		for (auto& tPair : gSounds)
		{
			UnloadSound(tPair.second);
		}
		gSounds.clear();
		
		CloseAudioDevice();
		gAudioInit = false;
	}
	return 1.0;
}

extern "C" double rp_is_audio_ready(void)
{
	return gAudioInit ? 1.0 : 0.0;
}

extern "C" double rp_set_master_volume(double volume)
{
	SetMasterVolume((float)volume);
	return 1.0;
}

extern "C" double rp_get_master_volume(void)
{
	return (double)GetMasterVolume();
}

extern "C" double rp_set_audio_stream_buffer_size_default(double size)
{
	SetAudioStreamBufferSizeDefault((int)size);
	return 1.0;
}

extern "C" double rp_set_update_interval(double ms)
{
	if (ms < 1.0) ms = 1.0;
	gSleepMs = (int)ms;
	return 1.0;
}

extern "C" double rp_load_sound(const char* filename)
{
	if (!filename || !gAudioInit)
		return -1.0;
	Sound tSnd = LoadSound(filename);
	if (!IsSoundReady(tSnd))
		return -1.0;
	int tId = gNextSound++;
	gSounds[tId] = tSnd;
	return (double)tId;
}

extern "C" double rp_unload_sound(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
	{
		UnloadSound(tIt->second);
		gSounds.erase(tIt);
	}
	return 1.0;
}

extern "C" double rp_play_sound(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		PlaySound(tIt->second);
	return 1.0;
}

extern "C" double rp_stop_sound(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		StopSound(tIt->second);
	return 1.0;
}

extern "C" double rp_pause_sound(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		PauseSound(tIt->second);
	return 1.0;
}

extern "C" double rp_resume_sound(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		ResumeSound(tIt->second);
	return 1.0;
}

extern "C" double rp_is_sound_playing(double handle)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		return IsSoundPlaying(tIt->second) ? 1.0 : 0.0;
	return 0.0;
}

extern "C" double rp_set_sound_volume(double handle, double volume)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		SetSoundVolume(tIt->second, (float)volume);
	return 1.0;
}

extern "C" double rp_set_sound_pitch(double handle, double pitch)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		SetSoundPitch(tIt->second, (float)pitch);
	return 1.0;
}

extern "C" double rp_set_sound_pan(double handle, double pan)
{
	int tId = (int)handle;
	auto tIt = gSounds.find(tId);
	if (tIt != gSounds.end())
		SetSoundPan(tIt->second, (float)pan);
	return 1.0;
}

extern "C" double rp_load_music(const char* filename)
{
	if (!filename || !gAudioInit) return -1.0;
	Music tMus = LoadMusicStream(filename);
	if (!IsMusicReady(tMus)) return -1.0;
	int tId = gNextMusic++;
	{
		std::lock_guard<std::mutex> tLock(gMusicMutex);
		gMusics[tId] = tMus;
	}
	return (double)tId;
}

extern "C" double rp_unload_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
	{
		UnloadMusicStream(tIt->second);
		gMusics.erase(tIt);
	}
	return 1.0;
}

extern "C" double rp_play_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		PlayMusicStream(tIt->second);
	return 1.0;
}

extern "C" double rp_stop_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		StopMusicStream(tIt->second);
	return 1.0;
}

extern "C" double rp_pause_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		PauseMusicStream(tIt->second);
	return 1.0;
}

extern "C" double rp_resume_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		ResumeMusicStream(tIt->second);
	return 1.0;
}

extern "C" double rp_is_music_playing(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		return IsMusicStreamPlaying(tIt->second) ? 1.0 : 0.0;
	return 0.0;
}

extern "C" double rp_update_music(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		UpdateMusicStream(tIt->second);
	return 1.0;
}

extern "C" double rp_update_all(void)
{
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	for (auto& tPair : gMusics)
	{
		UpdateMusicStream(tPair.second);
	}
	return 1.0;
}

extern "C" double rp_seek_music(double handle, double position)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		SeekMusicStream(tIt->second, (float)position);
	return 1.0;
}

extern "C" double rp_set_music_volume(double handle, double volume)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		SetMusicVolume(tIt->second, (float)volume);
	return 1.0;
}

extern "C" double rp_set_music_pitch(double handle, double pitch)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		SetMusicPitch(tIt->second, (float)pitch);
	return 1.0;
}

extern "C" double rp_set_music_pan(double handle, double pan)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		SetMusicPan(tIt->second, (float)pan);
	return 1.0;
}

extern "C" double rp_get_music_time_length(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		return (double)GetMusicTimeLength(tIt->second);
	return 0.0;
}

extern "C" double rp_get_music_time_played(double handle)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
		return (double)GetMusicTimePlayed(tIt->second);
	return 0.0;
}

extern "C" double rp_set_music_loop(double handle, double loop)
{
	int tId = (int)handle;
	std::lock_guard<std::mutex> tLock(gMusicMutex);
	auto tIt = gMusics.find(tId);
	if (tIt != gMusics.end())
	{
		tIt->second.looping = (loop != 0.0);
	}
	return 1.0;
}
