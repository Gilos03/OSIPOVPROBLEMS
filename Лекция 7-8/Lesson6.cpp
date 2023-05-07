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
    
    vector<Test>& get_list()
    {
        return list;
    }
    
    void set (string student)
    {
        this->student = student;
    }
    
    string get ()
    {
    return student;
    }
    
    string get_student_name(string name)
    {
        name = student;
        return name;
    }

    friend ostream& operator<< (ostream & os,const RecordBookPage& page);
    
    friend istream& operator>> (istream & is,const RecordBookPage& page);
    
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

};

    ostream& operator << (ostream & os, RecordBookPage& page) 
    {
        os << "Student Name: " << setw(15) << page.get() << endl;
        os << setw(15) << "Test/Exam Name" << setw(25) << "Grade" << endl;
        os << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (auto current_it = begin(page.get_list()); current_it != end(page.get_list()); current_it++) {
        os << setw(15) << current_it->name << setw(25) << current_it->grade << endl;
    }
    return os;
    }
    istream& operator >> (istream & is, RecordBookPage& page)
    {
    string name;
    unsigned n;
    is >> name >> n;
    page.get() = name;
    vector<Test> temp_list;
    for (unsigned j = 0; j < n; ++j) {
        Test New_test;
        is >> New_test.name >> New_test.grade;
        temp_list.push_back(New_test);
    }
    page.get_list() = temp_list;
    return is;
    }

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
    Group operator+ (ifstream& fin)
    {
        rhand = new RecordBookPage;
        rhand->ptr_back;
        lhand->ptr;
        lhand=rhand;
        string name;
        fin >> name;
        rhand->add_student_data(name, fin);
        cout << "Student: " << name << "has been added" << endl;
        return *this;
    }
    Group operator- (ifstream& fin)
    {
        RecordBookPage* ptr_end_list = rhand;
        string name_copy;
        string name;
        fin >> name;
        while (rhand->ptr_back != nullptr || lhand->get_student_name(name_copy) != name)
        {
            if(lhand->get_student_name(name_copy) == name)
            {
                lhand = rhand->ptr_back;
                if(rhand->ptr != nullptr)
                {
                    RecordBookPage* ptrr = rhand ->ptr;
                    ptrr->ptr_back = lhand;
                    lhand->ptr = rhand->ptr;
            }
            delete rhand;
            rhand = lhand;
            cout << "Student:" << name << "has been removed" << endl;
            break;
        }
        lhand = rhand->ptr_back;
        rhand = lhand;
        }
        rhand = ptr_end_list;
        lhand = rhand;
        return *this;
    }
    /*void add_student(ifstream &fin){
        rhand = new RecordBookPage;
        rhand -> ptr_back = lhand;
        lhand -> ptr = rhand;
        lhand = rhand;
        string name;
        fin >> name;
        rhand -> add_student_data(name, fin);
        cout << "Student: " << name << " added" << endl;
    }*/

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
            rhand = lhand;
            if(name == lhand -> get_student_name(name_copy))
            {
                lhand -> print();
                break;
            }
            if(lhand->ptr_back == nullptr)
            {
                cout << "There no student with name: " << name << endl;
                break;
            }
        }
        rhand = ptr_end_list;
        lhand = rhand;
    }
    };

int main() {
    string student_to_find;
    ifstream fin("students.txt");
    Group group(fin);
    fin >> student_to_find;
    group.find_student(student_to_find);
    group + fin;
    group - fin;
    //group.add_student(fin);
    //group.delete_students(fin);
    fin.close();
    RecordBookPage page;
    std::cin >> page;
    std::cout << page;

    // Тест добавления студента и его тестовых данных
    /*ifstream fin1("Data.txt");
    group.add_student(fin1);
    fin1.close();*/

    // Тест на удаление студента
    ifstream fin2("Data.txt");
    group.delete_students(fin2);
    fin2.close();

    // Проверка поиска студента по имени
    string student_find = "Shemyakin Dmitriy";
    group.find_student(student_find);

    // Тестовая печать страницы книги записей
    RecordBookPage page1;
    page1.add_student_data("Shemyakin Dmitriy", fin);
    page1.print();
    return 0;
}