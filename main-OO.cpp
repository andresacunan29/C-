#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <mysql/jdbc.h> 
#include <conio.h>
#include <iomanip>
using namespace std;

// reads in a password without echoing it to the screen
string myget_passwd()
{
	string passwd;
	char ch;
	for (;;)
	{
		ch = 0;
		while (ch == 0)   // Ugh. Mic rosoft not following standards on getch, so need to keep reading until a new char is typed. 
			ch = _getch();           // get char WITHIOUT echo! (should really be getch(), but MS is not following standrads again.)
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed
				   // read until end of line ... so future getlines work. 
	string dummy;
	getline(cin, dummy);
	return passwd;
}

void createTables(string hostname, string port, string username, string password, string database_name)
{
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(hostname + ":" + port, username, password);
		/* Connect to the MySQL test database */
		con->setSchema(database_name);

		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS Students_Course_T");
		cout << "Students_Course_T Table is Dropped" << endl;

		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS Course_T");
		cout << "Course_T Table is Dropped" << endl;

		stmt = con->createStatement();
		stmt->execute("CREATE TABLE Course_T(courseid int(11) NOT NULL AUTO_INCREMENT, prefix varchar(20), number int(11), title varchar(30), credits int(11), PRIMARY KEY (courseid) )");
		cout << "Course_T Table is Created" << endl << endl;

		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS Grade_T");
		cout << "Grade_T Table is Dropped" << endl;

		stmt = con->createStatement();
		stmt->execute("CREATE TABLE Grade_T(gradeid int(11) NOT NULL AUTO_INCREMENT, g_type varchar(20), g_number double, PRIMARY KEY (gradeid) )");
		cout << "Grade_T Table is Created" << endl << endl;

		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS Semester_T");
		cout << "Semester_T Table is Dropped" << endl;

		stmt = con->createStatement();
		stmt->execute("CREATE TABLE Semester_T(semid int(11) NOT NULL AUTO_INCREMENT,code varchar(20), year int(11), description varchar(30), PRIMARY KEY (semid) )");
		cout << "Semester_T Table is Created" << endl << endl;

		stmt = con->createStatement();
		stmt->execute("CREATE TABLE Students_Course_T(lname varchar(20), fname varchar(20), courseid int(11), gradeid int(11), semid int(11), FOREIGN KEY (courseid) REFERENCES Course_T(courseid), FOREIGN KEY (gradeid) REFERENCES Grade_T(gradeid), FOREIGN KEY (semid) REFERENCES Semester_T(semid) )");
		cout << "Students_Course_T Table is Created" << endl << endl;

		delete stmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: " << e.what();
	}
}

int main()
{
	// Database connection credentials.
	std::string hostname = "luredir.hopto.org";
	std::string port = "40306";
	std::string username = "aacuna";
	std::string password = "aacuna0329";
	std::string database_name = "aacuna";

	//// Prompt user for database credentials.
	////std::cout << "Hostname: ";
	////std::getline(std::cin, hostname);
	////std::cout << "Port Number:";
	////std::getline(std::cin, port);
	////std::cout << "Username: ";
	////std::getline(std::cin, username);
	////std::cout << "Password: ";
	////std::getline(std::cin, password);
	////std::cout << "Database Name: ";
	////std::getline(std::cin, database_name);
	////std::cout << "Whose GPA you want ";
	////std::getline(std::cin, database_name);


	//createTables(hostname, port, username, password, database_name);

	sql::Driver *driver;
	sql::Connection *con = NULL;
	sql::Statement *stmt = NULL;
	sql::ResultSet *res = NULL;

	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect(hostname + ":" + port, username, password);
	/* Connect to the MySQL test database */
	con->setSchema(database_name);

	string action = "";
	cout << "Welcome to the Student Management System" << endl << endl;
	while (action != "q")
	{
		cout << "Please choose from the below menu" << endl;
		cout << "Press a for add" << endl;
		cout << "Press l for list" << endl;
		cout << "Press d for delete" << endl;
		cout << "Press t for transcript" << endl;
		cout << "Press q for exit" << endl << endl;

		std::getline(std::cin, action);
		if (action == "a")
		{
			string action2 = "";
			cout << "Please choose from the below menu" << endl;
			cout << "Press c for add course" << endl;
			cout << "Press g for add grade" << endl;
			cout << "Press m for add semester" << endl;
			cout << "Press s for add student" << endl;
			cout << "Press t for add student course" << endl << endl;

			std::getline(std::cin, action2);
			if (action2 == "c")
			{
				cout << "Enter course prefix: ";
				string course_prefix = "";
				std::getline(std::cin, course_prefix);

				cout << "Enter course title: ";
				string course_title = "";
				std::getline(std::cin, course_title);

				cout << "Enter course number: ";
				string course_number = "";
				std::getline(std::cin, course_number);

				cout << "Enter course credits: ";
				string course_credits = "";
				std::getline(std::cin, course_credits);

				try {

					stmt = con->createStatement();
					stmt->execute("Insert into Course_T (prefix, number, title, credits) values ('" + course_prefix + "'," + course_number + ",'" + course_title + "'," + course_credits + ")");
					cout << "New Course Inserted" << endl << endl;

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}

			}
			else if (action2 == "g")
			{
				cout << "Enter grade type: ";
				string type = "";
				std::getline(std::cin, type);

				cout << "Enter grade gpa: ";
				string gpa = "";
				std::getline(std::cin, gpa);

				try {

					stmt = con->createStatement();
					stmt->execute("Insert into Grade_T (g_type, g_number) values ('" + type + "'," + gpa + ")");
					cout << "New Grade Inserted" << endl << endl;

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}
			else if (action2 == "m")
			{
				cout << "Enter semester code: ";
				string code = "";
				std::getline(std::cin, code);

				cout << "Enter semester year: ";
				string year = "";
				std::getline(std::cin, year);

				cout << "Enter semester name: ";
				string desc = "";
				std::getline(std::cin, desc);

				try {

					stmt = con->createStatement();
					stmt->execute("Insert into Semester_T (code, year, description) values ('" + code + "'," + year + ",'" + desc + "')");
					cout << "New Semester Inserted" << endl << endl;

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}
			else if (action2 == "s")
			{
				cout << "Enter student last name: ";
				string lastname = "";
				std::getline(std::cin, lastname);

				cout << "Enter student first name: ";
				string firstname = "";
				std::getline(std::cin, firstname);

				cout << "Enter phone number: ";
				string phone = "";
				std::getline(std::cin, phone);

				try {

					stmt = con->createStatement();
					stmt->execute("Insert into Students_T (lname, fname, phone) values ('" + lastname + "','" + firstname + "','" + phone + "')");
					cout << "New Student Inserted" << endl << endl;

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}
			else if (action2 == "t")
			{
				cout << "Enter student last name: ";
				string lastname = "";
				std::getline(std::cin, lastname);

				cout << "Enter student first name: ";
				string firstname = "";
				std::getline(std::cin, firstname);

				cout << "Enter course prefix: ";
				string course_prefix = "";
				std::getline(std::cin, course_prefix);

				cout << "Enter course number: ";
				string course_number = "";
				std::getline(std::cin, course_number);

				cout << "Enter grade type: ";
				string type = "";
				std::getline(std::cin, type);

				cout << "Enter semester code: ";
				string code = "";
				std::getline(std::cin, code);

				string courseid = "";
				string gradeid = "";
				string semid = "";

				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Course_T where prefix ='" + course_prefix + "' and number =" + course_number);
					while (res->next()) {
						courseid = res->getString("courseid");
					}

					if (!courseid.empty())
					{
						stmt = con->createStatement();
						res = stmt->executeQuery("Select * from Grade_T where g_type ='" + type + "'");
						while (res->next()) {
							gradeid = res->getString("gradeid");
						}

						if (!gradeid.empty())
						{
							stmt = con->createStatement();
							res = stmt->executeQuery("Select * from Semester_T where code ='" + code + "'");
							while (res->next()) {
								semid = res->getString("semid");
							}

							if (!semid.empty())
							{
								stmt = con->createStatement();
								stmt->execute("Insert into Students_Course_T (lname, fname, courseid, gradeid, semid) values ('" + lastname + "','" + firstname + "'," + courseid + "," + gradeid + "," + semid + ")");
								cout << "Student Enrolled Successfully" << endl << endl;
							}
							else
							{
								cout << "Wrong Semester";
							}

						}
						else
						{
							cout << "Wrong Grade";
						}

					}
					else
					{
						cout << "Wrong Course Prefix or Number";
					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}

		}
		else if (action == "l")
		{
			string action2 = "";
			cout << "Please choose from the below menu" << endl;
			cout << "Press c for list of all courses" << endl;
			cout << "Press g for list of all grades" << endl;
			cout << "Press m for list of all semesters" << endl;
			cout << "Press s for list of all students" << endl;
			cout << "Press t for list of all taken courses" << endl << endl;

			std::getline(std::cin, action2);
			if (action2 == "c")
			{
				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Course_T");
					while (res->next()) {
						cout << "Course Prefix: " + res->getString("prefix") << endl;
						cout << "Course Number: " + res->getString("number") << endl;
						cout << "Course Title: " + res->getString("title") << endl;
						cout << "Credit Hours: " + res->getString("credits") << endl << endl;
					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}
			else if (action2 == "g")
			{
				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Grade_T");
					while (res->next()) {
						cout << "Grade Type: " + res->getString("g_type") << endl;
						cout << "Grade Number: " + res->getString("g_number") << endl << endl;
					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}

			else if (action2 == "m")
			{
				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Semester_T");
					while (res->next()) {
						cout << "Semester Code: " + res->getString("code") << endl;
						cout << "Semester Year: " + res->getString("year") << endl << endl;
						cout << "Semester Description: " + res->getString("description") << endl << endl;
					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}

			else if (action2 == "s")
			{
				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Students_T");
					while (res->next()) {
						cout << "Last Name: " + res->getString("lname") << endl;
						cout << "First Name: " + res->getString("fname") << endl << endl;
						cout << "Phone: " + res->getString("phone") << endl << endl;
					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}

			else if (action2 == "t")
			{
				try {

					stmt = con->createStatement();
					res = stmt->executeQuery("Select * from Students_Course_T");
					while (res->next()) {
						cout << "Last Name: " + res->getString("lname") << endl;
						cout << "First Name: " + res->getString("fname") << endl;

						string courseid = res->getString("courseid");
						string gradeid = res->getString("gradeid");
						string semid = res->getString("semid");

						string semcode = "";
						string prefix = "";
						string number = "";
						string title = "";
						string gradcode = "";

						sql::Statement *stmt2 = NULL;
						sql::ResultSet *res2 = NULL;

						stmt2 = con->createStatement();
						res2 = stmt2->executeQuery("Select * from Semester_T where semid=" + semid);
						while (res2->next()) {
							semcode = res2->getString("code");
						}

						stmt2 = con->createStatement();
						res2 = stmt2->executeQuery("Select * from Course_T where courseid=" + courseid);
						while (res2->next()) {
							prefix = res2->getString("prefix");
							number = res2->getString("number");
							title = res2->getString("title");
						}

						stmt2 = con->createStatement();
						res2 = stmt2->executeQuery("Select * from Grade_T where gradeid=" + gradeid);
						while (res2->next()) {
							gradcode = res2->getString("g_type");

						}

						cout << "Semester Code: " + semcode << endl;
						cout << "Course Prefix: " + prefix << endl;
						cout << "Course Number: " + number << endl;
						cout << "Course Name: " + title << endl;
						cout << "Grade Code: " + gradcode << endl;

					}

				}
				catch (sql::SQLException &e) {
					cout << "# ERR: " << e.what();
				}
			}

		}
		else if (action == "d")
		{
			cout << "Enter student last name: ";
			string lastname = "";
			std::getline(std::cin, lastname);

			cout << "Enter student first name: ";
			string firstname = "";
			std::getline(std::cin, firstname);

			try {

				stmt = con->createStatement();
				stmt->execute("Delete from Students_T where lname='" + lastname + "' and fname='" + firstname + "'");

				stmt = con->createStatement();
				stmt->execute("Delete from Addresses_T where lname='" + lastname + "' and fname='" + firstname + "'");

				stmt = con->createStatement();
				stmt->execute("Delete from Students_Course_T where lname='" + lastname + "' and fname='" + firstname + "'");

				cout << "Student Deleted" << endl << endl;

			}
			catch (sql::SQLException &e) {
				cout << "# ERR: " << e.what();
			}
		}
		else if (action == "t")
		{
			cout << "Enter student last name: ";
			string lastname = "";
			std::getline(std::cin, lastname);

			cout << "Enter student first name: ";
			string firstname = "";
			std::getline(std::cin, firstname);

			try {
				bool check = true;
				string temp = "";
				int tot_courses = 0;
				double credithrs = 0;
				double gpa = 0;

				stmt = con->createStatement();
				res = stmt->executeQuery("Select * from Students_Course_T where lname='" + lastname + "' and fname='" + firstname + "' ORDER BY semid ASC");
				while (res->next()) {
					if (check) {
						cout << "*** Transcript ***" << endl << endl;
						cout << "Last Name: " + res->getString("lname") << endl;
						cout << "First Name: " + res->getString("fname") << endl << endl;

						sql::Statement *stmt2 = NULL;
						sql::ResultSet *res2 = NULL;

						stmt2 = con->createStatement();
						res2 = stmt2->executeQuery("Select * from Semester_T where semid=" + res->getString("semid"));
						while (res2->next()) {
							cout << res2->getString("description") << endl;
							temp = res2->getString("description");
						}

						check = false;
					}

					string courseid = res->getString("courseid");
					string gradeid = res->getString("gradeid");
					string semid = res->getString("semid");
					tot_courses++;

					string semcode = "";
					string prefix = "";
					string number = "";
					string title = "";
					string gradcode = "";

					sql::Statement *stmt2 = NULL;
					sql::ResultSet *res2 = NULL;

					stmt2 = con->createStatement();
					res2 = stmt2->executeQuery("Select * from Semester_T where semid=" + semid);
					while (res2->next()) {
						semcode = res2->getString("description");
					}

					stmt2 = con->createStatement();
					res2 = stmt2->executeQuery("Select * from Course_T where courseid=" + courseid);
					while (res2->next()) {
						prefix = res2->getString("prefix");
						number = res2->getString("number");
						title = res2->getString("title");
						credithrs = credithrs + res2->getInt("credits");
					}

					stmt2 = con->createStatement();
					res2 = stmt2->executeQuery("Select * from Grade_T where gradeid=" + gradeid);
					while (res2->next()) {
						gradcode = res2->getString("g_type");
						gpa = gpa + res2->getInt("g_number");

					}

					if (temp != semcode)
					{
						cout << semcode << endl;
						temp = semcode;
					}


					cout << "Course Prefix: " + prefix << endl;
					cout << "Course Number: " + number << endl;
					cout << "Course Name: " + title << endl;
					cout << "Grade Code: " + gradcode << endl << endl;

				}

				cout << "Credit Hours: " + to_string(credithrs) + "" << endl;
				double final_gpa = gpa / credithrs;
				cout << "GPA: " + to_string(final_gpa) + "" << endl;


			}

			catch (sql::SQLException &e) {
				cout << "# ERR: " << e.what();
			}
		}
		else if (action == "q")
		{
			delete res;
			delete stmt;
			delete con;

			//system("pause");
			return EXIT_SUCCESS;
		}
		else
		{

		}
	}


}