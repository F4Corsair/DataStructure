@echo off
gcc .\quickSortOptiIter.c -c
gcc ..\..\Iter\linkedStack.o .\quickSortOptiIter.o -o linkedStack
linkedStack.exe