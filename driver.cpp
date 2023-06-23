//
// Created by Gucci HP on 4/4/2022.
//

#include "PGMimageProcessor.cpp"

    int main(int argc, char *argv[]){
        RMCLEB001::PGMimageProcessor process((argv[argc - 1]));
        process.parseArguments(argc,argv);
        process.readPGMFile(process.fileName);
        process.extractComponents(process.threshold,process.minValidSize);

        //perform functions based on which options have been input on command line
        if (process.sizeSet == true){
            process.filterComponentsBySize(process.minValidSize,process.maxValidSize);
        }
        if (process.writeSet == true) {
            process.writeComponents(process.outputPGMName);
        }
        if (process.printSet == true) {
            process.printAnalysis();
        }
        return 0;
    }