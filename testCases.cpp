//
// Created by Gucci HP on 4/4/2022.
//
#define CATCH_CONFIG_MAIN
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"
#include "catch.hpp"
namespace RMCLEB001 {
    TEST_CASE ("PGMimageProcessor Class Unit Tests")
    {
//        SECTION("compareComponents") {
//            ConnectedComponent *ptr1 = new ConnectedComponent(std::make_pair(5,2));
//            ptr1->addToCoordinates(std::make_pair(2,1));
//            ConnectedComponent *ptr2 = new ConnectedComponent(std::make_pair(5,2));
//            std::shared_ptr<ConnectedComponent *> c1 = std::make_shared<ConnectedComponent *>(ptr1);
//            std::shared_ptr<ConnectedComponent *> c2 = std::make_shared<ConnectedComponent *>(ptr1);
//            REQUIRE(PGMimageProcessor::compareComponents(c1,c2) != 0);
//        }

//        SECTION("Extract Components") {
//            PGMimageProcessor process("shapes");
//            char *argv[2] = {"Application3","shapes.pgm"};
//            process.parseArguments(2, argv);
//            process.readPGMFile(process.fileName);
//            REQUIRE(process.extractComponents(200,5000) == 3);
//
//        }

//        SECTION("Valid coord") {
//        PGMimageProcessor process("shapes");
//        char *argv[2] = {"Application3","shapes.pgm"};
//        REQUIRE(process.validCoord(-2,-2,5,5) == 0);
//        REQUIRE(process.validCoord(-2,4,5,5) == 0);
//        REQUIRE(process.validCoord(5,-2,5,5) == 0);
//        REQUIRE(process.validCoord(20,20,5,5) == 0);
//        REQUIRE(process.validCoord(2,20,5,5) == 0);
//        REQUIRE(process.validCoord(20,2,5,5) == 0);
//        REQUIRE(process.validCoord(2,2,5,5) == 1);
//        }
    }
}