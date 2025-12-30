
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.text";
const string UsersFileName = "Users.txt";


struct sClientInfo
{
	string AccountNumber;
	string PIN;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct sUsersInfo
{
	string Name;
	string Password;
	short Permissions;
	bool MarkForDelete = false;
};



enum enMainMenueOptions {
	eClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdataClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogOut = 8
};
enum enTransactionsMenueOption { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };
enum enManageUsersOption { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainUserMenue = 6 };
enum enUserPermissions
{
	pAllPermission = -1,
	pShowChientList = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64,
};


sUsersInfo CurrentUser;


void ShowMainMenueScreen();
void ShowTransactionsMenueScreen();
void SaveClientsDataToFile(string FileName, vector<sClientInfo>& vClients);
void SaveClientDataToFile(string FileName, string stDataLine);
void Login();
void ShowMainUsersMenueScreen();
string ReadUserName();
string ReadUserPassword();
vector<sUsersInfo> LoadUsersDataFromFile(string FileName);




vector<string> SplitvString(string St1, string delim)
{
	vector <string> vString;
	short Pos = 0;
	string sWord = "";
	while ((Pos = St1.find(delim)) != string::npos)
	{
		sWord = St1.substr(0, Pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		St1.erase(0, Pos + delim.length());
	}
	if (St1 != "")
	{
		vString.push_back(St1);
	}
	return vString;
}
sUsersInfo ConvertUserLineToRecord(string strUserInfoLine, string Seperator = "#//#")
{
	sUsersInfo User;
	vector<string>vUsersData;

	vUsersData = SplitvString(strUserInfoLine, Seperator);

	User.Name = vUsersData[0];
	User.Password = vUsersData[1];
	User.Permissions = stoi(vUsersData[2]);

	return User;
}

sClientInfo ConvertLineToRecord(string strClientInfoLine, string Seperator = "#//#")
{
	sClientInfo Client;
	vector<string>vClientData;

	vClientData = SplitvString(strClientInfoLine, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PIN = vClientData[1];
	Client.Name = vClientData[2];
	Client.PhoneNumber = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

short ReadMainMenueOption()
{
	short Number = 0;

	do {

		cout << "\nChoose What do you want to do ?[1 To 8]?";
		cin >> Number;

	} while (Number < 1 || Number>8);

	return Number;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter an account number ?";
	cin >> AccountNumber;

	return AccountNumber;
}

bool ClientExistsByAccountNumber(string AccountNumber)
{
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{
		string DataLine = "";
		sClientInfo Client;

		while (getline(MyFile, DataLine))
		{
			Client = ConvertLineToRecord(DataLine);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}
	return false;
}

bool FindUserByUserName(string UserName, vector <sUsersInfo>& vUsers, sUsersInfo& UserInfo)
{

	for (sUsersInfo& U : vUsers)
	{
		if (U.Name == UserName)
		{
			UserInfo = U;
			return true;
		}
	}

	return false;
}

void PrintClientRecord(sClientInfo Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PIN;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

short ReadUsersPermissions()
{

	char Answer = 'n';
	short AllPermissions = 0;

	enUserPermissions UserPermissions;

	cout << "\nDo you want to give full access?y/n?";
	cin >> Answer;

	if (tolower(Answer) == 'y')
	{
		return enUserPermissions::pAllPermission;
	}
	else
	{
		

		cout << "\nDo you want to give access to?";


		cout << "\nShow Client List? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pShowChientList;


		cout << "\nAdd New Client? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pAddNewClient;


		cout << "\nDelete Client? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pDeleteClient;


		cout << "\nUpdate Client? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pUpdateClient;


		cout << "\nFind Client? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pFindClient;


		cout << "\nTransactions? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pTransactions;


		cout << "\nManage Users? y/n?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			AllPermissions = AllPermissions + enUserPermissions::pManageUsers;

	}

	return AllPermissions;
}

sClientInfo ReadNewClientInfo()
{
	sClientInfo ClientInfo;

	cout << "\nEnter an account number? ";
	getline(cin >> ws, ClientInfo.AccountNumber);

	while (ClientExistsByAccountNumber(ClientInfo.AccountNumber))
	{
		cout << "\nClient With [" << ClientInfo.AccountNumber << "] already exists,Enter another Account Number?";
		getline(cin, ClientInfo.AccountNumber);
	}


	cout << "\nEnter PinCode? ";
	getline(cin >> ws, ClientInfo.PIN);

	cout << "\nEnter Name? ";
	getline(cin, ClientInfo.Name);

	cout << "\nEnter Phone? ";
	getline(cin, ClientInfo.PhoneNumber);

	cout << "\nEnter AccountBalance? ";
	cin >> ClientInfo.AccountBalance;

	return ClientInfo;
}

string ConvertRecordeUserToLine(sUsersInfo& UsersInfo, string Dilem = "#//#")
{
	string DateLine = "";

	DateLine = UsersInfo.Name + Dilem + UsersInfo.Password + Dilem + to_string(UsersInfo.Permissions);

	return DateLine;
}

string ConvertRecordToLine(sClientInfo& ClientInfo, string Dilem = "#//#")
{
	string Text = "";

	Text += ClientInfo.AccountNumber + Dilem;
	Text += ClientInfo.PIN + Dilem;
	Text += ClientInfo.Name + Dilem;
	Text += ClientInfo.PhoneNumber + Dilem;
	Text += to_string(ClientInfo.AccountBalance);

	return Text;
}

bool CheckAccessPermission(enUserPermissions Permissions)
{

	if (CurrentUser.Permissions == enUserPermissions::pAllPermission)
		return true;

	if (Permissions & CurrentUser.Permissions)
		return true;


	return false;
}

void ShowAccessMessage()
{
	system("cls");
	cout << "\n*****************************************\n";
	cout << "Access Denied,\n";
	cout << "You don't have permission to do this,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "*****************************************\n";


}

void PrintUserCard(sUsersInfo& User)
{

	cout << "\nThe following are the User details:\n";

	cout << "-------------------------------------\n";
	cout << "UserName     :" << User.Name << endl;
	cout << "Password     :" << User.Password << endl;
	cout << "Permissions  :" << User.Permissions << endl;
	cout << "-------------------------------------\n";
}

void PrintUsersRecord(sUsersInfo User)
{
	cout << "|" << left << setw(15) << User.Name;
	cout << "|" << left << setw(15) << User.Password;
	cout << "|" << left << setw(15) << User.Permissions;
}

void SaveClientDataToFile(string FileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}

}

void AddNewClient()
{

	sClientInfo Client;

	Client = ReadNewClientInfo();
	SaveClientDataToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
	char AddMore = 'y';
	do
	{


		cout << "\nAdding New Client:\n";

		AddNewClient();

		cout << "\nClient added successfully,do you want to add more clients (Y or N) ?";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{
	for (sClientInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

void ShowAddNewClientsScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pAddNewClient))
	{
		ShowAccessMessage();
		return;
	}

	cout << "_______________________________________\n";
	cout << "\tAdding New Clients Screen\n";
	cout << "_______________________________________\n";

	AddNewClients();

}



bool FindClientAccountNumber(string AccountNumber, vector<sClientInfo>& vClients, sClientInfo& Client)
{

	for (sClientInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

vector<sClientInfo> LoadClientsDataFromFile(string FileName)
{


	vector<sClientInfo> vClients;

	fstream MyFile;

	MyFile.open(FileName, ios::in);


	if (MyFile.is_open())
	{
		string Line = "";
		sClientInfo Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}

void PrintClientCard(sClientInfo& ClientInfo)
{
	cout << "\nThe following are the client details:\n\n";

	cout << setw(17) << "AccountNumber   : " << ClientInfo.AccountNumber << endl;
	cout << setw(17) << "pin Code        : " << ClientInfo.PIN << endl;
	cout << setw(17) << "Name            : " << ClientInfo.Name << endl;
	cout << setw(17) << "Phone           : " << ClientInfo.PhoneNumber << endl;
	cout << setw(17) << "Account Balance : " << ClientInfo.AccountBalance << endl;

}

void SaveClientsDataToFile(string FileName, vector<sClientInfo>& vClients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClientInfo& C : vClients)
		{
			string DataLine = "";
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

}

void ShowAllClientsScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pShowChientList))
	{
		ShowAccessMessage();
		return;
	}


	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n\n";
	cout << "----------------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number ";
	cout << "| " << left << setw(10) << "Pin Code ";
	cout << "| " << left << setw(40) << "Client Name ";
	cout << "| " << left << setw(12) << "Phone ";
	cout << "| " << left << setw(8) << "Account Balance ";
	cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";


	if (vClients.size() == 0)
	{
		cout << "\n\nNo Available In The System !\n";
	}

	for (sClientInfo& Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n\n----------------------------------------------------------------------------------------------------------------\n\n";



}

void GoBackToMainMenue()
{
	cout << "\n\nPress Any Key To Go Back To Main Menue ...!";
	system("pause>0");
	ShowMainMenueScreen();
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{

	sClientInfo Client;
	char Answer = 'n';

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);


		cout << "\nAre you sure that you want to delete this Client\n";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);


			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\nClient deleted Successfully\n";

			return true;
		}
		else
		{
			cout << "\nClient was not deleted.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
	}
	return false;
}

sClientInfo ChangeClientRecord(string AccountNumber)
{
	sClientInfo ClientInfo;

	ClientInfo.AccountNumber = AccountNumber;

	cout << "\nEnter PinCode?";
	getline(cin >> ws, ClientInfo.PIN);

	cout << "\nEnter Name?";
	getline(cin, ClientInfo.Name);

	cout << "\nEnter Phone?";
	getline(cin, ClientInfo.PhoneNumber);

	cout << "\nEnter AccountBalance?";
	cin >> ClientInfo.AccountBalance;


	return ClientInfo;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClientInfo>& vClients)
{


	sClientInfo Client;
	char Answer = 'n';

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\nAre you sure that you want to update this Client? (Y or N)?";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			for (sClientInfo& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nClient Updated Successfully\n";
			return true;
		}
		else
		{
			cout << "\nClient was not Updated.\n";
			return false;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not found !\n\n";
		return false;
	}


}

void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pFindClient))
	{
		ShowAccessMessage();
		return;
	}

	cout << "---------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------\n";

	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	sClientInfo Client;

	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient With Account Number[" << AccountNumber << "] is Not found!" << endl;
	}

}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pDeleteClient))
	{
		ShowAccessMessage();
		return;
	}

	cout << "------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "------------------------------------\n";

	vector<sClientInfo>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);
}



void GoBackToTransactionMenue()
{
	cout << "\nPress Any Key To Go Back To Transaction Menue ...";
	system("pause>0");
	ShowTransactionsMenueScreen();
}

float ReadWithdrawAmount()
{
	float Amount = 0.0;

	cout << "\nPlease enter withdraw amount ?";
	cin >> Amount;

	return Amount;
}

void ShowUpdateClientInfoScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pUpdateClient))
	{
		ShowAccessMessage();
		return;
	}


	cout << "--------------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "--------------------------------------\n";

	vector<sClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);

}

bool DepositBalanceToClinetByAccountNumber(string AccountNumber, double Amount, vector<sClientInfo>& vClient)
{


	char Answer = 'n';

	cout << "\nAre you sure that you want to perform this transaction? y/n ?";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClientInfo& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance = C.AccountBalance + Amount;
				SaveClientsDataToFile(ClientsFileName, vClient);
				cout << "\nDone Successfully New Balance = " << C.AccountBalance << endl;
				return true;
			}
		}

	}

	return false;

}

void ShowTransactionDepositScreen()
{
	cout << "-----------------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-----------------------------------------\n";

	vector<sClientInfo>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	sClientInfo Client;

	while (!FindClientAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease enter an account number ?";
		AccountNumber = ReadClientAccountNumber();
	}


	PrintClientCard(Client);

	double Amount = 0.0;
	cout << "\nPlease enter deposit amount ?";
	cin >> Amount;



	DepositBalanceToClinetByAccountNumber(AccountNumber, Amount, vClient);

}

double TotalBalances(vector<sClientInfo>& vClient)
{
	double TotalBalances = 0.0;

	for (sClientInfo Client : vClient)
	{
		TotalBalances = TotalBalances + Client.AccountBalance;
	}

	return TotalBalances;
}

void PrintClientRecordBalanceLine(sClientInfo& Client)
{
	cout << "| " << left << setw(20) << Client.AccountNumber;
	cout << "| " << left << setw(35) << Client.Name;
	cout << "| " << left << setw(40) << Client.AccountBalance;

}




void ShowTotalBalances()
{
	vector<sClientInfo> vClient = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClient.size() << ") Client(s).\n";

	cout << "----------------------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(35) << "Client Name ";
	cout << "| " << left << setw(40) << "Account Balance ";
	cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";


	if (vClient.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In The System!";
	}
	else
	{

		for (sClientInfo& Client : vClient)
		{
			PrintClientRecordBalanceLine(Client);
			cout << endl;
		}

		cout << "\n\n----------------------------------------------------------------------------------------------------------------------\n\n";

		cout << "\t\t\t\t\t\tTotal Balances = " << TotalBalances(vClient) << endl;
	}

}

void ShowTransactionsWithdrawScreen()
{
	cout << "-------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------------\n";

	vector<sClientInfo>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	sClientInfo Client;

	while (!FindClientAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		cout << "\nPlease enter an account number ?";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0.0;
	cout << "\nPlease enter deposit amount ?";
	cin >> Amount;


	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance,you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount ?";
		cin >> Amount;
	}


	DepositBalanceToClinetByAccountNumber(AccountNumber, Amount * -1, vClient);


}

void ShowExitScreen()
{
	cout << "------------------------------\n";
	cout << "\tProgram Ends\n";
	cout << "------------------------------\n";
}

void PerformTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption)
{

	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOption::eDeposit:
		system("cls");
		ShowTransactionDepositScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eWithdraw:
		system("cls");
		ShowTransactionsWithdrawScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eTotalBalances:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOption::eMainMenue:

		ShowMainMenueScreen();

	}


}

short ReadTransactionsMenueOption()
{
	short Choice = 0;

	do
	{
		cout << "\nChoose What do you want to do?[1 To 4]?";
		cin >> Choice;

	} while (Choice < 1 || Choice > 4);

	return Choice;
}

void ShowTransactionsMenueScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pTransactions))
	{
		ShowAccessMessage();
		return;
	}
	system("cls");
	cout << "==========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "==========================================\n";


	PerformTransactionsMenueOption((enTransactionsMenueOption)ReadTransactionsMenueOption());
}

void SaveUsersDataToFile(string FileName, vector<sUsersInfo>& vUsers)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sUsersInfo& U : vUsers)
		{
			string DataLine = "";
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertRecordeUserToLine(U);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

}

bool MarkUserForDeleteByUsername(string Username, vector <sUsersInfo>& vUsers)
{

	for (sUsersInfo& User : vUsers)
	{
		if (User.Name == Username)
		{
			User.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteUserByUserName(string Username, vector <sUsersInfo>& vUsers)
{
	sUsersInfo UsersInfo;

	if (Username == "Admin")
	{
		cout << "\nYou can Not delete this User.";
		return false;
	}

	if (!FindUserByUserName(Username, vUsers, UsersInfo))
	{
		cout << "\nUser with Username (" << Username << ") is Not found !\n\n";
		return false;
	}
	else
	{

		PrintUserCard(UsersInfo);


		char Answer = 'n';

		cout << "Are you sure that you want to delete this user ?y/n?";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			vUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "\nUser Deleted Successfully.\n";
			return true;
		}
		else
		{
			cout << "\nUser was not deleted.\n";
		}

	}



}

void ShowDeleteUsersScreen()
{
	cout << "------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "------------------------------------\n";

	vector <sUsersInfo>vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();

	DeleteUserByUserName(Username, vUsers);

}

sUsersInfo ChangeUserRecorde(string Username)
{
	sUsersInfo UserInfo;

	UserInfo.Name = Username;
	UserInfo.Password = ReadUserPassword();
	UserInfo.Permissions = ReadUsersPermissions();

	return UserInfo;
}

bool UpdateUserByUsername(string Username, vector<sUsersInfo>& vUsers)
{
	sUsersInfo UserInfo;

	if (!FindUserByUserName(Username, vUsers, UserInfo))
	{
		cout << "\nUser with Username (" << Username << ") is Not found !\n\n";
		return false;
	}
	else
	{
		PrintUserCard(UserInfo);

		char Answer = 'n';
		cout << "\n\nAre you sure that you want to update this User?y/n?";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			for (sUsersInfo& U : vUsers)
			{
				if (U.Name == Username)
				{
					U = ChangeUserRecorde(Username);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\nUser Updated Successfully\n";
			return true;
		}
		else
		{
			cout << "\nUser was not Updated.\n";
			return false;
		}


	}
}

void ShowUpdateUserScreen()
{
	cout << "--------------------------------------\n";
	cout << "\tUpdate Users Screen\n";
	cout << "--------------------------------------\n";

	vector<sUsersInfo>vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();

	UpdateUserByUsername(Username, vUsers);

}

void ShowFindUserScreen()
{
	cout << "---------------------------------\n";
	cout << "\tFind User Screen\n";
	cout << "---------------------------------\n";

	sUsersInfo UserInfo;
	vector<sUsersInfo>vUser = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	if (!FindUserByUserName(UserName, vUser, UserInfo))
	{
		cout << "\nUser with Username (" << UserName << ") is Not found !\n\n";
	}
	else
	{
		PrintUserCard(UserInfo);
	}
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOptions)
{


	switch (MainMenueOptions)
	{
	case enMainMenueOptions::eClientsList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdataClient:
		system("cls");
		ShowUpdateClientInfoScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactions:
		system("cls");
		ShowTransactionsMenueScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eManageUsers:
		system("cls");
		ShowMainUsersMenueScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eLogOut:
		system("cls");
		Login();
		break;
	}

}

void ShowMainMenueScreen()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tMain Menue Screen.\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Updata Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout\n";
	cout << "=============================================\n";

	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}




vector<sUsersInfo> LoadUsersDataFromFile(string FileName)
{

	vector<sUsersInfo> vUsers;

	fstream MyFile;

	MyFile.open(UsersFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		sUsersInfo User;

		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			vUsers.push_back(User);
		}

		MyFile.close();
	}

	return vUsers;
}


short ReadMainUsersOption()
{
	short Optoin = 0;

	do
	{
		cout << "\nChoose what do you want to do ?";
		cin >> Optoin;

	} while (Optoin < 1 || Optoin > 6);

	return Optoin;
}

void GoBackToMainManageMenue()
{
	cout << "\n\nPress Any Key To Go Back To Main Manage Menue Screen...";
	system("pause>0");
	ShowMainUsersMenueScreen();
}

void ShowAllUsersScreen()
{
	vector <sUsersInfo> vUsers = LoadUsersDataFromFile(UsersFileName);


	cout << "\t\t\tUsers List(" << vUsers.size() << ") User(s)\n\n";

	cout << "----------------------------------------------------------------------------------------------------------\n";
	cout << "|" << left << setw(15) << "User Name";
	cout << "|" << left << setw(15) << "Password";
	cout << "|" << left << setw(15) << "Permissions";
	cout << "\n\n----------------------------------------------------------------------------------------------------------\n";

	if (vUsers.size() == 0)
	{
		cout << "\n\nNo Available In The System !\n";
	}


	for (sUsersInfo& User : vUsers)
	{
		PrintUsersRecord(User);
		cout << endl;
	}
	cout << "\n\n----------------------------------------------------------------------------------------------------------\n";

}



void SaveUsersDataToFile(string FileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}

}

bool UserExistsByUserName(string UserName)
{
	vector<sUsersInfo>vUserName = LoadUsersDataFromFile(UsersFileName);

	for (sUsersInfo& U : vUserName)
	{
		if (U.Name == UserName)
			return true;
	}
	return false;
}

sUsersInfo ReadNewUser()
{
	sUsersInfo UsersInfo;


	UsersInfo.Name = ReadUserName();

	while (UserExistsByUserName(UsersInfo.Name))
	{
		cout << "\nUser with[" << UsersInfo.Name << "] is already exist,Enter another Username?";
		cin >> UsersInfo.Name;
	}

	UsersInfo.Password = ReadUserPassword();
	UsersInfo.Permissions = ReadUsersPermissions();

	return UsersInfo;
}

void AddNewUser()
{
	sUsersInfo User;

	User = ReadNewUser();
	SaveUsersDataToFile(UsersFileName, ConvertRecordeUserToLine(User));


}

void AddNewUsers()
{

	char AddMore = 'n';

	do
	{
		cout << "Adding New User:\n\n";

		AddNewUser();

		cout << "\nUser added successfully,do you want to add more Users (Y or N) ?";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

void ShowAddNewUsersScreeen()
{
	cout << "_______________________________________\n";
	cout << "\tAdding New Users Screen\n";
	cout << "_______________________________________\n";

	AddNewUsers();

}

void PerformMainUsersScreen(enManageUsersOption ManageUsersOption)
{

	switch (ManageUsersOption)
	{
	case enManageUsersOption::eListUsers:
		system("cls");
		ShowAllUsersScreen();
		GoBackToMainManageMenue();
		break;

	case enManageUsersOption::eAddNewUser:
		system("cls");
		ShowAddNewUsersScreeen();
		GoBackToMainManageMenue();
		break;

	case enManageUsersOption::eDeleteUser:
		system("cls");
		ShowDeleteUsersScreen();
		GoBackToMainManageMenue();
		break;

	case enManageUsersOption::eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToMainManageMenue();
		break;

	case enManageUsersOption::eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToMainManageMenue();
		break;

	case enManageUsersOption::eMainUserMenue:
		ShowMainMenueScreen();
		break;
	}

}

void ShowMainUsersMenueScreen()
{
	if (!CheckAccessPermission(enUserPermissions::pManageUsers))
	{
		ShowAccessMessage();
		return;
	}


	system("cls");
	cout << "=============================================\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "=============================================\n";

	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New Users.\n";
	cout << "\t[3] Delete Users.\n";
	cout << "\t[4] Update Users.\n";
	cout << "\t[5] Find Users.\n";
	cout << "\t[6] Main Menue.\n";

	cout << "=============================================\n";

	PerformMainUsersScreen((enManageUsersOption)ReadMainUsersOption());
}

string ReadUserName()
{
	string Username;

	cout << "Enter Username? ";
	getline(cin >> ws, Username);

	return Username;
}

string ReadUserPassword()
{
	string Password;

	cout << "\nEnter Password? ";
	getline(cin >> ws, Password);

	return Password;
}

bool FindUsersByNameAndPassWord(string UserName, string Password, sUsersInfo &User)
{
	vector <sUsersInfo> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (sUsersInfo& UserInfo : vUsers)
	{

		if (UserInfo.Name == UserName && UserInfo.Password == Password)
		{
			User = UserInfo;
			return true;
		}

	}
	return false;
}

bool ReadUserInfo(string Username,string Password)
{
	if (FindUsersByNameAndPassWord(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login()
{
	
	bool LoginFiled = false;

	do
	{
		system("cls");
		cout << "--------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "--------------------------------\n";

		if (LoginFiled)
		{
			cout << "Invlaid Username/Password\n";
		}

		string Username, Password;

		Username = ReadUserName();
		Password = ReadUserPassword();

	/*	if (ReadUserInfo(Username,Password))
		{
			LoginFiled = false;
		}
		else
		{
			LoginFiled = true;
		}*/

		LoginFiled = !ReadUserInfo(Username, Password);
	
	
	} while (LoginFiled);


	ShowMainMenueScreen();
}


int main()
{


	Login();

	return 0;
}

