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
    RecordBookPage *ptr = nullptr;
    RecordBookPage *ptr_back = nullptr;


    /* void add_subj(ifstream &f) {
         Test New_test;
         f >> New_test.name >> New_test.grade;
         list.push_back(New_test);
     } */
    void add_student_data(string name, ifstream &f){
        this->student = name;
        unsigned n;
        f >> n;
        for(unsigned j =0; j < n; ++j){
            Test New_test;
            f >> New_test.name >> New_test.grade;
            list.push_back(New_test);
        }
    }

    // Функция для вывода данных страницы на консоль
    void print() {
        cout << "Student Name: " << setw(15) << student << endl;
        cout << setw(15) << "Test/Exam Name" << setw(25) << "Grade" << endl;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (auto current_it = begin(list); current_it != end(list); current_it++) {
            cout << setw(15) << current_it ->name << setw(25) << current_it -> grade << endl;
        }
    }

    /*void add_student_name(string name) {
        this->student = name;
    }*/

    string get_student_name(string name){
        name = student;
        return name;
    }
};

class Group {
private:
    RecordBookPage *rhand;
    RecordBookPage *lhand;
    unsigned i;
public:
    Group(ifstream& fin)//конструктор
    {
        fin >> i;
        vector<string> students_to_add(i);
        lhand = new RecordBookPage;
        for(size_t j = 0; j < i; ++j)
        {
            fin >> students_to_add[j];
            lhand -> add_student_data(students_to_add[j],fin);
            rhand = new RecordBookPage;
            lhand -> ptr = rhand;
            rhand -> ptr_back = lhand;
            lhand = rhand;
        }
        cout << "Student added:"<< i << endl;
    }
    ~Group()//деструктор
    {
        while(rhand != nullptr)
        {
            RecordBookPage *tmp = rhand -> ptr_back;
            delete rhand;
            rhand = tmp;
        }
        cout << i << "Student deleted" << endl;
    }
    /*void create_group(unsigned i, vector<string> students_to_add, ifstream &fin) {
        lhand = new RecordBookPage;
        for (size_t j = 0; j < i - 1; ++j) {
            fin >> students_to_add[j];
            lhand->add_student_name(students_to_add[j]);
            lhand->add_subj(fin);
            rhand = new RecordBookPage;
            lhand->ptr = rhand;
            lhand = rhand;
        }
    }*/
    void add_student(ifstream &fin){
        rhand = new RecordBookPage;
        rhand -> ptr_back = lhand;
        lhand -> ptr = rhand;
        lhand = rhand;
        string name;
        fin >> name;
        rhand -> add_student_data(name, fin);
        cout << "Student: " << name << " added" << endl;
    }

    void delete_students(ifstream &fin) {
        RecordBookPage *ptr_end_list = rhand;
        string name_copy;
        string name;
        fin >> name;
        while(rhand != nullptr && lhand -> get_student_name(name_copy) != name)
        {
            lhand = rhand->ptr_back;
            if(lhand->get_student_name(name_copy) == name)
            {
                RecordBookPage *tmp = rhand->ptr;
                if (tmp != nullptr)
                {
                    tmp->ptr_back = lhand;
                }
                lhand->ptr = tmp;
                delete rhand;
                rhand = lhand;
                cout << "Student: "<< name << " deleted" << endl;
                break;
            }
            rhand = lhand;
        }
        rhand = ptr_end_list;
        lhand = rhand;
    }
    void find_student(string name){
        RecordBookPage *ptr_end_list = rhand;
        string name_copy = "a";
        while(rhand != nullptr)
        {
            lhand = rhand -> ptr_back;
            if(name == lhand -> get_student_name(name_copy))
            {
                lhand -> print();
                break;
            }
            rhand = lhand;
        }
        rhand = ptr_end_list;
        lhand = rhand;
    }
    };

int main() {
    string student_to_find;
    ifstream fin("Data.txt");
    Group group(fin);
    fin >> student_to_find;
    group.find_student(student_to_find);
    group.add_student(fin);
    group.delete_students(fin);
    fin.close();

    // Тест добавления студента и его тестовых данных
    ifstream fin1("Data.txt");
    group.add_student(fin1);
    fin1.close();

    // Тест на удаление студента
    ifstream fin2("Data.txt");
    group.delete_students(fin2);
    fin2.close();

    // Проверка поиска студента по имени
    string student_find = "Shemyakin Dmitriy";
    group.find_student(student_find);

    // Тестовая печать страницы книги записей
    RecordBookPage page;
    page.add_student_data("Shemyakin Dmitriy", fin);
    page.print();
    return 0;
}