#include "student/student_set.h"
#include <iostream>

using namespace std;

int main() {
    StudentSet a;
    a += Student("Masha", 1);
    a += Student("Dima", 2);

    StudentSet b;
    b += Student("Dima", 2);
    b += Student("Anya", 3);

    cout << "A = " << a << '\n';
    cout << "B = " << b << '\n';
    cout << "A | B = " << (a | b) << '\n';
    cout << "A & B = " << (a & b) << '\n';
    cout << "A - B = " << (a - b) << '\n';
}
