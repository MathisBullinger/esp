#include <iostream>
#include <cstddef>
#include <memory>
#include "./file.hpp"
#include "./record.hpp"

using namespace std;

int main() {
  File file{ "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Skyrim Special Edition\\Data\\Skyrim.esm" };

  int count = 0;

  while (!file.atEnd()) {
    Record { file };
    count++;

    if (count % 10000 == 0) std::cout << count << std::endl;
  }

  std::cout << count << std::endl;
  
  return 0;
}