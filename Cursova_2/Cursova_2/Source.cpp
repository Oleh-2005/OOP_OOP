#include<iostream> 
#include<windows.h>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include<deque> 
#include<list>
#include<map>
using namespace std;

struct User {
	int status;
	long TNumber;
	string password ;
	string Name;
	string Surname;
	string FName;
	string ResidenceAddress;
	string Login ;
};
struct test {
	string task;
	int number;
	string va;
	string vb;
	string vc;
	string answer;
	string theme;

};
struct ResumeTest {
	int number;
	int max_mark;
	int real_mark;
	int numberOftasks;
	string name;
	string nameOfuser;
	int fail;
	string task;
};
class Test {
public:
	Test() {
	
	}
	virtual void DoTest(vector<test>& v, string login) {

	}
	virtual void Show(vector<test>& v) {

	}

};
class Register {

public:
	Register(int Status) {
		int OK = 0;
		while (OK == 0) {
			User user;
			string sentence = "";
			string password = "";
			cout << "\nEnter your name : ";
			cin >> user.Name;
			cout << "\nEnter your surname : ";
			cin >> user.Surname;
			cout << "\nEnter your father`s name : ";
			cin >> user.FName;
			user.status = Status;
			cout << "\nEnter your residence address : ";
			cin >> user.ResidenceAddress;
			cout << "\nEnter your telephone number : ";
			cin >> user.TNumber;
			cout << "\nEnter your login : ";
			cin>>sentence;
			cout << "\nEnter your passord : ";
			cin>>password;

			bool ok = false;
			int shifter;					
			shifter = 4;
			User us;
			ifstream fin(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
			if (fin.is_open()) {
				while (fin >> us.Login) {
					fin  >> us.password >> us.status>>us.FName>>us.Name>>us.Surname>>us.TNumber>>us.ResidenceAddress;
					for (int i = 0; i < us.Login.length(); i++) {
						us.Login[i] = us.Login[i] - shifter;

					}
					for (int i = 0; i < us.password.length(); i++) {
						us.password[i] = us.password[i] - shifter;

					}
				    if (us.Login == sentence) {
				    	ok = true;
				    }
					
				}
				
				
			}
			fin.close();
			if (ok == false) {
				
				ofstream in(R"(C:\Users\Zver\Desktop\Cursova\users.txt)" ,ios::app);
				if (in.is_open()) {
					for (int i = 0; i < sentence.length(); i++) {
						sentence[i] = sentence[i] + shifter;

					}
					for (int i = 0; i < password.length(); i++) {
						password[i] = password[i] + shifter;

					}
					in << sentence << " " << password <<" "<< user.status << " "<< user.FName << " "<< user.Name << " "<< user.Surname << " "<< user.TNumber << " "<< user.ResidenceAddress<<endl;
					
				}
				in.close();
				OK++;
			}

			else {
				cout << "\n\n\t\tThis login is already exist" << endl;
				OK++;
			}
		}
	}
};
class Math : public Test {
public:
	Math(string login) : Test() {
		test t;
		vector<test> v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\math.txt)");
		if (in.is_open()) {
			while (in >> t.number) {
				in >> t.task >> t.va >> t.vb >> t.vc >> t.answer >> t.theme;
				v.push_back(t);
			}
		}
		in.close();
		cout << "\nEnter 1 if you want to see all groups of test\nEnter 2 if you want to do test" << endl;
		int WANT = 0;
		cout << "----> ";
		cin >> WANT;
		if (WANT == 1) {
			Show(v);
		}
		else if (WANT == 2) {
			DoTest(v , login);
		}
	}
	void DoTest(vector<test>& v, string login) override {
		string group;
		cout << "\nEnter from what group of thems you want to do test : ";
		cin >> group;
		vector<int> count;
		int Count = 0;
		for (int i = 0; i < v.size(); i++) {
			if (group == v[i].theme) {
				count.push_back(i);
				Count++;
			}
		}
		if (Count == 0) {
		}
		else {
			double ball = 0;
			double CostOfTrue = 12 / Count;
			cout << "\n\nIf you want to stop test enter --1\n\n";
			int save = 0;
			test t;
			int ii = 0;
			for (int i = 0; i < count.size(); i++) {
				cout << "Number : " << v[count[i]].number << "\nTask : " << v[count[i]].task << "\nVariants : " << v[count[i]].va << "  " << v[count[i]].vb << "  " << v[count[i]].vc << "\nYour variant : ";
				cin >> t.answer;
				if (t.answer == v[count[i]].answer) {
					ball = ball + CostOfTrue;
					cout << "\nYour answer is correct !\n";
				}
				else if (t.answer == "--1") {
					save++;
					ii = i;
					t.number = v[count[i]].number;
					break;
				}
				else {
					cout << "\nSorry . Your answer is incorrect \n";
				}
			}
			if (save == 0) {
				cout << "\nYour mark for test is " << ball << endl;
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << endl;
				}
				on.close();
			}
			else {
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\save.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << " " << t.number <<" "<<ii << " " << "math" << endl;
				}
				on.close();
				cout << "\n\nYour taste is save !\n\n";
			}
		}
	}
	void Show(vector<test>& v) override {
		vector<string> v2;
		v2.push_back(v[0].theme);
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if (v[i].theme != v2[j]) {
					v2.push_back(v[i].theme);
				}
			}
		}
		cout << "\n\t\tGroup of tests ";
		for (int i = 0; i < v2.size(); i++) {
			cout << "\n" << v2[i];
		}
	}
};
class Biology : public Test {
public:
	Biology(string login) : Test() {
		test t;
		vector<test> v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\biology.txt)");
		if (in.is_open()) {
			while (in >> t.number) {
				in >> t.task >> t.va >> t.vb >> t.vc >> t.answer >> t.theme;
				v.push_back(t);
			}
		}
		in.close();
		cout << "\nEnter 1 if you want to see all groups of test\nEnter 2 if you want to do test" << endl;
		int WANT = 0;
		cout << "----> ";
		cin >> WANT;
		if (WANT == 1) {
			Show(v);
		}
		else if (WANT == 2) {
			DoTest(v , login);
		}
	}
	void DoTest(vector<test>& v, string login) override {
		string group;
		cout << "\nEnter from what group of thems you want to do test : ";
		cin >> group;
		vector<int> count;
		int Count = 0;
		for (int i = 0; i < v.size(); i++) {
			if (group == v[i].theme) {
				count.push_back(i);
				Count++;
			}
		}
		if (Count == 0) {
		}
		else {
			double ball = 0;
			double CostOfTrue = 12 / Count;
			cout << "\n\nIf you want to stop test enter --1\n\n";
			int save = 0;
			int ii = 0;
			test t;
			for (int i = 0; i < count.size(); i++) {
				cout << "Number : " << v[count[i]].number << "\nTask : " << v[count[i]].task << "\nVariants : " << v[count[i]].va << "  " << v[count[i]].vb << "  " << v[count[i]].vc << "\nYour variant : ";
				cin >> t.answer;
				if (t.answer == v[count[i]].answer) {
					ball = ball + CostOfTrue;
					cout << "\nYour answer is correct !\n";
				}
				else if (t.answer == "--1") {
					save++;
					ii = i;
					t.number = v[count[i]].number;
					break;
				}
				else {
					cout << "\nSorry . Your answer is incorrect \n";
				}
			}
			if (save == 0) {
				cout << "\nYour mark for test is " << ball << endl;
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << endl;
				}
				on.close();
			}
			else {
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\save.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << " " << t.number << " " << ii << " " << "biology" << endl;
				}
				on.close();
				cout << "\n\nYour taste is save !\n\n";
			}
		}
	}
	void Show(vector<test>& v) override {
		vector<string> v2;
		v2.push_back(v[0].theme);
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if (v[i].theme != v2[j]) {
					v2.push_back(v[i].theme);
				}

			}
		}
		cout << "\n\t\tGroup of tests ";
		for (int i = 0; i < v2.size(); i++) {
			cout << "\n" << v2[i];
		}
	}
};
class UKR_History : public Test{
public :
	UKR_History(string login) : Test() {
		test t;
		vector<test> v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\UKR_history.txt)");
		if (in.is_open()) {
			while (in >> t.number) {
				in >> t.task >> t.va >> t.vb >> t.vc >> t.answer >> t.theme;
				v.push_back(t);
			}
		}
		in.close();
		cout << "\nEnter 1 if you want to see all groups of test\nEnter 2 if you want to do test" << endl;
		int WANT = 0;
		cout << "----> ";
		cin >> WANT;
		if (WANT == 1) {
			Show(v);
		}
		else if (WANT == 2) {
			DoTest(v , login);
		}
	}
	void DoTest(vector<test>& v, string login) override {
		string group;
		cout << "\nEnter from what group of thems you want to do test : ";
		cin >> group;
		vector<int> count;
		int Count = 0;
		for (int i = 0; i < v.size(); i++) {
			if (group == v[i].theme) {
				count.push_back(i);
				Count++;
			}
		}
		if (Count == 0) {
		}
		else {
			double ball = 0;
			double CostOfTrue = 12 / Count;
			cout << "\n\nIf you want to stop test enter --1\n\n";
			int save = 0;
			int ii = 0;
			test t;
			for (int i = 0; i < count.size(); i++) {
				cout << "Number : " << v[count[i]].number << "\nTask : " << v[count[i]].task << "\nVariants : " << v[count[i]].va << "  " << v[count[i]].vb << "  " << v[count[i]].vc << "\nYour variant : ";
				cin >> t.answer;
				if (t.answer == v[count[i]].answer) {
					ball = ball + CostOfTrue;
					cout << "\nYour answer is correct !\n";
				}
				else if (t.answer == "--1") {
					save++;
					ii = i;
					t.number = v[count[i]].number;
					break;
				}
				else {
					cout << "\nSorry . Your answer is incorrect \n";
				}
			}
			if (save == 0) {
				cout << "\nYour mark for test is " << ball << endl;
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << endl;
				}
				on.close();
			}
			else {
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\save.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << " " << t.number << " " << ii << " " << "UKR_h" << endl;
				}
				on.close();
				cout << "\n\nYour taste is save !\n\n";
			}
		}
	}
	void Show(vector<test>& v) override {
		vector<string> v2;
		v2.push_back(v[0].theme);
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if (v[i].theme != v2[j]) {
					v2.push_back(v[i].theme);
				}

			}
		}
		cout << "\n\t\tGroup of tests ";
		for (int i = 0; i < v2.size(); i++) {
			cout << "\n" << v2[i];
		}
	}
};
class Geography : public Test {
public:
	Geography(string login) : Test() {
	    test t;
	    vector<test> v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\geography.txt)");
		if (in.is_open()) {
			while (in >> t.number) {
				in >> t.task >> t.va >> t.vb >> t.vc >> t.answer >> t.theme;
				v.push_back(t);
			}
		}
		in.close();
		cout << "\nEnter 1 if you want to see all groups of test\nEnter 2 if you want to do test" << endl;
		int WANT = 0;
		cout << "----> ";
		cin >> WANT;
		if (WANT == 1) {
			Show(v);
		}
		else if (WANT == 2) {
			DoTest(v , login);
		}
	}
	void DoTest(vector<test>& v , string login) override {
		string group;
		cout << "\nEnter from what group of thems you want to do test : ";
		cin >> group;
		vector<int> count;
		int Count = 0;
		for (int i = 0; i < v.size(); i++) {
			if (group == v[i].theme) {
				count.push_back(i);
				Count++;
			}
		}
		if (Count == 0) {
		}
		else {
			double ball = 0;
			double CostOfTrue = 12 / Count;
			cout << "\n\nIf you want to stop test enter --1\n\n";
			int save = 0;
			test t;
			int ii = 0;
			for (int i = 0; i < count.size(); i++) {
				cout << "Number : " << v[count[i]].number << "\nTask : " << v[count[i]].task << "\nVariants : " << v[count[i]].va << "  " << v[count[i]].vb << "  " << v[count[i]].vc << "\nYour variant : ";
				cin >> t.answer;
				if (t.answer == v[count[i]].answer) {
					ball = ball + CostOfTrue;
					cout << "\nYour answer is correct !\n";
				}
				else if (t.answer == "--1") {
					ii = i;
					save++;
					t.number = v[count[i]].number;
					break;
				}
				else {
					cout << "\nSorry . Your answer is incorrect \n";
				}
			}
			if (save == 0) {
				cout << "\nYour mark for test is " << ball << endl;
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group << endl;
				}
				on.close();
			}
			else {
				ofstream on(R"(C:\Users\Zver\Desktop\Cursova\save.txt)", ios::app);
				if (on.is_open()) {
					on << login << " " << ball << " " << group <<" "<< t.number<<" "<<ii<<" "<<"geography"<< endl;
				}
				on.close();
				cout << "\n\nYour taste is save !\n\n";
			}
		}
	}
	void Show(vector<test> &v) override {
		vector<string> v2;
		v2.push_back(v[0].theme);
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if ( v[i].theme != v2[j]) {
					v2.push_back(v[i].theme);
				}

			}
		}
		cout << "\n\t\tGroup of tests ";
		for (int i = 0; i < v2.size(); i++) {
			cout << "\n" << v2[i];
		}
	}
};
class TTEST {
public:
	TTEST(string login) {
		cout << "\nEnetr 1 if you want to do test from ukrainian history\nEnter 2 if you want to do test from math\nEnter 3 if you want to do test from biology\nEnter 4 if you want to do test from geography\nEnter 5 if you want to exit\n";
		cout << "----> ";
		int want = 0;
		cin >> want;
		if (want == 5) {

		}
		else if (want == 1) {
			UKR_History his(login);
		}
		else if (want == 2) {
			Math ma(login);
		}
		else if (want == 3) {
			Biology bio(login);
		}
		else if (want == 4) {
			Geography geo(login);
		}
	}
};
class Data {
public:
	Data(int status , string login , string password) {
		if (status == 1) {

			User user;
			vector <User> v;
			int shifter;
			shifter = 4;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
			if (in.is_open()) {
				while (in >> user.Login) {
					in  >> user.password >> user.status >> user.FName >> user.Name >> user.Surname >> user.TNumber >> user.ResidenceAddress;
					for (int i = 0; i < user.Login.length(); i++) {
						user.Login[i] = user.Login[i] - shifter;

					}
					for (int i = 0; i < user.password.length(); i++) {
						user.password[i] = user.password[i] - shifter;

					}
					v.push_back(user);
				}
				for (int i = 0; i < v.size(); i++) {
					if (login == v[i].Login || password == v[i].password) {
						cout << "\nLogin : " << v[i].Login << "\tPassword : " << v[i].password << "\nName : " << v[i].Name << "\tSurname : " << v[i].Surname << "\nAddress : " << v[i].ResidenceAddress << "\tTelephone number : " << v[i].TNumber << "\nFathers name : " << v[i].FName << endl;
					}
					
				}
			}
			in.close();
		}
		else if (status == 0) {
			User user;
			vector <User> v;
			int shifter;
			shifter = 4;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
			if (in.is_open()) {
				while (in >> user.Login) {
					in  >> user.password >> user.status >> user.FName >> user.Name >> user.Surname >> user.TNumber >> user.ResidenceAddress;
					for (int i = 0; i < user.Login.length(); i++) {
						user.Login[i] = user.Login[i] - shifter;

					}
					for (int i = 0; i < user.password.length(); i++) {
						user.password[i] = user.password[i] - shifter;

					}
					v.push_back(user);
				}
				for (int i = 0; i < v.size(); i++) {
					cout << "\nLogin : " << v[i].Login << "\tPassword : " << v[i].password << "\tName : " << v[i].Name << "\tSurname : " << v[i].Surname << "\tAddress : " << v[i].ResidenceAddress << "\tTelephone number : " << v[i].TNumber << "\tFathers name : " << v[i].FName << endl;
					
				}
			}
			in.close();
		}

	}
};
class AddUser {
public:
	AddUser() {
		int OK = 0;
		while (OK == 0) {
			User user;
			string sentence = "";
			string password = "";
			cout << "\nEnter name : ";
			cin >> user.Name;
			cout << "\nEnter surname : ";
			cin >> user.Surname;
			cout << "\nEnter father`s name : ";
			cin >> user.FName;
			user.status = 0;
			cout << "\nEnter residence address : ";
			cin >> user.ResidenceAddress;
			cout << "\nEnter telephone number : ";
			cin >> user.TNumber;
			cout << "\nEnter login : ";
			cin >> sentence;
			cout << "\nEnter password : ";
			cin >> password;


			bool ok = false;
			int shifter;
			shifter = 4;
			User us;
			ifstream fin(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
			if (fin.is_open()) {
				while (fin >> us.Login) {
					fin >> us.password >> us.status >> us.FName >> us.Name >> us.Surname >> us.TNumber >> us.ResidenceAddress;
					for (int i = 0; i < us.Login.length(); i++) {
						us.Login[i] = us.Login[i] - shifter;

					}
					for (int i = 0; i < us.password.length(); i++) {
						us.password[i] = us.password[i] - shifter;

					}
					if (us.Login == sentence) {
						ok = true;
					}

				}


			}
			fin.close();
			if (ok == false) {

				ofstream in(R"(C:\Users\Zver\Desktop\Cursova\users.txt)", ios::app);
				if (in.is_open()) {
					for (int i = 0; i < sentence.length(); i++) {
						sentence[i] = sentence[i] + shifter;

					}
					for (int i = 0; i < password.length(); i++) {
						password[i] = password[i] + shifter;

					}
					in << sentence << " " << password << " " << user.status << " " << user.FName << " " << user.Name << " " << user.Surname << " " << user.TNumber << " " << user.ResidenceAddress << endl;

				}
				in.close();
				OK++;
			}

			else {
				cout << "\n\n\t\tThis login is already exist" << endl;
				OK++;
			}
		}
	}
};
class Change {
public:
	Change() {
		test t;
		vector<User>v;
		User user;
		int shifter;
		shifter = 4;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
		if (in.is_open()) {
			while (in >> user.Login) {
				in  >> user.password >> user.status >> user.FName >> user.Name >> user.Surname >> user.TNumber >> user.ResidenceAddress;
				for (int i = 0; i < user.Login.length(); i++) {
					user.Login[i] = user.Login[i] - shifter;

				}
				for (int i = 0; i < user.password.length(); i++) {
					user.password[i] = user.password[i] - shifter;

				}

				v.push_back(user);
			}
		}
		in.close();
		User u;
		cout << "\nEnter login of user , whos data you want to change : ";
		cin >> u.Login;
		int iii = 0;
		for (int i = 0; i < v.size(); i++) {
			if (u.Login == v[i].Login) {
				iii = i;
				cout << "\nEnter new password : ";
				cin >> v[i].password;
				cout << "\nEnter new login : ";
				cin >> v[i].Login;
				cout << "\nEnter new telephone number : ";
				cin >> v[i].TNumber;
				cout << "\nEnter new name : ";
				cin >> v[i].Name;
				cout << "\nEnter new surname : ";
				cin >> v[i].Surname;
				cout << "\nEnter new Fathers name : ";
				cin >> v[i].FName;
				cout << "\nEnter new address : ";
				cin >> v[i].ResidenceAddress;
			}
		}
		string sent = "";
		string pass = "";
		ofstream iin(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
		if (iin.is_open()) {
			for (int i = 0; i < v.size(); i++) {
				for (int j = 0; j < v[i].Login.length(); j++) {
					v[i].Login[j] = v[i].Login[j] + shifter;
				}

			}
			for (int i = 0; i < v.size(); i++) {
				for (int j = 0; j < v[i].password.length(); j++) {
					v[i].password[j] = v[i].password[j] + shifter;

				}
			}
			for (int i = 0; i < v.size(); i++) {
				iin << v[i].Login << " " << v[i].password << " " << v[i].status << " " << v[i].FName << " " << v[i].Name << " " << v[i].Surname << " " << v[i].TNumber << " " << v[i].ResidenceAddress << endl;
			}
		}
		iin.close();

	}
	
};
class Result {
public:
	Result(string login) {
		test t;
		vector<test>v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)");
		if (in.is_open()) {
			while (in >> t.task) {
				in >> t.number >> t.theme ;
				v.push_back(t);
			}
		}
		in.close();
		for (int i = 0; i < v.size(); i++) {
			if (v[i].task == login) {
				cout << "\nTheme : " << v[i].theme << "\t\tMark : " << v[i].number << endl;
			}
		}
	}
};
class Resume {
public:
	Resume(string login ) {
		ResumeTest t;
	
		vector<ResumeTest>v;
		ifstream in(R"(C:\Users\Zver\Desktop\Cursova\save.txt)");
		if (in.is_open()) {
			while (in >> t.nameOfuser) {
				in >> t.real_mark >> t.name>>t.numberOftasks>>t.number>>t.task;
				v.push_back(t);
			}
		}
		in.close();
		cout << "\nEnter theme of test : ";
		string the;
		cin >> the;
		int ii = 0;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].nameOfuser == login&&v[i].name == the) {
				ii = i;
				break;
			}
		}
		vector<test>v2;
		if(v[ii].task =="math"){
			test tt;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\math.txt)");
			if (in.is_open()) {
				while (in >> tt.number) {
					in >> tt.task >> tt.va >> tt.vb >> tt.vc >> tt.answer >> tt.theme;
					v2.push_back(tt);
				}
			}
			in.close();
		}
		else if (v[ii].task == "biology") {
			test tt;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\biology.txt)");
			if (in.is_open()) {
				while (in >> tt.number) {
					in >> tt.task >> tt.va >> tt.vb >> tt.vc >> tt.answer >> tt.theme;
					v2.push_back(tt);
				}
			}
			in.close();
		}
		else if (v[ii].task == "UKR_h") {
			test tt;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\UKR_history.txt)");
			if (in.is_open()) {
				while (in >> tt.number) {
					in >> tt.task >> tt.va >> tt.vb >> tt.vc >> tt.answer >> tt.theme;
					v2.push_back(tt);
				}
			}
			in.close();
		}
		else if (v[ii].task == "geography") {
			test tt;
			ifstream in(R"(C:\Users\Zver\Desktop\Cursova\geography.txt)");
			if (in.is_open()) {
				while (in >> tt.number) {
					in >> tt.task >> tt.va >> tt.vb >> tt.vc >> tt.answer >> tt.theme;
					v2.push_back(tt);
				}
			}
			in.close();
		}
		vector<int> count;
		int Count = 0;
		for (int i = 0; i < v2.size(); i++) {
			if (the == v2[i].theme) {
				count.push_back(i);
				Count++;
			}
		}
		if (Count == 0) {
			//cout << "JJJJJJJJ" << endl;
		}
		else {
			double ball = v[ii].real_mark;
			double CostOfTrue = 12 / Count;
			test t;
			for (int i = v[ii].number; i < count.size(); i++) {
				cout << "Number : " << v2[count[i]].number << "\nTask : " << v2[count[i]].task << "\nVariants : " << v2[count[i]].va << "  " << v2[count[i]].vb << "  " << v2[count[i]].vc << "\nYour variant : ";
				cin >> t.answer;
				if (t.answer == v2[count[i]].answer) {
					ball = ball + CostOfTrue;
					cout << "\nYour answer is correct !\n";
				}
				else {
					cout << "\nSorry . Your answer is incorrect \n";
				}
			}

			cout << "\nYour mark for test is " << ball << endl;
			ofstream on(R"(C:\Users\Zver\Desktop\Cursova\marks.txt)", ios::app);
			if (on.is_open()) {
				on << login << " " << ball << " " << v[ii].name << endl;
			}
			on.close();
			
		}
	}
};
class AddTask {
public:
	AddTask() {
		test t;
		string les;
		cout << "\nEnter number of Task : ";
		cin >> t.number;
		cout << "\nEnter from what lesson this task : ";
		cin >> les;
		cout << "\nEnter your task (use _ as SPACE): ";
		cin >> t.task;
		cout << "\nEnter va : ";
		cin >> t.va;
		cout << "\nEnter vb : ";
		cin >> t.vb;
		cout << "\nEnter vc : ";
		cin >> t.vc;
		cout << "\nEnter answer : ";
		cin >> t.answer;
		cout << "\nEnter theme of your task : ";
		cin >> t.theme;
		if (les == "geography") {
			ofstream in(R"(C:\Users\Zver\Desktop\Cursova\geography.txt)", ios::app);
			if (in.is_open()) {

				in << t.number << " " << t.task << " " << t.va << " " << t.vb << " " << t.vc << " " << t.answer << " " << t.theme << endl;

			}
			in.close();
		}
		if (les == "math") {
			ofstream in(R"(C:\Users\Zver\Desktop\Cursova\math.txt)", ios::app);
			if (in.is_open()) {

				in << t.number << " " << t.task << " " << t.va << " " << t.vb << " " << t.vc << " " << t.answer << " " << t.theme << endl;

			}
			in.close();
		}
		if (les == "biology") {
			ofstream in(R"(C:\Users\Zver\Desktop\Cursova\biology.txt)", ios::app);
			if (in.is_open()) {

				in << t.number << " " << t.task << " " << t.va << " " << t.vb << " " << t.vc << " " << t.answer << " " << t.theme << endl;

			}
			in.close();
		}
		if (les == "UKR_history") {
			ofstream in(R"(C:\Users\Zver\Desktop\Cursova\UKR_history.txt)", ios::app);
			if (in.is_open()) {

				in << t.number << " " << t.task << " " << t.va << " " << t.vb << " " << t.vc << " " << t.answer << " " << t.theme << endl;

			}
			in.close();
		}
	}
};
class SecondMenu {
public:
	SecondMenu(int status, string login, string password) {
		int exit = 0;
		while (exit == 0) {
			int want = 0;
			cout << "\nEnter 1 if you want to exit \nEnter 2 if you want to see data \nEnetr 3 if you want to continue test\nEnter 4 if you want to do test\nEnter 5 if you want to see your results from all tests" << endl;
			if (status == 0) {
				cout << "Enter 6 if you want to add user\nEnter 7 if you want to correct data\nEnter 8 if you want to add test\n";
			}
			cout << "----> ";
			cin >> want;
			if (want == 1) {
				exit++;
			}
			else if (want == 2) {
				Data data(status , login , password);
			}
			else if (want == 3) {
				Resume resume(login);
			}
			else if (want == 4) {
				TTEST test (login);
			}
			else if (want == 5) {
				Result res(login);
			}
			else if (want == 6 && status == 0) {
				AddUser add;				
			}
			else if (want == 7 && status == 0) {
				Change ch;
			}
			else if (want == 8 && status == 0) {
				AddTask at;
			}
		}
	}

};
class Login {

public :
	Login(int st) {
		User luser;
		cout << "\nEnter your login : ";
		cin >> luser.Login;
		cout << "\nEnter your password : ";
		int ok = 0;
		cin >> luser.password;
		User user;
		vector <User> v;
		int shifter;
		shifter = 4;
		ifstream fin(R"(C:\Users\Zver\Desktop\Cursova\users.txt)");
		if (fin.is_open()) {
			while (!fin.eof()) {
				fin >> user.Login >> user.password >> user.status >> user.FName >> user.Name >> user.Surname >> user.TNumber >> user.ResidenceAddress;
				for (int i = 0; i < user.Login.length(); i++) {
					user.Login[i] = user.Login[i] - shifter;

				}
				for (int i = 0; i < user.password.length(); i++) {
					user.password[i] = user.password[i] - shifter;

				}

				v.push_back(user);
			}
			for (int i = 0; i < v.size(); i++) {
				if (luser.Login == "Admin" || luser.password == "Admin" || luser.status == 0) {
					ok++;
				}
			}
			for (int i = 0; i < v.size(); i++) {
				if (luser.Login == v[i].Login || luser.password == v[i].password || luser.status == 1) {
					ok--;
				}
			}
		}
		if (ok > 0) {
			SecondMenu smenu(0 , luser.Login , luser.password);
		}
		else if (ok < 0) {
			SecondMenu smenu(1, luser.Login, luser.password);
		}


		else if (ok == 0){
			cout << "\n\n\t\tERROR !!! You enter incorrect login or password" << endl << endl;
		}
		fin.close();
	}

};
class FirstMenu {
public:
	FirstMenu() {
		int exit = 0;
		while (exit == 0) {
			int want = 0;
			cout << "\nEnter 1 if you want to login \nEnetr 2 if you want to exit \nEnter 3 if you want to register" << endl;;
			cout << "----> ";
			cin >> want;
			if (want == 2) {
				cout << "\n\n\t\tGOOD BYE !" << endl;
				exit++;
			}
			else if (want == 1) {
				Login login(1);
			}
			else if (want == 3) {
				Register reg(1);
			}
		}
	}
};
int main() {
	srand(unsigned(time(NULL)));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	FirstMenu menu;

	system("pause");
	return 0;
}