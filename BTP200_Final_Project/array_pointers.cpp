// Array of Pointers
 // array_pointers.cpp

 #include <iostream>
 using namespace std;

 const int N_CHARS = 31;

 struct Student {
     int no;
     double grade;
     char name[N_CHARS];
 };

 int main() {
     const int NO_STUDENTS = 3;
     Student john = {1234, 67.8, "john"};
     Student jane = {1235, 89.5, "jane"};
     Student dave = {1236, 78.4, "dave"};

     Student* pStudent[NO_STUDENTS]; // array of pointers 
     pStudent[0] = &john;
     pStudent[1] = &jane;
     pStudent[2] = &dave;

     for (int i = 0; i < NO_STUDENTS; i++) { 
         cout << pStudent[i]->no << endl;
         cout << pStudent[i]->grade << endl;
         cout << pStudent[i]->name << endl;
         cout << endl;
     }
 }
