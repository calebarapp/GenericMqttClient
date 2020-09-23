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
OBJ = $(SRC:.c=.o)

# Includes
DEPS = $(HDIR)/MqttManager.h
LIBS = -lpaho-mqtt3c

#flags
CXXFLAGS = -Wall -I$(HDIR) -L$(LDIR)
DEBUGFLAGS = $(CXXFLAGS) -g

# Object files
$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

# Release
release: prep $(RELDIR)/$(EXENAME)
$(RELDIR)/$(EXENAME): $(OBJ)
	$(CXX) -o $@ $^  $(CXXFLAGS) $(LIBS) 

# Debug
debug: prep $(DEBUGDIR)/$(EXENAME)
$(DEBUGDIR)/$(EXENAME): $(OBJ)
	$(CXX) -o $@ $^  $(DEBUGFLAGS) $(LIBS) 

#
#	Other Rules
#
all: clean debug release

prep:
	@mkdir -p $(DEBUGDIR) $(RELDIR)

clean:
	rm -rf $(BIN)/*