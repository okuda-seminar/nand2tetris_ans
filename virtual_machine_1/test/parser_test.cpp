#include "parser.hpp"

#include <string>

#include <gtest/gtest.h>

TEST(ParserTest, Advance) {
  vm::Parser parser("../test/parser_test.txt");
  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "push constant 1");

  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "pop this 2");

  parser.Advance();
  EXPECT_EQ(parser.GetCurrentLine(), "add");
}

TEST(ParserTest, GetVMCommandType) {
  vm::Parser parser("../test/parser_test.txt");
  vm::VMCommandType vm_command_type;

  parser.Advance();
  vm_command_type = parser.GetVMCommandType();
  EXPECT_EQ(vm_command_type, vm::VMCommandType::kC_PUSH);

  parser.Advance();
  vm_command_type = parser.GetVMCommandType();
  EXPECT_EQ(vm_command_type, vm::VMCommandType::kC_POP);

  parser.Advance();
  vm_command_type = parser.GetVMCommandType();
  EXPECT_EQ(vm_command_type, vm::VMCommandType::kC_ARITHMETIC);
}

TEST(ParserTest, GetArg1) {
  vm::Parser parser("../test/parser_test.txt");
  std::string arg_1;

  parser.Advance();
  parser.GetVMCommandType();
  arg_1 = parser.GetArg1();
  EXPECT_EQ(arg_1, "constant");

  parser.Advance();
  parser.GetVMCommandType();
  arg_1 = parser.GetArg1();
  EXPECT_EQ(arg_1, "this");

  parser.Advance();
  parser.GetVMCommandType();
  arg_1 = parser.GetArg1();
  EXPECT_EQ(arg_1, "add");
}

TEST(ParserTest, GetArg2) {
  vm::Parser parser("../test/parser_test.txt");
  int arg_2;

  parser.Advance();
  parser.GetVMCommandType();
  arg_2 = parser.GetArg2();
  EXPECT_EQ(arg_2, 1);

  parser.Advance();
  parser.GetVMCommandType();
  arg_2 = parser.GetArg2();
  EXPECT_EQ(arg_2, 2);
}
