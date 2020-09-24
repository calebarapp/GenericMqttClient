CXX = g++
EXENAME = GenericMqttClient

#	Directories
HDIR = ./header
LDIR = ./lib
ODIR = ./obj
SDIR = ./source
BIN = ./bin
DEBUGDIR = $(BIN)/debug
RELDIR = $(BIN)/release

# Project Files
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Includes
DEPS = $(HDIR)/MqttManager.h
LIBS = -lpaho-mqtt3c

#flags
CXXFLAGS = -Wall -I$(HDIR) -L$(LDIR)
# DEBUGFLAGS = $(CXXFLAGS) -g

# Object files
$(SDIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

# Release
release: prep $(RELDIR)/$(EXENAME) objclean
$(RELDIR)/$(EXENAME): $(OBJ)
	$(CXX) -o $@ $^  $(CXXFLAGS) $(LIBS) 

# Debug
debug: prep $(DEBUGDIR)/$(EXENAME) objclean
$(DEBUGDIR)/$(EXENAME): $(OBJ)
	$(CXX) -g -o $@ $^ $(CXXFLAGS)  $(LIBS)

#
#	Other Rules
#
all: clean debug release objclean

prep:
	@mkdir -p $(DEBUGDIR) $(RELDIR)

objclean:
	rm -r $(SDIR)/*.o

clean:
	rm -rf $(BIN)/*
