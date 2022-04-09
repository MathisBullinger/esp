#include "./record.hpp"

using namespace std;

void Record::printInfo() {
  if (!isGroup()) cout << "Record of type " << getType();
  else cout << "Group of type " << getGroupName();
  cout << " (" << size << " bytes)" << endl;
  if (!isGroup()) cout << "record ID: " << recordID << endl;
  if (isGroup()) printLabel();
  cout << "time stamp: " << getTime() << endl;
  if (!isGroup()) printFlags();
  cout << endl;
}

void Record::printFlags() {
  cout << "flags:" << endl;
  printFlag(Flag::esm);
  printFlag(Flag::localized);
  printFlag(Flag::compressed);
}

void Record::printFlag(Flag flag) {
  std::string label;
  switch (flag) {
    case Flag::esm:         label = "ESM:       "; break;
    case Flag::localized:   label = "localized: "; break;
    case Flag::compressed:  label = "compressed:"; break;
  };
  
  cout << "  " << label << " " << (getFlag(flag) == 1 ? "yes" : "no") << endl;
}

std::string Record::getGroupName() const {
  switch (recordID) {
    case 0: return "top";
    case 1: return "world children";
    case 2: return "interior cell block";
    case 3: return "interior cell sub-block";
    case 4: return "exterior cell block";
    case 5: return "exterior cell sub-block";
    case 6: return "cell children";
    case 7: return "topic children";
    case 8: return "cell persistent children";
    case 9: return "cell temporary children";
    default: return "unknown type";
  }
}

void Record::printLabel() {
  switch (recordID) {
    case 0:
      cout << getLabel<std::string>() << endl;
      break;
    case 2:
    case 3:
      cout << getLabel<int32_t>() << endl;
      break;
    case 4:
    case 5: {
      auto [x, y] = getLabel<Coords>();
      cout << x << ", " << y << endl;
      break;
    }
    default:
      cout << getLabel<int32_t>() << endl;
  }
}