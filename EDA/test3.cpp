#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>
#include <string>
#include <cstring>
using namespace std;

struct record
{
    double num;
    double file;
    record(double n, double f) : num(n), file(f) {}
};
bool operator==(const struct record &X, const struct record &Y)
{
    // return hash<string>()(X.num+X.file)==hash<string>()(Y.num+Y.file);
    return (Y.num == X.num) && (Y.file == X.file);
}

struct record_hash
{
    size_t operator()(const struct record &_r) const
    {
        string tmp = to_string(_r.file) + to_string(_r.num);
        return std::hash<string>()(tmp);
    }
};
int main()
{
    unordered_set<record, record_hash> records;
    records.emplace(record(81, 44));
    record r(81, 44);
    auto it = records.find(r);
    cout << it->num << " " << it->file << endl;
    return 0;
}