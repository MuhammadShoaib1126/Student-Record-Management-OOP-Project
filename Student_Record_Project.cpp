#include<iostream>
#include<fstream>
#include<ctime>

using namespace std;

struct Student
{
   int id  ;
   char name[50];
   float gpa ;
   int age ;
   char department[3];	
};

struct User 
{
	char name[50];
	char password[20];
};
 
void setColor(int colorCode) {
    cout << "\033[1;" << colorCode << "m";
}
void bold()
{
	cout << "\033[1m" ;
}
void italic()
{
	cout << "\033[3m";
}

Student* students = nullptr;
int studentCount = 0 ;
int capacity = 10 ;

User* user = nullptr;
int user_SIZE = 0 ;
int user_CAPACITY = 10 ;


const char* Binary_File = "students.data" ;
const char* Text_Header = "header.txt" ;
const char* Reporting_File = "reports.txt" ;
const char* Users = "users.data" ; 
void saveStudentRecordToBinary(bool);
void generateReport(bool);

bool checkName(char name[50] , char check[50])
{
	int l1 = 0 , l2 = 0;
	
	for( ; name[l1] !='\0' ; l1++) ;
	for( ; check[l2] !='\0' ; l2++) ;
	
	if(l1 != l2) return false ;
	
	
	for(int i = 0 ;  name[i] != '\0' && check[i] != '\0' ; i++)
	if(name[i] != check[i]) return false;
	
	return true;
}


void set_User()
{
	user = new User[user_CAPACITY];
	user_SIZE = 0 ; 
	user_CAPACITY = 10 ;
}

void User_resize()
{
	user_CAPACITY = user_CAPACITY * 2 ;
	User* temp = new User[user_CAPACITY];
	
	for(int i = 0 ; i < user_SIZE ; i++)
	temp[i] = user[i];
	
	delete []user;
	user = temp;
}
void User_cleanup()
{
	if(user != nullptr) 
	{
		delete [] user;
		user = nullptr;
	}
	user_CAPACITY = 10 ;
	user_SIZE = 0;
}

void add_user()
{
	if(user_SIZE >= user_CAPACITY)
	User_resize();
	
	User temp;
	setColor(37);
	cout << "Please Enter the Username: ";
	cin.getline(temp.name , 49);
	cout << "Please Enter the Password: ";
	cin.getline(temp.password , 19 );
	
	user[user_SIZE++] = temp; 
}
bool authenticateUser()
{
	User temp;
	setColor(37);
	cout << "Please Enter the Username: ";
	cin.getline(temp.name , 49);
	cout << "Please Enter the Password: ";
	cin.getline(temp.password,19);
	
	for(int i = 0 ; i < user_SIZE ; i++)
	{
		if((checkName(temp.name , user[i].name) == true) && (checkName(temp.password ,user[i].password) == true))
		return true;
	}
	return false;
}
bool alreadyregistered() 
{
	if(user_SIZE == 0) return false;
	/* We are calling this in creating account after taking input for new account so last element is input user so we check that if it exits 
	already*/
	User temp = user[user_SIZE - 1];
	for(int i = 0 ; i < user_SIZE -1 ; i++)
	if((checkName(temp.name , user[i].name) == true) && (checkName(temp.password ,user[i].password) == true))
	{
		user_SIZE--;
		return true;
	}
	return false;
}
void savedUserDatainBinaryFile()
{
	ofstream fout(Users , ios::binary);
	
	fout.write((char*)&user_SIZE , sizeof(user_SIZE));
	
	for(int i = 0 ; i < user_SIZE ; i++)
	fout.write((char*)&user[i] , sizeof(user[i]));
	
	fout.close();
}
void loadUsersFromFile()
{
	int savedUsers = 0 ;
	ifstream file(Users,ios::binary);
	if(!file.is_open()) return ;
	User_cleanup();
	set_User();
	file.read((char*)&savedUsers , sizeof(savedUsers));
	
	for(int i = 0 ; i < savedUsers ;  i++)
	{
		if(user_SIZE >= user_CAPACITY) User_resize();
		file.read((char*)&user[user_SIZE],sizeof(user[user_SIZE]));
		user_SIZE++;
	}
	
	file.close();
}

void setValues() 
{
	students = new Student[capacity];
	studentCount = 0 ;
}

void resize() 
{
	capacity = capacity * 2 ;
	Student* temp = new Student[capacity];
	
	for(int i = 0 ; i < studentCount ; i++)
	temp[i] = students[i];
	
	delete[] students;
	students = temp ;
}
void cleanup() 
{
	  if(students != nullptr)
	  {
	  	 delete[] students;
	  	 students = nullptr; 
	   } 
	   studentCount = 0;
	   capacity = 10 ;
}

int deptStudentsCount(int deptno)
{
    int countStudents = 0;
    for(int i = 0; i < studentCount; i++) {
        if(deptno == 1 && students[i].department[0] == 'C' && students[i].department[1] == 'S') 
            countStudents++;
        else if(deptno == 2 && students[i].department[0] == 'S' && students[i].department[1] == 'E') 
            countStudents++;
        else if(deptno == 3 && students[i].department[0] == 'E' && students[i].department[1] == 'E') 
            countStudents++;
    }
    return countStudents;
}
bool isValidAge (float age) 
{
	return (age >= 16 && age <= 23) ;
}
bool isValidGPA(float gpa)  
{
	return (gpa >= 0.0f && gpa <= 4.0f) ;
}

bool isStudentIdUnique(int id)  
{
	
	for(int i = 0 ; i < studentCount ; i++)
	{
		if(students[i].id == id) 
		return false;
	}
	return true;
}

void add_Student()
{
	system("cls");
	if(studentCount >= capacity) 
	resize() ;
	
	Student temp ;
	setColor(33);
	cout <<"\n==== ADD NEW STUDENT ====\n";
	
	int id ;
	do 
	{
	   while(true)
	   {
	   	    setColor(37);
	   	    cout << "Enter Student ID: ";
            cin >> id;
            if (cin.fail())
           {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(31);
            cout << "Invalid input! Please enter numbers only.\n";
            continue;
           }
          break;
	   }
	   cin.ignore();
       if (!isStudentIdUnique(id))
       setColor(31) , 
       cout << "Error: Student ID already exists! Please enter a unique ID.\n";
	} while (!isStudentIdUnique(id));

    temp.id = id; 
    setColor(37);
	cout << "Enter Student Name: ";
	cin.getline(temp.name , 49 );
	 
	float gpa;
	 
	do 
	{
	   while(true)
	   {
	   	   setColor(37);
	   	   cout << "Enter GPA (0.0 - 4.0): ";
	       cin >> gpa;
	   	
	       if (cin.fail())  
          {
              cin.clear();
              cin.ignore(1000, '\n');
              setColor(31);
              cout << "Invalid input! Please enter a numeric GPA.\n";
              continue;  
          }
          break;
	   }
	    if (!isValidGPA(gpa))  
        {setColor(31);
        cout << "Error: GPA must be between 0.0 and 4.0\n";
        }		
	} while (!isValidGPA(gpa));
	
	temp.gpa = gpa;
	cin.ignore();
	 
	 int age;

    do
   {
    while(true)
    {
    setColor(37);
    cout << "Enter Age (16 - 23): ";
    cin >> age;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
    } 
       break;
      
	}
    if (!isValidAge(age))
    {
    	setColor(31);
        cout << "Error: Age must be between 16 and 23!\n";
    }

    } while (!isValidAge(age));

    temp.age = age;
    cin.ignore();
    setColor(33);
	cout << "\nAvailable Departments:\n";
    cout << "1. CS - Computer Science\n";
    cout << "2. SE - Software Engineering\n"; 
    cout << "3. EE - Electrical Engineering\n";
	setColor(37);
	 int deptChoice;

    do
    {
    
    while(true)
    {
    	setColor(37);
    	cin >> deptChoice;
       if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
      } 
	  break; 
	  
	}
    cin.ignore();
    if(deptChoice == 1) 
        temp.department[0] = 'C', temp.department[1] = 'S', temp.department[2] = '\0';
    else if(deptChoice == 2)
        temp.department[0] = 'S', temp.department[1] = 'E', temp.department[2] = '\0';
    else if(deptChoice == 3)
        temp.department[0] = 'E', temp.department[1] = 'E', temp.department[2] = '\0';
    else 
        setColor(31) , cout << "\nInvalid Department Number!\n";

    } while(!(deptChoice > 0 && deptChoice < 4));

	 
	 students[studentCount++] = temp;
	 setColor(32);
	 cout << "\nStudent Added Successfully!\n" ;
	 saveStudentRecordToBinary(false);
	 generateReport(false);
	 
	 setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.get();
	 system("cls");
}

void displayAllStudents() 
{
	system("cls");
	if(studentCount == 0)
	{
		 setColor(33);
		 cout << "\nNo Students Found\n" ;
		 return ;
	}
	setColor(33);
	cout << "\n=== ALL STUDENTS ===\n" << endl;
    cout << "\nTotal students: " << studentCount << endl;
    setColor(37);
	cout << "------------------------------------------------------------" << endl;
    setColor(33);
    cout << "\nID\tName\tAge\tGPA\tDepartment\n"; 
    setColor(37);
    cout << "------------------------------------------------------------" << endl;
    
    
    for(int i = 0 ; i  < studentCount ; i++)
    {
    	setColor(33);
    	cout << students[i].id <<"\t"<<students[i].name <<"\t"<<students[i].age <<"\t"<<students[i].gpa <<"\t"
    	<<students[i].department << endl;
	}
	setColor(33);
	cout << "\nPress Enter to go back to Main Menu \n";
	cin.ignore();
	cin.get();
	system("cls");
}
int FindStudentById (int id)
{
	for(int i = 0 ;  i < studentCount ; i++)
	if(students[i].id == id )
	return i ;
	
	return -1 ;
}
void displayStudent (int index)
{
	if(index < 0 || index >= studentCount)
	{
		setColor(31);
		cout << "Invalid Student Number!\n";
		return ;
	}
	setColor(33);
	cout << "\n=== STUDENT DETAILS ===\n" ;
	cout << "ID: "<<students[index].id <<"\n";
	cout << "Name: " << students[index].name << endl;
	cout << "Age: " << students[index].age << endl;
	cout << "GPA:"<<students[index].gpa << endl;
	cout << "Department: " << students[index].department << endl;
	
	setColor(33);
}

void searchStudentById() 
{
	system("cls");
	if(studentCount == 0) 
	{
		setColor(33);
		cout << "\nNo Students Found\n";
		return ;
	}
	
	int id;

    while (true) {
    setColor(37);
    cout << "Enter Student ID to search: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
    }

    cin.ignore();
    break;
    }

	int index = FindStudentById(id);
	
	if(index != -1)
		displayStudent(index);
		
	else   setColor(31) , cout << "Student with ID " << id << " not found!" << endl;
	
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.get();
	system("cls");
}

void SearchStudentByName ()
{
	system("cls");
	if(studentCount == 0)
	{
		setColor(33);
		cout << "\nNo Students Found\n";
		return ;
	}
	char searchName[50];
	setColor(37);
	cout << "Enter student name to search: ";
	cin.ignore();
	cin.getline(searchName , 49 );
	
	bool found = false ;
	setColor(33);
	cout << "\n=== SEARCH RESULTS ===\n";
	
	for(int i = 0 ;  i <  studentCount ; i++)
	if(checkName(students[i].name , searchName))
	{
		displayStudent(i);
		found = true;
	}
	
	if(found == false) 
	setColor(31) , cout << "No Students found with name as :" <<searchName << endl;
	
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.get();
	system("cls");	
}

void editStudent() 
{
	system("cls");
	Student temp;
	
	if(studentCount == 0)
	{
		setColor(33);
		cout << "\nNo Student Found\n" ;
		return ;
	}
    int id;

    while (true)
   {
   	setColor(37);
    cout << "Enter Student ID to edit: ";
    cin >> id;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
    }

    break;
   }
    temp.id = id;
	int index = FindStudentById(id) ;
	if( index == -1)
	{
		setColor(31);
		cout << "Student with ID " << id << " not found  \n";
		return ;
	}
	displayStudent(index);
	setColor(33);
	cout << "\n=== EDIT STUDENT ===\n";
	
	cin.ignore();
	setColor(37);
	cout << "Enter new Name (current: " << students[index].name << "): ";
    cin.getline(temp.name, 49);
    
    do {
    
    while(true)
    {
    	setColor(37);
    	 cout << "Enter new GPA (current: " << students[index].gpa << "): ";
         cin >> temp.gpa;

         if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter a numeric GPA.\n";
        continue;
        }
        break;
	}
    cin.ignore();
    if (!isValidGPA(temp.gpa)) {
    	setColor(31);
        cout << "Error: GPA must be between 0.0 and 4.0!\n";
    }
    } while (!isValidGPA(temp.gpa));

    
    do {
     
     while(true)
     {
     	setColor(37);
     	cout << "Enter new Age (current: " << students[index].age << "): ";
        cin >> temp.age;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter a numeric age.\n";
        continue;
    } 
      break;
	 }
      cin.ignore();
    if (!isValidAge(temp.age)) {
    	setColor(31);
        cout << "Error: Age must be between 16 and 23!\n";
    }
    } while (!isValidAge(temp.age));
    setColor(33);
    cout << "\nAvailable Departments:\n";
    cout << "1. CS - Computer Science\n";
    cout << "2. SE - Software Engineering\n"; 
    cout << "3. EE - Electrical Engineering\n";
	setColor(37);
	cout << "Enter new Department (current: " << students[index].department << "): ";
	 
	int deptChoice;

    do
    {
    setColor(37);
    while(true)
    {
    	cin >> deptChoice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "\nInvalid input! Please enter numbers only.\n";
        continue;
    }
     break;
	}

    cin.ignore();

    if(deptChoice == 1) 
        temp.department[0] = 'C', temp.department[1] = 'S', temp.department[2] = '\0';
    else if(deptChoice == 2)
        temp.department[0] = 'S', temp.department[1] = 'E', temp.department[2] = '\0';
    else if(deptChoice == 3)
        temp.department[0] = 'E', temp.department[1] = 'E', temp.department[2] = '\0';
    else 
        setColor(31) , cout << "\nInvalid Department Number!\n";

    } while(!(deptChoice > 0 && deptChoice < 4));

	 
	 students[index] = temp;
	 setColor(32);
	 cout << "\nStudent Record Updated Successfully\n" ;
	 
	 saveStudentRecordToBinary(false);
	 generateReport(false);
	 
	 setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.get();
	 system("cls");
}
 
void deleteStudent() 
{
    system("cls");
	if(studentCount == 0)
	{
		setColor(33);
		cout << "\nNo Students Found\n";
		return ;
	}
    
    int id;
    while (true) {
    setColor(37);
    cout << "Enter Student ID to delete: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
    }
    break;
   }
    
	int index = FindStudentById(id);
	if(index == -1)
	{
		setColor(31);
		cout << "Student with ID " << id << " not found!" << endl;
		return ;
	}
	
	displayStudent(index);
	
	char confirming;
	setColor(33);
	cout << "\nAre you sure you want to delete this student? (y/n): ";
	cin >> confirming;
	
	if(confirming == 'y' || confirming == 'Y')
	{
		Student* temp = new Student[capacity];
		int j = 0 ;
		
		for(int i = 0 ; i < studentCount ; i++)
		if(id != students[i].id)
			temp[j++] = students[i];
		delete [] students;
		students = temp ;
		studentCount = j ;
		setColor(32);
		cout << "\nStudent Deleted Successfully!" <<endl;
	}
	else 
	setColor(31) , cout << "Deletion Cancelled\n" ; 	
	saveStudentRecordToBinary(false);
	generateReport(false);
	
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	system("cls");
}

void sortStudentById()
{
	system("cls");
	setColor(37);
	
	for(int i = 0 ; i < studentCount - 1 ; i++)
	for(int j = 0 ; j < studentCount - i -1 ; j++)
	if(students[j].id > students[j+1].id)
	{
		Student temp = students[j];
		students[j] = students[j+1];
		students[j+1] = temp ;
	} 
	
	setColor(32);
	cout << "\nStudents sorted by ID (Ascending) \n";
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}
bool checklexosmall(char c1[50] , char c2[50])
{
	int l1 = 0  , l2 = 0 ;
	
	for( ; c1[l1] != '\0' ; l1++);
	
	for( ; c2[l2] != '\0' ; l2++);
	
	
	for(int i = 0 ; c1[i] != '\0' && c2[i] != '\0' ; i++)
	{
		if(c1[i] < c2[i]) return true;
		if(c1[i] > c2[i]) return false;
	}
	return l1 < l2;
}
void sortStudentByName()
{
	system("cls");
	 for(int i = 0 ; i  <  studentCount - 1 ; i++)
	 for(int j = 0 ; j < studentCount - i -1 ; j++)
	 if(!(checklexosmall(students[j].name,students[j+1].name)))
	 {
	 	Student temp = students[j];
		students[j] = students[j+1];
		students[j+1] = temp ;
	 }
	 setColor(32);
	 cout << "\nStudents sorted by Name(Lexographically Small Name Comes First) \n";
	 setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}
void sortStudentByGPA()
{
	system("cls");
	for(int i = 0 ; i < studentCount - 1 ; i++)
	for(int j = 0 ; j < studentCount - i -1 ; j++)
	if(students[j].gpa > students[j+1].gpa)
	{
		Student temp = students[j];
		students[j] = students[j+1];
		students[j+1] = temp ;
	}
	setColor(32);
	cout << "\nStudents sorted by GPA(Lowest GPA to Highest GPA) \n";
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}

void sortStudentByAge() 
{
	system("cls");
	for(int i = 0 ; i < studentCount - 1 ; i++)
	for(int j = 0 ; j < studentCount - i -1 ; j++)
	if(students[j].age > students[j+1].age)
	{
		Student temp = students[j];
		students[j] = students[j+1];
		students[j+1] = temp ;
	}
	setColor(32);
	cout << "\nStudents sorted by AGE (Ascending) \n";
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}

void CalculateAverageGPA()
{
	system("cls");
	if(studentCount == 0) 
	{
		setColor(33);
		cout << "\nNo Students Found to calculate the Average GPA\n";
		return ;
	}
	
	float  sumValues = 0;
	
	for(int i = 0 ; i < studentCount ; i++)
	sumValues += students[i].gpa;
	setColor(33);
	cout <<"\nThe Average GPA of Students of all departments is : " << sumValues / studentCount <<'\n';
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}

void CalculateGPADeptwise()
{ 
    system("cls");
	if(studentCount == 0) 
	{
		setColor(33);
		cout << "\nNo Students Found to calculate the Average GPA\n";
		return ;
	}
	float sumCS = 0 , sumSE = 0 , sumEE = 0 , countCS = 0 , countSE = 0 , countEE = 0;
	
	for(int i = 0 ; i < studentCount ; i++)
	if(students[i].department[0] == 'C' && students[i].department[1] == 'S' ) sumCS += students[i].gpa , countCS++;
	else if(students[i].department[0] == 'S' && students[i].department[1] == 'E' ) sumSE += students[i].gpa , countSE++;
	else if(students[i].department[0] == 'E' && students[i].department[1] == 'E' ) sumEE += students[i].gpa , countEE++;
	setColor(33);
	cout << "\n=== Department-Wise Average GPA is : \n";
	
	if(countCS > 0 ) cout << "CS Department : "<<sumCS / countCS << '\n';
	else cout << "CS Department : No Students to calculate Average GPA\n";
	if(countSE > 0) cout << "SE Department : "<<sumSE / countSE << '\n';
	else cout << "SE Department : No Students to calculate Average GPA\n";
	if(countEE > 0 ) cout << "EE Department : "<<sumEE / countEE << '\n';
	else cout << "EE Department : No Students to calculate Average GPA\n" ;
	setColor(33);
	cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
	
}
void showDeptwiseStudent()
{
	system("cls");
	setColor(33);
	cout << "\n=== DEPARTMENT-WISE STUDENTS RECORD ===\n";
	
	if(studentCount == 0) 
	{
		setColor(33);
		cout << "\nNo Students Found\n";
		return ;
	}
	
	cout << "\nCOMPUTER SCIENCE(CS) DEPARTMENT \n";
	
	if(deptStudentsCount(1) == 0)
	cout << "\nNo Students Found in this Department\n";
	else 
	    for(int i = 0 ; i < studentCount ; i++)
          	if(students[i].department[0] == 'C' && students[i].department[1] == 'S') 
	           cout << students[i].id <<"\t"<<students[i].name <<"\t"<<students[i].age <<"\t"<<students[i].gpa <<"\t"<<endl;
	
	
	cout << "\nSOFTWARE ENGINEERING(SE) DEPARTMENT \n";
	if(deptStudentsCount(2) == 0)
	    cout << "\nNo Students Found in this Department\n";
	else 
       for(int i = 0 ; i < studentCount ; i++)
	     if(students[i].department[0] == 'S' && students[i].department[1] == 'E') 
	        cout << students[i].id <<"\t"<<students[i].name <<"\t"<<students[i].age <<"\t"<<students[i].gpa <<"\t"<<endl;
	
	cout << "\nELECTRICAL ENGINEERING(EE) DEPARTMENT \n";
	
	if(deptStudentsCount(3) == 0)
	   cout << "\nNo Students Found in this Department\n";
	else 
	    for(int i = 0 ; i < studentCount ; i++)
	        if(students[i].department[0] == 'E' && students[i].department[1] == 'E') 
	           cout << students[i].id <<"\t"<<students[i].name <<"\t"<<students[i].age <<"\t"<<students[i].gpa <<"\t"<<endl;
	setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	system("cls");
}
void saveStudentRecordToBinary(bool checker)
{
     ofstream file(Binary_File , ios::binary);
     file.write((char*)&studentCount , sizeof(studentCount));
     
     for(int i = 0 ; i < studentCount ; i++)
     file.write((char*)&students[i] , sizeof(students[i]));
     
     file.close();
     setColor(32);
     if(checker) cout << "\nRecord Saved in File Successfully\n";
     setColor(37);
}


void readFromBinary()
{
	int savedCount = 0 ;
	
	ifstream fin(Binary_File , ios::binary);
	
	if(!fin.is_open())
	{
		setColor(33);
		cout << "\nNo Student Record in File\n";
		return;
	}
	cleanup();
	setValues();
	
	fin.read((char*)& savedCount , sizeof(savedCount));
	
	for(int i = 0 ;  i < savedCount ; i++)
    {
    	if(studentCount >= capacity) resize();
    	fin.read((char*)&students[studentCount] , sizeof(students[studentCount]));
    	studentCount++;
	}
	
	fin.close();
	setColor(33);
	cout << "\nData Loaded : " << savedCount << " students \n";
	
}

void generateReport(bool checker)
{
	ofstream file(Reporting_File);
	
	if(!file.is_open())
    {
       setColor(31);
       cout << "Sorry Coudln't save data in Reporting File \n";
	   return ;	
	}	
	file << "STUDENT MANAGEMENT SYSTEM - DETAILED REPORT\n";

	file << "=============================================\n";
	file << "\nSYSTEM STATISTICS:\n";
    file << "Total Students: " << studentCount << endl;
	
	file << "ALL REGISTERED STUDENTS:\n";
    file << "ID\tName\t\tAge\tGPA\tDepartment\n";
    file << "---------------------------------------------\n";
    for(int i = 0; i < studentCount; i++) 
    {
        file << students[i].id << "\t" << students[i].name << "\t"
             << students[i].age << "\t" << students[i].gpa << "\t"
             << students[i].department << endl;
    }
    
    float  sumValues = 0;
	
	for(int i = 0 ; i < studentCount ; i++)
	sumValues += students[i].gpa;
	file << "Average GPA: " << (studentCount > 0 ? sumValues/studentCount : 0) << endl;
	
	file << "\nDEPARTMENT INFORMATION:\n";
    file << "CS: " << deptStudentsCount(1) << " students\n";
    file << "SE: " << deptStudentsCount(2) << " students\n"; 
    file << "EE: " << deptStudentsCount(3) << " students\n";
    
    time_t now = time(0);
    
    file << "Reported Generated on "<<ctime(&now)<<"\n" ;
    
    file.close();
    setColor(32);
    if(checker) cout << "Detailed Report Saved in File named : "<< Reporting_File <<'\n';
    setColor(37);
    
}


void createTextHeader() {
    ofstream file(Text_Header);
    file << "STUDENT RECORD MANAGEMENT SYSTEM\n";
    file << "Created: 2025\n";
    file << "BCSF24M503 and BCSF24M525\n";
    file << "Total Students: " << studentCount << endl;
    file << "Total_Users: " << user_SIZE << endl;
    file.close();
}

void displayReportFromFile()
{
	system("cls");
	 ifstream file(Reporting_File);
	 
	 if(!file.is_open())
	 {
	 	setColor(31);
	 	cout << "No Student Record Report File exit . Create a Student Record Report First\n";
	 }
	 setColor(33);
	 cout << "\n===DISPLAYING STUDENT RECORD REPORT FROM FILE ===\n";
	 string line;
	 
	 while(getline(file,line))
	 {
	 	cout << line << endl;
	 }
	 file.close();
	 setColor(33);
	 cout << "\nPress Enter to go back to Main Menu \n";
	 cin.ignore();
	 cin.get();
	 system("cls");
}

void displayWelcomeScreen() {
    system("cls");
    bold();
	italic();
    setColor(37);
    cout << "**************************************************\n";
    cout << "*           STUDENT MANAGEMENT SYSTEM           *\n";
    cout << "*           BCSF24M503 & BCSF24M525             *\n";
    cout << "**************************************************\n";
    setColor(32);
    cout << "           [Press Enter to Continue]             \n";
    cin.get();
}

void login_system()
{
    system("cls");
    setColor(37);
    cout << "==========================================\n";
    setColor(33);
	cout << "           WELCOME BACK!                 \n";
    cout << "      STUDENT MANAGEMENT SYSTEM          \n";
    setColor(37);
	cout << "==========================================\n\n";
    setColor(33);
	cout << "No account? Don't worry!\n\n";
    cout << "1. Create New Account\n";
    cout << "2. Login to Existing Account\n"; 
    cout << "3. Exit Program\n\n";
    setColor(32);
    cout << "Enter your choice (1-3): ";
}
void create_account_interface()
{
    system("cls");
    setColor(37);
    cout << "==========================================\n";
    setColor(33);
	cout << "           CREATE ACCOUNT                \n";
    setColor(37);
    cout << "==========================================\n\n";
    setColor(33);
	cout << "Let's get you started!\n\n";
}
void login_interface() 
{
    system("cls");
    setColor(37);
    cout << "==========================================\n";
    setColor(33);
	cout << "               LOGIN                     \n";
    setColor(37);
	cout << "==========================================\n\n";
    setColor(33);
	cout << "Welcome back! Please sign in\n\n";
}
void login_system_full()
{
	int choice;
	int attempts = 0 ;
	
	do
	{
		login_system();
		cin >> choice;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Invalid Input ! Please enter numbers 1-3 only \n";
			cout << "Press Enter to continue...";
			cin.get();
			continue;
		}
		cin.ignore();
		
		if(choice == 1)
		{
		    create_account_interface();
            add_user();
            if(alreadyregistered() == true) 
            {
            	setColor(31);
            	cout << "\nUser Already Registered!\n";
            	cout << "Press Enter to continue...";
                cin.get();
                login_system_full();
			}
			else 
            {
            setColor(32);
            cout << "\nAccount created successfully!\n";
            cout << "Press Enter to continue...";
            cin.get();
            savedUserDatainBinaryFile();
            login_system_full();
			}
            return;
		}
		else if(choice == 2)
		{
			while(1)
			{
				login_interface();
			if(authenticateUser())
			{
				setColor(32);
				cout << "\nLogin Successfull! Redirecting to main page\n";
				system("cls");
				return;
			}
			else 
			{
				setColor(31);
				cout << "\nLogin Failed! Please try again\n";
				setColor(32);
				cout << "Press Enter to continue...";
				cin.get();
				attempts++;
				if(attempts >= 3)
				{
					setColor(31);
					cout << "\nToo many failed attempts! Exiting...\n";
					setColor(37);
					exit(0);
				}
			}
			}
		}
		else if(choice == 3)
		{
			setColor(32);
			cout << "\nThankyou for using our system!\n";
			setColor(37);
			exit(0);
		}
		else 
        {
        	setColor(31);
            cout << "\nInvalid choice! Please try again.\n";
            setColor(32);
			cout << "Press Enter to continue...";
            cin.get();
        }
			
	}while(true);
}

void displayMainMenu() {
	//system("cls");
	setColor(37);
	
    cout << "\n=== STUDENT RECORD MANAGEMENT SYSTEM ===" << endl;
    
    setColor(33); 
    
    cout << "1.  Add New Student" << endl;
    cout << "2.  View All Students" << endl;
    cout << "3.  Department-Wise Students "<<endl;
    cout << "4.  Search Student by ID" << endl;
    cout << "5.  Search Student by Name" << endl;
    cout << "6.  Edit Student" << endl;
    cout << "7.  Delete Student" << endl;
    
    setColor(36); 
    
    cout << "8.  Sort Students by ID (Ascending) " << endl;
    cout << "9.  Sort Students by Name (Lexographically Small Name Comes First) " << endl;
    cout << "10. Sort Students by GPA (Lowest GPA to Highest GPA) " << endl;
    cout << "11. Sort Students by Age (Ascending) "<<endl;
    
    setColor(35);
    
    cout << "12. Average GPA of Students \n";
    cout << "13. Department-Wise Average GPA \n";
    cout << "14. Retrieve Student Record From Binary_File\n";
    cout << "15. Generate Report From Reporting File\n";
    setColor(31);  
    cout << "16. Exit" << endl;
    cout << "17. Clear_Screen"<<endl;
    setColor(37);
    cout << "=========================================" << endl;
    setColor(32);
	cout << "Enter your choice (1-17): ";
}
int main()
{
	
	displayWelcomeScreen();
	set_User();
	setValues();
	readFromBinary();
	loadUsersFromFile(); 
	createTextHeader();
	
	login_system_full();	
	int choice ;
	do 
	{
		displayMainMenu();
		cin >> choice;
		
		if(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(31);
        cout << "Invalid input! Please enter numbers 1-17 only.\n";
        continue;
    }
		if(choice == 1)         {  add_Student() ;  /*break;*/  }
		else if(choice == 2)    {  displayAllStudents() ;  /*break;*/  }
		else if(choice == 3)    {  showDeptwiseStudent();                                 }
		else if(choice == 4)    {  searchStudentById() ; /*break;*/  }
		else if(choice == 5)     { SearchStudentByName() ; /*break;*/ }
		else if(choice == 6)     { editStudent() ; /*break;*/}
		else if(choice == 7)     { deleteStudent() ; /*break;*/}
		else if(choice == 8)     { sortStudentById() ; /*break;*/}
		else if(choice == 9)     { sortStudentByName() ;/*break;*/}
		else if(choice == 10)     { sortStudentByGPA() ; /*break;*/}
		else if(choice == 11)     { sortStudentByAge() ; /*break*/                              }
		else if(choice == 12)     { CalculateAverageGPA() ; /*break;*/}
		else if(choice == 13)     { CalculateGPADeptwise() ; /*break;*/ }
		else if(choice == 14)     {  readFromBinary(); displayAllStudents(); }
		else if(choice == 15)     {   displayReportFromFile() ;                    }
		else if(choice == 16)   cout << "\nExiting Program\n";
		else if(choice == 17)  system("cls");
		else setColor(31) , cout << "Invalid Choice Please try again\n";
		if(choice == 16)
		{
			cout << "\nPress Enter to continue...\n";
			cin.ignore();
			cin.get();
		}
		
	} while(choice != 16);
	
	generateReport(true);
	createTextHeader();
	saveStudentRecordToBinary(true);
	User_cleanup();
	cleanup();
	return 0;
}