@echo off
gcc .\sparseMatrixTest.c .\sparseMatrix.c -c
gcc .\sparseMatrixTest.o .\sparseMatrix.o -o sparseMatrixTest
sparseMatrixTest.exe