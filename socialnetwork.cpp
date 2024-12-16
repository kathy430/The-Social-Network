#include <cassert>
#include <fstream>
#include <iostream>
#include "socialnetwork.hpp"

/*
    Copy constructor for SocialNetwork class, copies the userData vector
    and the 2D follower matrix.
*/
SocialNetwork::SocialNetwork(const SocialNetwork& other) {
    userData = other.userData;
    followerMatrix = other.followerMatrix;
}

/*
    This function accepts a string of the file name that is to be read. It opens 
    the file given and reads in user data, saving each user data into a private 
    vector userData.
*/
void SocialNetwork::getData(std::string inputFile) {
    // open file
    std::ifstream inFile;
    inFile.open(inputFile);
    assert(inFile.is_open());

    // read file
    char fileChar;
    std::string fileString = "";
    
    while (!inFile.eof()) {
        inFile >> fileChar;
        fileString += fileChar;

        // once the beginning is parsed, parse the rest and start creating users
        if (fileString == "{\"users\":[") {
            fileString = "";
            
            while (fileString != "]}"){
                // reading a new user 
                inFile >> fileChar;
                
                if (fileChar == '{') {
                    User newUser;
                    fileString = "";
                    
                    // get user data
                    inFile >> fileChar;
                    while (fileString != "},") {
                        assert(fileChar = '\"');
                        
    
                        // start of first user data type after starting quotation mark
                        inFile >> std::noskipws >> fileChar;
                        while (fileChar != ',') {
                            // read until end of first quote
                            while (fileChar != '\"') {
                                fileString += fileChar;
                                inFile >> fileChar;
                            }
                            
                            // stop reading whitespace, get next character
                            inFile >> std::skipws >> fileChar;
                            
                            // make sure its retreving the correct syntax
                            assert(fileChar == ':');
                            inFile >> fileChar;
    
                            // read in actual user data
                            std::string userData = "";
                            std::vector<int> followsData;
                            
                            if (fileChar == '\"') {
                                // retreive data string with white space
                                inFile >> std::noskipws >> fileChar;
                                while (fileChar != '\"') {
                                    userData += fileChar;
                                    inFile >> fileChar;
                                }
                                inFile >> std::skipws >> fileChar;
                            }
                            else if (fileChar == '[') {
                                inFile >> fileChar;
                                assert(fileChar == '\"');
                                inFile >> fileChar;
                                while (fileChar != ']') {
                                    // if finished reading one number
                                    if (fileChar == '\"') {
                                        followsData.push_back(std::stoi(userData));
                                        userData = "";
                                    }
                                    else if (fileChar == ',') {
                                        // read starting quotation and get num
                                        inFile >> fileChar >> fileChar;
                                        continue;
                                    }
                                    else {
                                        userData += fileChar;
                                    }
                                    inFile >> fileChar;
                                }
                                inFile >> fileChar;
                            }
                            
                            if (fileString == "id_str") newUser.setID(userData);
                            else if (fileString == "name") newUser.setName(userData);
                            else if (fileString == "location") newUser.setLocation(userData);
                            else if (fileString == "pic_url") newUser.setPicURL(userData);
                            else if (fileString == "follows") newUser.setFollows(followsData);
    
                            fileString = "";

                            // check if we are done with current user data
                            if (fileChar == '}') {
                                fileString += fileChar;
                                break;
                            }
                            
                        }
    
                        // see if we are reading end of user or end of file
                        if (fileChar == '}') {
                            inFile >> fileChar;
                            if (fileChar == ',') {
                                fileString += fileChar;
                                continue;
                            }
                            else {
                                assert(fileChar == ']');
                                fileString = "";
                                fileString += fileChar;
                                break;
                            }
                        }
                        
                        // finished reading first data info for current user, prep for next
                        inFile >> fileChar;
                        assert(fileChar == '\"');                       
                    }
                    userData.push_back(newUser);
                }

                // check for end of file
                if (fileChar == ']') {
                    inFile >> fileChar;
                    fileString += fileChar;
                    assert(fileString == "]}");
                }
            }
        }
    }
    inFile.close();

    // order the data based on ID numbers
    std::vector<User> orderedData(userData.size());
    int userID;
    User currUser;
    for (int i = 0; i < userData.size(); i++) {
        currUser = userData.at(i);
        userID = currUser.getID();
        orderedData.at(userID - 1) = currUser;
    }
    userData = orderedData;
}

/*
    This function creates a 2D follower matrix with the user names on the Y-axis
    and the followers of the user on the X-axis.
*/
void SocialNetwork::createFollowerMatrix() {
    User currUser;
    int size = userData.size();

    // create matrix
    for (int i = 0; i < userData.size(); i++) {
        currUser = userData.at(i);

        // add in each user's follow data
        std::vector<int> userFollowData = currUser.getFollows();
        std::vector<bool> matrixFollowData(size);
        for (int i = 0; i < userFollowData.size(); i++) {
            // set the ID - 1 to 1 to indicate that the user follows
            int idOfFollowed = userFollowData.at(i);
            matrixFollowData.at(idOfFollowed - 1) = 1;
        }
        // add in each user follow vector
        followerMatrix.push_back(matrixFollowData);
    }
}

/*
    This function creates the index HTML file based on the private 
    userData vector.
*/
void SocialNetwork::createIndex() {
    std::ofstream outFile("index.html");
    outFile << "<!DOCTYPE html>" << std::endl;
    outFile << "<html>" << std::endl;
    outFile << "<head>" << std::endl;
    outFile << "<title>My Social Network</title>" << std::endl;
    outFile << "</head>" << std::endl;
    outFile << "<body>" << std::endl;
    outFile << "<h1>My Social Network: User List</h1>" << std::endl;
    outFile << "<o1>" << std::endl;

    // print all user html links
    User currUser;
    for (int i = 0; i < userData.size(); i++) {
        currUser = userData.at(i);
        outFile << "<li><a href=\"user" << currUser.getID() << ".html\">" 
                  << currUser.getName() << "</a></li>" << std::endl;
    }

    outFile << "</o1>" << std::endl;
    outFile << "</body>" << std::endl << std::endl;
    outFile << "</html>" << std::endl << std::endl;
    
    outFile.close();
}

/*
    This function creates each individual user HTML file that is in the 
    private userData vector. It outputs the user's name, location, picture,
    follows, followers, and mutuals in their respective HTML files.
*/
void SocialNetwork::createUserHTML() {
    User currUser;
    std::string file;
    for (int i = 0; i < userData.size(); i++) {
        currUser = userData.at(i);
        file = "user" + std::to_string(currUser.getID()) + ".html";
        std::ofstream outFile(file);

        // user bio
        outFile << "<!DOCTYPE html>" << std::endl;
        outFile << "<head>" << std::endl;
        outFile << "<title>" << currUser.getName() << " Profile</title>" << std::endl;
        outFile << "</head>" << std::endl;
        outFile << "<body>" << std::endl;
        outFile << "<h1>" << currUser.getName();
        if (currUser.getLocation() != "") outFile << " in " << currUser.getLocation();
        outFile << "</h1>" << std::endl;
        outFile << "<img alt=\"Profile pic\" src=\"" << currUser.getPicURL() << "\" />" << std::endl;

        // bool to see if follows/followers/mutuals is empty
        bool empty = true;
        
        // follows
        outFile << "<h2>Follows</h2>" << std::endl;
        std::vector<int> followData = currUser.getFollows();
        for (int j = 0; j < followData.size(); j++) {
            empty = false;
            if (j == 0) outFile << "<u1>" << std::endl;
            int followedID = followData.at(j);
            outFile << "<li><a href=\"user" << std::to_string(followedID) << ".html\">" 
                    << userData.at(followedID - 1).getName() << "</a></li>" << std::endl;
        }
        if (empty) outFile << "<p>None</p>" << std::endl;
        else {
            empty = true;
            outFile << "</u1>" << std::endl;
        }

        // followers
        outFile << "<h2>Followers</h2>" << std::endl;
        for (int j = 0; j < userData.size(); j++) {
            // current user = i, check if anyone(j) follows i
            if (followerMatrix.at(j).at(i) == 1) {
                // after finding first follower output beginning of unordered list
                if (empty) {
                    outFile << "<u1>" << std::endl;
                    empty = false;
                }
                outFile << "<li><a href=\"user" << std::to_string(j + 1) << ".html\">"
                        << userData.at(j).getName() << "</a></li>" << std::endl;
            }
        }
        if (empty) outFile << "<p>None</p>" << std::endl;
        else {
            empty = true;
            outFile << "</u1>" << std::endl;
        }

        // mutuals
        outFile << "<h2>Mutuals</h2>" << std::endl;
        for (int j = 0; j < followData.size(); j++) {
            // look at who the current user(i) follows and check if that person(j) follows back
            int followedID = followData.at(j) - 1;
            if (followerMatrix.at(followedID).at(i) == 1) {
                if (empty) {
                    outFile << "<u1>" << std::endl;
                    empty = false;
                }
                outFile << "<li<a href=\"user" << std::to_string(followedID + 1)
                        << ".html\">" << userData.at(followedID).getName()
                        << "</a></li>" << std::endl;
            }
        }
        if (empty) outFile << "<p>None</p>" << std::endl;
        else {
            empty = true;
            outFile << "</u1>" << std::endl;
        }
        outFile << "</body>" << std::endl << std::endl;
        outFile << "</html>" << std::endl << std::endl;
        
        outFile.close();
    }
}