#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <bit>

#define TEST

class File {
public:
  File(const std::string& path) {
    file = fopen(path.c_str(), "rb");
    if (!file) std::cerr << "couldn't open file: " << path << std::endl;
  };

  ~File() {
    close();
  }

  void close() {
    if (file) fclose(file);
    file = nullptr;
  }

  template <typename T>
  void read(T& data, int count = 1) const {
    readData(&data, count);
  }

  template <typename T>
  T read() const {
    T data;
    fread(&data, sizeof (T), 1, file);
    return data;
  }

  template <typename T>
  T* readAlloc() const {
    T* data = new T();
    fread(data, sizeof (T), 1, file);
    return data;
  }

  template <typename T>
  T* readAlloc(int size) const {
    T* data = new T[size];
    fread(data, sizeof (T), size, file);
    return data;
  }

  void seek(const long position) const {
    fseek(file, position, SEEK_SET);
  }

  void seekBy(const long offset) const {
    fseek(file, offset, SEEK_CUR);
  }

  template <typename T>
  void seekBy() const {
    fseek(file, sizeof (T), SEEK_CUR);
  }

  bool atEnd() {
    return feof(file);
  }

private:
  FILE* file;

  template <typename T>
  void readData(T* mem, size_t elementCount) const {
    if constexpr (std::endian::native == std::endian::big)
      fread(mem, sizeof (T), elementCount, file);
    else
      readLittleEndian(mem, elementCount);
  }

  template <typename T>
  void readLittleEndian(T* mem, size_t elementCount) const {
    T* value = new T();
    for (size_t i = 0; i < elementCount; i++) {
      fread(value, sizeof (T), 1, file);
      byteSwap(value, mem + i);
    }
  }

  template <typename T>
  static void byteSwap(T* source, T* dest) {
    if constexpr (sizeof (T) == 1) {
      *dest = *source;
      return;
    }

    auto bytesSource = (uint8_t*)(void*)(source);
    auto bytesDest = (uint8_t*)(void*)(dest);

    for (size_t i = 0; i < sizeof (T); i++)
      bytesDest[i] = bytesSource[sizeof (T) - i - 1];
  }
};