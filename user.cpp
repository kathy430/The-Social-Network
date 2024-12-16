#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "user.hpp"

/*
    Constructor for User, sets id to 0, and everything else to an empty string.
*/
User::User() {
    id = 0;
    name = "";
    location = "";
    picURL = "";
}

/*
    Copy constructor for User variable.
*/
User::User(const User& other) {
    id = other.id;
    name = other.name;
    location = other.location;
    picURL = other.picURL;
    follows = other.follows;
}

/*
    This function accepts a string and converts it into an int for the user's ID.
*/
void User::setID(std::string idData) {
    id = std::stoi(idData);
}

/*
    This function accepts a string and sets it as the user's name.
*/
void User::setName(std::string nameData) {
    name = nameData;
}

/*
    This function accepts a string and sets it as the user's location.
*/
void User::setLocation(std::string locationData) {
    location = locationData;
}

/*
    This function accepts a string and sets it as the user's picture URL.
*/
void User::setPicURL(std::string urlData) {
    picURL = urlData;
}

/*
    This function accepts a vector of follower IDs and sets it to the
    user's follows vector.
*/
void User::setFollows(std::vector<int> followsData) {
    for (int i = 0; i < followsData.size(); i++) {
        follows.push_back(followsData.at(i));
    }
}

/*
    This function returns the user's id. 
*/
int User::getID() {
    return id;
}

/*
    This function returns the user's name.
*/
std::string User::getName() {
    return name;
}

/*
    This function returns the user's location.
*/
std::string User::getLocation() {
    return location;
}

/*
    This function returns the user's picture URL.
*/
std::string User::getPicURL() {
    return picURL;
}

/*
    This function returns the user's following vector.
*/
std::vector<int> User::getFollows() {
    return follows;
}
