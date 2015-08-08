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

$pfile "SDL_active.h"
$pfile "SDL_keyboard.h"
$pfile "SDL_mouse.h"
$pfile "SDL_joystick.h"
$pfile "SDL_quit.h"

#define SDL_RELEASED	0
#define SDL_PRESSED	1

typedef enum {
       SDL_NOEVENT = 0,
       SDL_ACTIVEEVENT,
       SDL_KEYDOWN,
       SDL_KEYUP,
       SDL_MOUSEMOTION,
       SDL_MOUSEBUTTONDOWN,
       SDL_MOUSEBUTTONUP,
       SDL_JOYAXISMOTION,
       SDL_JOYBALLMOTION,
       SDL_JOYHATMOTION,
       SDL_JOYBUTTONDOWN,
       SDL_JOYBUTTONUP,
       SDL_QUIT,
       SDL_SYSWMEVENT,
       SDL_EVENT_RESERVEDA,
       SDL_EVENT_RESERVEDB,
       SDL_VIDEORESIZE,
       SDL_VIDEOEXPOSE,
       SDL_EVENT_RESERVED2,
       SDL_EVENT_RESERVED3,
       SDL_EVENT_RESERVED4,
       SDL_EVENT_RESERVED5,
       SDL_EVENT_RESERVED6,
       SDL_EVENT_RESERVED7,
       SDL_USEREVENT = 24,
       SDL_NUMEVENTS = 32
} SDL_EventType;

typedef enum {
	SDL_ACTIVEEVENTMASK	= SDL_EVENTMASK(SDL_ACTIVEEVENT),
	SDL_KEYDOWNMASK		= SDL_EVENTMASK(SDL_KEYDOWN),
	SDL_KEYUPMASK		= SDL_EVENTMASK(SDL_KEYUP),
	SDL_KEYEVENTMASK	= SDL_EVENTMASK(SDL_KEYDOWN)|
	                          SDL_EVENTMASK(SDL_KEYUP),
	SDL_MOUSEMOTIONMASK	= SDL_EVENTMASK(SDL_MOUSEMOTION),
	SDL_MOUSEBUTTONDOWNMASK	= SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN),
	SDL_MOUSEBUTTONUPMASK	= SDL_EVENTMASK(SDL_MOUSEBUTTONUP),
	SDL_MOUSEEVENTMASK	= SDL_EVENTMASK(SDL_MOUSEMOTION)|
	                          SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN)|
	                          SDL_EVENTMASK(SDL_MOUSEBUTTONUP),
	SDL_JOYAXISMOTIONMASK	= SDL_EVENTMASK(SDL_JOYAXISMOTION),
	SDL_JOYBALLMOTIONMASK	= SDL_EVENTMASK(SDL_JOYBALLMOTION),
	SDL_JOYHATMOTIONMASK	= SDL_EVENTMASK(SDL_JOYHATMOTION),
	SDL_JOYBUTTONDOWNMASK	= SDL_EVENTMASK(SDL_JOYBUTTONDOWN),
	SDL_JOYBUTTONUPMASK	= SDL_EVENTMASK(SDL_JOYBUTTONUP),
	SDL_JOYEVENTMASK	= SDL_EVENTMASK(SDL_JOYAXISMOTION)|
	                          SDL_EVENTMASK(SDL_JOYBALLMOTION)|
	                          SDL_EVENTMASK(SDL_JOYHATMOTION)|
	                          SDL_EVENTMASK(SDL_JOYBUTTONDOWN)|
	                          SDL_EVENTMASK(SDL_JOYBUTTONUP),
	SDL_VIDEORESIZEMASK	= SDL_EVENTMASK(SDL_VIDEORESIZE),
	SDL_VIDEOEXPOSEMASK	= SDL_EVENTMASK(SDL_VIDEOEXPOSE),
	SDL_QUITMASK		= SDL_EVENTMASK(SDL_QUIT),
	SDL_SYSWMEVENTMASK	= SDL_EVENTMASK(SDL_SYSWMEVENT)
} SDL_EventMask ;

#define SDL_ALLEVENTS		0xFFFFFFFF

typedef struct SDL_ActiveEvent {
	Uint8 type;
	Uint8 gain;
	Uint8 state;
} SDL_ActiveEvent;

typedef struct SDL_KeyboardEvent {
	Uint8 type;
	Uint8 which;
	Uint8 state;
	SDL_keysym keysym;
} SDL_KeyboardEvent;

typedef struct SDL_MouseMotionEvent {
	Uint8 type;
	Uint8 which;
	Uint8 state;
	Uint16 x, y;
	Sint16 xrel;
	Sint16 yrel;
} SDL_MouseMotionEvent;

typedef struct SDL_MouseButtonEvent {
	Uint8 type;
	Uint8 which;
	Uint8 button;
	Uint8 state;
	Uint16 x, y;
} SDL_MouseButtonEvent;

typedef struct SDL_JoyAxisEvent {
	Uint8 type;
	Uint8 which;
	Uint8 axis;
	Sint16 value;
} SDL_JoyAxisEvent;

typedef struct SDL_JoyBallEvent {
	Uint8 type;
	Uint8 which;
	Uint8 ball;
	Sint16 xrel;
	Sint16 yrel;
} SDL_JoyBallEvent;

typedef struct SDL_JoyHatEvent {
	Uint8 type;
	Uint8 which;
	Uint8 hat;
	Uint8 value;
} SDL_JoyHatEvent;

typedef struct SDL_JoyButtonEvent {
	Uint8 type;
	Uint8 which;
	Uint8 button;
	Uint8 state;
} SDL_JoyButtonEvent;

typedef struct SDL_ResizeEvent {
	Uint8 type;
	int w;
	int h;
} SDL_ResizeEvent;

typedef struct SDL_ExposeEvent {
	Uint8 type;
} SDL_ExposeEvent;

typedef struct SDL_QuitEvent {
	Uint8 type;
} SDL_QuitEvent;

typedef struct SDL_UserEvent {
	Uint8 type;
	int code;
	void *data1;
	void *data2;
} SDL_UserEvent;

// NOTE: dummy struct for SDL_SysWMmsg
struct SDL_SysWMmsg;

typedef struct SDL_SysWMEvent {
	Uint8 type;
	SDL_SysWMmsg *msg;
} SDL_SysWMEvent;

// NOTE: tolua++ 1.0.92 does not support "typedef union...", see pattern
//       matcher in tolua++-1.0.92/src/bin/lua/container.lua
// typedef union SDL_Event {
// } SDL_Event;
union SDL_Event {
	Uint8 type;
	SDL_ActiveEvent active;
	SDL_KeyboardEvent key;
	SDL_MouseMotionEvent motion;
	SDL_MouseButtonEvent button;
	SDL_JoyAxisEvent jaxis;
	SDL_JoyBallEvent jball;
	SDL_JoyHatEvent jhat;
	SDL_JoyButtonEvent jbutton;
	SDL_ResizeEvent resize;
	SDL_ExposeEvent expose;
	SDL_QuitEvent quit;
	SDL_UserEvent user;
	SDL_SysWMEvent syswm;
};

extern void SDL_PumpEvents(void);

typedef enum {
	SDL_ADDEVENT,
	SDL_PEEKEVENT,
	SDL_GETEVENT
} SDL_eventaction;

extern int SDL_PeepEvents(SDL_Event *events, int numevents,
				SDL_eventaction action, Uint32 mask);
extern int SDL_PollEvent(SDL_Event *event);
extern int SDL_WaitEvent(SDL_Event *event);
extern int SDL_PushEvent(SDL_Event *event);

// TODO
// typedef int (*SDL_EventFilter)(const SDL_Event *event);
// extern void SDL_SetEventFilter(SDL_EventFilter filter);
// extern SDL_EventFilter SDL_GetEventFilter(void);

#define SDL_QUERY	-1
#define SDL_IGNORE	 0
#define SDL_DISABLE	 0
#define SDL_ENABLE	 1

extern Uint8 SDL_EventState(Uint8 type, int state);
