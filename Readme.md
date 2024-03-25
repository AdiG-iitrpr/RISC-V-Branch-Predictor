## Branch Predictor

This repository contains the code to predict the accuracy of different branch predictors (1 bit , 2 bit etc.) .

### Building the project

---

To be able to compile the code, you need:

- A C++17 compiler (g++ >= 9 should be fine)

- CMake build system

To build the project, you need to use the `cmake` utility to generate the makefile .

- Clone the repository and go inside the folder path.

  ```
- Create a `build` folder by :

  ```
  mkdir build
  ```

- Go inside the `build` folder by :

  ```
  cd build
  ```

- Issue the following command to generate the makefile :

  ```
  cmake ..
  ```

- Run `make` to build the binaries . The main executable is called `assembler`.

### Running the Branch Predictor

---

Once compiled, you should be ready to use this implementation of prediction of accuracy of a branch predictor. If you execute the binary `branchPredictor` without any arguments, it will present you the command line usage :

```
./branchPredictor
Usage: ./branchPredictor <1: tracefile path>
```

Following the list of parameters you need to specify :

- `<1. traceFile path>` The path to the traceFile for which branch prediction accuracy needs to be calculated.

Example :

```
./branchPredictor ../input/traceFile1.txt
```
