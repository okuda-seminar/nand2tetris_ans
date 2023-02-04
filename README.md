# nand2tetris_ans

## Overview
This repository contains the answers to "nand2tetris".

## Setup
You can set up the environment by following these steps.
```
git clone https://github.com/okuda-seminar/nand2tetris_ans.git
cd nand2tetris_ans
make build
make up
make exec
```

### Build
This project uses CMake to build all programs. CMake is an open-source, cross-platform build system generator that simplifies the cimpilation process by setting up configuratons. It then generates native Makefiles automatically. To build the project, follow these steps.
```
cd assembler  // This line varies depending on the folder you want to build
mkdir build
cd build
cmake ..
make
```
Notes: It is a common practice to craete the build directory at the root level to separate CMake-related files from the project files because CMake generates many related files.
