#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transaction.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Account  
{
	private:
		string Username;
		string CardNumber;
		time_t CreationDate;
		time_t ExpirationDate;
		long int Balance;
		long int Loan;
		vector<Transaction> User_transactions;
		vector<string> IPs_Allowed;

	public:

		Account(string , string , string);
		void renewal();
		void add_ip(string);
		void deposit(long int);
		bool transfer(vector<Account>&, string, long int);
		bool withdraw(long int);
		void add_profits();
		bool get_loan(vector<Account>&, long int);
		void pay_loan(long int);

		//getters setters
		long int getBalance();
		string getCardNumber();
		string getUsername();
		long int getLoanVal();
		time_t getExpireDate();
		time_t getCreationDate();
		vector<string> getAllowedIPs();
		void print_info();

};
#endif //ACCOUNT_H