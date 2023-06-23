//
// Created by Gucci HP on 4/2/2022.
//

#include "ConnectedComponent.h"
namespace RMCLEB001 {
//contructor
    ConnectedComponent::ConnectedComponent(std::pair<int, int> pixel) {
        coordinates = new std::vector<std::pair<int, int>>;
        id = count;
        coordinates->push_back(pixel);
        count++;
        numPixels = 0;
    }

//destructor
    ConnectedComponent::~ConnectedComponent() {

    }


//getters
    int ConnectedComponent::getNumPixels() const {
        return numPixels;
    }

    int ConnectedComponent::getId() const {
        return id;
    }

//std::vector<std::pair<int,int>> ConnectedComponent::getVector() const {
//    return coordinates;
//}


//increment numpixels variable
    void ConnectedComponent::incrementNumPixels() {
        numPixels++;
    }

    void ConnectedComponent::addToCoordinates(std::pair<int, int> pixel) {
        coordinates->push_back(pixel);
    }

// Move Constructor
    ConnectedComponent::ConnectedComponent(ConnectedComponent &&source) {
        this->id = source.id;
        this->coordinates = (source.coordinates);
        this->numPixels = source.numPixels;

        source.coordinates = nullptr;
    }

    //move assignment
   ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent && rhs)
    {
        if(this != &rhs) // Checks to make that we are not performing a self-assignment
        {

        }
        return *this;
    }

    //copy assignment
    ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent & rhs)
    {
        if(this != &rhs) // Checks to make that we are not performing a self-assignment
        {
            this->id = rhs.id;
            this->numPixels = rhs.numPixels;
            this->coordinates = rhs.coordinates;
        }
        return *this;
    }

    //copy constructor

    ConnectedComponent::ConnectedComponent(const ConnectedComponent &p) {
        this->id = p.id;
        this->numPixels = p.numPixels;
        this->coordinates = p.coordinates;

    }



}