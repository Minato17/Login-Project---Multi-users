#pragma warning(disable : 4996)
#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include<cstdlib>
#include<time.h>
#include<ctime>

using namespace std;

class RandomPassword {
private:
	string genPassword()
	{
		int i;
		int s;
		srand(time(0));
		char a[4];
		const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		s = sizeof(alphanum) - 1;
		string c;
		for (i = 0; i < 4; i++)
			c.push_back(alphanum[rand() % s]);
		return c;
	}
	string passwo;
public:

	RandomPassword()
	{
		this->passwo = genPassword();
	}
	string getPassword()
	{
		return passwo;
	}
};

class ResetPassword {
private:
	string userName;
	string passWord;
	string q, q2, q3;
	string a, a2, a3;
	bool identityConfirmed;

	bool verifyUserName()
	{
		fstream dat;
		dat.open("data.txt", ios::in | ios::out | ios::app);
		string nu;
		int nr = 0;
		dat.seekg(0);
		while (getline(dat, nu))
		{
			nr++;
			if (nr % 10 == 1)
			{
				if (nu == userName)
					return true;
			}
		}
		dat.close();
		return false;
	}
	void getSavedSecurityQA()
	{
		fstream dat;
		dat.open("data.txt", ios::in | ios::out | ios::app);
		string nu;
		int nr = 0;
		dat.seekg(0);
		while (getline(dat, nu))
		{
			nr++;
			if (nr % 10 == 1)
			{
				if (nu == userName)
				{
					getline(dat, nu);
					getline(dat, q);
					getline(dat, a);
					getline(dat, q2);
					getline(dat, a2);
					getline(dat, q3);
					getline(dat, a3);
					break;
				}
			}
		}
		dat.close();
	}

	bool getUserSecurityAnswers()
	{
		string d, d2, d3;
		identityConfirmed = false;
		cout << "                                        Raspundeti la urmatoarele intrebari: \n";
		cin.ignore();
		cout << "\n                                        " << q << "\n\n                                        Raspuns: ";
		getline(cin, d);
		cout << "\n                                        " << q2 << "\n\n                                        Raspuns: ";
		getline(cin, d2);
		cout << "\n                                        " << q3 << "\n\n                                        Raspuns: ";
		getline(cin, d3);
		if (d == a && d2 == a2 && d3 == a3)
			identityConfirmed = true;
		else
			identityConfirmed = false;
		return identityConfirmed;
	}

	void getNewPassword()
	{
		RandomPassword *random = new RandomPassword();
		passWord = random->getPassword();
		cout << "\n                                        Noua ta parola este: " << passWord << endl;;
	}

	void updatePassWord()
	{
		fstream dat;
		fstream data;
		data.open("dat.txt", ios::in | ios::out | ios::app);
		dat.open("data.txt", ios::in | ios::out | ios::app);
		dat.seekg(0);
		data.seekg(0);
		string nu;
		int nr = 0;
		while (getline(dat, nu))
		{
			nr++;
			data << nu << endl;
			if (nr % 10 == 1)
			{
				if (nu == userName)
				{
					getline(dat, nu);
					getNewPassword();
					data << passWord << endl;
				}
			}
		}
		dat.close();
		data.close();
		remove("data.txt");
		rename("dat.txt", "data.txt");
	}
public:
	ResetPassword(string s)
	{
		userName = s;
		while (!verifyUserName())
		{
			cout << "\n                                        UserName gresit!!! \n\n                                        Introduceti din nou: ";
			cin >> userName;
			cout << endl;
		}
		getSavedSecurityQA();
		if (getUserSecurityAnswers())
		{
			updatePassWord();
			fstream fin("Evenimente.log", ios::in | ios::out | ios::app);
			time_t * rawtime = new time_t;
			struct tm * timeinfo;
			time(rawtime);
			timeinfo = localtime(rawtime);
			fin << "Usernameul: - " << userName << " - si a resetat parola la data de: " << asctime(timeinfo);
			fin.close();
		}
		else
		{
			cout << "\n                                        Eroare!!! Raspunsuri gresite!!!\n";
			fstream fin("Evenimente.log", ios::in | ios::out | ios::app);
			time_t * rawtime = new time_t;
			struct tm * timeinfo;
			time(rawtime);
			timeinfo = localtime(rawtime);
			fin << "Schimbare de parola nereusita la data de: " << asctime(timeinfo);
			fin.close();
		}
	}
};

class Identity {
private:
	string userName;
	string userPassword;
	bool identityConfirmed;

	void confirmIdentity(string n, string b)
	{
		fstream dat;
		identityConfirmed = false;
		dat.open("data.txt", ios::in | ios::out | ios::app);
		string nu;
		int nr = 0;
		dat.seekg(0);
		while (getline(dat, nu))
		{
			nr++;
			if (nr % 2 == 1)
			{
				if (nu == n)
				{
					getline(dat, nu);
					if (nu == b)
						identityConfirmed = true;
				}
			}
		}
		dat.close();
	}
public:
	Identity(string u, string p)
	{
		userName = u;
		userPassword = p;
	}

	bool getConfirmedIdentity()
	{
		confirmIdentity(userName, userPassword);
		return identityConfirmed;
	}
};

class NewUser {
private:
	string userName;
	string passWord;
	string a, a2, a3;
	string q, q2, q3;
	string getNewPassword()
	{
		RandomPassword *random = new RandomPassword();
		passWord = random->getPassword();
		return passWord;
	}
	bool verifyUserName(string n)
	{
		fstream dat;
		dat.open("data.txt", ios::in | ios::out | ios::app);
		string nu;
		int nr = 0;
		dat.seekg(0);
		while (getline(dat, nu))
		{
			nr++;
			if (nr % 10 == 1)
			{
				if (nu == n)
					return false;
			}
		}
		dat.close();
		return true;
	}
public:

	NewUser(string u)
	{
		userName = u;
		passWord = getNewPassword();
	}

	void setSecurityQA()
	{
		fstream dat;
		dat.open("data.txt", ios::in | ios::out | ios::app);
		cout << "\n                                        Prima intrebare: ";
		cin.ignore();
		getline(cin, q);
		cout << "\n                                        RASPUNS: ";
		getline(cin, a);
		do {
			cout << "\n                                        A doua intrebare: ";
			getline(cin, q2);
			if (q == q2)
				cout << "\n                                        Intrebari identice!!! Puneti alta intrebare!\n\n";
		} while (q2 == q);
		cout << "\n                                        RASPUNS: ";
		getline(cin, a2);
		do {
			cout << "\n                                        A treia intrebare: ";
			getline(cin, q3);
			if (q == q3 || q2 == q3)
				cout << "\n                                        Intrebari identice!!! Puneti alta intrebare!\n\n";
		} while (q == q3 || q2 == q3);
		cout << "\n                                        RASPUNS: ";
		getline(cin, a3);
	}
	void createUserProfile()
	{
		fstream dat;
		fstream fin("Evenimente.log", ios::in | ios::out | ios::app);
		dat.open("data.txt", ios::in | ios::out | ios::app);
		string b;
		while (dat.eof()) {
			getline(dat, b);
		}
		NewUser *h = NULL;
		string n;
		cout << "\n                                        UserName(fara spatiu): ";
		cin >> n;
		while (!verifyUserName(n))
		{
			cout << "\n                                        UserName(fara spatiu): ";
			cin >> n;
		}
		h = new NewUser(n);
		cout << "\n                                        Parola ta: ";
		cout << h->passWord << endl;
		h->setSecurityQA();
		dat << h->userName << endl;
		dat << h->passWord << endl;
		dat << h->q << endl;
		dat << h->a << endl;
		dat << h->q2 << endl;
		dat << h->a2 << endl;
		dat << h->q3 << endl;
		dat << h->a3 << endl;
		dat << "\n---------------------------------------\n";
		time_t * rawtime = new time_t;
		struct tm * timeinfo;
		time(rawtime);
		timeinfo = localtime(rawtime);
		string v;
		while (fin.eof()) {
			getline(fin, v);
		}
		fin << h->userName << " a devenit membru la data de: " << asctime(timeinfo);
		dat.close();
		fin.close();
	}
};


int main()
{
	NewUser *c = NULL;
	ResetPassword *r = NULL;
	Identity*i = NULL;
	string s = "start https://cv.upt.ro/";
	string pass, a, b, g;
	unsigned int opt;
	do {
		system("cls");
		cout << "------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\n                                        1.Creare profil\n\n                                        2.Autentificare\n\n                                        3.Resetare parola\n\n                                        0.Iesire\n\n";
		cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
		do {
			cout << "                                        Optiunea dumneavoastra: ";
			cin >> opt;
			if (!(opt == 1 || opt == 2 || opt == 3 || opt == 0))
				cout << "                                        Optiune Incorecta!!!\n";
		} while (!(opt == 1 || opt == 2 || opt == 3 || opt == 0));
		cout << endl;
		switch (opt)
		{
		case 1:
			c->createUserProfile();
			break;
		case 2:
			cout << "                                        Introduceti UserName: ";
			cin >> a;
			cout << endl;
			cout << "                                        Introduceti parola: ";
			cin >> b;
			cout << endl;
			i = new Identity(a, b);
			if (!(i->getConfirmedIdentity()))
			{
				fstream fin("Evenimente.log", ios::in | ios::out | ios::app);
				cout << "                                        UserName sau parola gresita!\n";
				time_t * rawtime = new time_t;
				struct tm * timeinfo;
				time(rawtime);
				timeinfo = localtime(rawtime);
				fin << "Logare gresita la data de: " << asctime(timeinfo);
				break;
			}
			else
			{
				fstream fin("Evenimente.log", ios::in | ios::out | ios::app);
				time_t * rawtime = new time_t;
				struct tm * timeinfo;
				time(rawtime);
				timeinfo = localtime(rawtime);
				fin << "Usernameul: - " << a << " - s-a logat cu succes la data de: " << asctime(timeinfo);
				system(s.c_str());
			}
			break;
		case 3:
			cout << "                                        Introduceti UserName-ul: ";
			cin >> g;
			cout << endl;
			r = new ResetPassword(g);
			break;
		case 0:
			exit(0);
		}
		system("pause");
	} while (1);

	return 0;
}