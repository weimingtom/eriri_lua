# Microsoft Developer Studio Project File - Name="freetype" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=freetype - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "freetype.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freetype.mak" CFG="freetype - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freetype - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "freetype - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freetype - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "FT2_BUILD_LIBRARY" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "freetype - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "FT_DEBUG_LEVEL_ERROR" /D "FT_DEBUG_LEVEL_TRACE" /D "FT2_BUILD_LIBRARY" /FR /FD /GZ /c
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

# Name "freetype - Win32 Release"
# Name "freetype - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter ""
# Begin Group "autofit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\autofit\afangles.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afangles.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afcjk.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afcjk.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afdummy.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afdummy.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aferrors.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afglobal.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afglobal.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afhints.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afhints.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afindic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afindic.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aflatin.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aflatin.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aflatin2.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aflatin2.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afloader.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afloader.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afmodule.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afmodule.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afpic.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\aftypes.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afwarp.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\autofit\afwarp.h
# End Source File
# Begin Source File

SOURCE=.\src\autofit\autofit.c
# End Source File
# End Group
# Begin Group "base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\base\basepic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\basepic.h
# End Source File
# Begin Source File

SOURCE=.\src\base\ftadvanc.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftapi.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftbase.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftbase.h
# End Source File
# Begin Source File

SOURCE=.\src\base\ftbbox.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftbdf.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftbitmap.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftcalc.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftcid.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftdbgmem.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftdebug.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftfstype.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftgasp.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftgloadr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftglyph.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftgxval.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftinit.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftlcdfil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftmm.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftotval.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftoutln.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftpatent.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftpfr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftrfork.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftsnames.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftstream.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftstroke.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftsynth.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftsystem.c
# End Source File
# Begin Source File

SOURCE=.\src\base\fttrigon.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\fttype1.c
# End Source File
# Begin Source File

SOURCE=.\src\base\ftutil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftwinfnt.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\base\ftxf86.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "cache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cache\ftcache.c
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcbasic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftccache.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftccache.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftccback.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftccmap.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcerror.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcglyph.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcglyph.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcimage.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcimage.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcmanag.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcmanag.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcmru.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcmru.h
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcsbits.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cache\ftcsbits.h
# End Source File
# End Group
# Begin Group "cff"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cff\cff.c
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffcmap.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffcmap.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffdrivr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffdrivr.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cfferrs.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffgload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffgload.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffload.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffparse.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffparse.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cff\cffpic.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cfftoken.h
# End Source File
# Begin Source File

SOURCE=.\src\cff\cfftypes.h
# End Source File
# End Group
# Begin Group "cid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\cid\ciderrs.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidgload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidgload.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidload.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidparse.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidparse.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidriver.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidriver.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\cidtoken.h
# End Source File
# Begin Source File

SOURCE=.\src\cid\type1cid.c
# End Source File
# End Group
# Begin Group "gxvalid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\gxvalid\gxvalid.c
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvalid.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvbsln.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvcommn.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvcommn.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxverror.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvfeat.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvfeat.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvfgen.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvjust.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvkern.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvlcar.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmod.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmod.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort0.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort2.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort4.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmort5.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx.h
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx0.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx2.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx4.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvmorx5.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvopbd.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvprop.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gxvalid\gxvtrak.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "otvalid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\otvalid\otvalid.c
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvalid.h
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvbase.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvcommn.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvcommn.h
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otverror.h
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvgdef.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvgpos.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvgpos.h
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvgsub.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvjstf.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvmath.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvmod.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\otvalid\otvmod.h
# End Source File
# End Group
# Begin Group "psaux"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\psaux\afmparse.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\afmparse.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psaux.c
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psauxerr.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psauxmod.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psauxmod.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psconv.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psconv.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\psobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\t1cmap.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\t1cmap.h
# End Source File
# Begin Source File

SOURCE=.\src\psaux\t1decode.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psaux\t1decode.h
# End Source File
# End Group
# Begin Group "pshinter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\pshinter\pshalgo.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshalgo.h
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshglob.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshglob.h
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshinter.c
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshmod.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshmod.h
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshnterr.h
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshpic.h
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshrec.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pshinter\pshrec.h
# End Source File
# End Group
# Begin Group "psnames"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\psnames\psmodule.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psnames\psmodule.h
# End Source File
# Begin Source File

SOURCE=.\src\psnames\psnamerr.h
# End Source File
# Begin Source File

SOURCE=.\src\psnames\psnames.c
# End Source File
# Begin Source File

SOURCE=.\src\psnames\pspic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\psnames\pspic.h
# End Source File
# Begin Source File

SOURCE=.\src\psnames\pstables.h
# End Source File
# End Group
# Begin Group "sfnt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sfnt\sfdriver.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfdriver.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sferrors.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfnt.c
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfntpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfntpic.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\sfobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttbdf.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttbdf.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttcmap.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttcmap.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttcmapc.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttkern.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttkern.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttload.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttmtx.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttmtx.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttpost.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttpost.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttsbit.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttsbit.h
# End Source File
# Begin Source File

SOURCE=.\src\sfnt\ttsbit0.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "smooth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\smooth\ftgrays.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftgrays.h
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftsmerrs.h
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftsmooth.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftsmooth.h
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftspic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\smooth\ftspic.h
# End Source File
# Begin Source File

SOURCE=.\src\smooth\smooth.c
# End Source File
# End Group
# Begin Group "truetype"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\truetype\truetype.c
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttdriver.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttdriver.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\tterrors.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttgload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttgload.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttgxvar.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttgxvar.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttinterp.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttinterp.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttpic.h
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttpload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\truetype\ttpload.h
# End Source File
# End Group
# Begin Group "type1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\type1\t1afm.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1afm.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1driver.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1driver.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1errors.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1gload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1gload.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1load.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1load.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1objs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1objs.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1parse.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1parse.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\t1tokens.h
# End Source File
# Begin Source File

SOURCE=.\src\type1\type1.c
# End Source File
# End Group
# Begin Group "bdf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bdf\bdf.c
# End Source File
# Begin Source File

SOURCE=.\src\bdf\bdf.h
# End Source File
# Begin Source File

SOURCE=.\src\bdf\bdfdrivr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\bdf\bdfdrivr.h
# End Source File
# Begin Source File

SOURCE=.\src\bdf\bdferror.h
# End Source File
# Begin Source File

SOURCE=.\src\bdf\bdflib.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "pcf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\pcf\pcf.c
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcf.h
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfdrivr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfdrivr.h
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcferror.h
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfread.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfread.h
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfutil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pcf\pcfutil.h
# End Source File
# End Group
# Begin Group "pfr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\pfr\pfr.c
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrcmap.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrcmap.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrdrivr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrdrivr.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrerror.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrgload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrgload.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrload.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrload.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrobjs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrobjs.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrsbit.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrsbit.h
# End Source File
# Begin Source File

SOURCE=.\src\pfr\pfrtypes.h
# End Source File
# End Group
# Begin Group "winfonts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\winfonts\fnterrs.h
# End Source File
# Begin Source File

SOURCE=.\src\winfonts\winfnt.c
# End Source File
# Begin Source File

SOURCE=.\src\winfonts\winfnt.h
# End Source File
# End Group
# Begin Group "raster"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\raster\ftmisc.h
# End Source File
# Begin Source File

SOURCE=.\src\raster\ftraster.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\raster\ftraster.h
# End Source File
# Begin Source File

SOURCE=.\src\raster\ftrend1.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\raster\ftrend1.h
# End Source File
# Begin Source File

SOURCE=.\src\raster\raster.c
# End Source File
# Begin Source File

SOURCE=.\src\raster\rasterrs.h
# End Source File
# Begin Source File

SOURCE=.\src\raster\rastpic.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\raster\rastpic.h
# End Source File
# End Group
# Begin Group "type42"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\type42\t42drivr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42drivr.h
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42error.h
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42objs.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42objs.h
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42parse.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42parse.h
# End Source File
# Begin Source File

SOURCE=.\src\type42\t42types.h
# End Source File
# Begin Source File

SOURCE=.\src\type42\type42.c
# End Source File
# End Group
# Begin Group "lzw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\lzw\ftlzw.c
# End Source File
# Begin Source File

SOURCE=.\src\lzw\ftzopen.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\lzw\ftzopen.h
# End Source File
# End Group
# Begin Group "gzip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\gzip\adler32.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\ftgzip.c
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infblock.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infblock.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infcodes.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infcodes.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\inffixed.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\inflate.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\inftrees.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\inftrees.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infutil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\infutil.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\zconf.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\zlib.h
# End Source File
# Begin Source File

SOURCE=.\src\gzip\zutil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\gzip\zutil.h
# End Source File
# End Group
# End Group
# Begin Group "builds"

# PROP Default_Filter ""
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\builds\win32\ftdebug.c
# End Source File
# End Group
# End Group
# End Target
# End Project
