#include "code_writer.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "parser.hpp"

namespace vm {

CodeWriter::CodeWriter(const std::string output_file) {
  output_stream_.open(output_file);
  if (!output_stream_) {
    std::cerr << "failed to open the output file " << output_file << std::endl;
    exit(-1);
  }
}

CodeWriter::~CodeWriter() {
  output_stream_.close();
}

void CodeWriter::SetVMFileName(const std::string file_name) {
  vm_file_name_ = file_name;
}

void CodeWriter::WriteArithmetic(const std::string command) {
  if (command == "add") WriteAdd();
  else if (command == "sub") WriteSub();
  else if (command == "neg") WriteNeg();
  else if (command == "eq") WriteEq();
  else if (command == "gt") WriteGt();
  else if (command == "lt") WriteLt();
  else if (command == "and") WriteAnd();
  else if (command == "or") WriteOr();
  else if (command == "not") WriteNot();
  else std::cerr << "invalid arithmetic " << command << std::endl;
}

void CodeWriter::WritePushPop(const VMCommandType command_type,
                              const std::string segment,
                              const int index) {
  if (command_type == VMCommandType::kC_PUSH) WritePush(segment, index);
  else if (command_type == VMCommandType::kC_POP) WritePop(segment, index);
}

void CodeWriter::WriteAdd() {
  output_stream_ << "// add" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=D+M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WriteSub() {
  output_stream_ << "// sub" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=M-D" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WriteNeg() {
  output_stream_ << "// neg" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=-M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WriteEq() {
  output_stream_ << "// eq" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M-D" << std::endl;
  output_stream_ << "@LABEL" << label_count_ << std::endl;
  output_stream_ << "D;JEQ" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=0" << std::endl;
  output_stream_ << "@ENDLABEL" << label_count_ << std::endl;
  output_stream_ << "0;JMP" << std::endl;
  output_stream_ << "(LABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=-1" << std::endl;
  output_stream_ << "(ENDLABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;

  ++label_count_;
}

void CodeWriter::WriteGt() {
  output_stream_ << "// gt" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M-D" << std::endl;
  output_stream_ << "@LABEL" << label_count_ << std::endl;
  output_stream_ << "D;JGT" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=0" << std::endl;
  output_stream_ << "@ENDLABEL" << label_count_ << std::endl;
  output_stream_ << "0;JMP" << std::endl;
  output_stream_ << "(LABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=-1" << std::endl;
  output_stream_ << "(ENDLABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;

  ++label_count_;
}

void CodeWriter::WriteLt() {
  output_stream_ << "// lt" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M-D" << std::endl;
  output_stream_ << "@LABEL" << label_count_ << std::endl;
  output_stream_ << "D;JLT" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=0" << std::endl;
  output_stream_ << "@ENDLABEL" << label_count_ << std::endl;
  output_stream_ << "0;JMP" << std::endl;
  output_stream_ << "(LABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=-1" << std::endl;
  output_stream_ << "(ENDLABEL" << label_count_ << ")" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;

  ++label_count_;
}

void CodeWriter::WriteAnd() {
  output_stream_ << "// and" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=D&M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WriteOr() {
  output_stream_ << "// or" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "D=M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=D|M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WriteNot() {
  output_stream_ << "// not" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "AM=M-1" << std::endl;
  output_stream_ << "M=!M" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WritePush(const std::string segment, const int index) {
  output_stream_ << "// push " << segment << index << std::endl;

  if (segment == "constant")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
  } else if (segment == "argument")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@ARG" << std::endl;
    output_stream_ << "A=M+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "local")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@LCL" << std::endl;
    output_stream_ << "A=M+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "this")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@THIS" << std::endl;
    output_stream_ << "A=M+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "that")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@THAT" << std::endl;
    output_stream_ << "A=M+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "pointer")
  {
    if (index != 0 && index != 1) {
      std::cerr << "The pointer segment should be indicate 0 or 1." << std::endl;
      exit(-1);
    }
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@3" << std::endl;
    output_stream_ << "A=A+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "static")
  {
    output_stream_ << "@" << vm_file_name_ << "." << index << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else if (segment == "temp")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@5" << std::endl;
    output_stream_ << "A=A+D" << std::endl;
    output_stream_ << "D=M" << std::endl;
  } else
  {
    std::cerr << "invalid segment " << segment << std::endl;
    exit(-1);
  }

  output_stream_ << "@SP" << std::endl;
  output_stream_ << "A=M" << std::endl;
  output_stream_ << "M=D" << std::endl;
  output_stream_ << "@SP" << std::endl;
  output_stream_ << "M=M+1" << std::endl;
}

void CodeWriter::WritePop(const std::string segment, const int index) {
  output_stream_ << "// pop " << segment << index << std::endl;

  if (segment == "argument")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@ARG" << std::endl;
    output_stream_ << "D=M+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "local")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@LCL" << std::endl;
    output_stream_ << "D=M+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "this")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@THIS" << std::endl;
    output_stream_ << "D=M+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "that")
  {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@THAT" << std::endl;
    output_stream_ << "D=M+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "pointer")
  {
    if (index != 0 && index != 1) {
      std::cerr << "The pointer segment should be indicate 0 or 1." << std::endl;
      exit(-1);
    }
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@3" << std::endl;
    output_stream_ << "D=A+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "static")
  {
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@" << vm_file_name_ << "." << index << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else if (segment == "temp") {
    output_stream_ << "@" << index << std::endl;
    output_stream_ << "D=A" << std::endl;
    output_stream_ << "@5" << std::endl;
    output_stream_ << "D=A+D" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "M=D" << std::endl;
    output_stream_ << "@SP" << std::endl;
    output_stream_ << "AM=M-1" << std::endl;
    output_stream_ << "D=M" << std::endl;
    output_stream_ << "@R13" << std::endl;
    output_stream_ << "A=M" << std::endl;
    output_stream_ << "M=D" << std::endl;
  } else
  {
    std::cerr << "invalid segment " << segment << std::endl;
    exit(-1);
  }
}

} // namespace vm
