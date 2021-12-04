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

void Account::print_info()
{   
    cout << "---------------------------------------" << endl;
    cout << "Info about account username : " << this->Username << endl;
    cout << "Ips Allowed : ";
    for (auto it = IPs_Allowed.begin() ; it != IPs_Allowed.end() ; it++)
    {
        cout << *it;
        if(it != IPs_Allowed.end())
            cout << " ";
    }
    cout << endl;

    cout << "Card Number : " << CardNumber << endl;
    cout <<  "Balance : " << Balance << endl;
    cout << "Loans : " <<  Loan << endl;
    char *c_date = ctime(&CreationDate);
    cout << "Creation Date :" << c_date << endl;
    char *e_date = ctime(&ExpirationDate);
    cout << "Expiration Date : " << e_date << endl;
    cout << "---------------------------------------" << endl;
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
    auto it = IPs_Allowed.end();
    it--;
    cout << "IP ADDED: " <<  (*it) << endl;
}

void Account::deposit(long int d)
{
    if(d > 0)
        this->Balance += d;
}

bool Account::transfer(vector<Account>& AccountList , string r_username , long int money)
{

    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == r_username)
        {
            if(this->Balance >= money)
            {
                (*it).deposit(money);
                this->Balance -= money;
                return true;
            }
            else
            {
                cout << "Not enough balance to transfer"<<endl;
                return false;
            }
            
        }
    }

    cout << "No user with username : " << r_username << endl;
    return false;
    
}

bool Account::withdraw(long int w)
{
    if(this->Balance - w >= 0)
    {
        this->Balance -= w;
        cout << "Withdrawn : " << w << endl;
        cout << "Current Balance : " << this-Balance << endl; 
        return true;
    }
    else
    {
        cout << "Error : Not Enough Balance!" << endl;
        cout << "Current Balance : " << this-Balance << endl;
        return false;
    }
}

void Account::add_profits()
{
    this->Balance = this->Balance * 109/100;   
}

bool Account::get_loan(vector<Account>& AccountList, long int l)
{
    long int sum = 0; //Bank's Balance
    for (auto it = AccountList.begin() ; it != AccountList.end() ; it++)
    {
        sum += (*it).getBalance();
    }
    if(sum >= l)
    {
        if(this->Balance*3/4 >= l)
        {
            this->Loan = (l*115/100); 
            return true;
        }
        else
        {
            cout << "Can't give loan. You have insufficient balance. (3/4 Balance)" << endl;
            return false;
        }
    }
    else
    {
        cout << "Can't give loan. Not enough balance in bank." << endl;
        return false;
    }
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

        return;
    }
    else
    {
        cout << "There is no loan to be paid." << endl;
        return;
    }
}

string Account::getCardNumber()
{
    return this->CardNumber;
}

string Account::getUsername()
{
    return this->Username;
}

vector<string> Account::getAllowedIPs()
{
    return IPs_Allowed;
}

long int Account::getBalance()
{
    return this->Balance;
}

long int Account::getLoanVal()
{
    return this->Loan;
}

time_t Account::getExpireDate()
{
    return this->ExpirationDate;
}

time_t Account::getCreationDate()
{
    return this->CreationDate;
}