#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "nif.h"
#include "staticsequence.h"
#include "sortingmethods.h"

void show_help() {
  std::cout << "Uso: ./ordenacion -size <s> -ord <m> -init <i> [f] -trace <y|n>\n";
  std::cout << "Opciones:\n"
            << "  -size <s>     Tamaño de la secuencia\n"
            << "  -ord <m>      Método de ordenación: 1=Inserción, 2=Sacudida, 3=Quick, 4=Heap, 5=Shell\n"
            << "  -init <i> [f] Inicialización: manual | random | file <nombre_fichero>\n"
            << "  -trace <y|n>  Mostrar traza\n"
            << "  --help        Mostrar ayuda\n";
}

int main(int argc, char* argv[]) {
  if (argc < 9) {
    show_help();
    return 1;
  }

  int size = 0;
  int metodo = 0;
  std::string init_mode;
  std::string file_name;
  bool trace = false;
  float alfa_shell = 0.5;

  // Leer argumentos
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--help") {
      show_help();
      return 0;
    } else if (arg == "-size") {
      size = std::stoi(argv[++i]);
    } else if (arg == "-ord") {
      metodo = std::stoi(argv[++i]);
    } else if (arg == "-init") {
      init_mode = argv[++i];
      if (init_mode == "file" && i + 1 < argc) {
        file_name = argv[++i];
      }
    } else if (arg == "-trace") {
      std::string t = argv[++i];
      trace = (t == "y");
    }
  }

  staticSequence<nif> seq(size);

  if (init_mode == "manual") {
    std::cout << "Introduce " << size << " NIFs:\n";
    for (int i = 0; i < size; ++i) {
      long val;
      std::cin >> val;
      seq.insert(nif(val));
    }
  } else if (init_mode == "random") {
    for (int i = 0; i < size; ++i) {
      seq.insert(nif());
    }
  } else if (init_mode == "file") {
    std::ifstream file(file_name);
    long val;
    while (file >> val && !seq.isFull()) {
      seq.insert(nif(val));
    }
  } else {
    std::cerr << "Modo de inicialización no válido.\n";
    return 1;
  }

  if (trace) {
    std::cout << "Secuencia antes de ordenar:\n";
    for (unsigned i = 0; i < seq.size(); ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << "\n";
  }

  SortMethod<nif>* sorter = nullptr;
  switch (metodo) {
    case 1: sorter = new InsertionSort<nif>(seq); break;
    case 2: sorter = new ShakeSort<nif>(seq); break;
    case 3: sorter = new QuickSort<nif>(seq); break;
    case 4: sorter = new HeapSort<nif>(seq); break;
    case 5: sorter = new ShellSort<nif>(seq, alfa_shell); break;
    default:
      std::cerr << "Método de ordenación no válido.\n";
      return 1;
  }

  sorter->Sort();
  delete sorter;

  if (trace) {
    std::cout << "Secuencia después de ordenar:\n";
    for (unsigned i = 0; i < seq.size(); ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
