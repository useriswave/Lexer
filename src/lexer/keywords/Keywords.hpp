#pragma once

#include "lexer/tokens/Token.hpp"

#include <string_view>
#include <unordered_map>

namespace Dumblang {

const std::unordered_map<std::string_view, TokenType> keywords {
    { "class", TokenType::Class },
    { "eof", TokenType::Eof },
    { "false", TokenType::False },
    { "fn", TokenType::Fn },
    { "for", TokenType::For },
    { "if", TokenType::If },
    { "null", TokenType::Null },
    { "print", TokenType::Print },
    { "return", TokenType::Return },
    { "super", TokenType::Super },
    { "this", TokenType::This },
    { "true", TokenType::True },
    { "let", TokenType::Let },
    { "const", TokenType::Const },
    { "while", TokenType::While },
};

}
