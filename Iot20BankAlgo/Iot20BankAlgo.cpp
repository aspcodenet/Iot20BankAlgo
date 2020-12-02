#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

class Account
{
public:
	Account() {  }
	Account(std::string id, float balance = 0)
	{
		this->id = id;
		this->balance = balance;
	}
	std::string GetId()
	{
		return id;
	}
private:
	std::string id;
	float balance;
};

class IAccountStorage
{
public:
	virtual void AddAccount(std::string id) = 0;
	virtual Account* GetAccount(std::string id) = 0;
};

class VectorAccountStorage : public IAccountStorage
{
public:
	~VectorAccountStorage()
	{
		for (int i = 0; i < accounts.size(); i++)
			delete accounts[i];
	}
	void AddAccount(std::string id) override
	{
		Account* account = new Account(id);
		accounts.push_back(account);
	}
	Account* GetAccount(std::string id) override
	{
		for (int i = 0; i < accounts.size(); i++)
			if (accounts[i]->GetId() == id) return accounts[i];
		return nullptr;
	}
private:
	std::vector<Account *> accounts;
};



class VectorAccountNoPtrStorage : public IAccountStorage
{
public:
	void AddAccount(std::string id) override
	{
		Account account = Account(id);
		accounts.push_back(account);
	}
	Account* GetAccount(std::string id) override
	{
		for (int i = 0; i < accounts.size(); i++)
			if (accounts[i].GetId() == id) return &accounts[i];
		return nullptr;
	}
private:
	std::vector<Account> accounts;
};


class VectorAccountMapStorage : public IAccountStorage
{
public:
	void AddAccount(std::string id) override
	{
		Account account = Account(id);
		accounts[id] = account;
	}
	Account* GetAccount(std::string id) override
	{
		Account a = accounts[id];
		if (a.GetId() == id)
			return &a;
		return nullptr;
	}
private:
	map<string, Account> accounts;
};






class Bank
{
public:
	Bank(IAccountStorage* storage)
	{
		accountStorage = storage;
	}
	bool AddAccount(std::string id)
	{
		//if (id[0] == '1') return false;
		accountStorage->AddAccount(id);
		return true;
	}
	Account* GetAccount(std::string id)
	{
		return accountStorage->GetAccount(id);
	}
private:
	IAccountStorage* accountStorage;
};


void MapDemo()
{
//	map<string, Account> accounts;


	
	map<int,string> jerseys;
	jerseys[13] = "Mats Sundin";
	
	map<string, int> accounts;
	accounts["1343"] = 122;
	accounts["1223"] = 100;
	accounts["1223"] = accounts["1223"] + 100;

	string cont;
	cin >> cont;
}


int main()
{
	//MapDemo();

	
	//SJUSOVARE?? :) Ta main.cpp från studentportalen i "Uppgift bankalgoritmer" (Introduktion)
	//och skapa ett C++ projekt och bara pasta in. Precis detta jag gjort här.
	//så börjar vi på samma nivå
	//
	// kl 09:00 börjar vi med denna labb
	/*	 Loop i main som skapar konton med id från  "1" -> "500000" - OBS ja ta 500000 istället
		Sen i main ska du göra sökningar - och mäta/skriva ut hur många millisekunder frågan tar!
		cin >> kontonummer
		bank->GetAccount(kontonummer)
		Konto hittades/hittades inte. Tog 23 millisekunder...
	 */


	/*
	 * Reflektion: SVÅRT  ? Ja!
	 * Vad ska ni kunna ? Förstå skillnader JA
	 *						Skriva egen kod typ som nedan: NEJ
	 * Jag förenklar snart livet för er: - alltid vector, alltid objekt (inte new)						
	 */
	

	//
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point slut;

	//VectorAccountStorage* storage = new VectorAccountStorage();
	VectorAccountNoPtrStorage* storage = new VectorAccountNoPtrStorage();
	//VectorAccountMapStorage* storage = new VectorAccountMapStorage();
	Bank* bank = new Bank(storage);

	int antal = 500000;

	start = high_resolution_clock::now();
	for(int i = 0; i < antal;i++)
	{
		//Add some noice to the heap
		bank->AddAccount(std::to_string(i));
	}

	slut = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(slut - start).count();
	std::cout << "Insert tog " << duration << " milliseconds\n";


	while(1)
	{
		string kontonummer;
		cout << "Ange kontonummer:";
		cin >> kontonummer;
		
		start = high_resolution_clock::now();
		Account* acc = bank->GetAccount(kontonummer);
		slut = high_resolution_clock::now();
		
		if (acc == NULL)
		{
			printf("Konton finns inte");
		}
		else
			printf("Konton finns");

		auto duration = duration_cast<milliseconds>(slut - start).count();
		std::cout << "Sök tog " << duration << " milliseconds\n";

	}
	return 0;
}