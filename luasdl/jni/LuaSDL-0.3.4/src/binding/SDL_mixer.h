/* ================================================================== */
/*
 * tolua++ bindings for LuaSDL, adapted from SDL header files.
 * This file is part of LuaSDL.
 *
 * Author: Kein-Hong Man <khman@users.sf.net> 2007
 */
/* ================================================================== */

/*
    SDL_mixer:  An audio mixer library based on the SDL library
    Copyright (C) 1997-2004 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#define SDL_MIXER_MAJOR_VERSION	1
#define SDL_MIXER_MINOR_VERSION	2
#define SDL_MIXER_PATCHLEVEL	8

// interface for macros

void SDL_MIXER_VERSION (SDL_version *ver_info);

#define MIX_MAJOR_VERSION	SDL_MIXER_MAJOR_VERSION
#define MIX_MINOR_VERSION	SDL_MIXER_MINOR_VERSION
#define MIX_PATCHLEVEL		SDL_MIXER_PATCHLEVEL

#define MIX_DEFAULT_FREQUENCY	22050
#define MIX_DEFAULT_CHANNELS	2
#define MIX_MAX_VOLUME		128

typedef struct Mix_Chunk {
	int allocated;
        void *abuf; // Uint8 *
	Uint32 alen;
	Uint8 volume;
} Mix_Chunk;

typedef enum {
	MIX_NO_FADING,
	MIX_FADING_OUT,
	MIX_FADING_IN
} Mix_Fading;

typedef enum {
	MUS_NONE,
	MUS_CMD,
	MUS_WAV,
	MUS_MOD,
	MUS_MID,
	MUS_OGG,
	MUS_MP3,
	MUS_MP3_MAD
} Mix_MusicType;

typedef struct _Mix_Music Mix_Music;

extern int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
extern int Mix_AllocateChannels(int numchans);
extern int Mix_QuerySpec(int *frequency = 0, Uint16 *format = 0, int *channels = 0);
extern Mix_Chunk * Mix_LoadWAV_RW(SDL_RWops *src, int freesrc);

// interface for macros

Mix_Chunk * Mix_LoadWAV(const char *file);

extern Mix_Music * Mix_LoadMUS(const char *file);
extern Mix_Music * Mix_LoadMUS_RW(SDL_RWops *rw);
extern Mix_Chunk * Mix_QuickLoad_WAV(void *mem);
extern Mix_Chunk * Mix_QuickLoad_RAW(void *mem, Uint32 len);

extern void Mix_FreeChunk(Mix_Chunk *chunk);
extern void Mix_FreeMusic(Mix_Music *music);

// TODO
// extern Mix_MusicType Mix_GetMusicType(const Mix_Music *music);

// TODO
// extern void Mix_SetPostMix(void (*mix_func)
//                              (void *udata, Uint8 *stream, int len), void *arg);

// TODO
// extern void Mix_HookMusic(void (*mix_func)
//                           (void *udata, Uint8 *stream, int len), void *arg);

// TODO
// extern void Mix_HookMusicFinished(void (*music_finished)(void));

// TODO
// extern void * Mix_GetMusicHookData(void);

// TODO
// extern void Mix_ChannelFinished(void (*channel_finished)(int channel));

#define MIX_CHANNEL_POST  -2

// TODO
// typedef void (*Mix_EffectFunc_t)(int chan, void *stream, int len, void *udata);
// typedef void (*Mix_EffectDone_t)(int chan, void *udata);

// extern int Mix_RegisterEffect(int chan, Mix_EffectFunc_t f,
// 					Mix_EffectDone_t d, void *arg);
// extern int Mix_UnregisterEffect(int channel, Mix_EffectFunc_t f);
// extern int Mix_UnregisterAllEffects(int channel);

// interface for macro

static const char* _MIX_EFFECTSMAXSPEED @ MIX_EFFECTSMAXSPEED;

// implementation for macro

$       static const char* _MIX_EFFECTSMAXSPEED = MIX_EFFECTSMAXSPEED;

extern int Mix_SetPanning(int channel, Uint8 left, Uint8 right);
extern int Mix_SetPosition(int channel, Sint16 angle, Uint8 distance);
extern int Mix_SetDistance(int channel, Uint8 distance);
extern int Mix_SetReverseStereo(int channel, int flip);
// NOTE: not yet implemented by SDL_mixer
// extern no_parse_int Mix_SetReverb(int channel, Uint8 echo);

extern int Mix_ReserveChannels(int num);

extern int Mix_GroupChannel(int which, int tag);
extern int Mix_GroupChannels(int from, int to, int tag);
extern int Mix_GroupAvailable(int tag);
extern int Mix_GroupCount(int tag);
extern int Mix_GroupOldest(int tag);
extern int Mix_GroupNewer(int tag);

extern int Mix_PlayChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ticks);
extern int Mix_PlayMusic(Mix_Music *music, int loops);
extern int Mix_FadeInMusic(Mix_Music *music, int loops, int ms);
extern int Mix_FadeInMusicPos(Mix_Music *music, int loops, int ms, double position);
extern int Mix_FadeInChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ms, int ticks);

// interface for macros

int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);
int Mix_FadeInChannel(int channel, Mix_Chunk *chunk, int loops, int ms);

extern int Mix_Volume(int channel, int volume);
extern int Mix_VolumeChunk(Mix_Chunk *chunk, int volume);
extern int Mix_VolumeMusic(int volume);

extern int Mix_HaltChannel(int channel);
extern int Mix_HaltGroup(int tag);
extern int Mix_HaltMusic(void);

extern int Mix_ExpireChannel(int channel, int ticks);

extern int Mix_FadeOutChannel(int which, int ms);
extern int Mix_FadeOutGroup(int tag, int ms);
extern int Mix_FadeOutMusic(int ms);

extern Mix_Fading Mix_FadingMusic(void);
extern Mix_Fading Mix_FadingChannel(int which);

extern void Mix_Pause(int channel);
extern void Mix_Resume(int channel);
extern int Mix_Paused(int channel);

extern void Mix_PauseMusic(void);
extern void Mix_ResumeMusic(void);
extern void Mix_RewindMusic(void);
extern int Mix_PausedMusic(void);

extern int Mix_SetMusicPosition(double position);

extern int Mix_Playing(int channel);
extern int Mix_PlayingMusic(void);

extern int Mix_SetMusicCMD(const char *command);

extern int Mix_SetSynchroValue(int value);
extern int Mix_GetSynchroValue(void);

extern Mix_Chunk * Mix_GetChunk(int channel);

extern void Mix_CloseAudio(void);

$[

if not SDL.MIX_CHANNELS then
    SDL.MIX_CHANNELS = 8
end

if SDL.SDL_BYTEORDER == SDL.SDL_LIL_ENDIAN then
SDL.MIX_DEFAULT_FORMAT = SDL.AUDIO_S16LSB
else
SDL.MIX_DEFAULT_FORMAT = SDL.AUDIO_S16MSB
end

SDL.MIX_VERSION = SDL.SDL_MIXER_VERSION

SDL.Mix_SetError = SDL.SDL_SetError
SDL.Mix_GetError = SDL.SDL_GetError

$]
