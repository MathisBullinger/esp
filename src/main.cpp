#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>
#include <memory>

int main() {
  std::string esmPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Skyrim Special Edition\\Data\\Skyrim.esm";

  auto file = fopen(esmPath.c_str(), "rb");

  if (!file) {
    std::cerr << "couldn't open file: " << esmPath << std::endl;
    return 0;
  }

  unsigned char recordType[4];
  std::uint32_t groupSize;
  std::uint8_t label[4];
  std::int32_t groupType;
  std::int16_t timeStamp;
  std::int16_t vci;
  std::uint32_t unknown;
  
  fread(recordType, 1, 4, file);
  fread(&groupSize, sizeof(groupSize), 1, file);
  fread(label, 1, 4, file);
  fread(&groupType, sizeof(groupType), 1, file);
  fread(&timeStamp, sizeof(timeStamp), 1, file);
  fread(&vci, sizeof(vci), 1, file);
  fread(&unknown, sizeof(unknown), 1, file);

  auto records = std::make_unique<std::uint8_t[]>(groupSize - 24);
  fread(records.get(), 1, groupSize - 24, file);
  

  std::cout << "record type: " << recordType << std::endl;
  std::cout << "group size: " << groupSize << std::endl;
  std::cout << "group type: " << groupType << std::endl;

  std::cout << "records:";
  for (auto i = 0; i < groupSize - 24; i++)
    std::cout << " " << (int)records.get()[i];
  std::cout << std::endl;

  return 0;
}