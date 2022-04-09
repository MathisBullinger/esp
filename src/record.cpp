#include "./record.hpp"

Record::Record(File& file) : file{file} {
  filePos = file.getPosition();
  file.read(type[0], 4);
  file.read(size);
  if (isGroup()) size -= 24;
  file.read(flags);
  file.read(recordID);
  file.read(timeStamp);
  file.seekBy<uint16_t>();
  file.seekBy<uint16_t>();
  file.seekBy<uint16_t>();
  // data = file.readAlloc<uint8_t>(size);
  file.seekBy(size);
};

Record::~Record() {
  delete[] data;
}

void Record::skip(const File& file) {
  file.seekBy(4);
  auto size = file.read<uint32_t>();
  file.seekBy(10 + 2 * 3 + size);
}

bool Record::getFlag(Flag flag) const {
  return flags & (uint32_t)flag;
}

std::string Record::getTime() const {
  auto year = timeStamp >> 9;
  auto month = timeStamp >> 5 & 0xf;
  auto day = timeStamp & 0b11111;

  return std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
}

std::string Record::getType() const {
  std::string strType;
  strType.append(type, 4);
  return strType;
}

uint32_t Record::getSize() const {
  return size;
}

bool Record::isGroup() const {
  return type[0] == 'G' && type[1] == 'R' && type[2] == 'U' && type[3] == 'P';
}