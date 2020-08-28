@ECHO OFF

set PROJECTDIR=%cd%\..
set UEDIR=D:\ue_engine\engines\UE_4.25\UE_4.25\Engine

cd /d "%UEDIR%\Build"
"%UEDIR%\Build\BatchFiles\Build.bat" GrasshopperAREditor Win64 Development -Project="%PROJECTDIR%\GrasshopperAR.uproject" -WaitMutex -FromMsBuild

PAUSE