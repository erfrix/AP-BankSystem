#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
using namespace std;

class Transaction  
{
	private:
		string Sender;
		string Reciever;
		long int Amount;
	public:

		Transaction(string,string,long int);
};
#endif