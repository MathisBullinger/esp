#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

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
  void read(T& data) const {
    fread(data, sizeof (T), 1, file);
  }

  template <typename T>
  T read() const {
    T data;
    fread(&data, sizeof (T), 1, file);
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

private:
  FILE* file;
};