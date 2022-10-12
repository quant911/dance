# Microsoft Developer Studio Project File - Name="dance" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dance - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dance.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dance.mak" CFG="dance - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dance - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dance - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dance - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(DANCE_DIR)/libinclude" /I "$(DANCE_DIR)/VCOLLIDE/src" /I "$(DANCE_DIR)/VCOLLIDE/RAPID" /D "NDEBUG" /D "_IMPORTING2" /D "WIN32" /D "_WINDOWS" /D "_EXPORTING_DANCE_CORE" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vcollide.lib rapid.lib minpack.lib glutShared32.lib glu32.lib tk.lib tcl.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcd" /out:"../bin/dance.exe" /implib:"$(DANCE_DIR)/lib/WinNT/dance.lib" /libpath:"$(DANCE_DIR)/lib/WinNT"
# SUBTRACT LINK32 /profile /pdb:none

!ELSEIF  "$(CFG)" == "dance - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dance___"
# PROP BASE Intermediate_Dir "dance___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "$(DANCE_DIR)/libinclude" /I "$(DANCE_DIR)/VCOLLIDE/src" /I "$(DANCE_DIR)/VCOLLIDE/RAPID" /D "_DEBUG" /D "_IMPROTING2" /D "WIN32" /D "_WINDOWS" /D "_EXPORTING_DANCE_CORE" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vcollide.lib rapid.lib minpack.lib glutShared32.lib glu32.lib tk.lib tcl.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd" /out:"../bin/dance.exe" /implib:"$(DANCE_DIR)/lib/WinNT/dance.lib" /libpath:"$(DANCE_DIR)/lib/WinNT"
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "dance - Win32 Release"
# Name "dance - Win32 Debug"
# Begin Source File

SOURCE=.\APPcommands.cxx
# End Source File
# Begin Source File

SOURCE=.\Ball.cxx
# End Source File
# Begin Source File

SOURCE=.\Ball.h
# End Source File
# Begin Source File

SOURCE=.\BallAux.cxx
# End Source File
# Begin Source File

SOURCE=.\BallAux.h
# End Source File
# Begin Source File

SOURCE=.\BallMath.cxx
# End Source File
# Begin Source File

SOURCE=.\BallMath.h
# End Source File
# Begin Source File

SOURCE=.\BoundingBox.cxx
# End Source File
# Begin Source File

SOURCE=.\BoundingBox.h
# End Source File
# Begin Source File

SOURCE=.\CoordSystem.cxx
# End Source File
# Begin Source File

SOURCE=.\CoordSystem.h
# End Source File
# Begin Source File

SOURCE=.\DActuator.cxx
# End Source File
# Begin Source File

SOURCE=.\DActuator.h
# End Source File
# Begin Source File

SOURCE=.\dance.cxx
# End Source File
# Begin Source File

SOURCE=.\dance.h
# End Source File
# Begin Source File

SOURCE=.\DanceObject.cxx
# End Source File
# Begin Source File

SOURCE=.\DanceObject.h
# End Source File
# Begin Source File

SOURCE=.\DanceObjectList.cxx
# End Source File
# Begin Source File

SOURCE=.\DanceObjectList.h
# End Source File
# Begin Source File

SOURCE=.\DanceObjectRefList.cxx
# End Source File
# Begin Source File

SOURCE=.\DanceObjectRefList.h
# End Source File
# Begin Source File

SOURCE=.\danceTcl.cxx
# End Source File
# Begin Source File

SOURCE=.\danceTcl.h
# End Source File
# Begin Source File

SOURCE=.\defs.h
# End Source File
# Begin Source File

SOURCE=.\DGeometry.cxx
# End Source File
# Begin Source File

SOURCE=.\DGeometry.h
# End Source File
# Begin Source File

SOURCE=.\DLight.cxx
# End Source File
# Begin Source File

SOURCE=.\DLight.h
# End Source File
# Begin Source File

SOURCE=.\DSimulator.cxx
# End Source File
# Begin Source File

SOURCE=.\DSimulator.h
# End Source File
# Begin Source File

SOURCE=.\DSimulatorManager.cxx
# End Source File
# Begin Source File

SOURCE=.\DSimulatorManager.h
# End Source File
# Begin Source File

SOURCE=.\DSystem.cxx
# End Source File
# Begin Source File

SOURCE=.\DSystem.h
# End Source File
# Begin Source File

SOURCE=.\DView.cxx
# End Source File
# Begin Source File

SOURCE=.\DView.h
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\GLutilities.cxx
# End Source File
# Begin Source File

SOURCE=.\GLutilities.h
# End Source File
# Begin Source File

SOURCE=.\main.cxx
# End Source File
# Begin Source File

SOURCE=.\MonitorPoints.cxx
# End Source File
# Begin Source File

SOURCE=.\MonitorPoints.h
# End Source File
# Begin Source File

SOURCE=.\myMath.cxx
# End Source File
# Begin Source File

SOURCE=.\myMath.h
# End Source File
# Begin Source File

SOURCE=.\PlugIn.h
# End Source File
# Begin Source File

SOURCE=.\PlugInManager.cxx
# End Source File
# Begin Source File

SOURCE=.\PlugInManager.h
# End Source File
# Begin Source File

SOURCE=.\Proximity.cxx
# End Source File
# Begin Source File

SOURCE=.\Proximity.h
# End Source File
# Begin Source File

SOURCE=.\Quaternion.cxx
# End Source File
# Begin Source File

SOURCE=.\Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\SimulatorEvents.cxx
# End Source File
# Begin Source File

SOURCE=.\SimulatorEvents.h
# End Source File
# Begin Source File

SOURCE=.\vector.cxx
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# Begin Source File

SOURCE=.\ViewManager.cxx
# End Source File
# Begin Source File

SOURCE=.\ViewManager.h
# End Source File
# Begin Source File

SOURCE=.\WinDlfcn.c
# End Source File
# Begin Source File

SOURCE=.\WinDlfcn.h
# End Source File
# End Target
# End Project
