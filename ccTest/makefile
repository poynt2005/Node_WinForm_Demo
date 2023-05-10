cc = gcc
cxx = g++
cflags = -I"../csdll/CallWinForm/CallWinForm"
ldflags = -L"../csdll/CallWinForm/x64/Release"
libs = -lCallWinForm

test:
	$(cxx) $(cflags) -c test.cc -o test.o
	$(cxx) $(ldflags) test.o -o test.exe $(libs)