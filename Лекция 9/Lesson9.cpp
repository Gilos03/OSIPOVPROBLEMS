#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T>
class Subject
{
public:
    string name;
    virtual void mark(T mark) = 0;
    virtual void print () = 0;
    virtual ~Subject (){}
};
template <typename T>
class Zachet : public Subject<T>
{
public:
    bool result;
    void mark (T mark)
    {
        result = mark < 40 ? false:true;
    }
    void print ()
    {
        cout << this->name << ' ' << (result ? "Score":"No score") << endl;
    }
};
template <typename T>
class Exam : public Subject<T>
{
public:
    int result;
    void mark (T mark)
    {
        result = mark;
    }
    void print ()
    {
        cout << this->name << ' ';
        switch (result)
        {
            case 5:
                cout << "Great";
                break;
            case 4:
                cout << "Good";
                break;
            case 3:
                cout << "Satisfactory";
                break;
            default: cout << "Unsatisfactory";
        }
        cout << endl;
    }
};
int main ()
{
    Subject<int>* p;
    vector <Subject<int>*> list;
    p = new Zachet<int>;
    p->name = "Foreign language";
    p->mark(39);
    list.push_back(p);
    p = new Zachet<int>;
    p->name = "The practice of effective communications";
    p->mark(100);
    list.push_back(p);
    p = new Exam<int>;
    p->name = "Fundamentals of Programming";
    p->mark(5);
    list.push_back(p);
    p = new Exam<int>;
    p->name = "Algebra";
    p->mark(5);
    list.push_back(p);
    p = new Zachet<int>;
    p->name = "Fitness";
    p->mark(94);
    list.push_back(p);
    p = new Exam<int>;
    p->name = "Mathematical Analysis";
    p->mark(5);
    list.push_back(p);
    for (auto x: list)
        x->print();
    return 0;
}