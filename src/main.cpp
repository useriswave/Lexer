#include <print>

#include "lexer/Lexer.hpp"
#include "persistence/FileReader.hpp"

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::println(stderr, "Usage: ./path/to/dumblang <file_path>");
        return 1;
    }

    const auto code { FileReader::read_and_get_file_content(argv[1]) };

    if (!code) {
        std::println(stderr, "{}", code.error().message());
        return 1;
    }

    Lexer lexer{ code.value() };
    const auto tokens { lexer.tokenize() };

    for (const auto& token : tokens) {
        std::println("{}", token);
    }
}
