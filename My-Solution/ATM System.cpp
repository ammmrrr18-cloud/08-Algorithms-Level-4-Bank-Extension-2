
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

void ShowATMMainMenueScreen();
void ShowQuickWithdrawScreen();
void ShowNormalWithDrawScreen();
void Login();



enum enATM_MainMenue
{
	enQuickWithdraw = 1, NormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5
};

struct stClientInfo
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};


const string ClientFileName = "Clients.text";
stClientInfo CurrentClient;



vector <string> SplitString(string S1, string Delim)
{
	vector <string> vString;

	short Pos = 0;
	string sWord;

	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos);

		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, Pos + Delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}

	return vString;
}

stClientInfo ConvertLineToRecorde(string DateLine, string Seperatopr = "#//#")
{
	vector <string>vClients = SplitString(DateLine,Seperatopr);
	stClientInfo UserInfo;

	UserInfo.AccountNumber = vClients[0];
	UserInfo.PinCode = vClients[1];
	UserInfo.Name = vClients[2];
	UserInfo.Phone = vClients[3];
	UserInfo.AccountBalance = stod(vClients[4]);

	return UserInfo;
}

vector<stClientInfo> LoadClientDataFromFile(string FileName)
{

	vector<stClientInfo>vClients;

	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string DateLine = "";
		stClientInfo User;

		while (getline(MyFile, DateLine))
		{
			User = ConvertLineToRecorde(DateLine);
			vClients.push_back(User);
		}
		MyFile.close();
	}
	
	return vClients;
}

short ReadATMMainMenue()
{
	short Number = 0;

	do
	{
		cout << "Choose What do you want to do ?(1 To 5)?";
		cin >> Number;

	} while (Number < 1 || Number>5);

	return Number;
}

short GetWithdrawAmount(short QuickWithDrawOption)
{
	short arrWithdrawAmount[] = { 20,50,100,200,400,600,800,1000,9 };

	return arrWithdrawAmount[QuickWithDrawOption - 1];

}

short ReadQuickWithdrawOptioin()
{

	short Number = 0;

	while (Number<1 || Number>9)
	{
		cout << "Choose What to withdraw from [1] to [9] ?";
		cin >> Number;
	}

	return Number;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress AnyKey To Go Back To Main Menue...";
	system("pause>0");
	ShowATMMainMenueScreen();
}

string ConvertRecordToLine(stClientInfo Client, string Seperatopr = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperatopr;
	stClientRecord += Client.PinCode + Seperatopr;
	stClientRecord += Client.Name + Seperatopr;
	stClientRecord += Client.Phone + Seperatopr;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

vector <stClientInfo> SaveCleintsDataToFile(string FileName, vector <stClientInfo> vClients)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{

		for (stClientInfo C : vClients)
		{

			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.  
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;

			}

		}

		MyFile.close();

	}

	return vClients;

}

double ReadDepositAmount()
{
	double Amount;
	cout << "\nEnter a positive Deposit Amount? ";

	cin >> Amount;
	while (Amount <= 0)
	{
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;
	}
	return Amount;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClientInfo>& vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{

		for (stClientInfo& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

				return true;
			}

		}


	}
	return false;
}

void PerformDepositOption(vector<stClientInfo> vClients,double DepositAmount)
{

	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients))
	{
		CurrentClient.AccountBalance += DepositAmount;
	}

}

void PerformQuickWithdrawByAccountNumber(vector<stClientInfo>&vClients, short QuickWithDrawOption)
{

	if (QuickWithDrawOption == 9)
		return;

	short WithdrawAmount = GetWithdrawAmount(QuickWithDrawOption);


	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance,make another choice.\n";
		cout << "Press AnyKey To Continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClients))
	{
		CurrentClient.AccountBalance -= WithdrawAmount;
	}
	
}

void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "==============================================\n";
	cout << "\t\tQuick Withdraw Menue\n";
	cout << "==============================================\n";
	cout << "\t[1] 20           [2] 50    \n";
	cout << "\t[3] 100          [4] 200     \n";
	cout << "\t[5] 400          [6] 600    \n";
	cout << "\t[7] 800          [8] 1000  \n";
	cout << "\t[9] Exit\n";
	cout << "==============================================\n";
	cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;

	vector<stClientInfo>vClients = LoadClientDataFromFile(ClientFileName);


	PerformQuickWithdrawByAccountNumber(vClients, ReadQuickWithdrawOptioin());
}

int ReadNormalWithdraw()
{
	int Amount = 0;

	cout << "\nEnter an amount multiple of 5's ? ";

	cin >> Amount;

		
	while (Amount % 5 != 0)
	{
		cout << "\nPlease enter an amount in multiples of 5?";
		cin >> Amount;
	}
	
	return Amount;
}

void PerfromNormalWithdrawOption(vector<stClientInfo>&vClients, double WithdrawAmount)
{

	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance,make another choice.\n";
		cout << "Press AnyKey To Continue...";
		system("pause>0");
		ShowNormalWithDrawScreen();
		return;

	}

	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClients))
	{
		CurrentClient.AccountBalance -= WithdrawAmount;
	}
}

int ReadPositiveDepositAmount()
{
	int Number = 0;

	do
	{

		cout << "\nEnter a positive Deposit Amount ?";
		cin >> Number;

	} while (Number < 0);

	return Number;
}

void ShowDepositScreen()
{
	cout << "==============================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "==============================================\n";

	vector<stClientInfo> vClients = LoadClientDataFromFile(ClientFileName);


	PerformDepositOption(vClients, ReadDepositAmount());
}

void ShowNormalWithDrawScreen()
{
	system("cls");
	cout << "==============================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "==============================================\n";

	vector<stClientInfo>vClients = LoadClientDataFromFile(ClientFileName);

	PerfromNormalWithdrawOption(vClients, ReadNormalWithdraw());
}

void ShowCheckBalanceScreen()
{
	cout << "==============================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "==============================================\n";

	cout << "\nYour Balance is : " << CurrentClient.AccountBalance;

}


void PerformATMMainMenueScreen(enATM_MainMenue ATM_MainMenue)
{
	switch (ATM_MainMenue)
	{
	case enATM_MainMenue::enQuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenue();
		break;

	case enATM_MainMenue::NormalWithdraw:
		system("cls");
		ShowNormalWithDrawScreen();
		GoBackToMainMenue();
		break;

	case enATM_MainMenue::enDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenue();
		break;

	case enATM_MainMenue::enCheckBalance:
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenue();
		break;

	case enATM_MainMenue::enLogout:
		Login();


	}
}

void ShowATMMainMenueScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\tATM Main Menue Screen\n";
	cout << "====================================\n";
	cout << "[1] Quick Withdraw.\n";
	cout << "[2] Normal Withdraw.\n";
	cout << "[3] Deposit .\n";
	cout << "[4] Check Balance.\n";
	cout << "[5] Logout .\n";
	cout << "====================================\n";

	PerformATMMainMenueScreen((enATM_MainMenue)ReadATMMainMenue());

}

bool FindClientByAccountNumberAndPinCode(string AccountNumber,string PinCode, stClientInfo &ClientInfo)
{
	vector<stClientInfo>vClients = LoadClientDataFromFile(ClientFileName);

	for (stClientInfo&Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
		{
			ClientInfo = Client;
			return true;
		}
	}

	return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
	if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
		return true;
	else
		return false;
}

string ReadAccountNumber()
{
	string AccountNumber = "";

	cout << "Enter Account Number ? ";
	cin >> AccountNumber;

	return AccountNumber;
}

string ReadPinCode()
{
	string PinCode = "";

	cout << "Enter PinCode ?";
	cin >> PinCode;

	return PinCode;
}

void Login()
{
	
	string AccountNumber = "", PinCode = "";

	bool LoginFail = false;
	do
	{
		system("cls");
		cout << "---------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "---------------------------\n";

		if (LoginFail)
		{
			cout << "Invlaid Account Number/PinCode !\n";
		}

		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();


		LoginFail = !LoadClientInfo(AccountNumber, PinCode);


	} while (LoginFail);


	ShowATMMainMenueScreen();

}


int main()
{
   

	Login();





	return 0;
}

