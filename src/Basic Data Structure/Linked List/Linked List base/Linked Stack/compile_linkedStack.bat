@echo off
gcc .\linkedStack.c -c
gcc .\linkedStack.o ..\linkedList.o -o linkedStack
linkedStack.exe