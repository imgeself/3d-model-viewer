# We are using GLEW and Gtkmm which C++ version of Gtk+ lib.
# GTK+ introduced the native GtkGLArea in 3.16.
# Check that we have at least that version:
ifneq ($(shell pkg-config --atleast-version=3.16 gtkmm-3.0 && echo 1 || echo 0),1)
	$(error $(shell  pkg-config --print-errors --atleast-version=3.16 gtkmm-3.0))
endif

# Compiler
CC := g++

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

# Targets
EXECUTABLE := 3d-object-viewer
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Final Paths
INSTALLBINDIR := /usr/local/bin

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS += $(shell pkg-config --cflags gtkmm-3.0)
CFLAGS += -std=c++11

LIBS += $(shell pkg-config --libs gtkmm-3.0)
LIBS += -lGL -lGLEW

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) -c -o $@ $<

$(TARGET) : $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIBS)

install:
	@echo "Installing $(EXECUTABLE)..."; cp $(TARGET) $(INSTALLBINDIR)

clean:
	@echo "Cleaning $(TARGET)..."; rm -r $(BUILDDIR) $(TARGETDIR)

uninstall:
	@echo "Uninstalling $(EXECUTABLE)..."; rm -r $(INSTALLBINDIR)/$(EXECUTABLE)

.PHONY: clean
