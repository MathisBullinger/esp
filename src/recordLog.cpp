#include "./record.hpp"

using namespace std;

void Record::printInfo() const {
  cout << "Record of type " << getType() << " (" << size << " bytes)" <<  endl;
  cout << "record ID: " << recordID << endl;
  cout << "time stamp: " << getTime() << endl;
  cout << endl;
}

void Record::printFlags() const {
  cout << "flags:" << endl;
  printFlag(Flag::esm);
  printFlag(Flag::localized);
  printFlag(Flag::compressed);
}

void Record::printFlag(Flag flag) const {
  std::string label;
  switch (flag) {
    case Flag::esm:         label = "ESM:       "; break;
    case Flag::localized:   label = "localized: "; break;
    case Flag::compressed:  label = "compressed:"; break;
  };
  
  cout << "  " << label << " " << (getFlag(flag) == 1 ? "yes" : "no") << endl;
}