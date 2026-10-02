#pragma once

#include <string_view>

namespace ErrorHandler {

void report(std::size_t line, std::size_t column, std::string_view message, std::string_view where="");

}
