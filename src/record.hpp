#pragma once

#include <string.h>
#include "./file.hpp"

class Record {
public:
  Record(File& file);
  ~Record();

  enum class Flag : uint32_t {
    esm        = 0x00000001,
    localized  = 0x00000080,
    compressed = 0x00040000
  };

  static void skip(const File& file);
  void printInfo() const;

  bool getFlag(Flag flag) const;
  std::string getTime() const;
  std::string getType() const;
  uint32_t getSize() const;
  
private:
  File& file;
  char type[4];
  uint32_t size = 0;
  uint32_t flags;
  uint32_t recordID;
  uint16_t timeStamp;
  uint8_t* data = nullptr;

  void printFlags() const;
  void printFlag(Flag flag) const;
};