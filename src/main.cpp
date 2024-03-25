#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <memory>
#include <string>


int main(int argc, char **argv) {

   if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <1:traceFile path>" << std::endl;
      return EXIT_FAILURE;
   }

   std::string traceFilePath = argv[1];

   std::cout << "===  Branch Predictor ===\n";
   std::cout << "Tracefile: " << traceFilePath << std::endl;

   return EXIT_SUCCESS;
}