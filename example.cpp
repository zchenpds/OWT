#include <iostream>
#include <iomanip>
#include "owt.h"

using namespace std::chrono_literals;
std::chrono::nanoseconds arr[][2] = {
  {10ns, 20ns},
  {20ns, 30ns},
  {30ns, 35ns},
  {40ns, 42ns},
  {50ns, 65ns},
  {60ns, 68ns},
  {70ns, 83ns},
  {80ns, 93ns},
  {90ns, 100ns},
  {100ns, 110ns},
  {110ns, 120ns}
};

int main()
{
  Owt<std::chrono::nanoseconds> owt(30ns);
  std::cout << \
    "|  pts  |  sys  | trans.|\n"\
    "|-------|-------|-------|\n";
  for ( const auto & ptssys : arr) {
    std::cout << "|";
    std::cout << std::setw(7) << ptssys[0].count() << "|";
    std::cout << std::setw(7) << ptssys[1].count() << "|";
    std::cout << std::setw(7) << owt(ptssys[0], ptssys[1]).count() << "|\n";
  }
  std::cout << std::endl;
  return 0;
}