#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

class Person {
protected:
    string name;
    int age;
    
public:
    virtual void getdata() = 0;
    virtual void putdata() = 0;
    virtual ~Person() {}
};

class Professor : public Person {
private:
    int publications;
    int cur_id;
    static int id_counter;
    
public:
    Professor() {
        cur_id = ++id_counter;
    }
    
    void getdata() override {
        cin >> name >> age >> publications;
    }
    
    void putdata() override {
        cout << name << " " << age << " " << publications << " " << cur_id << endl;
    }
};

class Student : public Person {
private:
    int marks[6];
    int cur_id;
    static int id_counter;
    
public:
    Student() {
        cur_id = ++id_counter;
    }
    
    void getdata() override {
        cin >> name >> age;
        for (int i = 0; i < 6; i++) {
            cin >> marks[i];
        }
    }
    
    void putdata() override {
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += marks[i];
        }
        cout << name << " " << age << " " << sum << " " << cur_id << endl;
    }
};

// Initialize static variables
int Professor::id_counter = 0;
int Student::id_counter = 0;

int main() {
    int n, val;
    cin >> n; // number of objects to create
    
    Person* per[n];
    
    for (int i = 0; i < n; i++) {
        cin >> val;
        if (val == 1) {
            // Create Professor object
            per[i] = new Professor;
        } else {
            // Create Student object
            per[i] = new Student;
        }
        per[i]->getdata(); // get data from user
    }
    
    for (int i = 0; i < n; i++) {
        per[i]->putdata(); // display data
    }
    
    // Clean up memory
    for (int i = 0; i < n; i++) {
        delete per[i];
    }
    
    return 0;
}