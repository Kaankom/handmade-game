@echo off

mkdir ..\build
pushd ..\build
cl -Zi ..\code\game.cpp user32.lib
popd
