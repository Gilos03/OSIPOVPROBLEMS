#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Определяем класс для представления экзамена
class Test {
public:
    string name;
    double grade;
};

// Определяем класс для представления страницы зачетной книжки студента
class RecordBookPage {
private:
    string student;
    //vector<Test> list;
public:
    vector<Test> list;
    RecordBookPage *ptr;
    RecordBookPage *ptr_back;

    void add_subject(ifstream &f) {
        Test New_test;
        f >> New_test.name >> New_test.grade;
        list.push_back(New_test);
    }

    // Печать данных страницы зачетки
    void print(ofstream &of) {
        of << "Student Name: " << setw(15) << this->student << endl;
        of << setw(15) << "Test/Exam Name" << setw(25) << "Grade" << endl;
        of << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (int i = 0; i < list.size(); i++) {
            of << setw(15) << list[i].name << setw(25) << list[i].grade << endl;
        }
    }

    void add_student_name(string name) {
        this->student = name;
    }

    string student_name() {
        return this->student;
    }

    // Деструктор для деаллокации памяти, выделенной с помощью оператора new
    ~RecordBookPage() {
        delete ptr;
    }
};

class Group {
private:
    RecordBookPage *lhand;
public:
    RecordBookPage* getLhand() const {
           return lhand;
       }
    void create_group(unsigned i, vector<string> students_to_add, ifstream &fin) {
        lhand = new RecordBookPage;
        RecordBookPage *current = lhand;
        for (size_t j = 0; j < i - 1; ++j) {
            fin >> students_to_add[j];
            current->add_student_name(students_to_add[j]);
            current->add_subject(fin);
            current->ptr = new RecordBookPage;
            current->ptr->ptr_back = current;
            current = current->ptr;
        }
    }

    void insert_record_book(unsigned index, RecordBookPage book) {
        // Находим RecordBookPage, предшествующий новому вставляемому элемента
        RecordBookPage *current = lhand;
        for (unsigned i = 0; i < index - 1; ++i) {
            if (current == nullptr) {
                return;
            }
            current = current->ptr;
        }

        // Вставляем новый элемент
        RecordBookPage *new_page = new RecordBookPage;
        new_page->add_student_name(book.student_name());
        new_page->list = book.list;
        new_page->ptr = current->ptr;
        new_page->ptr_back = current;
        if (current->ptr != nullptr) {
            current->ptr->ptr_back = new_page;
        }
        current->ptr = new_page;
    }

    void delete_record_book(unsigned index) {
        // Находим RecordBookPage, предшествующий удаляемому элемента
        RecordBookPage *current = lhand;
        for (unsigned i = 0; i < index - 1; ++i) {
            if (current == nullptr) {
                return;
            }
            current = current->ptr;
        }

        // Удаляем элемент
        RecordBookPage *page_to_delete = current->ptr;
        if (page_to_delete == nullptr) {
            return;
        }
        current->ptr = page_to_delete->ptr;
        if (page_to_delete->ptr != nullptr) {
            page_to_delete->ptr->ptr_back = current;
        }
        delete page_to_delete;
    }

    // Деструктор для удаления связанного списка объектов RecordBookPage
    ~Group() {
        // Обход связанного списка и удаление каждого объекта RecordBookPage
        RecordBookPage *current = lhand;
        while (current != nullptr) {
            RecordBookPage *tmp = current;
            current = current->ptr_back;
            delete tmp;
        }
        lhand = nullptr;
    }
};

void find_student(string name, Group &group, ofstream &of) {
    RecordBookPage *current = group.getLhand(); // start at the head of the linked list
    unsigned i = 0;
    while (current) {  // loop through each RecordBookPage in the linked list
        if (current->student_name() == name) {  // check if the student name matches
            of << "Number of student's gradebook: " << i << endl;
            of << "Student's data is:" << endl;
            current->print(of);  // print the student's grade data
            return;
        }
        current = current->ptr;  // move to the next RecordBookPage in the list
        i++;
    }
    of << "Student not found" << endl;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    unsigned n;
    fin >> n;
    vector<string> students_to_add(n);
    Group g;
    g.create_group(n, students_to_add, fin);
    string name;
    fin >> name;
    find_student(name, g, fout);
    fin.close();
    fout.close();
    return 0;
}