// CS315 Project 1 by Kathy Yuen

#include <iostream>
#include "socialnetwork.hpp"
#include "user.hpp"

int main() {
    SocialNetwork userData;
    userData.getData("input.json");
    userData.createFollowerMatrix();
    userData.createIndex();
    userData.createUserHTML();

    return 0;
}
