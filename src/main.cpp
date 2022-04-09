#include <iostream>
#include <cstddef>
#include <memory>
#include "./file.hpp"
#include "./record.hpp"

using namespace std;

int main() {
  // File file{ "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Skyrim Special Edition\\Data\\Skyrim.esm" };
  File file{ "/mnt/c/Program Files (x86)/Steam/steamapps/common/Skyrim Special Edition/Data/Skyrim.esm" };

  while (!file.atEnd()) Record{file}.printInfo();

  return 0;
}