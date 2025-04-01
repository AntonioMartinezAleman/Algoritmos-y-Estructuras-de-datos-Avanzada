# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -Wextra -std=c++11

# Archivos fuente
SRCS = BigUnsigned.cc BigInteger.cc main.cc

# Archivos objeto generados
OBJS = $(SRCS:.cc=.o)

# Nombre del ejecutable
TARGET = programa

# Regla principal para compilar todo
all: $(TARGET)

# Compilación del ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar archivos individuales
%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)