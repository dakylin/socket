MODULE=GetTime
CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

#HEADER_PATH = -I./include/
#LIB_PATH = -L./lib/

#LIBS = -lpthread
#ODBCROOT=/ODBC
#INC=$(ODBCROOT)/include
#HEADER_PATH=-I$(INC) ./
#LIB_PATH =-L$(ODBCROOT)/lib
HEADER_PATH=-I./

VERSION = 1.0.0.1
TARGET = $(MODULE).$(VERSION)

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LIB_PATH) $(LIBS)

$(OBJS):%.o : %.cc
	$(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)

clean:
	$(RM) $(TARGET) *.o 