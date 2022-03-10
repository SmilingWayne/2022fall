#include <iostream>

#include <cstring>
#include <string>
using namespace std;
class memory
{
    string m;
    int num;

public:
    static void *operator new(size_t size);
    static void operator delete(void *p);

    // 利用操作符重载实现内存的高效分配
private:
    memory *next;
    static memory *p_free;
};
const int NUM = 32; // 设置常量
memory *memory::p_free = NULL;
void *memory::operator new(size_t size)
{
    memory *p;
    if (p_free == NULL)
    {
        p_free = (memory *)malloc(size * NUM);
        for (p = p_free; p != p_free + NUM - 1; p++)
        {
            p->next = p + 1;
        }
        p->next = NULL;
    }
    p = p_free;
    p_free = p_free->next;
    memset(p, 0, size);
    return p;
}

void memory::operator delete(void *p)
{
    ((memory *)p)->next = p_free;
    p_free = (memory *)p;
}
int main()
{
}