#include "transaction.hpp" 
	
Transaction::Transaction(string sender , string reciever , long int amount)
{
    this->Sender = sender;
    this->Reciever = reciever;
    this->Amount = amount;

}