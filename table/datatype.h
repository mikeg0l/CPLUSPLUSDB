#pragma once

#include <variant>
#include <string>

using DataType = std::variant<std::string, int, float, bool>;
