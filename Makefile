# @author Petr Flajsingr (xflajs00), Dominik Dvořák (xdvora1t)
# Makefile pro CLI a GUI rozhrani reversi

CFLAGS=-std=c++11 -Wall -Wextra -pedantic -o2
CXX=g++
QM=qmakefile
CLIOBJ=clifunctions.o aiplayer.o gameinfo.o reversicli.o savefiles.o
GUIFILES=aiplayer.cpp gameinfo.cpp main.cpp reversigui.cpp savefiles.cpp
CLINAME=hra2016-cli
GUINAME=hra2016
QMAKE=qmake

ifneq ("$(wildcard /usr/local/share/QT-5.5.1/5.5/gcc_64/bin/qmake)", "")
QMAKE="/usr/local/share/QT-5.5.1/5.5/gcc_64/bin/qmake"
LD_LIBRARY_PATH="/usr/local/share/QT-5.5.1/5.5/gcc_64/lib"
export LD_LIBRARY_PATH
endif

all: create-bin cli gui

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $*.cpp -o $*.o

create-bin:
	@mkdir -p ../bin
	@mkdir -p ../bin/saves

cli: $(CLIOBJ)
	$(CXX) $(FLAGS) $^ -o ../bin/$(CLINAME)

gui: $(GUIOBJ)
	$(QMAKE) -o qMakefile && make -f qMakefile
	mv reversi ../bin/hra2016

clean:
	rm -rf *.o
	make -f qMakefile clean

run-gui:
	cd ../bin && ./hra2016

run-cli:
	cd ../bin && ./hra2016-cli

run: all run-gui run-cli
