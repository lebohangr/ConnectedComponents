//
// Created by Gucci HP on 4/2/2022.
//

#ifndef ASSIGNMENT3_CONNECTEDCOMPONENT_H
#define ASSIGNMENT3_CONNECTEDCOMPONENT_H
#include <vector>
#include <utility>      // std::pair, std::make_pair
namespace RMCLEB001 {
    class ConnectedComponent {
        static int count;

    private:
        int numPixels;
        int id;
        std::vector<std::pair<int, int>> *coordinates;

    public:
        ConnectedComponent(std::pair<int, int>); //constructor
        ~ConnectedComponent(); //destructor
        ConnectedComponent(ConnectedComponent &&source); //move constructor
        ConnectedComponent& operator=(ConnectedComponent && rhs); //move assignment
        ConnectedComponent& operator=(const ConnectedComponent & rhs); // copy assignment
        ConnectedComponent(const ConnectedComponent & p); //copy constructor
        void addToCoordinates(std::pair<int, int> pixel);

        int getNumPixels() const;

        int getId() const;

        std::vector<std::pair<int, int>> getVector() const;

        void incrementNumPixels();

    };

    int ConnectedComponent::count = 0;


}
#endif //ASSIGNMENT3_CONNECTEDCOMPONENT_H
