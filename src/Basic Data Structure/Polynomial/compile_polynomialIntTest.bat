@echo off
gcc .\polynomial_int.c .\polynomialIntTest.c -c
gcc .\polynomial_int.o .\polynomialIntTest.o -o polynomialIntTest
polynomialIntTest.exe