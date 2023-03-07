#include "code_writer.hpp"

#include <cstring>
#include <fstream>

#include <gtest/gtest.h>

TEST(CodeWriterTest, WriteArithmetic) {
  vm::CodeWriter code_writer("../test/code_writer_write_arithmetic_test.txt");
  code_writer.WriteArithmetic("add");
  code_writer.WriteArithmetic("eq");
  code_writer.~CodeWriter();

  std::ifstream file1("../test/code_writer_write_arithmetic_test.txt");
  std::ifstream file2("../test/expected_write_arithmetic_test.txt");

  // Check if the files have the same size.
  const std::streamsize file1_size = file1.tellg();
  const std::streamsize file2_size = file2.tellg();

  EXPECT_EQ(file1_size, file2_size);

  // Read the contents of the files.
  file1.seekg(0);
  file2.seekg(0);

  char* buffer1 = new char[file1_size];
  char* buffer2 = new char[file2_size];

  file1.read(buffer1, file1_size);
  file2.read(buffer2, file2_size);

  // Compare the contents of the files.
  const bool result = std::memcmp(buffer1, buffer2, file1_size) == 0;

  delete[] buffer1;
  delete[] buffer2;

  EXPECT_TRUE(result);
}

TEST(CodeWriteTest, WritePushPop) {
  vm::CodeWriter code_writer("../test/code_writer_write_pushpop_test.txt");
  code_writer.WritePushPop(vm::VMCommandType::kC_PUSH, "constant", 0);
  code_writer.WritePushPop(vm::VMCommandType::kC_POP, "this", 1);
  code_writer.~CodeWriter();

  std::ifstream file1("../test/code_writer_write_pushpop_test.txt");
  std::ifstream file2("../test/expected_write_pushpop_test.txt");

  // Check if the files have the same size.
  const std::streamsize file1_size = file1.tellg();
  const std::streamsize file2_size = file2.tellg();

  EXPECT_EQ(file1_size, file2_size);

  // Read the contents of the files.
  file1.seekg(0);
  file2.seekg(0);

  char* buffer1 = new char[file1_size];
  char* buffer2 = new char[file2_size];

  file1.read(buffer1, file1_size);
  file2.read(buffer2, file2_size);

  // Compare the contents of the files.
  const bool result = std::memcmp(buffer1, buffer2, file1_size) == 0;

  delete[] buffer1;
  delete[] buffer2;

  EXPECT_TRUE(result);
}
