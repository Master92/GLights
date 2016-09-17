##  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation version 2.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License along
##  with this program; if not, write to the Free Software Foundation, Inc.,
##  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA,
##  or see see <http://gnu.org/licenses/gpl-2.0.txt>


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS) `pkg-config --cflags gtkmm-3.0`
CXXFLAGS = $(BASICOPTS) `pkg-config --cflags gtkmm-3.0`
CCADMIN = 


# Define the target directories.
BINDIR=bin
DISTDIR=dist


all: $(DISTDIR)/GLights

## Target: GLights
CPPFLAGS_GLights = \
	-Iincludes
OBJS =  \
	$(BINDIR)/main.o \
	$(BINDIR)/GlightsNewRoundDialog.o \
	$(BINDIR)/UpdateThread.o \
	$(BINDIR)/Communicator.o \
	$(BINDIR)/GlightsAboutDialog.o \
	$(BINDIR)/GlightsTimerDialog.o \
	$(BINDIR)/GlightsConnectDialog.o
USERLIBS = `pkg-config --libs gtkmm-3.0` $(SYSLIBS_GLights) 
LIBS =   
LDLIBS_GLights = $(USERLIBS)


# Link or archive
$(DISTDIR)/GLights: $(BINDIR) $(DISTDIR) $(OBJS) $(LIBS)
	$(LINK.cc) -o $@ $(OBJS) $(LDLIBS_GLights)


# Compile source files into .o files
$(BINDIR)/main.o: $(BINDIR) main.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ main.cpp

$(BINDIR)/GlightsNewRoundDialog.o: $(BINDIR) src/GlightsNewRoundDialog.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/GlightsNewRoundDialog.cpp

$(BINDIR)/UpdateThread.o: $(BINDIR) src/UpdateThread.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/UpdateThread.cpp

$(BINDIR)/Communicator.o: $(BINDIR) src/Communicator.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/Communicator.cpp

$(BINDIR)/GlightsAboutDialog.o: $(BINDIR) src/GlightsAboutDialog.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/GlightsAboutDialog.cpp

$(BINDIR)/GlightsTimerDialog.o: $(BINDIR) src/GlightsTimerDialog.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/GlightsTimerDialog.cpp

$(BINDIR)/GlightsConnectDialog.o: $(BINDIR) src/GlightsConnectDialog.cpp
	$(COMPILE.cc) $(CCFLAGS_GLights) $(CPPFLAGS_GLights) -o $@ src/GlightsConnectDialog.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(DISTDIR)/GLights \
		$(BINDIR)/main.o \
		$(BINDIR)/GlightsNewRoundDialog.o \
		$(BINDIR)/UpdateThread.o \
		$(BINDIR)/Communicator.o \
		$(BINDIR)/GlightsAboutDialog.o \
		$(BINDIR)/GlightsTimerDialog.o \
		$(BINDIR)/GlightsConnectDialog.o
	$(CCADMIN)
	rm -f -r $(BINDIR)
	rm -f -r $(DISTDIR)


# Create the target directory (if needed)
$(BINDIR):
	mkdir -p $(BINDIR)
	
$(DISTDIR):
	mkdir -p $(DISTDIR)
	cp GLights.glade $(DISTDIR)/.


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

