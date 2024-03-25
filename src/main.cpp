#include "branchPredictor/BranchPredictor.h"
#include "branchPredictor/Parser.h"

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

   std::unique_ptr<Parser> parser(new Parser());
   std::unique_ptr<BranchPredictor> branchPredictor(new BranchPredictor(*parser));

   branchPredictor->simulate(traceFilePath);

   return EXIT_SUCCESS;
}