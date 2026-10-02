#pragma once

#include "tokens/Token.hpp"

#include <vector>
#include <string_view>

class Lexer final
{
public:
    explicit Lexer(std::string_view source)
        : m_source { source }
    {}

public:
    [[nodiscard]]
    const std::vector<Token>& tokenize();

private:
    void lex_token() noexcept;
    void handle_special_chars() noexcept;
    void handle_string() noexcept;
    void handle_alpha() noexcept;
    void handle_digits() noexcept;
    void skip_whitespace() noexcept;
    void handle_division_or_comment() noexcept;

private:
    [[nodiscard]] bool at_eof() const noexcept;
    [[nodiscard]] bool at_eol() const noexcept;
    [[nodiscard]] bool match(char expected) noexcept;
    [[nodiscard]] char peek() const noexcept;
    [[nodiscard]] char peek_next() const noexcept;
    [[nodiscard]] std::string_view substr() const;
    char advance() noexcept;
    void add_token(TokenType type, std::optional<Literal> literal = std::nullopt);

private:
    std::vector<Token> m_tokens{};
    std::string_view m_source{};
    std::size_t m_current{};
    std::size_t m_start{};
    std::size_t m_col{};
    std::size_t m_line{ 1 };
};
