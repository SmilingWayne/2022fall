#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
 
using namespace std;
 
const int maxn = 1e6 + 5;
 
struct Node
{
    int cnt;
    Node *fail;
    Node *child[26];
    Node()
    {
        cnt = 0;
        fail = NULL;
        for(int i = 0;i < 26;i++)
            child[i] = NULL;
    }
};
 
char s[maxn];
Node *root;
 
void makeTrie(char *kw)
{
    Node *p = root;
    for(int i = 0;kw[i] != '\0';i++)
    {
        int ix = kw[i] - 'a';
        if(p->child[ix] == NULL)
            p->child[ix] = new Node();
        p = p->child[ix];
    }
    p->cnt++;
}
 
void makefail()
{
    queue<Node *> q;
    q.push(root);
    while(!q.empty())
    {
        Node *p = q.front();
        q.pop();
        for(int i = 0;i < 26;i++)
        {
            Node *f = p->fail;
            if(p->child[i])
            {
                //找p->child[i] 的失配指针
                while(f)
                {
                    if(f->child[i])
                    {
                        p->child[i]->fail = f->child[i];
                        break;
                    }
                    else
                        f = f->fail;
                }
                if(f == NULL)
                    p->child[i]->fail = root;
                //
                q.push(p->child[i]);
            }
        }
    }
}
 
int acauto()
{
    int ans = 0;
    Node *p = root;
    for(int i = 0;s[i] != '\0';i++)
    {
        int ix = s[i] - 'a';
        //开始匹配当前字符
        while(p)
        {
            if(p->child[ix])
            {
                p = p->child[ix];
                break;
            }
            else
                p = p->fail;
        }
        //如果没有匹配的
        if(p == NULL)
        {
            p = root;
            continue;
        }
        //成功匹配一个字符
        Node *t = p;
        while(t != root)
        {
            if(t->cnt)
            {
                ans += t->cnt;
                t->cnt = 0;
            }
            t = t->fail;
        }
    }
    return ans;
}

void _free(Node *p)
{
    for(int i = 0;i < 26;i++)
        if(p->child[i])
            _free(p->child[i]);
    free(p);
}
 
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int N;
        scanf("%d",&N);
        root = new Node();
        for(int i = 0;i < N;i++)
        {
            char keyword[55];
            scanf("%s",keyword);
            makeTrie(keyword);
        }
        makefail();
        scanf("%s",s);
        printf("%d\n",acauto());
        _free(root);
    }
    return 0;
}
