#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transaction.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class account  
{
	private:
		string Username;
		string CardNumber;
		time_t CreationDate;
		time_t ExpirationDate;
		long int Balance;
		vector<transaction> User_transactions;
		vector<string> IPs_Allowed;

	public:

		account(string , string);
		virtual ~account();

};
#endif //ACCOUNT_H