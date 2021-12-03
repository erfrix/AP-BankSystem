#include <iostream>
#include <string>
#include <vector>

#include "account.hpp"
#include "transaction.hpp"

using namespace std;

vector<Transaction> Bank_transactions;
vector<Account> Accounts;

void create()
{
    string data_usr_ip;
    cin >> data_usr_ip;

    string temp = data_usr_ip;
    int p = 0;
    string extract[2];

    string username , ip , cardnumber;

    if(temp.find(" ") == string::npos)
    {
        data_usr_ip += ":"; // for the loop to work 
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
        cout << "Cannot accept input. Please don't use spaces." << endl;
    }
    
    bool c1 = check_username(username);
    bool c2 = check_ip(ip);
    cardnumber = generate_cardnumber();



}

bool check_username(string username)
{
    char first_char = username[0];
    string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    if(isdigit(first_char) == 0)
    {
        return (username.find_first_not_of(allowedChars) == string::npos);
    }
    else
        return false;
}

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
        for (auto it : Accounts)
        {
            if(it.getCardNumber() == cardnumber)
            success = false;
        }
    }
    cout << "Card Number : " << cardnumber << endl;

    return cardnumber;

}

void add_ip()
{

}

void renewal()
{

}

void deposit()
{

}

void withdraw()
{

}

void transfer()
{

}

void add_profits()
{

}

void get_loan()
{

}

void pay_loan()
{

}

void show_info()
{

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
            create();
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
        else if(command == "add_profits")
            add_profits();
        else if(command == "get_loan")
            get_loan();
        else if(command == "pay_loan")
            pay_loan();
        else if(command == "ip" || command == "card_number")
            show_info();
        else if(command == "bank")
            show_bank_info;
    }

}