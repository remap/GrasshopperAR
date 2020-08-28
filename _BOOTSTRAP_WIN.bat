@ECHO OFF

set PROJECTDIR=%cd%
:: set UEDIR=D:\ue_engine\engines\UE_4.25\UE_4.25\Engine
set UEDIR=C:\Program Files\Epic Games\UE_4.25\Engine

FOR /F "tokens=1 USEBACKQ" %%F IN (`git config user.name`) DO (
SET _STRING=%%F
)
:: ECHO %_STRING%

setlocal enabledelayedexpansion
set "_UCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ"
set "_LCASE=abcdefghijklmnopqrstuvwxyz"

for /l %%a in (0,1,25) do (
   call set "_FROM=%%_UCASE:~%%a,1%%
   call set "_TO=%%_LCASE:~%%a,1%%
   call set "_STRING=%%_STRING:!_FROM!=!_TO!%%
)

git checkout -b "%_STRING%-dev"
endlocal

"%UEDIR%/Binaries/DotNET/UnrealBuildTool.exe" -projectfiles -project="%PROJECTDIR%\GrasshopperAR.uproject" -game -rocket -progress

cd "%PROJECTDIR%/scripts"
CMD /C "build.bat"

cd /d "%PROJECTDIR%"
"%UEDIR%\Binaries\Win64\UE4Editor.exe" "%PROJECTDIR%\GrasshopperAR.uproject"

:: "%UEDIR%\Build\BatchFiles" BuildCookRun -nocompileeditor -nop4 -project="%PROJECTDIR%\GrasshopperAR.uproject" -cook -stage -archive -archivedirectory="%PROJECTDIR%\Packaged" -package -clientconfig=Shipping -ue4exe=%UEDIR%\Binaries\Win64\UE4Editor-Cmd.exe -clean -pak -prereqs -nodebuginfo -targetplatform=Win64 -build -utf8output -compile

PAUSE
