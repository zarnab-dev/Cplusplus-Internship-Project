#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>

class authsystem {
private:
    bool userexists(const std::string& username);
public:
    int registeruser();
    int loginuser();
    void changepassword(); // New function for updating credentials
    void forgotpassword(); // Recovery via 5-digit ID
};

#endif