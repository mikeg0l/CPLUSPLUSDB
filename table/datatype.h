#pragma once

#include <variant>
#include <string>
/*
 https://stackoverflow.com/questions/62079146/how-to-use-a-single-variable-which-can-have-multiple-data-types-in-c
 https://en.cppreference.com/w/cpp/utility/variant
 */
using DataType = std::variant<std::string, int, float, bool>;
