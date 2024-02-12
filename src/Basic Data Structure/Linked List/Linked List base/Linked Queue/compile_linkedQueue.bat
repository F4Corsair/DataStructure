@echo off
gcc .\linkedQueue.c -c
gcc .\linkedQueue.o ..\linkedList.o -o linkedQueue
linkedQueue.exe