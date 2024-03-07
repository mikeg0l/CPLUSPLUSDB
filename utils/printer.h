#pragma once

#include <string>

struct Printer {
    static void printHorizontalLine(unsigned long long size);
    static void printColumnOrValue(const std::string& a);
};