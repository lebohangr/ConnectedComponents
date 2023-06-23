//
// Created by Gucci HP on 4/1/2022.
//

#include "PGMimageProcessor.h"
#include "ConnectedComponent.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "vector"
#include "algorithm"
#include <cstring>

namespace RMCLEB001 {
//constructor
    PGMimageProcessor::PGMimageProcessor(std::string inputFile) {

        threshold = 128;
        minValidSize = 3;
        //maxValidSize = 9000;

        fileName = inputFile;
        minThreshold = 0;
        maxThreshold = 255;
        printSet = false;
        thresholdSet = false;
        sizeSet = false;
        writeSet = false;
    }

    PGMimageProcessor::~PGMimageProcessor() {
        //free up memory used by pixelArray array
        for (int i = 0; i < numOfRows; ++i) {
            delete[] pixelArray[i];
        }
        delete[] pixelArray;

        for (int i = 0; i < numOfRows; ++i) {
            delete[] visited[i];
        }
        delete[] visited;
    }

    void PGMimageProcessor::readPGMFile(std::string &fileName) {
        row = 0, col = 0, numOfRows = 0, numOfCols = 0;
        std::stringstream ss;
        std::ifstream infile(fileName, std::ios::binary);

        std::string inputLine = "";

        getline(infile, inputLine);      // read the version P5 on line 1
        if (inputLine.compare("P5") != 0) std::cerr << "Version error" << std::endl;
        std::cout << "Version : " << inputLine << std::endl;
        std::streampos oldpos; // stores the position of file pointer

        while (true) {
            oldpos = infile.tellg();
            getline(infile, inputLine);  // read the second line : comment
            if (inputLine.at(0) != '#') {
                break;
            } else std::cout << "Comment : " << inputLine << std::endl;
        }
        infile.seekg(oldpos);   // get back to the position in file stream with the width and height
        ss << infile.rdbuf();   //read the third line : width and height
        ss >> numOfCols >> numOfRows;
        std::cout << numOfCols << " columns and " << numOfRows << " rows" << std::endl;
        maxDefualtSize = numOfRows * numOfCols;

        // Visited array
        visited = new int *[numOfRows];
        for (int g = 0; g < numOfRows; ++g) {
            visited[g] = new int[numOfCols];
        }

        for (row = 0; row < numOfRows; row++) {    //set visited values to 0
            for (col = 0; col < numOfCols; col++) {
                visited[row][col] = 0;
            }
        }

        int maxVal;  //maximum intensity value of pixels
        ss >> maxVal;
        std::cout << maxVal << std::endl;




        //   unsigned char pixel;

        pixelArray = new int *[numOfRows];
        for (int i = 0; i < numOfRows; ++i) {
            pixelArray[i] = new int[numOfCols];
        }

        for (row = 0; row < numOfRows; row++) {    //record the pixel values
            for (col = 0; col < numOfCols; col++) {
                ss.read((char *) &pixel, 1);
                pixelArray[row][col] = pixel;
            }
        }
        infile.close();
    }

//parse arguments
    void PGMimageProcessor::parseArguments(int argc, char *argv[]) {
        // -s <int> <int> -t <int> -p -w <pgmfile>
        if (argc > 1) {
            for (int i = 0; i < argc; i++) {
                if (strcmp(argv[i], "-s") == 0) {
                    sizeSet = true;
                    minValidSize = strtol(argv[i + 1], NULL, 10);
                    maxValidSize = strtol(argv[i + 2], NULL, 10);
                }
                //    if (i!=4) {
                if (strcmp(argv[i], "-t") == 0) {
                    thresholdSet = true;
                    threshold = strtol(argv[i + 1], NULL, 10);
                }
                //   }

                if (strcmp(argv[i], "-p") == 0) {
                    printSet = true;
                }
                //   if (i!=4) {
                if (strcmp(argv[i], "-w") == 0) {
                    writeSet = true;
                    outputPGMName = argv[i + 1];
                }
                //  }
            }
            fileName = argv[argc - 1];
        }
    }

// Compares two connected components according to numPixels.
    bool compareComponents(std::shared_ptr<ConnectedComponent *> c1, std::shared_ptr<ConnectedComponent *> c2) {
        ConnectedComponent *ptr1 = *c1;
        ConnectedComponent *ptr2 = *c2;
        return (ptr1->getNumPixels() < ptr2->getNumPixels());
    }


///* process the input image to extract all the connected components,
//based on the supplied threshold (0...255) and excluding any components
//of less than the minValidSize. The final number of components that
//you store in your container (after discarding undersized one)
//must be returned.
//*/
    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize) {
        //threshold the pixels in pixelArray to only hold pixel values of 0 or 255
        for (int i = 0; i < numOfRows; i++) {
            for (int j = 0; j < numOfCols; j++) {
                //output1 << pixelArray[k][r] << " ";
                if (pixelArray[i][j] >= threshold) {
                    pixelArray[i][j] = 255;
                } else {
                    pixelArray[i][j] = 0;
                }
            }
        }

        //find components
        int count = 0;
        for (int row = 0; row < numOfRows; row++) {
            for (int col = 0; col < numOfCols; col++) {
                if ((pixelArray[row][col] == 255) && (visited[row][col] != 1)) {
                    count++;
                    //std::cout<<"New component: "<< count << std::endl;
                    ConnectedComponent *component = new ConnectedComponent(std::make_pair(row, col));
                    bfs(numOfRows, numOfCols, pixelArray, row, col, component);
                }
            }
        }
        //remove undersized components
        for (int g = 0; g < connectedComponents.size(); g++) {
            ConnectedComponent *ptr = *connectedComponents.at(g);
            if (ptr->getNumPixels() < minValidSize) {
                //std::cout << "Num pixels removed: " << ptr->getNumPixels() << "  minValidSize: " << minValidSize <<std::endl;
                connectedComponents.erase(connectedComponents.begin() + g);
            }
        }

        //sort connectedComponents acording to numPixels
        std::sort(connectedComponents.begin(), connectedComponents.end(), compareComponents);
        return connectedComponents.size();
    }

    void PGMimageProcessor::printAnalysis() {

        //print out sorted vector
        std::cout << "\nComponenents sorted by numPixels : \n";
        for (std::shared_ptr<ConnectedComponent *> ptr: connectedComponents) {
            ConnectedComponent *g = *ptr;
            printComponentData(*g);
        }
        std::cout << "\nTotal number of components: " << getComponentCount() << std::endl;
        std::cout << "\nSize of smallest component: " << getSmallestSize() << std::endl;
        std::cout << "\nSize of largest component: " << getLargestSize() << std::endl;

    }


/* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize) {
        //filter out components
        std::cout << "\nComponenents filtered out by minSize: " << minSize << " & maxSize: " << maxSize << "\n";
        int pos = 0; //position in vector
        for (std::shared_ptr<ConnectedComponent *> ptr: connectedComponents) {
            ConnectedComponent *g = *ptr;
            if (g->getNumPixels() < minSize || g->getNumPixels() > maxSize) {
                connectedComponents.erase(connectedComponents.begin() + pos);
                printComponentData(*g);
            }
            pos++;

        }
        return connectedComponents.size();
    }

/* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
    bool PGMimageProcessor::writeComponents(const std::string &outFileName) {
        std::ofstream output1(outFileName);  // output the intensity values of the pgm file
        output1 << "P2\n" << numOfCols << " " << numOfRows << "\n" << 255 << std::endl;
        for (int k = 0; k < numOfRows; k++) {
            for (int r = 0; r < numOfCols; r++) {
                output1 << pixelArray[k][r] << " ";
            }
        }
        output1.close();
        return 1;
    }

// return number of components
    int PGMimageProcessor::getComponentCount(void) const {
        return connectedComponents.size();
    }

// return number of pixels in largest component
    int PGMimageProcessor::getLargestSize(void) const {
        ConnectedComponent *ptr = *connectedComponents.at(
                connectedComponents.size() - 1); //vector is sorted from smallest to biggest numPixels
        return ptr->getNumPixels();

    }

// return number of pixels in smallest component
    int PGMimageProcessor::getSmallestSize(void) const {
        ConnectedComponent *ptr = *connectedComponents.at(0); //vector is sorted from smallest to biggest numPixels
        return ptr->getNumPixels();

    }

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
    void PGMimageProcessor::printComponentData(const ConnectedComponent &theComponent) const {
        std::cout << "Component ID: " << theComponent.getId() << " Number of pixels: " << theComponent.getNumPixels()
                  << "\n";
    }


// Function to check if coordinate is valid
    int PGMimageProcessor::validCoord(int x, int y, int n, int m) {

        if (x < 0 || y < 0) {
            return 0;
        }
        if (x >= n || y >= m) {
            return 0;
        }
        return 1;
    }

// Function to run bfs
    void PGMimageProcessor::bfs(int n, int m, int **pixelArray, int x, int y, ConnectedComponent *component) {

        // Creating queue for bfs
        std::queue<std::pair<int, int>> obj;

        // Pushing pair of {x, y}
        obj.push({x, y});

        // Marking {x, y} as visited
        visited[x][y] = 1;

        // Until queue is empty
        while (obj.empty() != 1) {

            // Extracting front pair
            std::pair<int, int> coord = obj.front();
            int x = coord.first;
            int y = coord.second;
            // int maxThreshold = maxThreshold;


            // Popping front pair of queue
            obj.pop();

            // For morth Cell
            if (validCoord(x + 1, y, n, m)
                && visited[x + 1][y] == 0
                && pixelArray[x + 1][y] == maxThreshold) {
                component->addToCoordinates(std::make_pair(x + 1, y));
                component->incrementNumPixels();
                obj.push({x + 1, y});
                visited[x + 1][y] = 1;
            }

            // For south Cell
            if (validCoord(x - 1, y, n, m)
                && visited[x - 1][y] == 0
                && pixelArray[x - 1][y] == maxThreshold) {
                component->addToCoordinates(std::make_pair(x - 1, y));
                component->incrementNumPixels();

                obj.push({x - 1, y});
                visited[x - 1][y] = 1;
            }

            // For east Cell
            if (validCoord(x, y + 1, n, m)
                && visited[x][y + 1] == 0
                && pixelArray[x][y + 1] == maxThreshold) {
                component->addToCoordinates(std::make_pair(x, y + 1));
                component->incrementNumPixels();
                obj.push({x, y + 1});
                visited[x][y + 1] = 1;
            }

            // For west Cell
            if (validCoord(x, y - 1, n, m)
                && visited[x][y - 1] == 0
                && pixelArray[x][y - 1] == maxThreshold) {
                component->addToCoordinates(std::make_pair(x, y - 1));
                component->incrementNumPixels();
                obj.push({x, y - 1});
                visited[x][y - 1] = 1;
            }
        }
        //wrap pointer to component object in smart pointer
        std::shared_ptr<ConnectedComponent *> componentPtr = std::make_shared<ConnectedComponent *>(component);
        //add smart pointer to collection of smart pointers
        connectedComponents.push_back(componentPtr);
       // ConnectedComponent *ptr = *connectedComponents.at(component->getId());
        //std::cout << "Num pixels: " << ptr->getNumPixels() <<std::endl;



    }
//move constructor
    PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&source) noexcept {
        this->numOfRows = source.numOfRows;
        this->numOfCols = source.numOfCols;
        this->threshold = source.threshold;
        this->minValidSize = source.minValidSize;
        this->fileName = source.fileName;
        this->minThreshold = source.minThreshold;
        this->maxThreshold = source.maxThreshold;
        this->printSet = source.printSet;
        this->thresholdSet = source.thresholdSet;
        this->sizeSet = source.sizeSet;
        this->writeSet = source.writeSet;
        this->connectedComponents = source.connectedComponents;
        this ->visited = source.visited;
        this ->pixelArray = source.pixelArray;
        source.pixelArray = nullptr;
        source.visited = nullptr;

    }
//move assignment constructor
    PGMimageProcessor &PGMimageProcessor::operator=(PGMimageProcessor &&rhs) {
        this->numOfRows = rhs.numOfRows;
        this->numOfCols = rhs.numOfCols;
        this->threshold = rhs.threshold;
        this->minValidSize = rhs.minValidSize;
        this->fileName = rhs.fileName;
        this->minThreshold = rhs.minThreshold;
        this->maxThreshold = rhs.maxThreshold;
        this->printSet = rhs.printSet;
        this->thresholdSet = rhs.thresholdSet;
        this->sizeSet = rhs.sizeSet;
        this->writeSet = rhs.writeSet;
        this->connectedComponents = rhs.connectedComponents;
//        this ->visited = rhs.visited;
//        this ->pixelArray = rhs.pixelArray;

        if(this->pixelArray != nullptr)
        {
            delete this->pixelArray;
            this->pixelArray = nullptr;
        }
        if(rhs.pixelArray != nullptr)

        {
            this->pixelArray = rhs.pixelArray;
            rhs.pixelArray = nullptr;
        }

        //////////////////////////////////////////////
        if(this->visited != nullptr)
        {
            delete this->visited;
            this->visited = nullptr;
        }
        if(rhs.visited != nullptr)

        {
            this->visited = rhs.visited;
            rhs.visited = nullptr;
        }

        return *this;
    }

//copy assignment constructor
    PGMimageProcessor &PGMimageProcessor::operator=(const PGMimageProcessor &rhs) {
        if(this != &rhs)
        {
            this->numOfRows = rhs.numOfRows;
            this->numOfCols = rhs.numOfCols;
            this->threshold = rhs.threshold;
            this->minValidSize = rhs.minValidSize;
            this->fileName = rhs.fileName;
            this->minThreshold = rhs.minThreshold;
            this->maxThreshold = rhs.maxThreshold;
            this->printSet = rhs.printSet;
            this->thresholdSet = rhs.thresholdSet;
            this->sizeSet = rhs.sizeSet;
            this->writeSet = rhs.writeSet;
            this->connectedComponents = rhs.connectedComponents;

            if(this->visited != nullptr)
            {
                delete this->visited;
                this->visited = nullptr;
            }
            if(rhs.visited != nullptr)
            {
                this->visited = new auto(*rhs.visited);
            }


            if(this->pixelArray != nullptr)
            {
                delete this->pixelArray;
                this->pixelArray = nullptr;
            }
            if(rhs.pixelArray != nullptr)
            {
                this->pixelArray = new auto(*rhs.pixelArray);
            }
        }
        return *this;
    }
//copy constructor
    PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &p) {
        this->threshold = p.threshold;
        this->minValidSize = p.minValidSize;
        this->fileName = p.fileName;
        this->minThreshold = p.minThreshold;
        this->maxThreshold = p.maxThreshold;
        this->printSet = p.printSet;
        this->thresholdSet = p.thresholdSet;
        this->sizeSet = p.sizeSet;
        this->writeSet = p.writeSet;
        this->connectedComponents = p.connectedComponents;
        this ->visited = p.visited;
        this ->pixelArray = p.pixelArray;

        if(p.visited != nullptr)
        {
            visited = new auto(*p.visited);
        }
        if(p.pixelArray != nullptr)
        {
            pixelArray = new auto(*p.pixelArray);
        }
    }

}




