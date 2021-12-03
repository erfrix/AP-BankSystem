#include "account.hpp"  

//Creation of new account
Account::Account(string username , string ip , string cardnumber)
{
    //set username - checked if duplicate in main
    this->Username = username;
    //set the first allowed ip to access
    IPs_Allowed.push_back(ip);
    //set bal to 0
    this->Balance = 0;
    //set loan to 0
    this->Loan = 0;
    //set card number - checked if duplicate in main
    this->CardNumber = cardnumber;

    //set creation date
    this->CreationDate = time(NULL);

    //set expiration date
    struct tm creation_t = *localtime(&CreationDate);
    struct tm expiration_t = creation_t;
    expiration_t.tm_year += 2;
    this->ExpirationDate = mktime(&expiration_t);
    
}

void Account::renewal()
{
    if(this->Balance >= 5)
    {
        struct tm expiration_t = *localtime(&ExpirationDate);
        expiration_t.tm_year += 2;
        this->ExpirationDate = mktime(&expiration_t);
        this->Balance -= 5;
    }
    else
    {
        cout << "Not Enough Balance To Renew. Giving Loan." << endl;
        this->Loan = 5 - this->Balance;
        cout << "Loan Given :" << this->Loan << endl;
        this->Balance = 0;
        cout << "Balance set to 0" << endl;
    }
}

void Account::add_ip(string ip)
{
    IPs_Allowed.push_back(ip);
}

void Account::deposit(long int d)
{
    if(d > 0)
        this->Balance += d;
}
int Account::withdraw(long int w)
{
    if(this->Balance - w >= 0)
    {
        this->Balance -= w;
        cout << "Withdrawn : " << w << endl;
        cout << "Current Balance : " << this-Balance << endl; 
        return 1;
    }
    else
    {
        cout << "Error : Not Enough Balance!" << endl;
        cout << "Current Balance : " << this-Balance << endl;
        return -1;
    }
}
void Account::add_profits()
{
    this->Balance = this->Balance * 109/100;   
}
int Account::get_loan(long int l)
{
    if(this->Loan == 0)
        this->Loan = l; 
}
void Account::pay_loan(long int l)
{
    if(this->Loan > 0)
    {
        if(this->Loan - l < 0)
        {
            this->Balance = l - this->Loan;
            this->Loan = 0;
        }
        else
        {
            this->Loan -= l;
        }
    }
}