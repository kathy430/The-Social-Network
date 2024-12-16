#ifndef SOCIAL_NETWORK_HPP
#define SOCIAL_NETWORK_HPP

#include <vector>
#include "user.hpp"

class SocialNetwork {
    public:
        // constructor
        SocialNetwork() {};

        // copy constructor
        SocialNetwork(const SocialNetwork& other);

        // destructor
        ~SocialNetwork() {};

        // reads and saves data for each user read 
        void getData(std::string inputFile);
        // creates a 2d array of followers
        void createFollowerMatrix();

        // creates the index html file
        void createIndex();
        // creates each individual user html file
        void createUserHTML();

    private:
        std::vector<User> userData;
        std::vector<std::vector<bool>> followerMatrix;
};

#endif