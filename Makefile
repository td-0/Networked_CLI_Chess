# Makefile for CLI_Chess

FLAGS   = -Wall -Wextra
COMPILE = g++ -g ${FLAGS}
MODULES = board piece network
HEADERS = ${MODULES:=.h}
SOURCE  = ${MODULES:=.cpp} main.cpp
EXEC    = cli-chess
OBJECTS = ${SOURCE:.cpp=.o}

${EXEC} : ${OBJECTS}
	${COMPILE} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILE} -c ${SOURCE}

clean:
	rm -f ${EXEC} ${OBJECTS}
