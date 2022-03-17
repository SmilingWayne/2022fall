#include <iostream>
#include <string>

using namespace std;

/**
 * 这里进行的是异常输入输出的检测
 * */
class ExceptionClass
{
    string name;

    friend ostream &operator<<(ostream &out, const ExceptionClass &a);

public:
    ExceptionClass(){};
    ExceptionClass(const string &a)
    {
        name = a;
    }
};
ostream &operator<<(ostream &out, const ExceptionClass &a)
{
    out << a.name << endl;
    return cout;
}

int main()
{
    try
    {
        int a = 0;
        cout << "Input a Number" << endl;
        cin >> a;
        if (a < 0)
        {
            throw ExceptionClass("Below Zero");
        }
        cout << "Win" << endl;
    }
    catch (ExceptionClass t)
    {

        cout << t;
    }
}