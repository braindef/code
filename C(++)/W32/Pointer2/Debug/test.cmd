@echo off
Pointer2
if errorlevel 2 goto zwei
if errorlevel 1 goto eins
if errorlevel 0 goto null

:zwei
echo Es wurde 2 zurück gegeben
goto ende

:eins
echo Es wurde 1 zurück gegeben
goto ende

:null
echo Es wurde 0 zurück gegeben
goto ende

:ende
Pause
