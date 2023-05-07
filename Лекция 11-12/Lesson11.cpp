#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Temp{
public:
    virtual ~Temp() {}
};
template <typename T>

class Subject: public Temp{
public:
    T mark;
};

// Определяем класс для представления страницы зачетной книжки студента
class RecordBookPage {
private:
    string student;
    vector<Temp*> list;
public:
    RecordBookPage(){ }
    
    RecordBookPage(string student){
        this->student = student;
    }
    
    static string study_plan[6];

    ~RecordBookPage(){list.clear();}
    
    const string & get_name() const{
        return student;
    }
    
    void add_exam(Temp* x){
        list.push_back(x);
    }
    
    void read(ifstream & f){
        getline(f,student);
        for(int i = 0; i < 6; ++i){
            Temp* x;
            string s;
            getline(f, s);
            int b;
            stringstream ss(s);
            if(ss >> b){
                if(b > 1){
                    x = new Subject<int>;
                    dynamic_cast<Subject<int>*>(x)->mark = b;
            }
                else{
                    x = new Subject<bool>;
                    dynamic_cast<Subject<bool>*>(x)->mark = b;
            }
            add_exam(x);
        }
    }
}
    
    void write(ostream & f){
        f << student << '\n';
        size_t i = 0;
        for(i = 0; i < 3; ++i){
            int c = dynamic_cast<Subject<int>*>(list[i])->mark;
            if (c==5) f << study_plan[i] << " " << "Отлично" << '\n';
            if (c==4) f << study_plan[i] << " " << "Хорошо" << '\n';
            if (c==3) f << study_plan[i] << " " << "Удовлетворительно" << '\n';
            
        }
        for (i = 3; i < 6; ++i){
            bool a = dynamic_cast<Subject<bool>*>(list[i])->mark;
            if (a==1) f << study_plan[i] << " " << "Зачет" << '\n';
            else f << study_plan[i] << " " << "Незачет" << '\n';
        }
        f << endl;
    }
};

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

string RecordBookPage::study_plan[] = {"Основы программирования 12.01.22","Алгебра и геометрия 20.01.22","Математический анализ 10.01.22", "Физическая культура 25.12.22", "Практика эффективной коммуникации 30.12.22", "Английский язык 24.12.22"};

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