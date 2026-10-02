#include "Lexer.hpp"
#include "errors/ErrorHandler.hpp"
#include "lexer/tokens/Token.hpp"
#include "keywords/Keywords.hpp"
#include "utils/Utils.hpp"

#include <format>

const std::vector<Token>& Lexer::tokenize()
{
    while (!at_eof()) {
        lex_token();
        m_start = m_current;
    }

    add_token(TokenType::Eof, "eof");
    return m_tokens;
}

void Lexer::lex_token() noexcept
{
    const auto c { peek() };

    if (std::isspace(c)) {
        skip_whitespace();
    } else if (std::isalpha(c)) {
        handle_alpha();
    } else if (std::isdigit(c)) {
        handle_digits();
    } else {
        handle_special_chars();
    }
}

void Lexer::handle_special_chars() noexcept
{
    switch (advance()) {
    case '(': add_token(TokenType::LeftParen); break;
    case ')': add_token(TokenType::RightParen); break;
    case '{': add_token(TokenType::LeftBrace); break;
    case '}': add_token(TokenType::RightBrace); break;
    case ',': add_token(TokenType::Comma); break;
    case '.': add_token(TokenType::Dot); break;
    case ':': add_token(TokenType::Colon); break;
    case ';': add_token(TokenType::Semicolon); break;
    case '!': add_token(match('=') ? TokenType::Bang : TokenType::BangEqual); break;
    case '-': add_token(match('=') ? TokenType::MinusEqual : TokenType::Minus); break;
    case '+': add_token(match('=') ? TokenType::PlusEqual : TokenType::Plus); break;
    case '*': add_token(match('=') ? TokenType::StarEqual : TokenType::Star); break;
    case '=': add_token(match('=') ? TokenType::EqualEqual : TokenType::Equal); break;
    case '>': add_token(match('=') ? TokenType::GreaterEqual : TokenType::Greater); break;
    case '<': add_token(match('=') ? TokenType::LessEqual : TokenType::Less); break;
    case '|': add_token(match('|') ? TokenType::Or : TokenType::Pipe); break;
    case '&': add_token(match('&') ? TokenType::And : TokenType::Ampersand); break;
    case '/': handle_division_or_comment(); break;
    case '"': handle_string(); break;
    default: ErrorHandler::report(m_line, m_current-1, std::format("Unspecified Character '{}'", m_source[m_current-1]) );
    }
}

void Lexer::handle_alpha() noexcept
{
    for (; std::isalnum(peek()); advance());

    const auto lexeme { substr() };

    if (auto it { Dumblang::keywords.find(lexeme) }; it != Dumblang::keywords.end()) {
        add_token(Dumblang::keywords.at(lexeme));
    } else {
        add_token(TokenType::Identifier);
    }
}

void Lexer::handle_digits() noexcept
{
    for (; !at_eof() && std::isdigit(peek()); advance());

    if (peek() == '.' && std::isdigit(peek_next())) {
        advance();
    }

    for (; !at_eof() && std::isdigit(peek()); advance());

    add_token(TokenType::Number, Utils::sv_to_double(substr()));
}

void Lexer::handle_string() noexcept
{
    const auto col_copy { m_col };
    const auto line_copy { m_line };

    while (!at_eof() && peek() != '"') {
        if (peek() == '\n') {
            ++m_line;
            m_col = 0;
        }

        advance();
    }

    if (at_eof()) {
        ErrorHandler::report(line_copy, col_copy, "Unterminated String", substr());
    } else {
        add_token(TokenType::String, substr());
        advance();
    }
}

void Lexer::skip_whitespace() noexcept
{
    while (!at_eof() && std::isspace(peek())) {
        if (advance() == '\n') {
            ++m_line;
            m_col = 0;
        }
    }
}

void Lexer::handle_division_or_comment() noexcept
{
    if (match('/')) {
        for (; !at_eof() && peek() != '\n'; advance());
    } else {
        add_token(TokenType::Slash);
    }
}

bool Lexer::at_eof() const noexcept
{
    return m_current >= m_source.size();
}

char Lexer::advance() noexcept
{
    ++m_col;
    return m_source[m_current++];
}

char Lexer::peek() const noexcept
{
    return at_eof() ? '\0' : m_source[m_current];
}

char Lexer::peek_next() const noexcept
{
    return at_eof() ? '\0' : m_source[m_current+1];
}

void Lexer::add_token(TokenType type, std::optional<Literal> literal)
{
    m_tokens.emplace_back(substr(), literal, type, m_line, m_col);
}

std::string_view Lexer::substr() const
{
    if (!at_eof() && m_source[m_start] == '"') {
        return m_source.substr(m_start+1, (m_current - m_start) - 1);
    }

    return m_source.substr(m_start, m_current - m_start);
}

bool Lexer::match(char expected) noexcept
{
    return !at_eof() && m_source[m_current] == expected ? advance(), true : false;
}
