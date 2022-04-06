#include <iostream>
#include <cstddef>
#include <memory>
#include "./file.hpp"

using namespace std;

int main() {
  File file{ "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Skyrim Special Edition\\Data\\Skyrim.esm" };

  unsigned char recordType[4];
  // std::uint32_t groupSize;
  uint8_t label[4];
  // std::int32_t groupType;
  // std::int16_t timeStamp;
  // std::int16_t vci;
  // std::uint32_t unknown;
  
  // fread(recordType, 1, 4, file);
  // fread(&groupSize, sizeof(groupSize), 1, file);
  // fread(label, 1, 4, file);
  // fread(&groupType, sizeof(groupType), 1, file);
  // fread(&timeStamp, sizeof(timeStamp), 1, file);
  // fread(&vci, sizeof(vci), 1, file);
  // fread(&unknown, sizeof(unknown), 1, file);

  // auto records = std::make_unique<std::uint8_t[]>(groupSize - 24);
  // fread(records.get(), 1, groupSize - 24, file);
  
  file.read(recordType);
  auto size = file.read<uint32_t>();
  auto flags = file.read<uint32_t>();
  auto recordID = file.read<uint32_t>();
  auto timeStamp = file.read<uint16_t>();
  auto vcInfo = file.read<uint16_t>();
  auto internalVersion = file.read<uint16_t>();
  file.seekBy<uint16_t>();

  cout << "record type: " << recordType << endl;
  cout << "size: " << size << endl;
  
  return 0;
}