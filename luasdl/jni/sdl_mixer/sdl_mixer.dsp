# Microsoft Developer Studio Project File - Name="sdl_mixer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sdl_mixer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sdl_mixer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sdl_mixer.mak" CFG="sdl_mixer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sdl_mixer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sdl_mixer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sdl_mixer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /O2 /I "..\sdl\include" /I "..\sdl" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D _WIN32_WINNT=0x0400 /D "BUILD_SDL" /D "_WIN32" /D "WAV_MUSIC" /D "MID_MUSIC" /D DECLSPEC="" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "sdl_mixer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /I "..\sdl\include" /I "..\sdl" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D _WIN32_WINNT=0x0400 /D "BUILD_SDL" /D "_WIN32" /D "WAV_MUSIC" /D "MID_MUSIC" /D DECLSPEC="" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "sdl_mixer - Win32 Release"
# Name "sdl_mixer - Win32 Debug"
# Begin Source File

SOURCE=.\dynamic_flac.c
# End Source File
# Begin Source File

SOURCE=.\dynamic_flac.h
# End Source File
# Begin Source File

SOURCE=.\dynamic_mod.c
# End Source File
# Begin Source File

SOURCE=.\dynamic_mod.h
# End Source File
# Begin Source File

SOURCE=.\dynamic_mp3.c
# End Source File
# Begin Source File

SOURCE=.\dynamic_mp3.h
# End Source File
# Begin Source File

SOURCE=.\dynamic_ogg.c
# End Source File
# Begin Source File

SOURCE=.\dynamic_ogg.h
# End Source File
# Begin Source File

SOURCE=.\effect_position.c
# End Source File
# Begin Source File

SOURCE=.\effect_stereoreverse.c
# End Source File
# Begin Source File

SOURCE=.\effects_internal.c
# End Source File
# Begin Source File

SOURCE=.\effects_internal.h
# End Source File
# Begin Source File

SOURCE=.\load_aiff.c
# End Source File
# Begin Source File

SOURCE=.\load_aiff.h
# End Source File
# Begin Source File

SOURCE=.\load_flac.c
# End Source File
# Begin Source File

SOURCE=.\load_flac.h
# End Source File
# Begin Source File

SOURCE=.\load_ogg.c
# End Source File
# Begin Source File

SOURCE=.\load_ogg.h
# End Source File
# Begin Source File

SOURCE=.\load_voc.c
# End Source File
# Begin Source File

SOURCE=.\load_voc.h
# End Source File
# Begin Source File

SOURCE=.\mixer.c
# End Source File
# Begin Source File

SOURCE=.\music.c
# End Source File
# Begin Source File

SOURCE=.\music_cmd.c
# End Source File
# Begin Source File

SOURCE=.\music_cmd.h
# End Source File
# Begin Source File

SOURCE=.\music_flac.c
# End Source File
# Begin Source File

SOURCE=.\music_flac.h
# End Source File
# Begin Source File

SOURCE=.\music_mad.c
# End Source File
# Begin Source File

SOURCE=.\music_mad.h
# End Source File
# Begin Source File

SOURCE=.\music_mod.c
# End Source File
# Begin Source File

SOURCE=.\music_mod.h
# End Source File
# Begin Source File

SOURCE=.\music_ogg.c
# End Source File
# Begin Source File

SOURCE=.\music_ogg.h
# End Source File
# Begin Source File

SOURCE=.\SDL_mixer.h
# End Source File
# Begin Source File

SOURCE=.\wavestream.c
# End Source File
# Begin Source File

SOURCE=.\wavestream.h
# End Source File
# End Target
# End Project
