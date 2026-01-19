# * atlas * Texture atlas tool
# Copyright (C) 2026 Juliet Colman 

# Source files directory
SRCDIR := source
# Relies on lo-res library for blitting
LO_RES :=  ../lo-res
LO_RES_LIB_PATH := $(LO_RES)/build
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

# Target library name
TARGET := $(BUILDDIR)/atlas

# Flags for compiling
CXXFLAGS := -std=c++20 -Wall -I$(LO_RES)/include 

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Dependencies
DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin) # macOS
    # Add Mac-specific flags or configurations if needed
    LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT
    CXX := clang++
else ifeq ($(OS), Windows_NT) # Windows
    # Add Windows-specific flags or configurations if needed
else ifneq ("$(wildcard /proc/device-tree/model)","") # Raspberry Pi
    # Add Raspberry Pi-specific flags or configurations if needed
    CXXFLAGS += -DRASPBERRY_PI -DLO_RES_USE_FRAMEBUFFER
    CXX := g++
endif

# Default rule
all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ -L$(LO_RES_LIB_PATH) -llores 


# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR)/%.o: $(THIRD_PARTY_SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	@rm -rf $(TARGET) $(BUILDDIR)

-include $(DEPS)

.PHONY: all clean

