#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <string>
using namespace std;

// student class:

class student{
private:
    int rollno;
    char name[50], lastName[50];
    int phyMarks, cheMarks, mathsMarks, engMarks, csMarks;
    float percentage;
    char grade;
    void calculate();

public:
    void getData();
    void showData();
    int getRollnum();
};

// calculate function of student class:

void student::calculate(){
    percentage = (phyMarks + cheMarks + mathsMarks + engMarks + csMarks)/5.0;
    if(percentage >= 80){
        grade = 'A';
    }else if(percentage >= 70){
        grade = 'B';
    }else if(percentage >= 60){
        grade = 'C';
    }else if(percentage >= 50){
        grade = 'D';
    }else if(percentage >= 40){
        grade = 'E';
    }else if(percentage >= 33){
        grade = 'F';
    }else{
        grade = 'F';
    }
}

// getData function of student class:

void student::getData(){
    system("CLS");
    cout<<"\nEnter the Roll number of student: ";
    cin>>rollno;
    cout<<"\nEnter the First Name of student: ";
    cin>>name;
    cout<<"\nEnter the Last Name of student: ";
    cin>>lastName;
    cout<<"\nEnter the Marks in Physics out of 100: ";
    cin>>phyMarks;
    cout<<"\nEnter the Marks in Chemistry out of 100: ";
    cin>>cheMarks;
    cout<<"\nEnter the Marks in Maths out of 100: ";
    cin>>mathsMarks;
    cout<<"\nEnter the Marks in English out of 100: ";
    cin>>engMarks;
    cout<<"\nEnter the Marks in Computer Science out of 100: ";
    cin>>csMarks;
    calculate();
}

// showData function of student class:

void student::showData(){
    system("CLS");
    cout<<"\t---------------------------";
    cout<<"\n\t      STUDENT DETAIL\n";
    cout<<"\t---------------------------";
    cout<<"\n\n\tRoll number of student: "<<rollno;
    cout<<"\n\n\tName of student: "<<name<<" "<<lastName;
    cout<<"\n\n\tMarks in Physics: "<<phyMarks;
    cout<<"\n\n\tMarks in Chemistry: "<<cheMarks;
    cout<<"\n\n\tMarks in Mathematics: "<<mathsMarks;
    cout<<"\n\n\tMarks in English: "<<engMarks;
    cout<<"\n\n\tMarks in Computer Science: "<<csMarks;
    cout<<"\n\n\tPercentage of student is: "<<percentage;
    cout<<"\n\n\tGrade of student is: "<<grade;
}

// getRollnum function of student class:

int student::getRollnum(){
    return rollno;
}

// function to write or create student information in local database:

void writeStudent(){
    student st;
    ofstream outfile;
    outfile.open("student.dat", ios::binary | ios::app);
    st.getData();
    outfile.write((char*)&st, sizeof(student));
    outfile.close();
    cout<<"\n\nStudent record has been Created ";
    cout<<"\n\nPress Any Key to Continue... ";
    cin.ignore();
    getch();
}

// function to display student record from database using roll no:

void displayStudent(int n){
    system("CLS");
    student st;
    ifstream infile;
    infile.open("student.dat", ios::binary);
    if(!infile){
        cout<<"File could not be open!! Press any key...";
        getch();
        return;
    }

    int temp = 0;
    while(infile.read((char*)&st, sizeof(student))){
        if(st.getRollnum() == n){
            st.showData();
            temp = 1;
        }
    }
    infile.close();
    if(temp == 0){
        cout<<"\n\n\tRECORD DOES NOT EXIST...!!!";
        getch();
    }
}

// function to modify student record in database:

void modifyStudent(int n){
    system("CLS");
    int found = 0;
    student st;
    fstream file;
    file.open("student.dat", ios::binary | ios::in | ios::out);
    if(!file){
        cout<<"\n\n\tFile could not be open !!";
        getch();
        return;
    }
    while(file.read((char*)&st, sizeof(student)) && found==0){
        if(st.getRollnum() == n){
            st.showData();
            cout<<"\n\n\tPlease Enter the new details of student "<<endl;
            st.getData();
            int pos = (-1)*sizeof(st);
            file.seekp(pos, ios::cur);
            file.write((char*)&st, sizeof(student));
            cout<<"\n\n\t Record Updated";
            found = 1;
        }
    }
    file.close();
    if(found == 0){
        cout<<"\n\n\tRECORD NOT FOUND...!!!";
    }
    getch();
}

// function to delete details of student from database:

void deleteStudent(int n){
    student st;
    ifstream infile;
    infile.open("student.dat", ios::binary);
    if(!infile){
        cout<<"\n\n\tFile could not be open !! Press any Key...";
        getch();
        return;
    }
    ofstream outfile;
    outfile.open("temp.dat", ios::out);
    infile.seekg(0, ios::beg);
    while(infile.read((char*)&st, sizeof(student))){
        if(st.getRollnum() != n){
            outfile.write((char*)&st, sizeof(student));
        }
    }
    outfile.close();
    infile.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    cout<<"\n\n\tRECORD DELETED...";
    getch();
}

// function to get the result menu:

void result(){
    char ch;
    int rollno;
    cout<<"\n\n\n\tRESULT MENU";
    cout<<"\n\n\t1. Student Report Card";
    cout<<"\n\n\t2. Back to Main Menu";
    cout<<"\n\n\n\tEnter choice (1/2)? ";
    cin>>ch;
    switch(ch){
    case '1':
        cout<<"\n\n\tEnter Roll number of Student: ";
        cin>>rollno;
        displayStudent(rollno);
        break;
    case '2':
        break;
    default:
        cout<<"\a";
    }
}

// function to show the Main menu:

void studentEntryMenu(){
    char ch;
    int num;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1. Create Student Record";
    cout<<"\n\n\t2. Search Student Record";
    cout<<"\n\n\t3. Modify Student Record";
    cout<<"\n\n\t4. Delete Student Record";
    cout<<"\n\n\t5. Back to Main Menu";
    cout<<"\n\n\tPlease Enter your choice (1-5): ";
    cin>>ch;
    switch(ch){
    case '1':
        writeStudent();
        break;
    case '2':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        displayStudent(num);
        break;
    case '3':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        modifyStudent(num);
        break;
    case '4':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        deleteStudent(num);
        break;
    case '5':
        break;
    default:
        cout<<"\a";
        studentEntryMenu();
    }
}

// main function:

int main(){
    int password();
    password();
    char ch;
    cout.setf(ios::fixed | ios::showpoint);
    cout<<setprecision(2);
    cout<<"\n\n\t\tREPORT CARD";
    do{
        cout<<"\n\t--------------------------------------------";
        cout<<"\n\t  STUDENT REPORT CARD MANAGEMENT SYSTEM\n";
        cout<<"\t--------------------------------------------";

        cout<<"\n\n\t\t**MAIN MENU**";
        cout<<"\n\n\t2. CRUD Menu";
        cout<<"\n\n\t1. Result Menu";
        cout<<"\n\n\t3. EXIT";
        cout<<"\n\n\tPlease Select Your Option: ";
        cin>>ch;
        switch(ch){
            case '1':
                result();
                break;
            case '2':
                studentEntryMenu();
                break;
            case '3':
                cout<<"\n\n STUDENT REPORT CARD MANAGEMENT SYSTEM \n\n";
                return 0;
                break;
            default:
                cout<<"\n\n\tError...!!!...Wrong choice Entered...!!!";
        }
    } while(ch != '3');
}

// password function:

int password(){
    string pass = "";
    char ch;
    cout<<"\n\n\n\n\n\n\t--------------------------------------------";
    cout<<"\n\tSTUDENT REPORT CARD MANAGEMENT SYSTEM LOGIN\n";
    cout<<"\t--------------------------------------------\n";
    cout<<"\n\n\tEnter password: ";
    ch = _getch();
    while(ch != 13){
        pass.push_back(ch);
        cout<<'*';
        ch = _getch();
    }
    if(pass == "12345"){
        cout<<"\n\n\n\tAccess Granted \n\n\n";
        system("PAUSE");
    }else{
        cout<<"\n\n\n\tAccess Aborted...Please Try Again!\n";
        system("PAUSE");
        password();
    }
}
