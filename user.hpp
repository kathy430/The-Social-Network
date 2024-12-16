#ifndef USER_HPP
#define USER_HPP

#include <vector>

class User {
    public:
        // default constructor
        User();
        
        // copy constructor
        User(const User& other);

        // destructor
        ~User() {};

        std::vector<User> getData(std::string inputFile);
        
        // set user variables 
        void setID(std::string idData);
        void setName(std::string nameData);
        void setLocation(std::string locationData);
        void setPicURL(std::string urlData);
        void setFollows(std::vector<int> followsData);

        // get user variables
        int getID();
        std::string getName();
        std::string getLocation();
        std::string getPicURL();
        std::vector<int> getFollows();

    private:
        int id;
        std::string name;
        std::string location;
        std::string picURL;
        std::vector<int> follows;
};

#endif