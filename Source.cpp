#include<iostream>
#include<string>
#include<fstream>
#include<sstream>//headerfile for stringstream
#include<algorithm>
using namespace std;
struct login {
	string username;
	string password;
};
struct Faculty {
	
	string name;
	string qualification;
	string phone_no;
	string address;
	string courses[5];
	int n_courses;
	string password;
};
bool search_course(string c);
bool search_course_code(int c);
string code_to_title(int code)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		while (getline(fin, line))
		{
			string fields[5];
			stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}

			if (fields[1] == std::to_string(code))
			{
				return fields[0];
				break;
			}

		}
		
	}
}
int title_t0_code(string title)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}

			if (fields[0] == title)
			{
				return std::stoi(fields[1]);
				break;
			}

		}

	}
}
void displayreg_Course(string k)
{
	bool key = false;
	ifstream fin("Registered courses.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			string fields[3];
			stringstream ss(line);
			for (int y = 0; y < 3; y++)
			{
				getline(ss, fields[y], '\t');
			}
			if (fields[0] == k)
			{
				key = true;
				cout << "Courses registered by " << k << " are: ";
				stringstream courses(fields[2]);//creating a stringstream object and initializes it with field[4]
				string course;
				int count = 0;
				while (getline(courses, course, ' '))
				{
					bool j = false;
					if (count > 0)//checking if the course is last or not 
					{
						cout << ",";
					}
					j = search_course_code(std::stoi(course));
					if (j == true)
					{
						cout << code_to_title(std::stoi(course));
						count++;
					}
					else {
						cout << "Course removed ";
					}
					count++;

				}
			}
		}
		fin.close();
		if (!key)
		{
			cout << "No subject Registered by " << k << " Student " << endl;
		}
	}
	
}
void display_student_eachcourse(int code)
{
	bool key = false;
	ifstream fin("Registered courses.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			string fields[3];
			stringstream ss(line);
			for (int y = 0; y < 3; y++)
			{
				getline(ss, fields[y], '\t');
			}
			
				
				
				stringstream courses(fields[2]);//creating a stringstream object and initializes it with field[4]
				string course;
				int count = 0;
				while (getline(courses, course, ' '))
				{
					if (course == to_string(code))
					{
						key = true;
						cout <<"Student "<<count+1<<": " << fields[0] << endl;
						count++;
					}

				}
			
		}
		fin.close();
		if (!key)
		{
			cout << "No student Registered this course " << endl;
		}
	}
}
void display_std_Faculty(string name)
{
	ifstream file;
	file.open("SampleFaculty.txt");
	if (file.is_open())
	{
		string line;
		bool flag = false;
		while (getline(file, line))
		{
			string fields[6];
			stringstream ss(line);
			for (int i = 0; i < 6; i++)
			{
				getline(ss, fields[i], '\t');
			}
			if (fields[0] == name)
			{
				stringstream courses(fields[4]);//creating a stringstream object and initializes it with field[4]
				string course;
				int count = 0;//variable to keep record of courses enter


				while (getline(courses, course, ','))
				{
					if (count > 0)//checking if the course is last or not 
					{
						cout << endl;
					}
					bool j = search_course(course);
					if (j == true)
					{
						cout << course << ": " << endl;
						display_student_eachcourse(title_t0_code(course));

					}

					count++;
				}
			}
				

		}
		file.close();
	}

}
// Function To add New faculty 
	void addFaculaty(int s) {
		for (int i = 0; i < s; i++) {
			Faculty faculty;

			cout << " Name : ";
			getline(cin, faculty.name);
			cout << "Qualification : ";
			getline(cin, faculty.qualification);
			cout << "Phone no: ";
			getline(cin, faculty.phone_no);
			cout << "Address: ";
			getline(cin, faculty.address);
			cout << "Enter the no of courses(maximum 5) taught by " << faculty.name<<": ";
			cin >> faculty.n_courses;
			cin.ignore();
			for (int j = 0; j < faculty.n_courses; j++)
			{
				bool c = false;
				do {
					cout << "Enter course " << j + 1 << " name:";
					getline(cin, faculty.courses[j]);
					c = search_course(faculty.courses[j]);
					if (c == false)
					{
						cout << "1nstitute does not offer this course" << endl;
					}
				} while (!c);
				

			}
			bool passflag;
			do {
				passflag = false;
				cout << "Assign Password: ";
				getline(cin, faculty.password);
				ifstream fp("Faculty_password.txt");

				if (fp.is_open())
				{
					string line;
					while (getline(fp, line))
					{
						string fields[2];
						stringstream pass(line);
						for (int p = 0; p < 2; p++)
						{
							getline(pass, fields[p], '\t');
						}
						if (fields[1] == faculty.password)
						{
							cout << "Password already exists ";
							passflag = true;
							break;
						}

					}
					fp.close();

				}
				else
				{
					cout << "Error opening file " << endl;
				}

			} while ((passflag));
			
			
			ofstream passfile;
			passfile.open("Faculty_password.txt", ios::app);
			if (passfile.is_open())
			{
				passfile << faculty.name << "\t" << faculty.password << "\t";
				passfile << endl;
				cout << "{  Password also stored in file  }" << endl;
			}
			else 
			{
				cout << "Error openning faculty password file " << endl;
			}
			passfile.close();
			ofstream file;
			file.open("SampleFaculty.txt",ios::app);
			if (file.is_open()) {
				//write faculty information to the file
				file<< faculty.name << "\t" << faculty.qualification << "\t" << faculty.phone_no << "\t" << faculty.address << "\t";
				for (int j = 0; j < faculty.n_courses; j++)
				{
					
					file << faculty.courses[j] ;
					if (j < faculty.n_courses - 1)
					{
						file<< ',';
					}

				}
				file << "\t"+faculty.password+"\t";
				file << endl;
				cout << "Faculty added successfully" << endl;
			}
			else {
				cout << "Error opening file" << endl;
			}

			file.close();

			}

		}
	void searchFaculty(string name)
	
	
	{
			ifstream file;
			file.open("SampleFaculty.txt");
			if (file.is_open())
			{
				string line;
				bool flag = false;
				while (getline(file, line))
				{
					string fields[6];
					std::stringstream ss(line);
					for (int i = 0; i < 6; i++)
					{
						getline(ss, fields[i], '\t');
					}
					//converting both the search name and the field seperated name to lowercase
					transform(name.begin(), name.end(), name.begin(), ::tolower);
					transform(fields[0].begin(), fields[0].end(), fields[0].begin(), ::tolower);
					
					if (fields[0] == name)
					{
						cout << "Name:" << fields[0] << endl;
						cout << "Qualification: " << fields[1] << endl;
						cout << "Phone no: " << fields[2] << endl;
						cout << "Address : " << fields[3] << endl;
						cout << "Courses taught: ";
						stringstream courses(fields[4]);//creating a stringstream object and initializes it with field[4]
						string course;
						int count = 0;//variable to keep record of courses enter
						
					
						while (getline(courses, course, ','))
						{
							bool j = false;
							if (count>0)//checking if the course is last or not 
							{
								cout << ",";
							}
							j = search_course(course);
							if (j == true)
							{
								cout << course;
							}
							else {
								cout << "Course removed ";
							}
							count++;
						}
						cout<<endl << "Password: " << fields[5];
						cout << endl;
						flag = true;
					}



				}
				if (!flag)
				{
					cout << "No such faculaty member found " << endl;
				}

			}
		
		
    }
	void updateFaculaty(string name)
	{
		ifstream file;
		file.open("SampleFaculty.txt");
		if (file.is_open())
		{
			string line;
			bool flag = false;
			ofstream file2;
			file2.open("temp.txt");//creating an empty file to store updated data
			while (getline(file, line))
			{
				
				string fields[6];
				std::stringstream ss(line);
				for (int i = 0; i < 6; i++)
				{
					getline(ss, fields[i], '\t');
				}
				//converting both the search name and the field seperated name to lowercase
				transform(name.begin(), name.end(), name.begin(), ::tolower);
				transform(fields[0].begin(), fields[0].end(), fields[0].begin(), ::tolower);

				if (fields[0] == name)
				{
					cout << "Name:"<< fields[0] << endl;
					
					cout << "Qualification: ";
					cin>> fields[1] ;
					cin.ignore();
					cout << "Phone no: ";
					cin>>fields[2] ;
					cout << "Address : ";
						cin>>fields[3];
						int num_courses;
						cout << "Enter the no of courses: ";
						cin>> num_courses;
						cin.ignore();
						fields[4] = " ";//setting fields of course to empty first
						for (int i = 0; i < num_courses; i++)
						{
							string course;

							bool c = false;
							do {

								cout << "Enter the course " << i + 1 << "name: ";
								getline(cin, course);
								c = search_course(course);
								if (c == false)
								{
									cout << "1nstitute does not offer this course" << endl;
								}
							} while (!c);


							fields[4] += course + ',';

						}
						fields[4].pop_back();//removing extra space from the end added in the above for loop
						cout << "Password: " << fields[5]<<endl;
					
					//update the line
					line = fields[0] + '\t' + fields[1] + '\t' + fields[2] + '\t' + fields[3] + '\t'+ fields[4]+'\t'+fields[5]+'\t';
					flag = true;
				}
				//writing the line to the temporary file
				file2 << line << endl;
				

			}
			file.close();
			file2.close();
			
			if (!flag)
			{ 
				remove("temp.txt");//deleting the updated file
				cout << "No such faculaty member found " << endl;
			}
			else {
				//replace the original file with the temporary file
				remove("SampleFaculty.txt");
				rename("temp.txt", "SampleFaculty.txt");
				cout << "Faculaty data updated " << endl;
			}

		}
	}
	struct id {
		int code = 2022;
		string rollno;
};
struct student {
	string name;
	id roll_no;
	string qualification;
	int phone_no;
	string address;
	string course[6];


};
void addstudent(int n)
{
	for (int i = 0; i < n; i++)
	{    
		student std;
		cout << "Name: ";
		getline(cin, std.name);
		bool idflag;
		do {
			idflag = false;
			cout << "Roll no :"<<std.roll_no.code;
			getline(cin, std.roll_no.rollno);
			id password = std.roll_no;
			ifstream sp("Student_password.txt");
			if (sp.is_open())
		    	{
				    string line;
				    while (getline(sp, line))
				    {
					   string fields[2];
					   stringstream spass(line);
					     for (int p = 0; p < 2; p++)
					     {
						getline(spass, fields[p], '\t');
					     }
					    if(fields[1]==std::to_string(password.code)+password.rollno)//converting the password into string type to compare

					    {
						 cout << "Password already exists ";
						 idflag = true;
						 break;
					    }
				    }
				  sp.close();
			}

			     else {
				cout << "Error opening file" << endl;
			     }

		} while (idflag);
		ofstream stdpass("Student_password.txt", ios::app);
		if (stdpass.is_open())
		{
			stdpass << std.name << "\t" << std.roll_no.code<<std.roll_no.rollno<< "\t";
			stdpass << endl;
			cout << "{ Password stored in file }";
		}
		else
		{
			cout << "Error opening student password file " << endl;
		}
		stdpass.close();
		cout << "Qualification: ";
		getline(cin, std.qualification);
		cout << "Phone no ";
		cin >> std.phone_no;
		cin.ignore();
		cout << "Address";
		getline(cin, std.address);

		//opening file to save student
		ofstream fout;
		fout.open("STd.txt",ios::app);
		if (fout.is_open())
		{
			//writing student data to file
			fout << std.name << "\t" << std.roll_no.code<<std.roll_no.rollno << "\t" << std.qualification << "\t" << std.phone_no << "\t" << std.address << endl;
			cout << "Student Added successfully "<<endl;
		}
		else {
			cout << "error opening file ";

		}
		fout.close();
	   }
}
void updateStudent(string name)
{
	ifstream fin;
	fin.open("STd.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		ofstream fout;
		fout.open("temp.txt");//creating an empty file to add updated data
		while (getline(fin, line))
		{

			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			
			if (fields[0] == name)
			{
				
				cout << "Name:"<< fields[0]<<endl;
				cout << "Roll-no: " << fields[1] << endl;

				cout << "Qualification: ";
				cin >> fields[2];
				cout << "Phone no: ";
				cin >> fields[3];
				cout << "Address : ";
				cin >> fields[4];

				//update the line
				line = fields[0] + '\t' + fields[1] + '\t' + fields[2] + '\t' + fields[3] + '\t'+fields[4]+'\t';
				flag = true;
			}
			//writing the line to the temporary file
			fout << line << endl;
			

		}
		fin.close();
		fout.close();
		if (!flag)
		{
			remove("temp.txt");//deleting the updated file
			cout << "No such Student  found " << endl;
		}
		else {
			remove("STd.txt");
			rename("temp.txt", "STd.txt");
			cout << "Student data updated " << endl;

		}

	}
}
void SearchStudent(string r)
{
	ifstream file;
	file.open("STd.txt");
	if (file.is_open())
	{
		string line;
		bool flag = false;
		while (getline(file, line))
		{
			string fields[5];
			stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			if (fields[1] == r)
			{
				cout << "Name : " << fields[0] << endl;
				cout << "Roll-no: " << fields[1] << endl;
				cout << "Qualification: " << fields[2] << endl;
				cout << "Phone no " << fields[3] << endl;
				cout << "Address: " << fields[4] << endl;
				displayreg_Course(fields[1]);
				flag = true;

			}
		}
		if (!flag)
		{
			cout << "No such student found" << endl;
		}
	}
}
struct course {
	string title;
	int code;
	string department;
	int credithour;
	string batch;

};

void addcourse(int n)
{
	for (int k = 0; k < n; k++)
	{
		course c;
		cout << "Title: ";
		getline(cin, c.title);
		bool found = false;
		do {
			cout << "Code: ";
			cin >> c.code;
			bool flag = search_course_code(c.code);
			if (flag)
			{
				cout << "This code already exists please assign new code : ";
				found = true;
				
			}
			else
			{
				found = false;
			}
			
		} while (found);
		
		cin.ignore();
		cout << "Department: ";
		getline(cin, c.department);
		cout << "Credithour: ";
		cin >> c.credithour;
		cin.ignore();
		cout << "Batch: ";
		getline(cin, c.batch);
		ofstream fileout;
		fileout.open("Courses.txt",ios::app);
		if (fileout.is_open())
		{
			fileout << c.title << "\t" << c.code << "\t" << c.department <<"\t"<<c.credithour<<"\t"  << c.batch << "\t";
			
			fileout << endl;
			cout << "{ Course added successfuly }" << endl;
		}
		else {
			cout << "Error opening file " << endl;
		}
		fileout.close();
		

	}
}
void showteachers(string c)
{
	cout << "Teachers teaching this subject : ";
	ifstream facfile("SampleFaculty.txt");
	if (facfile.is_open())
	{
		string line;
		bool flag = false;
		while (getline(facfile, line))
		{
			string fields[6];
			std::stringstream ct(line);
			for (int k = 0; k < 6; k++)
			{
				getline(ct, fields[k], '\t');
			}
			stringstream cc(fields[4]);
			string course;
			int count = 0;
			while (getline(cc, course, ','))
			{
			   
				transform(course.begin(), course.end(), course.begin(), ::tolower);
				transform(c.begin(), c.end(), c.begin(), ::tolower);
				if (c == course)
				{
					if (flag)
					{
						cout << ",";
					}
					else {
						flag = true;
					}
					cout << fields[0];
					count++;
				}
				

			}
			

		}
		if (!flag)
		{
			cout << "No teacher teaching this course " << endl;
		}
	}
	else {
		cout << "Error opening file" << endl;
	}
	cout << endl;
	facfile.close();
}

const int max_size = 50;
bool logintest(login admin)
{
	login user;
	bool flag=false;
	do {
		cout << "Username: ";
		getline(cin, user.username);
		cout << "Password: ";
		getline(cin, user.password);


		if ((admin.username == user.username) && (admin.password == user.password))
		{
			cout << "Successfully login as an admin " << endl;
			flag = true;
			return true;
		}


		else {
			cout << "Incorrect password or username.Please try again" << endl;
			
		}

	} while (!flag );
	
	
	
}
void updatecourse(string c)
{
	ifstream filein("Courses.txt");
	if (filein.is_open())
	{
		string line;
		bool flag = false;
		ofstream fout;
		fout.open("temp.txt");//creating an empty file to add updated data
		while (getline(filein, line))
		{

			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			transform(c.begin(), c.end(), c.begin(), ::tolower);
			transform(fields[0].begin(), fields[0].end(), fields[0].begin(), ::tolower);
			if (fields[0] == c)
			{
				cout << "Title: "<<fields[0]<<endl;
				cout << "Code: ";
				cin >> fields[1];
				cin.ignore();
				cout << "Department: "<<fields[2]<<endl;
				cout << "Credithour: ";
				cin >> fields[3];
				cout << "Batch: "<<fields[4]<<endl;
				//update the line
				line = fields[0] + '\t' + fields[1] + '\t' + fields[2] + '\t' + fields[3] + '\t' + fields[4] + '\t';
				flag = true;
			}
			//writing the line to the temporary file
			fout << line << endl;


		}
		filein.close();
		fout.close();
		if (!flag)
		{
			remove("temp.txt");//deleting the updated file
			cout << "No such course  found " << endl;
		}
		else {
			remove("Courses.txt");
			rename("temp.txt", "Courses.txt");
			cout << "course data updated " << endl;

		}
	}
}
void search_course_department(string c)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		int count = 1;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			//converting both the search name and the field seperated name to lowercase
			transform(c.begin(), c.end(), c.begin(), ::tolower);
			transform(fields[2].begin(), fields[2].end(), fields[2].begin(), ::tolower);
		
			if (fields[2] == c)
			{
				cout << count << ") " << fields[0] << endl;
				flag = true;
				count++;
				
			}

		}
		if (!flag)
		{
			cout << "This department is offering no course " << endl;
		}
		
	}
	fin.close();
}
void search_course_batch(string c)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		int count = 1;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			//converting both the search name and the field seperated name to lowercase
			transform(c.begin(), c.end(), c.begin(), ::tolower);
			transform(fields[2].begin(), fields[2].end(), fields[2].begin(), ::tolower);

			if (fields[4] == c)
			{
				cout <<count<<") " << fields[0] << endl;
				flag= true;
				count++;


			}

		}
		if (!flag)
		{
			cout << "There's no courses in this batch " << endl;
		}

	}
	fin.close();
}
bool search_course(string c)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			//converting both the search name and the field seperated name to lowercase
			transform(c.begin(), c.end(), c.begin(), ::tolower);
			transform(fields[0].begin(), fields[0].end(), fields[0].begin(), ::tolower);
			if (fields[0] == c)
			{
				flag = true;
				break;
			}

		}
		if (flag)
		{
			return true;
		}
		else {
			return false;
		}
	}
	fin.close();
}
bool search_course_code(int c)
{
	ifstream fin;
	bool flag = false;
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			
			if (fields[1] == std::to_string(c) )
			{
				flag = true;
				break;
			}

		}
		if (flag)
		{
			return true;
		}
		else {
			return false;
		}
	}
}
void display_course_code(int c)
{
	ifstream fin;
	
	fin.open("Courses.txt");
	if (fin.is_open())
	{
		string line;
		bool flag = false;
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}

			if (fields[1] == std::to_string(c))
			{
				cout << "Title : " << fields[0] << endl;
				cout << "Code: " << fields[1] << endl;
				cout << "Department : " << fields[2] << endl;
				cout << "Credit hour: " << fields[3] << endl;
				cout << "Batch: " << fields[4] << endl;
			}

		}
		
	}
}
void display_course(string c )
{
	ifstream fin;
	fin.open("Courses.txt");
	if (fin.is_open())
	{

		string line;
		
		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			if (fields[0] == c)
			{
				cout << "Title : " << fields[0] << endl;
				cout << "Code: " << fields[1] << endl;
				cout << "Department : " << fields[2] << endl;
				cout << "Credit hour: " << fields[3] << endl;
				cout << "Batch: " << fields[4] << endl;
			}


		}
	}

}
void remove_course(int course)
{
	ifstream filein("Courses.txt");
	ofstream fileout("temp.txt");
	string line;
	while (getline(filein, line))
	{
		string fields[5];
		std::stringstream ss(line);
		for (int i = 0; i < 5; i++)
		{
			getline(ss, fields[i], '\t');
		}
		//if course code matches the input code then we are not writting it in the temporary file which is removing the course we entered
		if (fields[1] != to_string(course))
		{
			fileout << line << endl;
		}
	}
	filein.close();
	fileout.close();
	//remove the file with old data
	remove("Courses.txt");
	rename("temp.txt", "Courses.txt");
	cout << "{ Course removed successfully }" << endl;

}
bool loginfaculty(login c)
{
	
	bool passflag;
	
		passflag = false;
		ifstream fp("Faculty_password.txt");

		if (fp.is_open())
		{
			string line;
			while (getline(fp, line))
			{
				string fields[2];
				stringstream pass(line);
				for (int p = 0; p < 2; p++)
				{
					getline(pass, fields[p], '\t');
				}
				if ((fields[1] == c.password)&&(fields[0]==c.username))
				{
					
					passflag = false;
					return true;
					break;
				}
				else {
					passflag = true;
					
				}

			}
			if (passflag)
			{
				cout << "Wrong Password or Username please renter correct data " << endl;
				return false;
			}
			fp.close();

		}
		else
		{
			cout << "Error opening file " << endl;
		}

	

}
bool loginstudent(login stdnt)
{
	ifstream sp("Student_password.txt");
	bool idflag = false;
	if (sp.is_open())
	{
		string line;
		while (getline(sp, line))
		{
			string fields[2];
			stringstream spass(line);
			for (int p = 0; p < 2; p++)
			{
				getline(spass, fields[p], '\t');
			}
			if ((fields[1] == stdnt.password)&&(fields[0]==stdnt.username))//converting the password into string type to compare

			{

				idflag = true;
				return true;
				break;
			}
		}
		sp.close();
		if (!idflag)
		{
			cout << "Wrong password or username plaease renter ." << endl;
			return false;
		}
	}
}
bool checkreg_course(string roll, int code)
{
	bool key = false;
	ifstream fin("Registered courses.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			string fields[3];
			stringstream ss(line);
			for (int y = 0; y < 3; y++)
			{
				getline(ss, fields[y], '\t');
			}
			if (fields[0] == roll)
			{
				stringstream courses(fields[2]);//creating a stringstream object and initializes it with field[4]
				string course;
				while (getline(courses, course, ' '))
				{
					if (course == std::to_string(code))
					{
						cout << "You have already registered it " << endl;
						return true;
					}
					
				}
			}
		}
		fin.close();
	}
	return false;
}
void registerCourse(login q,int s)
{
	ifstream fin;
	fin.open("Courses.txt");
	if (fin.is_open())
	{

		string line;

		while (getline(fin, line))
		{
			string fields[5];
			std::stringstream ss(line);
			for (int i = 0; i < 5; i++)
			{
				getline(ss, fields[i], '\t');
			}
			cout << "Title : " << fields[0] << "      ";
			cout << "Code: " << fields[1] << endl;
		}
	}
	fin.close();
	ofstream fo("Registered courses.txt", ios::app);
	if (!fo.is_open())
	{
		cout << "Error opening file " << endl;
	}
	fo << q.password << '\t' << q.username << '\t';
	string name;
	int  code;
	cout << "Enter the code of the course you want to register" << endl;
		int c[6];
		int count = 0;
	for (int i = 0; i < s; i++)
	{
		bool flag = false;
		bool flag2;
		bool flag3 = false;
		do {
			do {
				do {

					flag2 = false;
					cout << "Course " << i + 1 << "code : ";
					cin >> c[i];
					flag = checkreg_course(q.password, c[i]);
					flag3 = search_course_code(c[i]);
					if (flag3)
					{
						for (int f = 0; f < i; f++)
						{

							if (c[i] == c[f])
							{
								cout << "You have already registered this course " << endl;
								flag2 = true;
							}
						}
					}
					else
					{
						cout << "Invalid code " << endl;
					}

				} while (!flag3);


			} while (flag2);
		
	  } while (flag);
		fo << c[i]<<" ";
		

	}
	fo << endl;
	fo.close();

}
void menu() {
	
	cout << endl;
	cout << " _________________________________________"<<endl;
	cout << "| Press 1 for faculty relatrd activities  |" << endl;
	cout << "| Press 2 for student related activites   | " << endl;
	cout << "| Press 3 for courses related activities  |" << endl;
	cout << "| Press 4 to logout                       |" << endl;
	cout << "|_________________________________________|"<<endl;
	cout << "Enter your choice : ";


}
void faculty_related_activities() {
	cout << endl;
	cout << " ____________________________________________________________________"<<endl;
	cout << "| 1) Add new Faculty                                                 |" << endl;
	cout << "| 2) Update Faculty info(like Qualification, Mobile No., Address)    |" << endl;
	cout << "| 3) Search Faculty(Name)                                            |" << endl;
	cout << "|____________________________________________________________________|"<<endl;
	cout << "enter your choice : ";
}
void student_related_activities()
{
	cout << endl;
	cout << " ____________________________________________________________________" << endl;
	cout << "| 1) Add new Student.                                                |" << endl;
	cout << "| 2) Update Student info(like Qualification, Mobile No., Address)    |" << endl;
	cout << "| 3) Search Student(Roll No.)                                        |" << endl;
	cout << "|____________________________________________________________________|" << endl;
	cout << "enter your choice: ";
}
void course_related_activities()
{
	cout << endl;
	cout << " ____________________________________________________________________" << endl;
	cout << "| 1) Add new Course.                                                 |" << endl;
	cout << "| 2) Update Course info(like credit hour, code)                      |" << endl;
	cout << "| 3) Remove Course                                                   |" << endl;
	cout << "| 4) Search Course(Title, Code)                                      |" << endl;
	cout << "| 5) View Course(Department wise or batch wise)                      |" << endl;
	cout << "| 6) View teachers teaching a specific course                        |" << endl;
	cout << "| 7) View students learning  a specific course                       |" << endl;
	cout << "|____________________________________________________________________|" << endl;
	cout << "Enter your choice: ";
}

int main()
{ 
	cout << "===========================================" << endl;
	cout << "||     A Learning Managment System       ||" << endl;
	cout << "===========================================" << endl;
	options:
	cout << "Press 1 to login as an Admin " << endl;
	cout << "Press 2 to login as a Faculty member " << endl;
	cout << "Press 3 to login as a student " << endl;
	cout << "Press 4 to exit the program " << endl;
	int choice,select,select2,entry;
	char choice2;
	bool facultytest = false;
	
	cout << "Choice: ";
	cin >> choice;
	cin.ignore();
	bool admintest = false;
	switch (choice)
	{
	case 1:
	{
		login admin;
		admin.username = "Aizaz";
		admin.password = "100aizaz";
        admintest = logintest(admin);
		break;

	}
	case 2:
	{
		login t;
		do {
			
			cout << "Username: ";
			getline(cin, t.username);
			cout << "Password: ";
			getline(cin, t.password);
			facultytest = loginfaculty(t);
		} while (!facultytest);
		if (facultytest)
		{
			cout << "==========================================" << endl;
			cout << "|               TEACHER PANEL             |" << endl;
			cout << "==========================================" << endl;
			cout << endl;
			tdisplay:
			cout << " 1) To show your Information " << endl;
			cout << " 2) Show students in  my course " << endl;
			int option;
			cout << "Enter your choice: ";
			cin >> option;
			if (option == 1)
			{
				searchFaculty(t.username);
				
			}
			else if (option == 2)
			{
				cout << "Students in courses teach by " << t.username << " : " << endl;
				display_std_Faculty(t.username);

			}
			cout << "_________________________________________" << endl;
			cout << "| press a to goto this domain menu       | " << endl;
			cout << "| Press b to exit the Teachers panel     |" << endl;
			cout << "|________________________________________|" << endl;
			cout << "Enter your choice : ";
			cin >> choice2;

			if ((choice2 == 'a') || (choice2 == 'A'))
			{
				goto tdisplay;
			}
			else if ((choice2 == 'B') || (choice2 == 'b')) {
				goto options;
			}
			else {
				cout << "invalid choice " << endl;
			}
	   }
		break;
	}
	case 3:
	{
		login s;

		bool found = false;
		do {
			cout << "Usename: ";
			getline(cin, s.username);
			cout << "Roll_no(id): ";
			getline(cin, s.password);
			found = loginstudent(s);
		} while (!found); 
		if (found)
		{
			cout << "==========================================" << endl;
			cout << "|               STUDENT PANEL             |" << endl;
			cout << "==========================================" << endl;
			cout << endl;
		sd:
			cout << "1) Show information " << endl;
			cout << "2) Register courses " << endl;
			cout << "3) Display your registered subject " << endl;
			cout << "Enter your choice : ";
			int option;
			cin >> option;
			if (option == 1)
			{
				SearchStudent(s.password);
			}
			else if (option == 2)
			{
				int ccount;
				do{
				cout << "How many courses do you want to register (max 6): ";
				cin >> ccount;
				} while ((ccount < 1) && (ccount > 6));
				registerCourse(s, ccount);
				cout << "Your subject registered Successfully" << endl;
				
			}
			else if (option == 3)
			{
				displayreg_Course(s.password);
				cout << endl; 
			}
			cout<<endl << "_________________________________________" << endl;
			cout << "| press a to goto this domain menu       | " << endl;
			cout << "| Press b to exit the Student panel      |" << endl;
			cout << "|________________________________________|" << endl;
			cout << "Enter your choice : ";
			cin >> choice2;

			if ((choice2 == 'a') || (choice2 == 'A'))
			{
				goto sd;
			}
			else if ((choice2 == 'B') || (choice2 == 'b')) {
				goto options;
			}
			else {
				cout << "invalid choice " << endl;
			}

		}
		break;
	}
	case 4:
	{ 
		return 0;
	}

	}

	if (admintest == true) {
		cout << "==========================================" << endl;
		cout << "|                ADMIN PANEL             |" << endl;
		cout << "==========================================" << endl;
		displaymenu:
		menu();
		cin >> select;
		switch (select)
		{
		case 1:
			fdisplay:
			faculty_related_activities();
			cin >> select2;
			         switch (select2)
			         {
					 case 1:
						 cout << "How many enteries you want to made: ";
						 cin >> entry;
						 cin.ignore();
						 addFaculaty(entry);
						 cout << "Your member successfully added"<<endl;
						 break;

					 
					 case 2:
					 {
					 
						 cin.ignore();
						 cout << "Enter the name whose data you want to update :";
						 string name;
						 getline(cin, name);
						 updateFaculaty(name);
						 break;
					 }
					 case 3:
					 {
						 cin.ignore();
						 cout << "Enter the name whose match you want :";
						 string name;
						 getline(cin, name);
						 searchFaculty(name);
						 break;
					 }
					 default:
						 cout << "Invalid choice " << endl;
					 
					
				      }
					 cout << endl;
			cout << "Press a to goto main menu " << endl;
			cout << "press b to goto this domain menu " << endl;
			cout << "Press e to exit the admin panel " << endl;
			cout << "Enter your choice : " ;
			cin >> choice2;
			if ((choice2 == 'a')|| (choice2 == 'A'))
			{
				goto displaymenu;
			}
			else if( (choice2 == 'b')|| (choice2 == 'B'))
			{
				goto fdisplay;
			}
			else if ((choice2 == 'e') || (choice2 == 'E')) {
				goto options;
			}
			else {
				cout << "invalid choice " << endl;
			}
			break;
		case 2:
			sdisplay:
			student_related_activities();
			cin >> select2;
			           switch (select2) {
			                case 1:
			              {
				              cout << "How many students you want to add: ";
				              cin >> entry;
				              cin.ignore();
				              addstudent(entry);
				              break;

			              }
			                 case 2:
			              {

				              cin.ignore();
				              cout << "Enter the name whose data you want to update :";
				              string name;
				              getline(cin, name);
				              updateStudent(name);
				               break;
			              }
							 case 3:
							 {
								 cin.ignore();
								 cout << "Enter the roll no which you want to search : ";
								 string rol_no;
								 getline(cin, rol_no);
								 SearchStudent(rol_no);
								 break;
							 }

			            }
			cout << endl;
			cout << "Press a to goto main menu " << endl;
			cout << "press b to goto this domain menu " << endl;
			cout << "Press e to exit the admin panel " << endl;
			cout << "Enter your choice : ";
			cin >> choice2;
			if ((choice2 == 'a') || (choice2 == 'A'))
			{
				goto displaymenu;
			}
			else if ((choice2 == 'b') || (choice2 == 'B'))
			{
				goto sdisplay;
			}
			else if ((choice2 == 'e') || (choice2 == 'E')) {
				goto options;
			}
			break;
		case 3:
			cdisplay:
			course_related_activities();
			cin >> select2;
			switch (select2)
			{
			   case 1:
			       {
				   cout << "How many courses you want to enter: ";
				   cin >> entry;
				   cin.ignore();
				   addcourse(entry);
				   break;

			       }
			   case 2:
			   {
				   cout << "Enter the title of the course you want to update : ";
				   string name;
				   cin.ignore();
				   getline(cin, name);
				   updatecourse(name);
				   break;
			   }
			   case 3:
			   {
				   cout << "Enter the code of the course you want to remove : ";
				   int code;
				   cin >> code;
				   bool s = search_course_code(code);
				   if (s == true)
				   {
					   remove_course(code);
				   }
				   else
				   {
					   cout << "no such course found " << endl;
				   }
				   break;
			   }
			   case 4:
			   {
				   cout << "How you want to search " << endl << "1. Title" << endl << "2.Code" << endl << "Enter your choice: ";
				   int key;
				   cin >> key;
				   if (key == 1)
				   {
					   cout << "Enter the title of your desired course : ";
					   string name;
					   cin.ignore();
					   getline(cin, name);
					   bool s = search_course(name);
					   if (s == true)
					   {
						   display_course(name);
					   }
					   else
					   {
						   cout << "no such course found " << endl;
					   }
				   }
				   else if (key == 2)
				   {
					   cout << " Enter the code of your desired course: ";
					   int key2;
					   cin >> key2;
					   bool s = search_course_code(key2);
					   if (s == true)
					   {
						   display_course_code(key2);
					   }
					   else
					   {
						   cout << "no such course found " << endl;
					   }
				   }
				   break;
			   }
			   case 5:
			   {
				   cout << "How do yo want to view your courses : " << endl << "1) Department wise " << endl << "2) Batch wise " <<endl<< "Enter your choice : ";
				   int c;
				   cin >> c;
				   string name;
				   cin.ignore();
				   if (c == 1)
				   {
					   cout << "Department name: ";
					   getline(cin, name);
					   cout << "Courses: " << endl;
					   search_course_department(name);
				   }
				   else if (c == 2)
				   {
					   cout << "Enter batch: ";
					   getline(cin, name);
					   cout << "Courses: " << endl;
					   search_course_batch(name);
				   }
				   else {
					   cout << "Invalid choice " << endl;
				   }
				   break;
			   }
			   case 6:
			   {

				   cout << "Enter the course name whose Teachers you want to see: ";
				   string name;
				   cin.ignore();
				   getline(cin, name);
				   bool s = search_course(name);
				   if (s == true)
				   {
					   showteachers(name);
				   }
				   else
				   {
					   cout << "no such course found "<<endl;
				   }
				   
			   }
			   case 7:
			   {
				   cout << "Enter the code of the course whose students you want to display : ";
					   int c;
				   cin >> c;
				   display_student_eachcourse(c);
				   break;
			   }
			   default:
			   {
				   cout << "Invalid choice " << endl;
			   }
				}
			cout << endl;
			cout << "Press a to goto main menu " << endl;
			cout << "press b to goto this domain menu " << endl;
			cout << "Press e to exit the admin panel " << endl;
			cout << "Enter your choice : ";
			cin >> choice2;
			if ((choice2 == 'a') || (choice2 == 'A'))
			{
				goto displaymenu;
			}
			else if ((choice2 == 'b') || (choice2 == 'B'))
			{
				goto cdisplay;
			}
			else if ((choice2 == 'e') || (choice2 == 'E')) {
				goto options;
			}
			else {
				cout << "invalid choice " << endl;
			}
			break;
		}
		
		
		
	}

	system("pause");
	return 0;
}