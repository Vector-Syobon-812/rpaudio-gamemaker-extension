#define rp_init
{
    show_debug_message("start load audio");
    if(variable_global_exists("rp_dll_name"))
        if(variable_global_get("rp_dll_name")!=noone)
            exit;
    global.rp_dll_name = "rpAudio.dll";

    global._rp_init_audio = external_define(global.rp_dll_name, "rp_init_audio", dll_cdecl, ty_real, 0);
    global._rp_close_audio = external_define(global.rp_dll_name, "rp_close_audio", dll_cdecl, ty_real, 0);
    global._rp_is_audio_ready = external_define(global.rp_dll_name, "rp_is_audio_ready", dll_cdecl, ty_real, 0);

    global._rp_set_master_volume = external_define(global.rp_dll_name, "rp_set_master_volume", dll_cdecl, ty_real, 1, ty_real);
    global._rp_get_master_volume = external_define(global.rp_dll_name, "rp_get_master_volume", dll_cdecl, ty_real, 0);

    global._rp_load_sound = external_define(global.rp_dll_name, "rp_load_sound", dll_cdecl, ty_real, 1, ty_string);
    global._rp_unload_sound = external_define(global.rp_dll_name, "rp_unload_sound", dll_cdecl, ty_real, 1, ty_real);
    global._rp_sound_exists = external_define(global.rp_dll_name, "rp_sound_exists", dll_cdecl, ty_real, 1, ty_real);
    global._rp_play_sound = external_define(global.rp_dll_name, "rp_play_sound", dll_cdecl, ty_real, 1, ty_real);
    global._rp_stop_sound = external_define(global.rp_dll_name, "rp_stop_sound", dll_cdecl, ty_real, 1, ty_real);
    global._rp_pause_sound = external_define(global.rp_dll_name, "rp_pause_sound", dll_cdecl, ty_real, 1, ty_real);
    global._rp_resume_sound = external_define(global.rp_dll_name, "rp_resume_sound", dll_cdecl, ty_real, 1, ty_real);
    global._rp_is_sound_playing = external_define(global.rp_dll_name, "rp_is_sound_playing", dll_cdecl, ty_real, 1, ty_real);
    global._rp_set_sound_volume = external_define(global.rp_dll_name, "rp_set_sound_volume", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_sound_pitch = external_define(global.rp_dll_name, "rp_set_sound_pitch", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_sound_pan = external_define(global.rp_dll_name, "rp_set_sound_pan", dll_cdecl, ty_real, 2, ty_real, ty_real);

    global._rp_load_music = external_define(global.rp_dll_name, "rp_load_music", dll_cdecl, ty_real, 1, ty_string);
    global._rp_unload_music = external_define(global.rp_dll_name, "rp_unload_music", dll_cdecl, ty_real, 1, ty_real);
    global._rp_music_exists = external_define(global.rp_dll_name, "rp_music_exists", dll_cdecl, ty_real, 1, ty_real);
    global._rp_play_music = external_define(global.rp_dll_name, "rp_play_music", dll_cdecl, ty_real, 1, ty_real);
    global._rp_stop_music = external_define(global.rp_dll_name, "rp_stop_music", dll_cdecl, ty_real, 1, ty_real);
    global._rp_pause_music = external_define(global.rp_dll_name, "rp_pause_music", dll_cdecl, ty_real, 1, ty_real);
    global._rp_resume_music = external_define(global.rp_dll_name, "rp_resume_music", dll_cdecl, ty_real, 1, ty_real);
    global._rp_is_music_playing = external_define(global.rp_dll_name, "rp_is_music_playing", dll_cdecl, ty_real, 1, ty_real);
    //global._rp_update_music = external_define(global.rp_dll_name, "rp_update_music", dll_cdecl, ty_real, 1, ty_real);
    //global._rp_update_all = external_define(global.rp_dll_name, "rp_update_all", dll_cdecl, ty_real, 0);
    //now we have thread!!!!!!!!!!!
    global._rp_seek_music = external_define(global.rp_dll_name, "rp_seek_music", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_music_volume = external_define(global.rp_dll_name, "rp_set_music_volume", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_music_pitch = external_define(global.rp_dll_name, "rp_set_music_pitch", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_music_pan = external_define(global.rp_dll_name, "rp_set_music_pan", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_get_music_time_length = external_define(global.rp_dll_name, "rp_get_music_time_length", dll_cdecl, ty_real, 1, ty_real);
    global._rp_get_music_time_played = external_define(global.rp_dll_name, "rp_get_music_time_played", dll_cdecl, ty_real, 1, ty_real);
    global._rp_set_music_loop = external_define(global.rp_dll_name, "rp_set_music_loop", dll_cdecl, ty_real, 2, ty_real, ty_real);
    global._rp_set_music_default_buffer = external_define(global.rp_dll_name, "rp_set_audio_stream_buffer_size_default", dll_cdecl, ty_real, 1, ty_real);
    global._rp_set_update_ms = external_define(global.rp_dll_name, "rp_set_update_interval", dll_cdecl, ty_real, 1, ty_real);

    return true;
}

#define rp_free
{
    if(variable_global_exists("rp_dll_name"))
    {
        if(variable_global_get("rp_dll_name")==noone)
            exit;
        external_free(global.rp_dll_name);
        global.rp_dll_name=noone;
    }
}

#define rp_init_audio
{
    return external_call(global._rp_init_audio);
}

#define rp_close_audio
{
    return external_call(global._rp_close_audio);
}

#define rp_is_audio_ready
{
    return external_call(global._rp_is_audio_ready);
}

#define rp_set_music_default_buffer
{
    return external_call(global._rp_set_music_default_buffer,argument0);
}

#define rp_set_update_ms
{
    return external_call(global._rp_set_update_ms,argument0);
}

#define rp_get_master_volume
{
    return external_call(global._rp_get_master_volume);
}

#define rp_set_master_volume
{
    return external_call(global._rp_set_master_volume,argument0);
}

#define rp_load_music
{
    return external_call(global._rp_load_music,argument0);
}

#define rp_unload_music
{
    return external_call(global._rp_unload_music,argument0);
}

#define rp_play_music
{
    return external_call(global._rp_play_music,argument0);
}

#define rp_stop_music
{
    return external_call(global._rp_stop_music,argument0);
}

#define rp_pause_music
{
    return external_call(global._rp_pause_music,argument0);
}

#define rp_resume_music
{
    return external_call(global._rp_resume_music,argument0);
}

#define rp_seek_music
{
    return external_call(global._rp_seek_music,argument0,argument1);
}

#define rp_set_music_volume
{
    return external_call(global._rp_set_music_volume,argument0,argument1);
}

#define rp_set_music_pitch
{
    return external_call(global._rp_set_music_pitch,argument0,argument1);
}

#define rp_set_music_pan
{
    return external_call(global._rp_set_music_pan,argument0,argument1);
}

#define rp_set_music_loop
{
    return external_call(global._rp_set_music_loop,argument0,argument1);
}

#define rp_is_music_playing
{
    return external_call(global._rp_is_music_playing,argument0);
}

#define rp_get_music_time_length
{
    return external_call(global._rp_get_music_time_length,argument0);
}

#define rp_get_music_time_played
{
    return external_call(global._rp_get_music_time_played,argument0);
}

#define rp_load_sound
{
    return external_call(global._rp_load_sound,argument0);
}

#define rp_unload_sound
{
    return external_call(global._rp_unload_sound,argument0);
}

#define rp_play_sound
{
    return external_call(global._rp_play_sound,argument0);
}

#define rp_stop_sound
{
    return external_call(global._rp_stop_sound,argument0);
}

#define rp_pause_sound
{
    return external_call(global._rp_pause_sound,argument0);
}

#define rp_resume_sound
{
    return external_call(global._rp_resume_sound,argument0);
}

#define rp_set_sound_volume
{
    return external_call(global._rp_set_sound_volume,argument0,argument1);
}

#define rp_set_sound_pitch
{
    return external_call(global._rp_set_sound_pitch,argument0,argument1);
}

#define rp_set_sound_pan
{
    return external_call(global._rp_set_sound_pan,argument0,argument1);
}

#define rp_is_sound_playing
{
    return external_call(global._rp_is_sound_playing,argument0);
}

#define rp_sound_exists
{
    return external_call(global._rp_sound_exists,argument0);
}

#define rp_music_exists
{
    return external_call(global._rp_music_exists,argument0);
}