#include "parser.hpp"

#include <gtest/gtest.h>

TEST(ParserTest, Advance) {
  assembler::Parser parser("../test/parser_test.txt");
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
  assembler::Parser parser("../test/parser_test.txt");
  assembler::CommandType current;

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, assembler::CommandType::kA);

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, assembler::CommandType::kC);

  parser.Advance();
  current = parser.GetCommandType();
  EXPECT_EQ(current, assembler::CommandType::kL);
}

TEST(ParserTest, GetSymbol) {
  assembler::Parser parser("../test/symbol_test.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetSymbol(), "i");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetSymbol(), "LOOP");
}


TEST(ParserTest, GetDest) {
  assembler::Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetDest(), "D");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetDest(), "");
}

TEST(ParserTest, GetComp) {
  assembler::Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetComp(), "A");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetComp(), "D");
}

TEST(ParserTest, GetJump) {
  assembler::Parser parser("../test/parser_c_command.txt");
  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetJump(), "");

  parser.Advance();
  parser.GetCommandType();
  EXPECT_EQ(parser.GetJump(), "JGT");
}
