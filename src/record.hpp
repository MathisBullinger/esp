#pragma once

#include <string.h>
#include "./file.hpp"

using namespace std;

class Record {
public:
  Record(File& file) : file{file} {
    file.read(type[0], 4);
    file.read(size);
    if (getType() == "GRUP") size -= 24;
    file.read(flags);
    file.read(recordID);
    file.read(timeStamp);
    file.seekBy<uint16_t>();
    file.seekBy<uint16_t>();
    file.seekBy<uint16_t>();
    // data = file.readAlloc<uint8_t>(size);
    file.seekBy(size);
  };

  ~Record() {
    delete[] data;
  }

  static void skip(const File& file) {
    file.seekBy(4);
    auto size = file.read<uint32_t>();
    file.seekBy(10 + 2 * 3 + size);
  }

  void printInfo() const {
    cout << "Record of type " << getType() << " (" << size << " bytes)" <<  endl;
    cout << "record ID: " << recordID << endl;
    cout << "time stamp: " << getTime() << endl;
    cout << "flags:" << endl;
    printFlag(Flag::esm);
    printFlag(Flag::localized);
    printFlag(Flag::compressed);
    cout << endl;
  }

  enum class Flag : uint32_t {
    esm        = 0x00000001,
    localized  = 0x00000080,
    compressed = 0x00040000
  };

  bool getFlag(Flag flag) const {
    return flags & (uint32_t)flag;
  }

  std::string getTime() const {
    auto year = timeStamp >> 9;
    auto month = timeStamp >> 5 & 0xf;
    auto day = timeStamp & 0b11111;

    return to_string(year) + "/" + to_string(month) + "/" + to_string(day);
  }
  
  string getType() const {
    string strType;
    strType.append(type, 4);
    return strType;
  }

  auto getSize() const {
    return size;
  }
  
private:
  File& file;
  char type[4];
  uint32_t size = 0;
  uint32_t flags;
  uint32_t recordID;
  uint16_t timeStamp;
  uint8_t* data = nullptr;

  void printFlag(Flag flag) const {
    std::string label;

    switch (flag) {
      case Flag::esm:         label = "ESM:       "; break;
      case Flag::localized:   label = "localized: "; break;
      case Flag::compressed:  label = "compressed:"; break;
    };
    
    cout << "  " << label << " " << (getFlag(flag) == 1 ? "yes" : "no") << endl;
  }
};