# Microsoft Developer Studio Project File - Name="RAPID" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RAPID - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RAPID.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RAPID.mak" CFG="RAPID - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RAPID - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RAPID - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RAPID - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(DANCE_DIR)/libinclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\WinNT\RAPID.lib"

!ELSEIF  "$(CFG)" == "RAPID - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Zi /O2 /I "$(DANCE_DIR)/libinclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\WinNT\RAPID.lib"

!ENDIF 

# Begin Target

# Name "RAPID - Win32 Release"
# Name "RAPID - Win32 Debug"
# Begin Source File

SOURCE=.\build.cxx
# End Source File
# Begin Source File

SOURCE=.\collide.cxx
# End Source File
# Begin Source File

SOURCE=.\lmderBound.c
# End Source File
# Begin Source File

SOURCE=.\matvec.h
# End Source File
# Begin Source File

SOURCE=.\moments.h
# End Source File
# Begin Source File

SOURCE=.\obb.h
# End Source File
# Begin Source File

SOURCE=.\overlap.cxx
# End Source File
# Begin Source File

SOURCE=.\overlap.h
# End Source File
# Begin Source File

SOURCE=.\RAPID.cxx
# End Source File
# Begin Source File

SOURCE=.\RAPID.h
# End Source File
# Begin Source File

SOURCE=.\RAPID_private.h
# End Source File
# Begin Source File

SOURCE=.\RAPID_version.h
# End Source File
# End Target
# End Project
