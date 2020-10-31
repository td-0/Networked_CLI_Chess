# Makefile for CLI_Chess

FLAGS   = -Wall -Wextra
COMPILE = g++ -g ${FLAGS}
MODULES = board piece
HEADERS = ${MODULES:=.h}
SOURCE  = ${MODULES:=.cpp} main.cpp
EXEC    = chess
OBJECTS = ${SOURCE:.cpp=.o}

${EXEC} : ${OBJECTS}
	${COMPILE} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILE} -c ${SOURCE}

clean:
	rm -f ${EXEC} ${OBJECTS}
