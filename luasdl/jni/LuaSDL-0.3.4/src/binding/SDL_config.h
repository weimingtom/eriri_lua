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

$pfile "SDL_platform.h"

// NOTE: Manually select the platform file, since tolua++ doesn't seem
//       to have conditionals.

// __DREAMCAST__
// $pfile "SDL_config_dreamcast.h"
// __MACOS__
// $pfile "SDL_config_macos.h"
// __MACOSX__
// $pfile "SDL_config_macosx.h"
// __SYMBIAN32__
// $pfile "SDL_config_symbian.h"
// __WIN32__
$pfile "SDL_config_win32.h"
// __OS2__
// $pfile "SDL_config_os2.h"
// (others)
// $pfile "SDL_config_minimal.h"
