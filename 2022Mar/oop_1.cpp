#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
using namespace std;

// friend 这一块太傻逼了
/** const的具体使用
 * @param a
 * */
vector<int> combine(const vector<int> &a, const vector<int> &b)
{
    vector<int> ans(min(a.size(), b.size()), 0);
    for (int i = 0; i < min(a.size(), b.size()); i++)
    {
        ans[i] = a[i] + b[i];
    }
    return ans;
}

struct flight
{
    string flight_Number;
    string des;
    string ori;
    int dep_time;
    int arr_time;
    int passengers_Number;
};

void display(struct flight flights)
{
    cout << "Flight Number: " << flights.flight_Number << endl;
    cout << "Destination: " << flights.des << endl;

    cout << "Orientation: " << flights.ori << endl;
    cout << "Departure Time: " << flights.dep_time << endl;

    cout << "Arrival Time: " << flights.arr_time << endl;

    cout << "Passenger_Number: " << flights.passengers_Number << "\n"
         << endl;
}

class Flight_3;
class Flight_2
{
private:
    string number;
    string flight_1;
    string flight_2;
    string flight_3;
    string seat;
    int price;

public:
    Flight_2(string a, string b, string c, string d, string e, int h)
    {
        number = a;
        flight_1 = b;
        flight_2 = c;
        flight_3 = d;
        seat = e;
        price = h;
    }
};
void dis()
{
    cout << "Haha " << endl;
}
class Flight_3
{
    friend void dis();

private:
    string number;
    string flight_1;
    string flight_2;
    string flight_3;
    string seat;
    double passengers;
    double income;
    int price;

public:
    // friend class Flight_2;

    // friend void display(Flight_2 &c);

    Flight_3(string a, string b, string c, string d, string e, double f, double g, int h)
    {
        number = a;
        flight_1 = b;
        flight_2 = c;
        flight_3 = d;
        seat = e;
        passengers = f;
        income = g;
        price = h;
    }
    void dis()
    {
        cout << "OK?" << endl;
    }
};

class Flight
{
    friend void sayHello();

private:
    string number;
    int deptime;
    int depoff;
    int arrtime;
    int arroff;
    string origin;
    string destination;
    static int cnt;

public:
    Flight(string a, int b, int c, int d, int d2, string e, string f)
    {
        number = a;
        deptime = b;
        depoff = c;
        arrtime = d;
        arroff = d2;
        origin = e;
        destination = f;
    }
};

void sayHello()
{
    cout << "Hello!" << endl;
}

void run()
{

    const int length = 100;
    flight flights[length];
    for (int i = 0; i < length; i++)
    {
        flights[i].flight_Number = "Flight_" + to_string(i);
        flights[i].des = "Destination_" + to_string(i);
        flights[i].ori = "Orientation_" + to_string(i);

        flights[i].dep_time = abs(rand()) % 24;
        flights[i].arr_time = abs(rand()) % 24;
        flights[i].passengers_Number = abs(rand()) % 500;
        // flights[i]. = "destination" + to_string(i);
    }
    for (int i = 0; i < length; i++)
    {
        display(flights[i]);
    }
    string t1 = "hello world!";
    printf("%s\n", t1.c_str());

    vector<int> a(20, 0);
    for (int i = 0; i < 20; i++)
    {
        a[i] = rand() % 100;
    }
    vector<int> b(30, 0);
    for (int i = 0; i < 30; i++)
    {
        b[i] = rand() % 200;
    }
    vector<int> ans = combine(a, b);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " || ";
    }
    Flight *A = new Flight("AA0001", 755, -400, 1355, -400, "EDB", "TFB");
    cout << "\n"
         << endl;

    Flight_2 *C = new Flight_2("AA0001", "AA0040BERBOD", ".", ".", "B", 20);
    Flight_3 *B = new Flight_3("AA0001", "AA0040BERBOD", ".", ".", "B", 14.56, 230, 10);
    B->dis();
}
// 静态
// 常量

class Wheel
{

    double d;
    double thickness;
    string wheel_name;

public:
    Wheel()
    {
        d = 0;
        thickness = 0;
        wheel_name = "";
    }
    Wheel(const Wheel &a)
    {
        d = a.d;
        thickness = a.thickness;
        wheel_name = a.wheel_name;
    }
    Wheel(double a, double b, string c)
    {
        d = a;
        thickness = b;
        wheel_name = c;
    }
    void display()
    {
        cout << d << " " << thickness << " " << wheel_name;
    }
};

class Vehicle
{
    friend class Wheel;
    class Wheel wheel;
    string name;
    int num;

public:
    Vehicle(string name_, int num_, double a, double b, string c) : wheel(a, b, c)
    {
        name = name_;
        num = num_;
    }
    // Vehicle(string name_, int num_, const Wheel &w)
    // {
    //     name = name_;
    //     num = num_;
    //     wheel = w;
    // }

    void output()
    {
        cout << name + " |" << num << " |"
             << "|\n";
    }
};
int main()
{

    Wheel *w = new Wheel(12.3, 12.4, "Wheel_1");
    // Wheel *c = w;
    // c->display();
    Vehicle *a = new Vehicle("Vehicle_1", 100, 12.3, 12.4, "W_1");
    // Vehicle *b = new Vehicle("Vehicle_2", 200, new Wheel(12.3, 12.4, "Wheel_1"));
    // a.wheel = w;
    // a->output();
    // run();
}