#include <bits/stdc++.h>

using namespace std;

ifstream in("fisier.in");
ofstream out("fisier.out");

Minimum(vector <int>& v, int i)
{
    int minim = i * 2;

    if (i * 2 + 1 < v.size() && v[minim] > v[i * 2 + 1])
        minim = i * 2 + 1;

    for(int j = 0; j <= 10; j++)
    {
        if (i * 4 + j < v.size() && v[minim] > v[i * 4 + j])
            minim = i * 4 + j;
    }

    return minim;
}

Maximum(vector <int>& v, int i)
{
    int maxim = i * 2;

    if (i * 2 + 1 < v.size() && v[maxim] < v[i * 2 + 1])
        maxim = i * 2 + 1;

    for(int j = 0; j <= 10; j++)
    {
        if (i * 4 + j < v.size() && v[maxim] < v[i * 4 + j])
            maxim = i * 4 + j;
    }

    return maxim;
}

int Level(int i)
    int j = 0;
    while(i)
    {
        i /= 2;
        j++;
    }

    j = (j+1) % 2;

    return j;
}

void PushDownMin(vector <int>& v, int m)
{
    while (m * 2 < v.size())
    {
        int i = m;
        m = Minimum(v, i);
        if(v[m] < v[i])
        {
            if(m / 4 == i)
            {
                swap(v[m], v[i]);
                if(v[m] > v[m / 2])
                {
                    swap(v[m], v[i]);
                }
            }
            else
            {
                swap(v[m], v[i]);
            }
        }
        else
        {
            break;
        }

    }
}

void PushDownMax(vector <int>& v, int m)
{
    while (m * 2 < v.size())
    {
        int i = m;
        m = Maximum(v, i);
        if(v[m] > v[i])
        {
            if(m / 4 == i)
            {
                swap(v[m], v[i]);
                if(v[m] < v[m / 2])
                {
                    swap(v[m], v[i]);
                }
            }
            else
            {
                swap(v[m], v[i]);
            }
        }
        else
        {
            break;
        }

    }
}

void PushDown(vector <int>& v, int i)
{
    if(Level(i) == 0)
    {
        PushDownMin(v, i);
    }
    else
    {
        PushDownMax(v, i);
    }
}

void Build(vector <int>& v)
{
    for(int i  = (v.size() - 1) / 2; i >= 1; i--)
    {
        PushDown(v, i);
    }
}

void PushUpMin(vector <int>& v, int i)
{
    while(i/4 != 0 && v[i] < v[i/4])
    {
        swap(v[i], v[i/4]);
        i /= 4;
    }
}

void PushUpMax(vector <int>& v, int i)
{
    while(i/4 != 0 && v[i] > v[i/4])
    {
        swap(v[i], v[i/4]);
        i /= 4;
    }
}
void PushUp(vector <int>& v, int i)
{
    if(i != 1)
    {
        if(Level(i) == 0)
        {
            if(v[i] > v[i/2])
            {
                swap(v[i], v[i/2]);
                PushUpMax(v, v[i/2]);
            }
            else
            {
                PushUpMin(v, i);
            }
        }
        else
        {
            if(v[i] < v[i/2])
            {
                swap(v[i], v[i/2]);
                PushUpMin(v, v[i/2]);
            }
            else
            {
                PushUpMax(v, i);
            }
        }
    }
}

void OutMin(vector <int>& v)
{
    out << "Minimul este: " << v[1] << '\n';
}

void OutMax(vector <int>& v)
{
    out << "Maximul este: " << max(v[2], v[3]) << '\n';
}

void DeleteMin(vector <int>& v)
{
    v[1] = v[v.size() - 1];
    v.erase(v.end() - 1);
    PushDownMin(v, 1);
}

void DeleteMax(vector <int>& v)
{
    if(v[2] < v[3])
    {
        v[3] = v[v.size() - 1];
        v.erase(v.end() - 1);
        PushDownMax(v, 3);
    }
    else
    {
        v[2] = v[v.size() - 1];
        v.erase(v.end() - 1);
        PushDownMax(v, 2);
    }
}
void menu()
{
    vector <int> v;

    int totOperatii;
    in>>totOperatii;

    for(int i = 0; i < totOperatii; i++)
    {
        int op;
        in >> op;

        switch (op)
        {

        case 1:         ///build
        {
            int n;
            in >> n;

            v.assign(n+1, 0);

            for(int i = 1; i <= n; i++)
            {
                in >> v[i];
            }

            Build(v);
            break;
        }
        case 2:         ///inserez
        {
            int x;
            in >> x;
            v.push_back(x);
            PushUp(v, v.size()-1);
            break;
        }
        case 3:         ///sterg minimul
        {
            DeleteMin(v);
            break;
        }
        case 4:         ///sterg maximul
        {
            DeleteMax(v);
            break;
        }
        case 5:         ///afisez minimul
        {
            OutMin(v);
            break;
        }
        case 6:         ///afisez maximul
        {
            OutMax(v);
            break;
        }
        }
    }


}
int main()
{
    menu();
    return 0;
}
