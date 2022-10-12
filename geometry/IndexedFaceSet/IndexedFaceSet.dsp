# Microsoft Developer Studio Project File - Name="IndexedFaceSet" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=IndexedFaceSet - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IndexedFaceSet.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IndexedFaceSet.mak" CFG="IndexedFaceSet - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IndexedFaceSet - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IndexedFaceSet - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IndexedFaceSet - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(DANCE_DIR)/libinclude" /I "$(DANCE_DIR)/src" /I "$(DANCE_DIR)/VCOLLIDE/RAPID" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_IMPORTING" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 dance.lib rapid.lib minpack.lib glutShared32.lib opengl32.lib tcl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcd" /nodefaultlib:"libc" /out:"..\..\plugins\WinNT\IndexedFaceSet.dll" /implib:"../../lib/WinNT/IndexedFaceSet.lib" /libpath:"../../lib/WinNT"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "IndexedFaceSet - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "IndexedF"
# PROP BASE Intermediate_Dir "IndexedF"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(DANCE_DIR)/libinclude" /I "$(DANCE_DIR)/VCOLLIDE/RAPID" /I "$(DANCE_DIR)/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_IMPORTING" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 minpack.lib RAPID.lib dance.lib tcl.lib opengl32.lib dance.lib rapid.lib minpack.lib glutShared32.lib opengl32.lib tcl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /debug /machine:I386 /nodefaultlib:"LIBCD" /nodefaultlib:"library" /nodefaultlib:"libc" /nodefaultlib:"linbcmtd" /out:"../../plugins/WinNT/IndexedFaceSet.dll" /implib:"../../lib/WinNT/IndexedFaceSet.lib" /libpath:"../../lib/WinNT"

!ENDIF 

# Begin Target

# Name "IndexedFaceSet - Win32 Release"
# Name "IndexedFaceSet - Win32 Debug"
# Begin Source File

SOURCE=.\IndexedFaceSet.cxx
# End Source File
# Begin Source File

SOURCE=.\IndexedFaceSet.h
# End Source File
# Begin Source File

SOURCE=.\jacobi.cxx
# End Source File
# Begin Source File

SOURCE=.\Material.cxx
# End Source File
# Begin Source File

SOURCE=.\Material.h
# End Source File
# Begin Source File

SOURCE=.\matvec.h
# End Source File
# Begin Source File

SOURCE=.\moments.h
# End Source File
# Begin Source File

SOURCE=.\Obj.cxx
# End Source File
# Begin Source File

SOURCE=.\Ply.cxx
# End Source File
# Begin Source File

SOURCE=.\Vrml.cxx
# End Source File
# Begin Source File

SOURCE=.\WingedEdge.cxx
# End Source File
# Begin Source File

SOURCE=.\WingedEdge.h
# End Source File
# End Target
# End Project
