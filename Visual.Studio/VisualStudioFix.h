 /*
  * Hatari - Fix for compliation using Visual Studio 6
  *
  * This file is distributed under the GNU Public License, version 2 or at
  * your option any later version. Read the file gpl.txt for details.
  *
  * This file tells Visual Studio to ignore a number of relatively minor "warnings" that have found their
  * way into the HAtari source. None of the "warnings" will hamper the running or compliation or HAtari 
  * but it is possible not addressing them may make it difficult for other developers to be sure of the 
  * intentions of the original coders against whos code these warnings are raised.
  * As long as the original coder was aware of the warnings and of the implicit result of adding no 
  * explicit casts to remove them then things are good.
  *
  * 2009 Vaughan Kaufman
  *
  */

#if defined(_VCWIN_)					// Stop Visual Studio complaining about all the implicit type conversions (wish we would make them explict guys/girls)
	#pragma warning (disable:4244)		// conversion with potential data loss
	#pragma warning (disable:4761)		// integral size mismatch in argument
	#pragma warning (disable:4146)		// unary minus operator applied to unsigned type
	#pragma warning (disable:4018)		// signed / unsigned mismatch
	#pragma warning (disable:4102)		// ignore unused label warning
	#pragma warning (disable:4049)		// (this one is silly, its not important) compiler limit, end of line numbering
	#pragma warning (disable:4800)		// Performance Warning on Conversion of bool to int
	#pragma warning (disable:4805)		// warning C4805: '|=' : unsafe mix of type 'int' and type 'bool' in operation

	#ifndef __STDC__
	#define	__STDC__	TRUE
	#endif
#endif

 /*
  * KVK - Fix for compliation using Visual Studio 6
  *
  * Microsoft have created multiple versions of the standard C calls, a specific version exists for each type of string encoding 
  * format (in this case UNICODE (Wide) and ANSI (Ascii) versions. This has lead to there being versions with a A or a W after
  * the name to signify the encoding. There are other additional reasons why they have these different versions (something to 
  * do with the change from BSTR to string class passing I think, anyone?). The upshot is, we need to add a _ to the beginning of
  * some of the function names for HAtari to compile..
  *
  * 2009 Vaughan Kaufman
  * 2013 Vaughan Kaufman (revised for PrEv, NeXt Emulator)
  */

#if defined(_VCWIN_)
	#define STATIC_INLINE	static __inline
	#define GLOB_ONLYDIR 0
	
	#include <io.h>
	#include <direct.h>
	#include <stdbool.h>
	#include <tchar.h>

	#include <dirent.h>

	#if !defined TCHAR
	#define TCHAR	char
	#endif

#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif

	#define	stat	_stat
	#ifdef S_IRUSR
	#undef S_IRUSR
	#endif
	#define	S_IRUSR			_S_IREAD
	#ifdef S_IWUSR
	#undef S_IWUSR
	#endif
	#define	S_IWUSR			_S_IWRITE
	#ifdef S_ISDIR
	#undef S_ISDIR
	#endif
	#define S_ISDIR(val)	(_S_IFDIR & val)
	#ifdef S_IFDIR
	#undef S_IFDIR
	#endif
	#define	S_IFDIR			_S_IFDIR

	#define	strncasecmp	_strnicmp
	#ifndef strcasecmp
		#define	strcasecmp	_stricmp
	#endif
	#define	chdrive		_chdrive
	#define strdup		_strdup
	#define getcwd		_getcwd
	#define fileno		_fileno
	#define unlink		_unlink
	#define access		_access
	#ifndef mkdir
//		#define mkdir(name,mode) _mkdir(name)
	#endif
	#define	rmdir		_rmdir
//	#define	chmod		_chmod
	#define	itoa		_itoa
	#define	stricmp		_stricmp
	#define snprintf	_snprintf
	#define	vsnprintf	_vsnprintf

	#define __attribute__(x)	/* x */

	 // For new UI

	#ifndef _NEW_UI_TYPES
	#define _NEW_UI_TYPES
		typedef unsigned short		mode_t;
		
		#define	off_t	mode_t

		typedef signed __int8		int8;
		typedef unsigned __int8		uint8;
		typedef unsigned __int8		Uint8;
		typedef signed __int16		int16;
		typedef unsigned __int16	uint16;
		typedef unsigned __int16	Uint16;
		typedef signed __int32		int32;
		typedef unsigned __int32	uint32;
		typedef unsigned __int32	Uint32;
		typedef signed __int64		int64;
		typedef unsigned __int64	uint64;
		typedef void*				memptr;
	#endif

	#ifndef __inline__	
	#define __inline__	__inline
	#endif

//	#include "..\SDL\include\SDL_config_win32.h"

/*	 // Found in SDL_Config_Win32.h
	#define	int8_t	signed __int8
	#define uint8_t	unsigned __int8		
	#define int16_t signed __int16
	#define uint16_t unsigned __int16
	#define int32_t signed __int32
	#define	uint32_t unsigned __int32
	#define	int64_t	signed __int64
	#define	uint64_t unsigned __int64	
*/

/*	typedef signed __int8		int8_t;
	typedef unsigned __int8		uint8_t;
	typedef signed __int16		int16_t;
	typedef unsigned __int16	uint16_t;
	typedef signed __int32		int32_t;
	typedef unsigned __int32	uint32_t;
	typedef signed __int64		int64_t;
	typedef unsigned __int64	uint64_t;	
*/

		/* The variable-types used in the CPU core: */
	typedef unsigned __int8 uae_u8;
	typedef signed __int8 uae_s8;

	typedef unsigned __int16 uae_u16;
	typedef signed __int16 uae_s16;

//	typedef unsigned __int16 uae_u32;	// Found in SysDeps.h
	typedef signed __int32 uae_s32;

	typedef signed __int32 uaecptr;

	extern	void LOG_TRACE(int level, ...);
	extern	void LOG_TRACE_PRINT(char* strFirstString, ...);

	#ifdef JOY_BUTTON1
	#undef JOY_BUTTON1
	#endif
	#ifdef JOY_BUTTON2
	#undef JOY_BUTTON2
	#endif

	extern	void Win_OpenCon(void);

#endif
