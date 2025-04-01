# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Nombre del ejecutable final
TARGET = programa

# Archivos fuente (los .cc reales; los .h son incluidos dentro)
SRCS = nif.cc main.cc

# Archivos objeto que se generarán
OBJS = $(SRCS:.cc=.o)

# Regla principal: construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar nif.o
nif.o: nif.cc nif.h
	$(CXX) $(CXXFLAGS) -c nif.cc

# Regla para compilar main.o
# Incluimos todos los .h que use main.cc
main.o: main.cc nif.h hashtable.h dispersionfunction.h explorationfunction.h sequence.h dynamicsequence.h staticsequence.h
	$(CXX) $(CXXFLAGS) -c main.cc

# Limpieza de archivos intermedios y el ejecutable
.PHONY: clean
clean:
	rm -f *.o $(TARGET)
