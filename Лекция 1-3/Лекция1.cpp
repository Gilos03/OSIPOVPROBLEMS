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
    string student = "Shemyakin Dmitriy";
public:
    vector<Test> list;

    // Функция для ввода имени студента
    void enter_student_name() {
        cout << "Enter student name: ";
        getline(cin, student);
    }

    // Функция для изменения данных студента
    void change_student_data() {
        cout << "Current student name: " << student << endl;
        cout << "Enter new student name: ";
        getline(cin, student);
    }

    void add_subj(ifstream &f) {
        Test New_test;
        f >> New_test.name >> New_test.grade;
        list.push_back(New_test);
    }

    // Функция для вывода данных страницы на консоль
    void print(ofstream &f) {
        f << "Student Name: " << setw(15) << this->student << endl;
        f << setw(15) << "Test/Exam Name" << setw(25) << "Grade" << endl;
        f << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (int i = 0; i < size(list); i++) {
            f << setw(15) << list[i].name << setw(25) << list[i].grade << endl;
        }
    }

    // Функция для записи объекта в бинарный файл
    /*void write_to_binary_file(ofstream& bfile) {
        bfile.write(reinterpret_cast<char*>(&*this), sizeof(*this));
    }*/

    // Функция для чтения объекта из бинарного файла
    /*void read_from_binary_file(ifstream& bfile) {
        bfile.read(reinterpret_cast<char*>(&*this), sizeof(*this));
    }*/
    
    
    // Функция для записи объекта в бинарный файл
void write_to_binary_file(ofstream& bfile) {
    // Записываем размер строки имени студента
    size_t name_size = student.size();
    bfile.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));

    // Записываем строку имени студента
    bfile.write(student.data(), name_size);

    // Записать размер названий экзамена
    size_t list_size = list.size();
    bfile.write(reinterpret_cast<char*>(&list_size), sizeof(list_size));

    // Записать каждый экзамен из списка
    for (Test test : list) {
        // Записать размер строки названия экзаммена
        size_t test_name_size = test.name.size();
        bfile.write(reinterpret_cast<char*>(&test_name_size), sizeof(test_name_size));

        // Запсать название экзаммена
        bfile.write(test.name.data(), test_name_size);

        // Написать оценку за экзамен
        bfile.write(reinterpret_cast<char*>(&test.grade), sizeof(test.grade));
    }
}

// Функция для чтения объекта из бинарного файла
void read_from_binary_file(ifstream& bfile) {
    // Прочитайте размер строки имени студента
    size_t name_size;
    bfile.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

    // Считывание строки имени студента
    student.resize(name_size);
    bfile.read(student.data(), name_size);

    // Прочитайте размер списка экзаменов
    size_t list_size;
    bfile.read(reinterpret_cast<char*>(&list_size), sizeof(list_size));

    // Прочитать каждый тест в списке
    for (size_t i = 0; i < list_size; i++) {
        // Считывание размера строки названия экзамена
        size_t test_name_size;
        bfile.read(reinterpret_cast<char*>(&test_name_size), sizeof(test_name_size));

        // Считывание строки название экзамена
        string test_name(test_name_size, '\0');
        bfile.read(test_name.data(), test_name_size);

        // Прочитайте оценку экзамена
        double test_grade;
        bfile.read(reinterpret_cast<char*>(&test_grade), sizeof(test_grade));

        // Добавить экзамен в список
        list.push_back({test_name, test_grade});
    }
}
    
    
    
    
};

int main() {
    // Создаем пример страницы книги записей с данными тестов и экзаменов
    RecordBookPage Recbook;
    unsigned i;
    ifstream fin("Data.txt");
    fin >> i;
    for (unsigned j = 0; j < i; j++) {
        Recbook.add_subj(fin);
    }
    fin.close();

    // Вызываем функцию для ввода имени студента
    Recbook.enter_student_name();

    ofstream fout("out.txt");
    Recbook.print(fout);
    fout.close();

    // Вызываем функцию для изменения данных студента
    Recbook.change_student_data();

    ofstream bfile("bfile.bin", ios::binary);
    Recbook.write_to_binary_file(bfile);
    bfile.close();

    RecordBookPage Recbook2;
    ifstream bfile2("bfile.bin", ios::binary);
    Recbook2.read_from_binary_file(bfile2);
    bfile2.close();

    // Выводим данные, считанные из бинарного файла
    ofstream fout2("out2.txt");
    Recbook2.print(fout2);
    fout2.close();

    return 0;
}