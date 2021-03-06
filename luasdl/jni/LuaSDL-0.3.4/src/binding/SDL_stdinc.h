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

$pfile "SDL_config.h"

typedef enum SDL_bool {
	SDL_FALSE = 0,
	SDL_TRUE  = 1
} SDL_bool;

// NOTE: not sure how to deal with these
// SDL_arraysize(array)
// SDL_TABLESIZE(table)

// NOTE: Expose all of this so that we can prototype C code in Lua (faux-C).

// interface for macros

void * SDL_malloc(size_t size);
void * SDL_calloc(size_t nmemb, size_t size);
void * SDL_realloc(void *mem, size_t size);
void SDL_free(void *mem);

// NOTE: Unimplemented in Lua, no clear way of preserving call arguments,
//       at least, I don't know how to implement this properly.
// SDL_stack_alloc(type, count)
// SDL_stack_free(data)

// interface for macros

char * SDL_getenv(const char *name);
int SDL_putenv(const char *variable);

// TODO: need to pass the compare function, use Lua's table.sort for now
// extern void SDL_qsort(void *base, size_t nmemb, size_t size,
//            int (*compare)(const void *, const void *));

// NOTE: Implemented using Lua functions, see below, so it might work
//       slightly differently.
/* SDL_abs(X)    */
/* SDL_min(x, y) */
/* SDL_max(x, y) */

// interface for macros

int SDL_isdigit(int X);
int SDL_isspace(int X);
int SDL_toupper(int X);
int SDL_tolower(int X);

// interface for macros

void * SDL_memset(void *dst, int c, size_t len);
static void * _SDL_memcpy @ SDL_memcpy(void *dst, const void *src, size_t len);
static void * _SDL_revcpy @ SDL_revcpy(void *dst, const void *src, size_t len);
void * SDL_memmove(void *dst, const void *src, size_t len);
int SDL_memcmp(const void *s1, const void *s2, size_t len);

// implementation for macros

// NOTE: SDL 1.2.11 for MinGW (or rather, for __GNUC__ and i386) has inlined
//       versions of SDL_memcpy and SDL_revcpy that is wrapped by a do-while
//       loop, thus it cannot fit into a return statement and the following
//       hack is required.
$       inline void * _SDL_memcpy (void *dst, const void *src, size_t len)
$       {
$       #if defined(__GNUC__) && defined(i386)
$           SDL_memcpy(dst, src, len);
$           return dst;
$       #elif
$           return SDL_memcpy(dst, src, len);
$       #endif
$       }
$       inline void * _SDL_revcpy (void *dst, const void *src, size_t len)
$       {
$       #if defined(__GNUC__) && defined(i386)
$           SDL_revcpy(dst, src, len);
$           return dst;
$       #elif
$           return SDL_revcpy(dst, src, len);
$       #endif
$       }

// NOTE: The following have been aliased to SDL_memset and SDL_memcpy.
//       There is no reason to call this from a scripting engine, is there?
/* SDL_memset4(dst, val, len) */
/* SDL_memcpy4(dst, src, len) */

// TODO: need to test whether these calls work, for faux-C work

// NOTE: tolua++ 1.0.92 borks with parameter names of "string", this is
//       likely due to tolua++'s pattern-matching method.

// interface for macros

size_t SDL_strlen(const char *str);
size_t SDL_strlcpy(char *dst, const char *src, size_t maxlen);
size_t SDL_strlcat(char *dst, const char *src, size_t maxlen);
char * SDL_strdup(const char *str);
char * SDL_strrev(char *str);
char * SDL_strupr(char *str);
char * SDL_strlwr(char *str);
char * SDL_strchr(const char *str, int c);
char * SDL_strrchr(const char *str, int c);
char * SDL_strstr(const char *haystack, const char *needle);

// interface for macros

char * SDL_itoa(int value, char *str, int radix);
char * SDL_ltoa(long value, char *str, int radix);
char * SDL_uitoa(unsigned int value, char *str, int radix);
char * SDL_ultoa(unsigned long value, char *str, int radix);
long SDL_strtol(const char *str, char **endp, int base);
unsigned long SDL_strtoul(const char *str, char **endp, int base);

// NOTE: No 64 bit support as yet, casting to a Lua number (double) will fail
// extern Sint64 SDL_strtoll(const char *str, char **endp, int base);
// extern Uint64 SDL_strtoull(const char *str, char **endp, int base);

// interface for macros

double SDL_strtod(const char *str, char **endp);
int SDL_atoi(const char *str);
double SDL_atof(const char *str);

// interface for macros

int SDL_strcmp(const char *str1, const char *str2);
int SDL_strncmp(const char *str1, const char *str2, size_t maxlen);
int SDL_strcasecmp(const char *str1, const char *str2);
int SDL_strncasecmp(const char *str1, const char *str2, size_t maxlen);

// TODO: multiple parameters...
// extern int SDL_sscanf(const char *text, const char *fmt, ...);
// extern int SDL_snprintf(char *text, size_t maxlen, const char *fmt, ...);
// extern int SDL_vsnprintf(char *text, size_t maxlen, const char *fmt, va_list ap);

#define SDL_ICONV_ERROR		(size_t)-1
#define SDL_ICONV_E2BIG		(size_t)-2
#define SDL_ICONV_EILSEQ	(size_t)-3
#define SDL_ICONV_EINVAL	(size_t)-4

// NOTE: dummy struct
// WAS: typedef struct _SDL_iconv_t *SDL_iconv_t;
struct _SDL_iconv_t;

// interface for macros

struct _SDL_iconv_t * SDL_iconv_open(const char *tocode, const char *fromcode);
int SDL_iconv_close(struct _SDL_iconv_t * cd);

extern size_t SDL_iconv(struct _SDL_iconv_t * cd, const char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft);
extern char * SDL_iconv_string(const char *tocode, const char *fromcode, char *inbuf, size_t inbytesleft);

char * SDL_iconv_utf8_locale(char *inbuf);
Uint16 * SDL_iconv_utf8_ucs2(char *inbuf);
Uint32 * SDL_iconv_utf8_ucs4(char *inbuf);

$[

SDL.SDL_abs = math.abs
SDL.SDL_min = math.min
SDL.SDL_max = math.max

SDL.SDL_memset4 = SDL.SDL_memset
SDL.SDL_memcpy4 = SDL.SDL_memcpy

$]
