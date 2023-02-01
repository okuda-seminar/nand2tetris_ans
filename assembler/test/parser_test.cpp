#include "parser.hpp"

#include <gtest/gtest.h>

TEST(ParserTest, Advance) {
  Parser parser("../test/parser_test.txt");
  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "@i");

  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "M=1");

  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "(LOOP)");

  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "");
}

TEST(ParserTest, GetCommandType) {
  Parser parser("../test/parser_test.txt");
  CommandType current;

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, CommandType::kA);

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, CommandType::kC);

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, CommandType::kL);
}

TEST(ParserTest, GetSymbol) {
  Parser parser("../test/symbol_test.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetSymbol(), "i");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetSymbol(), "LOOP");
}


TEST(ParserTest, GetDest) {
  Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetDest(), "D");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetDest(), "");
}

TEST(ParserTest, GetComp) {
  Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetComp(), "A");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetComp(), "D");
}

TEST(ParserTest, GetJump) {
  Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetJump(), "");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetJump(), "JGT");
}
