# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Target executable name
TARGET = restaurant.exe

# Source files
SRCS = main.cpp \
       src/Ingredient.cpp \
       src/Produs.cpp \
       src/FelPrincipal.cpp \
       src/Desert.cpp \
       src/Bautura.cpp \
       src/Meniu.cpp \
       src/Comanda.cpp \
       src/Restaurant.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	@if exist $(TARGET) (del $(TARGET))
	@echo Cleaned!
