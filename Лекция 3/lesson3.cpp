#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Определяем класс для представления для экзамена
class Test {
public:
    string name;
    double grade;
};

// Определяем класс для представления страницы зачетной книжки студента
class RecordBookPage {
private:
    string student;
    vector<Test> list;
public:

    void add_subj(ifstream &f) {
        Test New_test;
        f >> New_test.name >> New_test.grade;
        list.push_back(New_test);
    }

    // Функция для вывода данных страницы на консоль
    void print(ofstream &of) {
        of << "Student Name: " << setw(15) << this->student << endl;
        of << setw(15) << "Test/Exam Name" << setw(25) << "Grade" << endl;
        of << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (int i = 0; i < size(list); i++) {
            of << setw(15) << list[i].name << setw(25) << list[i].grade << endl;
        }
    }

    void add_student_name(string name) {
        this->student = name;
    }

    string student_name() {
        return this->student;
    }
};

class Group {
private:
    vector<RecordBookPage> group;
public:
    void add_RecordBookpage(ifstream &f, unsigned n, string name) {
        RecordBookPage New_RecordBookPage;
        New_RecordBookPage.add_student_name(name);
        group.resize(n);
        for (unsigned i = 0; i < n; ++i)
            New_RecordBookPage.add_subj(f);
        group.push_back(New_RecordBookPage);
    }

    void find_student(string name, ofstream &of) {
        for (unsigned i = 0; i < group.size(); ++i) 
            if (name == group[i].student_name()){
                of << "Number of student's gradebook: " << i << endl;
                of << "Student's data is:" << endl;
                group[i].print(of);
                return;
            }
        of << "Student not found." << endl;
    }
};

int main() {
    Group group;
    unsigned n;
    string student_to_find;
    
    // Открыть входной файл
    ifstream fin("Data.txt");
    if (!fin) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    
    // Считайте количество предметов на одного ученика
    fin >> n;
    
    // Считывание имен студентов и добавление данных в группу
    for (unsigned i = 0; i < n; i++) {
        string name;
        fin >> name;
        group.add_RecordBookpage(fin, n, name);
    }
    
    // Прочитайте имя студента для поиска
    fin >> student_to_find;
    fin.close();
    
    
    ofstream of("out.txt");
    if (!of) {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    
    // Поиск данных о студентах и выходных данных
    group.find_student(student_to_find, of);
    
    // Закрыть выходной файл
    of.close();
    
    return 0;
}