#pragma once

#include <variant>
#include <format>
#include <optional>
#include <string_view>

#include <magic_enum/magic_enum.hpp>

enum class TokenType
{
    // single characters
    LeftParen, RightParen, LeftBrace, RightBrace,
    Comma, Dot, Colon, Semicolon,

    // one or two characters
    Bang, BangEqual,
    Minus, MinusEqual,
    Plus, PlusEqual,
    Slash, SlashEqual,
    Star, StarEqual,
    Equal, EqualEqual,
    Greater, GreaterEqual,
    Less, LessEqual,
    Ampersand, And,
    Pipe, Or,

    // literals
    Identifier, String, Number,

    // keywords
    Class, Else, False, True, Fn, For, While, If, Null,
    Print, Return, Super, This, Let, Const,

    // other
    Eof
};

using Literal =
    std::variant<std::string_view, double>;

struct Token final
{
    std::string_view lexeme{};
    std::optional<Literal> literal{};
    TokenType type{};
    std::size_t line{};
    std::size_t column{};
};

template<>
class std::formatter<Token>
{
public:
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const Token& token, std::format_context& ctx) const
    {
        return std::format_to(
            ctx.out()
            ,"{:-<50}\nLine/Column [{}/{}]: | {:^15} | {}"
            , ""
            , token.line
            , token.column
            , magic_enum::enum_name(token.type)
            , format_lexeme_or_literal(token)
        );
    }

private:
    std::string format_lexeme_or_literal(const Token& token) const
    {
        if (token.literal) {
            return std::visit(
                [](const auto& literal) {
                    return std::format("literal: {}", literal);
                }, *token.literal);
        }

        return std::format("lexeme: {:-<1}", token.lexeme);
    }
};
