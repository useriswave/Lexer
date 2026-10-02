#include "lexer/Lexer.hpp"
#include "lexer/tokens/Token.hpp"

#include <gtest/gtest.h>

struct LexerParams
{
    std::string code{};
    TokenType expected_type{};
};

struct LexerFixture : public testing::TestWithParam<LexerParams>
{
    std::optional<Lexer> lexer{};

    void SetUp() override
    {
        lexer.emplace(GetParam().code);
    }
};

TEST_P(LexerFixture, LexerTokenizesKeywords)
{ 
    EXPECT_EQ(GetParam().expected_type, lexer->tokenize()[0].type);
}

INSTANTIATE_TEST_SUITE_P(
    DifferentUserArgs,
    LexerFixture,
    ::testing::Values(
        LexerParams{ "class", TokenType::Class },
        LexerParams{ "eof", TokenType::Eof },
        LexerParams{ "false", TokenType::False },
        LexerParams{ "fn", TokenType::Fn },
        LexerParams{ "for", TokenType::For },
        LexerParams{ "if", TokenType::If },
        LexerParams{ "null", TokenType::Null },
        LexerParams{ "print", TokenType::Print },
        LexerParams{ "return", TokenType::Return },
        LexerParams{ "super", TokenType::Super },
        LexerParams{ "this", TokenType::This },
        LexerParams{ "true", TokenType::True },
        LexerParams{ "let", TokenType::Let },
        LexerParams{ "const", TokenType::Const },
        LexerParams{ "while", TokenType::While }
    )
);
