#include "ErrorHandler.hpp"

#include <print>

void ErrorHandler::report(std::size_t line, std::size_t column, std::string_view message, std::string_view where)
{
    std::println(stderr, "Error at line {}: {} at column: {} {}", line, message, column, where);
    // exit(1);
}

