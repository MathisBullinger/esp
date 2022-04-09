#pragma once

#include <string.h>
#include <utility>
#include "./file.hpp"

typedef std::pair<int16_t, int16_t> Coords;

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
  void printInfo();

  bool getFlag(Flag flag) const;
  std::string getTime() const;
  std::string getType() const;
  uint32_t getSize() const;
  std::string getGroupName() const;
  bool isGroup() const;
  
  template <typename T>
  T getLabel() {
    if constexpr (std::is_same<T, std::string>::value)
      return reinterpret_cast<char*>(&flags);

    return *reinterpret_cast<T*>(&flags);
  }
  
private:
  File& file;
  long filePos;
  
  char type[4];
  uint32_t size = 0;
  uint32_t flags;
  uint32_t recordID;
  uint16_t timeStamp;
  uint8_t* data = nullptr;

  void printFlags();
  void printFlag(Flag flag);
  void printLabel();
};