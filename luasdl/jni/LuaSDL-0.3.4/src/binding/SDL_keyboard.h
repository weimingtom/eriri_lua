/* ================================================================== */
/*
 * tolua++ bindings for LuaSDL, adapted from SDL header files.
 * This file is part of LuaSDL.
 *
 * Author: Kein-Hong Man <khman@users.sf.net> 2007
 */
/* ================================================================== */

/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2006 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

$pfile "SDL_keysym.h"

typedef struct SDL_keysym {
	Uint8 scancode;
	SDLKey sym;
	SDLMod mod;
	Uint16 unicode;
} SDL_keysym;

#define SDL_ALL_HOTKEYS		0xFFFFFFFF

extern int SDL_EnableUNICODE(int enable);

#define SDL_DEFAULT_REPEAT_DELAY	500
#define SDL_DEFAULT_REPEAT_INTERVAL	30

extern int SDL_EnableKeyRepeat(int delay, int interval);
extern void SDL_GetKeyRepeat(int *delay, int *interval);
// NOTE: implemented in sdllib.c, returning Uint8[]
// extern Uint8 * SDL_GetKeyState(int *numkeys = 0);
extern SDLMod SDL_GetModState(void);
extern void SDL_SetModState(SDLMod modstate);
extern char * SDL_GetKeyName(SDLKey key);
