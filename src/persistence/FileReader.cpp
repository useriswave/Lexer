#include "FileReader.hpp"

#include <fstream>
#include <filesystem>
#include <iterator>
#include <utility>

namespace fs = std::filesystem;

namespace {

[[nodiscard]]
std::string read_file_content(std::ifstream& inf)
{
    return { std::istreambuf_iterator<char>{inf}, {} };
}

[[nodiscard]]
std::string get_extension(const std::string& path)
{
    return fs::path{ path }.extension();
}

[[nodiscard]]
bool valid_extension(const std::string& path) noexcept
{
    return get_extension(path) == ".dmb";
}

}

std::string FileReader::FileError::message() const
{
    switch (type) {
    case ErrorType::FileDoesntExist: return std::format("File \"{}\" doesn't exist.", cause);
    case ErrorType::InvalidExtension: return std::format("Invalid file extension \"{}\".", cause);
    }

    std::unreachable();
}

[[nodiscard]]
std::expected<std::string, FileReader::FileError> FileReader::read_and_get_file_content(const std::string& path)
{
    std::ifstream inf{ path };

    if (!inf) {
        return std::unexpected{ FileError{ path, ErrorType::FileDoesntExist } };
    }

    if (!valid_extension(path)) {
        return std::unexpected{ FileError{ get_extension(path), ErrorType::InvalidExtension } };
    }

    return read_file_content(inf);
}

