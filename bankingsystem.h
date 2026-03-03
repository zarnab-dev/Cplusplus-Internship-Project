#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include <vector>
#include <string>

struct transaction { std::string type; double amount; };

class bankingsystem {
private:
    int account_id;
    double balance;
    std::vector<transaction> history;
public:
    explicit bankingsystem(int id);
    int get_id() const { return account_id; }
    void deposit();
    void withdraw();
    void transfer(std::vector<bankingsystem>& all_accounts);
    void showstatus() const;
};

#endif