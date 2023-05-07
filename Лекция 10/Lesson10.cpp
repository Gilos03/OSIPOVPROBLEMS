#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Определяем класс для представления для экзамена
class Subject {
public:
    string exam;
};

// Определяем класс для представления страницы зачетной книжки студента
class RecordBookPage {
private:
    string student;
    vector<Subject> list;
public:
    RecordBookPage(){ }
    
    RecordBookPage(string student){
        this->student = student;
    }
    
    static string study_plan[3];

    void set (string student){
        this->student = student;
    }
    
    string get (){
    return student;
    }
    
    ~RecordBookPage(){list.clear();}
    
    const string & get_name() const{
        return student;
    }
    
    void add_subject(Subject& x){
        list.push_back(x);
    }
    
    void read(ifstream & f){
        getline(f,student);
        for(int i = 0; i < 3; ++i){
            Subject x;
            string s;
            getline(f, s);
            x.exam = s;
            add_subject(x);
        }
    }
    
    void write(ostream & f){
        f << student << '\n';
        size_t i = 0;
        for(auto & subject: list){
            f << study_plan[i] << " " << subject.exam << '\n';
            ++i;
        }
        f << endl;
    }
};

ostream & operator << (ostream & os, RecordBookPage & zach){
    return os << zach.get();
}

istream & operator >> (istream & is, RecordBookPage & zach){
    string student;
    is >> student;
    zach.set(student);
    return is;
}

class Group {
private:
    ifstream & hh;
    ofstream & vv;
    string group_number;
    vector <RecordBookPage> students;
public:
    Group(ifstream & h, ofstream & v):hh(h), vv(v){read_st();}
    
    void read_st(){
        getline(hh, group_number);
        int n;
        if (hh >> n){
            string exxit;
            getline(hh, exxit);
            students.resize(n);
            for(auto & student: students)
                student.read(hh);
        }
    }
    
    void write_st(){
        vv << group_number << endl;
        for (auto & student: students)
            student.write(vv);
    }
    
    void st_find(){
        string Name;
        getline(hh,Name);
        for(int i = 0; i<size(students); ++i){
            if (students[i].get_name() == Name){
                cout << i << endl;
                students[i].write(cout);
            }
        }
    }
    void del_student(ifstream & del){
        string del_name;
        getline(del, del_name);
        for(size_t i =0; i < size(students); ++i){
            if(students[i].get_name() == del_name)
                students.erase(students.begin() + i);
        }
    }
    Group & operator- (ifstream & del){
        del_student(del);
        return *this;
    }
    void add_student(RecordBookPage & r){
        r.read(hh);
        r.write(cout);
        students.push_back(r);
    }
        Group & operator+ (RecordBookPage& r){
        add_student(r);
        return *this;
    }
    ~Group(){students.clear();hh.close();vv.close();}
};

string RecordBookPage::study_plan[] = {"Основы программирования","Алгебра","Математический анализ"};

int main() {
    ifstream t("students.txt");
    ifstream del("del.txt");
    Group y (t,(ofstream &) cout);
    y.st_find();
    y-del;
    y.write_st();
    RecordBookPage r;
    y+r;
    return 0;
}