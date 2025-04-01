#include "nif.h"
#include "hashtable.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <limits>

int readIntArg(int i, int argc, char* argv[]) {
  if (i+1 >= argc) {
    throw std::runtime_error("argumento incompleto");
  }
  return std::atoi(argv[i+1]);
}

void printUsage(const char* progName) {
  std::cout
    << "Uso: " << progName << " [opciones]\n"
    << "  -ts <s>       Tamaño de la tabla (p.ej. 10)\n"
    << "  -hash <type>  'open' o 'close'\n"
    << "  -fd <f>       Funcion de dispersion: 'mod', 'sum', 'rand'\n"
    << "  -bs <s>       blockSize (solo para 'close')\n"
    << "  -fe <f>       Funcion de exploracion: 'lin', 'quad', 'double', 're'\n"
    << "\nEjemplo:\n"
    << "  " << progName << " -ts 10 -hash close -fd sum -bs 3 -fe quad\n"
    << "O use '--help' o '-h' para ver esta ayuda.\n";
}

int main(int argc, char* argv[]) {
  std::srand(std::time(nullptr));

  // Si no se pasan argumentos, podría mostrarse la ayuda:
  if (argc == 1) {
    printUsage(argv[0]);
    return 0;
  }

  unsigned tableSize = 10;
  bool isOpen = false;
  std::string fdName = "mod";
  unsigned blockSize = 3;
  std::string feName = "lin";

  // Parseo de argumentos
  for (int i = 1; i < argc; i++) {
    // Si el usuario pone -h o --help, mostramos la ayuda y salimos
    if (!std::strcmp(argv[i], "-h") || !std::strcmp(argv[i], "--help")) {
      printUsage(argv[0]);
      return 0;
    }

    if (!std::strcmp(argv[i], "-ts")) {
      tableSize = readIntArg(i, argc, argv);
      i++;
    } else if (!std::strcmp(argv[i], "-hash")) {
      if (i+1 >= argc) throw std::runtime_error("Falta parametro en -hash");
      if (!std::strcmp(argv[i+1], "open")) {
        isOpen = true;
      } else if (!std::strcmp(argv[i+1], "close")) {
        isOpen = false;
      } else {
        throw std::runtime_error("Valor desconocido para -hash");
      }
      i++;
    } else if (!std::strcmp(argv[i], "-fd")) {
      if (i+1 >= argc) throw std::runtime_error("Falta parametro en -fd");
      fdName = argv[i+1];
      i++;
    } else if (!std::strcmp(argv[i], "-bs")) {
      blockSize = readIntArg(i, argc, argv);
      i++;
    } else if (!std::strcmp(argv[i], "-fe")) {
      if (i+1 >= argc) throw std::runtime_error("Falta parametro en -fe");
      feName = argv[i+1];
      i++;
    } else {
      std::cerr << "Argumento desconocido: " << argv[i] << "\n";
      printUsage(argv[0]);
      return 1;
    }
  }

  DispersionFunction<nif>* fdPtr = nullptr;
  if (fdName == "mod") {
    fdPtr = new ModuloDispersion<nif>(tableSize);
  } else if (fdName == "sum") {
    fdPtr = new SumDispersion<nif>(tableSize);
  } else if (fdName == "rand") {
    fdPtr = new RandomDispersion<nif>(tableSize);
  } else {
    std::cerr << "Funcion de dispersion desconocida: " << fdName << "\n";
    printUsage(argv[0]);
    return 1;
  }

  ExplorationFunction<nif>* fePtr = nullptr;
  if (!isOpen) {
    if (feName == "lin") {
      fePtr = new LinearExploration<nif>();
    } else if (feName == "quad") {
      fePtr = new QuadraticExploration<nif>();
    } else if (feName == "double") {
      fePtr = new DoubleDispersion<nif>(*fdPtr);
    } else if (feName == "re") {
      fePtr = new ReDispersion<nif>();
    } else {
      std::cerr << "Funcion de exploracion desconocida: " << feName << "\n";
      printUsage(argv[0]);
      return 1;
    }
  }

  Sequence<nif>* myTable = nullptr;
  try {
    if (isOpen) {
      myTable = new HashTable<nif, dynamicSequence<nif>>(tableSize, *fdPtr);
    } else {
      myTable = new HashTable<nif, staticSequence<nif>>(tableSize, *fdPtr, *fePtr, blockSize);
    }
  } catch (std::exception& e) {
    std::cerr << "Error al crear la tabla: " << e.what() << "\n";
    return 1;
  }

  while (true) {
    std::cout << "\nMENU:\n"
              << "  1) Insertar un nif\n"
              << "  2) Buscar un nif\n"
              << "  0) Salir\n"
              << "Opcion: ";

    int opcion;
    if (!(std::cin >> opcion)) {
      std::cerr << "Entrada inválida. Intente de nuevo.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    switch(opcion) {
      case 0: {
        std::cout << "Saliendo...\n";
        delete myTable;
        delete fePtr;
        delete fdPtr;
        return 0;
      }
      case 1: {
        std::cout << "Ingrese valor numerico del nif: ";
        long val;
        if (!(std::cin >> val)) {
          std::cerr << "Entrada inválida. Operacion cancelada.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        nif nuevo(val);
        if (myTable->insert(nuevo)) {
          std::cout << " -> Insertado correctamente.\n";
        } else {
          std::cout << " -> No se pudo insertar (tabla llena o error).\n";
        }
        break;
      }
      case 2: {
        std::cout << "Ingrese valor numerico del nif: ";
        long val;
        if (!(std::cin >> val)) {
          std::cerr << "Entrada inválida. Operacion cancelada.\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          break;
        }
        nif buscado(val);
        if (myTable->search(buscado)) {
          std::cout << " -> Encontrado en la tabla.\n";
        } else {
          std::cout << " -> No esta en la tabla.\n";
        }
        break;
      }
      default: {
        std::cout << "Opcion invalida.\n";
        break;
      }
    }
  }
}