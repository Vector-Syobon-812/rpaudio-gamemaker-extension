#ifndef RPAUDIO_H
#define RPAUDIO_H

#ifdef _WIN32
#define RP_EXPORT __declspec(dllexport)
#else
#define RP_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	RP_EXPORT double rp_init_audio(void);
	RP_EXPORT double rp_close_audio(void);
	RP_EXPORT double rp_is_audio_ready(void);
	
	RP_EXPORT double rp_set_master_volume(double volume);
	RP_EXPORT double rp_get_master_volume(void);
	
	RP_EXPORT double rp_set_audio_stream_buffer_size_default(double size);
	
	RP_EXPORT double rp_set_update_interval(double ms);
	
	RP_EXPORT double rp_load_sound(const char *filename);
	RP_EXPORT double rp_unload_sound(double handle);
	RP_EXPORT double rp_sound_exists(double handle);
	RP_EXPORT double rp_play_sound(double handle);
	RP_EXPORT double rp_stop_sound(double handle);
	RP_EXPORT double rp_pause_sound(double handle);
	RP_EXPORT double rp_resume_sound(double handle);
	RP_EXPORT double rp_is_sound_playing(double handle);
	RP_EXPORT double rp_set_sound_volume(double handle, double volume);
	RP_EXPORT double rp_set_sound_pitch(double handle, double pitch);
	RP_EXPORT double rp_set_sound_pan(double handle, double pan);
	
	RP_EXPORT double rp_load_music(const char *filename);
	RP_EXPORT double rp_unload_music(double handle);
	RP_EXPORT double rp_music_exists(double handle);
	RP_EXPORT double rp_play_music(double handle);
	RP_EXPORT double rp_stop_music(double handle);
	RP_EXPORT double rp_pause_music(double handle);
	RP_EXPORT double rp_resume_music(double handle);
	RP_EXPORT double rp_is_music_playing(double handle);
	RP_EXPORT double rp_update_music(double handle);
	RP_EXPORT double rp_update_all(void);
	RP_EXPORT double rp_seek_music(double handle, double position);
	RP_EXPORT double rp_set_music_volume(double handle, double volume);
	RP_EXPORT double rp_set_music_pitch(double handle, double pitch);
	RP_EXPORT double rp_set_music_pan(double handle, double pan);
	RP_EXPORT double rp_get_music_time_length(double handle);
	RP_EXPORT double rp_get_music_time_played(double handle);
	RP_EXPORT double rp_set_music_loop(double handle, double loop);
	
#ifdef __cplusplus
}
#endif

#endif // RPAUDIO_H
