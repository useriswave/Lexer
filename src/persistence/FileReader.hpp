#pragma once

#include <expected>
#include <string>

namespace FileReader {

enum class ErrorType
{
    FileDoesntExist,
    InvalidExtension,
};

struct FileError
{
    std::string cause{};
    ErrorType type{};

    [[nodiscard]]
    std::string message() const;
};


[[nodiscard]]
std::expected<std::string, FileError> read_and_get_file_content(const std::string& path);

}
