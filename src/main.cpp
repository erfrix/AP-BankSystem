#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "account.hpp"
#include "transaction.hpp"

using namespace std;

vector<Transaction> BankTransactions;
vector<Account> AccountList;

//Counts the ":" in string
int colonCounter(string s)
{
    int count = 0;
    int pos = 0;
    while(s.find(":" , pos) != string::npos)
    {
        pos = s.find(":" , pos) + 1;
        count++;
    }
    return count;
}

//Function to check username
bool check_username(string username , vector<Account>& subjects)
{
    //Check for duplicate.
    for (auto it = subjects.begin() ; it != subjects.end() ; it++)
    {
        if((*it).getUsername() == username)
        {
            cout << "Duplicate Username!" << endl;
            return false;
        }
    }
    
    char first_char = username[0];
    string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    if(isdigit(first_char) == false)
    {
        return (username.find_first_not_of(allowedChars) == string::npos);
    }
    else
        return false;
}

//Function to check each ip number
bool is_valid_ip_number(string s) //Checks if the number is valid for ip address. Also checks for negetive
{
    char first_digit = s[0];
    if(first_digit == '0' && s.length() != 1)
    {
        return false;
    } 
    else
    {
        if(!s.empty() && (s.find_first_not_of("0123456789") == string::npos))
        {
            int ip_number = stoi(s);
            if(ip_number >= 0 && ip_number <= 255)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

//Function that checks ip
bool check_ip(string ip)
{
    string numbers[4];
    
    int p = 0;
    if(ip.find(" ") == string::npos)
    {
        ip += "."; // for the loop to work 
        for (size_t i = 0; i < 4; i++)
        {
            p = ip.find(".");
            numbers[i] = ip.substr(0 , p);
            ip.erase(0 , p + 1);
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return false;
    }

    bool flag = true;
    for (size_t i = 0; i < 4; i++)
    {
        if(is_valid_ip_number(numbers[i]) == false)
            flag = false;
    }

    if(flag == true)
        return true;
    else
        return false;
    
}

//generates card number and checks if its duplicate. if yes generates another. at the end returns the card number as string.
string generate_cardnumber()
{
    bool success = false;
    string cardnumber;
    while(success != true)
    {
        success = true;

        srand(time(NULL));
        int number = 1000 + rand() % 9999;
        cardnumber = to_string(number); //Generates number : 1000 <= number <= 9999 -> 4 digits // Fast Random Generateion but it's biased.
        for (auto it = AccountList.begin() ; it != AccountList.end() ; it++)
        {
            if((*it).getCardNumber() == cardnumber)
            success = false;
        }
    }
    cout << "Card Number : " << cardnumber << endl;

    return cardnumber;

}

bool is_allowed_ip(Account& subject , string ip)
{
    bool result = false;

    vector<string> allowedIps = subject.getAllowedIPs();

    for (auto it = allowedIps.begin() ; it != allowedIps.end() ; it++)
    {
        if(ip == (*it))
        {
            result = true;
        }
    }

    return result;
}


void create(vector<Account>& AccountList)
{
    string data_usr_ip;
    cin >> data_usr_ip;

    string temp = data_usr_ip;
    int p = 0;
    string extract[2];

    string username , ip , cardnumber;

    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 1)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 2; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }

            username = extract[0];
            ip = extract[1];
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
            
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }
    
    bool c1 = check_username(username , AccountList);
    bool c2 = check_ip(ip);
    cardnumber = generate_cardnumber();

    if(c1 && c2)
    {
        AccountList.push_back( Account(username , ip , cardnumber) );
    }
    
}

void add_ip()
{
    string username , ip;
    
    string data_usr_ip;
    cin >> data_usr_ip;
    
    string temp = data_usr_ip;//Backup
    int p = 0;
    string extract[2];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 1)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 2; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    if(check_ip(ip))
    {
        for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
        {
            if((*it).getUsername() == username)
            {
            (*it).add_ip(ip);
            found = true;
            }
        }  
    }
    else
    {
        cout << "IP is not valid." << endl;
        return;
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }   
}

void renewal()
{
    string username , ip;

    string data_usr_ip;
    cin >> data_usr_ip;

    string temp = data_usr_ip;//Backup
    int p = 0;
    string extract[2];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 1)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 2; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == username)
        {
            if(is_allowed_ip((*it) , ip))
            {
                found = true;
                (*it).renewal();
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }
}


void deposit()
{
    string username, ip;
    long int money;

    string data_usr_ip;
    cin >> data_usr_ip;
    string temp = data_usr_ip;//Backup

    int p = 0;
    string extract[3];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 2)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 3; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
            money = stol(extract[2] , nullptr , 10);
            if(money < 0)
            {
                cout <<"Negative Number Error" << endl;
                return;
            }
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == username)
        {
            if(is_allowed_ip((*it) , ip))
            {
                found = true;
                (*it).deposit(money);
                cout << "Deposit Complete" << endl;
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }
}

void withdraw()
{
    string username, ip;
    long int money;

    string data;
    cin >> data;
    string temp = data;//Backup

    int p = 0;
    string extract[3];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 2)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 3; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
            money = stol(extract[2] , nullptr , 10);
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == username)
        {
            if(is_allowed_ip((*it) , ip))
            {
                found = true;
                cout << "--------Withdraw--------" << endl;
                (*it).withdraw(money);
                cout << "-----End Of Withdraw-----" << endl;
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }
}

void transfer()
{
    string s_username, s_ip, r_username;
    long int money;

    string data;
    cin >> data;
    string temp = data;//Backup

    int p = 0;
    string extract[3];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 3)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 4; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            s_username = extract[0];
            s_ip = extract[1];
            r_username = extract[2];
            money = stol(extract[3] , nullptr , 10);
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    
    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == s_username)
        {
            if(is_allowed_ip((*it) , s_ip))
            {
                cout << "--------Transfer--------" << endl;
                found = true;
                (*it).transfer(AccountList , r_username , money);
                cout << "-----End of Transfer----" << endl;
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found. - Credentials are not valid." << endl;
        return;
    }
}

// void add_profits()
// {
//     string username, ip;

//     string data_usr_ip;
//     cin >> data_usr_ip;
//     string temp = data_usr_ip;//Backup

//     int p = 0;
//     string extract[3];
//     if(temp.find(" ") == string::npos)
//     {
//         if(colonCounter(temp) == 2)
//         {
//             temp += ":"; // for the loop to work 
//             for (size_t i = 0; i < 3; i++)
//             {
//                 p = temp.find(":");
//                 extract[i] = temp.substr(0 , p);
//                 temp.erase(0 , p + 1);
//             }
//             username = extract[0];
//             ip = extract[1];
//             money = stol(extract[2] , nullptr , 10);
//             if(money < 0)
//             {
//                 cout <<"Negative Number Error" << endl;
//                 return;
//             }
//         }
//         else
//         {
//             cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
//             return;
//         }
//     }
//     else
//     {
//         cout << "Cannot accept input. Please don't use spaces." << endl;
//         return;
//     }

//     bool found = false;
//     for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
//     {
//         if((*it).getUsername() == username)
//         {
//             if(is_allowed_ip((*it) , ip))
//             {
//                 found = true;
//                 (*it).deposit(money);
//                 cout << "Deposit Complete" << endl;
//                 return;
//             }
//         }
//     }

//     if(!found)
//     {
//         cout << "No Matches Found." << endl;
//         return;
//     }
// }

void get_loan()
{
    string username, ip;
    long int money;

    string data;
    cin >> data;
    string temp = data;//Backup

    int p = 0;
    string extract[3];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 2)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 3; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
            money = stol(extract[2] , nullptr , 10);
            if(money <= 0)
            {
                cout <<"Negative Number Or Zero Error" << endl;
                return;
            }
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == username)
        {
            if(is_allowed_ip((*it) , ip))
            {
                found = true;
                cout << "-------------Get Loan---------------" << endl;
                (*it).get_loan(AccountList , money);
                cout << "----------End Of Get Loan-----------" << endl;
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }
}

void pay_loan()
{
    string username, ip;
    long int money;

    string data;
    cin >> data;
    string temp = data;//Backup

    int p = 0;
    string extract[3];
    if(temp.find(" ") == string::npos)
    {
        if(colonCounter(temp) == 2)
        {
            temp += ":"; // for the loop to work 
            for (size_t i = 0; i < 3; i++)
            {
                p = temp.find(":");
                extract[i] = temp.substr(0 , p);
                temp.erase(0 , p + 1);
            }
            username = extract[0];
            ip = extract[1];
            money = stol(extract[2] , nullptr , 10);
            if(money <= 0)
            {
                cout <<"Negative Number Or Zero Error" << endl;
                return;
            }
        }
        else
        {
            cout << "Cannot accept input. Incorrect Syntax : Colon" << endl;
            return;
        }
    }
    else
    {
        cout << "Cannot accept input. Please don't use spaces." << endl;
        return;
    }

    bool found = false;
    for (auto it = AccountList.begin() ; it != AccountList.end(); it++)
    {
        if((*it).getUsername() == username)
        {
            if(is_allowed_ip((*it) , ip))
            {
                found = true;
                cout << "-------------Pay Loan---------------" << endl;
                (*it).pay_loan(money);
                cout << "----------End Of Pay Loan-----------" << endl;
                return;
            }
        }
    }

    if(!found)
    {
        cout << "No Matches Found." << endl;
        return;
    }
}

void show_info(Account& subject)
{
    cout << "--------------------------------------------" << endl;
    
    cout << "Account Username : " <<  subject.getUsername() << endl;
    cout << "Account Card Number : " << subject.getCardNumber() << endl;
    cout << "Balance : " << subject.getBalance() << endl;
    cout << "Loan : " << subject.getLoanVal() << endl;
    
    time_t T = subject.getExpireDate();
    cout << "Expiration : " <<  ctime(&T) << endl;
    T = subject.getCreationDate();
    cout << "Creation : " << ctime(&T)<< endl;
    
    cout << "IP Whitelist : " << endl;
    for (auto it = subject.getAllowedIPs().begin() ; it != subject.getAllowedIPs().end() ; it++)
    {
        cout << ">  "<< (*it) << endl;
    }

    cout << "--------------------------------------------" << endl;
    
}

void show_bank_info()
{
    
}

int main()
{

    while(1)
    {
        string command;
        cin >> command;
        if(command == "create")
            create(AccountList);
        else if(command == "add_ip")
            add_ip();
        else if(command == "renewal")
            renewal();
        else if(command == "deposit")
            deposit();
        else if(command == "withdraw")
            withdraw();
        else if(command == "transfer")
            transfer();
        // else if(command == "add_profits")
        //     add_profits();
        else if(command == "get_loan")
            get_loan();
        else if(command == "pay_loan")
            pay_loan();
        else if(command == "bank")
            show_bank_info;
        else
        {
            for (auto it = AccountList.begin() ; it != AccountList.end() ; it++)
            {
                for (auto it2 = (*it).getAllowedIPs().begin() ; it2 != (*it).getAllowedIPs().end() ; it2++)
                {
                    if((*it2) == command)
                    {
                        show_info((*it));
                    }
                }
                
            }
            
        }
    }

    return 0;

}