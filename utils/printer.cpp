#include "printer.h"
#include "fmt/core.h"

void Printer::printHorizontalLine(unsigned long long size) {
    for (int i = 0; i < size; i++)
        fmt::print("--------------");
    fmt::println("");
}
