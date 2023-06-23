//
// Created by Gucci HP on 4/1/2022.
//

#ifndef ASSIGNMENT3_PGMIMAGEPROCESSOR_H
#define ASSIGNMENT3_PGMIMAGEPROCESSOR_H
#include "ConnectedComponent.h"
#include "string"

#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
namespace RMCLEB001{

    class PGMimageProcessor {
    public:
        int row, col, numOfRows, numOfCols, maxVal;
        unsigned char pixel;
        int **pixelArray;
        int **visited;
        std::vector<std::shared_ptr<ConnectedComponent *>> connectedComponents;


        int minValidSize;
        int maxValidSize;
        int minDefaultSize;
        int maxDefualtSize;
        int threshold;
        int thresholdDefault;
        int minThreshold;
        int maxThreshold;

        //booleans to check whether the different command line arguments have been set
        bool printSet;
        bool thresholdSet;
        bool sizeSet;
        bool writeSet;
        std::string outputPGMName;


        std::string fileName;

        PGMimageProcessor(std::string inputFile); //constructor
        ~PGMimageProcessor(); //destructor
        PGMimageProcessor(PGMimageProcessor &&source) noexcept ; //move constructor
        PGMimageProcessor& operator=(PGMimageProcessor && rhs); //move assignment
        PGMimageProcessor& operator=(const PGMimageProcessor & rhs); // copy assignment
        PGMimageProcessor(const PGMimageProcessor & p); //copy constructor



        int extractComponents(unsigned char threshold, int minValidSize);

        int filterComponentsBySize(int minSize, int maxSize);

        bool writeComponents(const std::string &outFileName);


        int getComponentCount(void) const;

        int getLargestSize(void) const;

        int getSmallestSize(void) const;

        void printComponentData(const ConnectedComponent &theComponent) const;

        void readPGMFile(std::string &fileName);

        void parseArguments(int argc, char *argv[]);


        int validCoord(int x, int y, int n, int m);

        void bfs(int n, int m, int **pixelArray, int x, int y, ConnectedComponent *component);
        //bool  compareComponents(std::shared_ptr<ConnectedComponent *> c1, std::shared_ptr<ConnectedComponent *> c2);

        void printAnalysis();
    };


}





#endif //ASSIGNMENT3_PGMIMAGEPROCESSOR_H
