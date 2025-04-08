#ifndef SORTINGMETHODS_H
#define SORTINGMETHODS_H

#include "staticsequence.h"
#include <algorithm>

// FUNCIONES PLANTILLA DE ORDENACIÓN

template <class Key>
void insertionSort(staticSequence<Key>& seq, unsigned size) {
  for (unsigned i = 1; i < size; ++i) {
    Key x = seq[i];
    int j = i - 1;
    while (j >= 0 && x < seq[j]) {
      seq[j + 1] = seq[j];
      j--;
    }
    seq[j + 1] = x;
  }
}

template <class Key>
void shakeSort(staticSequence<Key>& seq, unsigned size) {
  unsigned ini = 1;
  unsigned fin = size - 1;
  unsigned cam = size - 1;

  while (ini < fin) {
    for (int j = fin; j >= (int)ini; j--) {
      if (seq[j] < seq[j - 1]) {
        std::swap(seq[j], seq[j - 1]);
        cam = j;
      }
    }
    ini = cam + 1;

    for (unsigned j = ini; j <= fin; j++) {
      if (seq[j] < seq[j - 1]) {
        std::swap(seq[j], seq[j - 1]);
        cam = j;
      }
    }
    fin = cam - 1;
  }
}

template <class Key>
void quickSort(staticSequence<Key>& seq, int ini, int fin) {
  int i = ini;
  int j = fin;
  Key pivot = seq[(ini + fin) / 2];

  while (i <= j) {
    while (seq[i] < pivot) i++;
    while (seq[j] > pivot) j--;
    if (i <= j) {
      std::swap(seq[i], seq[j]);
      i++;
      j--;
    }
  }
  if (ini < j) quickSort(seq, ini, j);
  if (i < fin) quickSort(seq, i, fin);
}

template <class Key>
void baja(staticSequence<Key>& seq, unsigned i, unsigned n) {
  while (2 * i <= n) {
    unsigned h1 = 2 * i;
    unsigned h2 = h1 + 1;
    unsigned h = h1;
    if (h2 <= n && seq[h2 - 1] > seq[h1 - 1]) h = h2;
    if (seq[h - 1] <= seq[i - 1]) break;
    std::swap(seq[i - 1], seq[h - 1]);
    i = h;
  }
}

template <class Key>
void heapSort(staticSequence<Key>& seq, unsigned size) {
  for (int i = size / 2; i > 0; --i)
    baja(seq, i, size);
  for (int i = size; i > 1; --i) {
    std::swap(seq[0], seq[i - 1]);
    baja(seq, 1, i - 1);
  }
}

template <class Key>
void shellSort(staticSequence<Key>& seq, unsigned size, float alfa) {
  unsigned delta = size * alfa;
  while (delta > 0) {
    for (unsigned i = delta; i < size; ++i) {
      Key temp = seq[i];
      int j = i;
      while (j >= (int)delta && temp < seq[j - delta]) {
        seq[j] = seq[j - delta];
        j -= delta;
      }
      seq[j] = temp;
    }
    delta = delta * alfa;
  }
}

// CLASE BASE ABSTRACTA PARA ORDENACIÓN

template <class Key>
class SortMethod {
protected:
  staticSequence<Key>& seq_;
public:
  SortMethod(staticSequence<Key>& seq) : seq_(seq) {}
  virtual void Sort() = 0;
  virtual ~SortMethod() {}
};

// CLASES DERIVADAS PARA CADA ALGORITMO

template <class Key>
class InsertionSort : public SortMethod<Key> {
public:
  InsertionSort(staticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    insertionSort(this->seq_, this->seq_.size());
  }
};

template <class Key>
class ShakeSort : public SortMethod<Key> {
public:
  ShakeSort(staticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    shakeSort(this->seq_, this->seq_.size());
  }
};

template <class Key>
class QuickSort : public SortMethod<Key> {
public:
  QuickSort(staticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    quickSort(this->seq_, 0, this->seq_.size() - 1);
  }
};

template <class Key>
class HeapSort : public SortMethod<Key> {
public:
  HeapSort(staticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    heapSort(this->seq_, this->seq_.size());
  }
};

template <class Key>
class ShellSort : public SortMethod<Key> {
private:
  float alfa_;
public:
  ShellSort(staticSequence<Key>& seq, float alfa) : SortMethod<Key>(seq), alfa_(alfa) {}
  void Sort() override {
    shellSort(this->seq_, this->seq_.size(), alfa_);
  }
};

#endif