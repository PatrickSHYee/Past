hello: winmain.o
	g++ winmain.o `sdl-config --libs` -o hello
winmain.o: winmain.cpp PoundDefs.h
	g++ -c winmain.cpp PoundDefs.h `sdl-config --libs`
