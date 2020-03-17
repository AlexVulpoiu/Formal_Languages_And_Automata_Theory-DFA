#include <fstream>
#include <cstring>

using namespace std;

class DFA
{
public:
    int n, m, q0, k, l, stari_finale[1000], tranzitie[1000][256];
    char alfabet[1000];

public:
    DFA();

    bool evaluate(char word[]);
};

DFA::DFA()
{
    ifstream f("automat.in");

    int i, x, y;
    char c;

    f >> n;
    f >> m;
    for(i = 0; i < m; i++)
        f >> alfabet[i];
    f >> q0;
    f >> k;
    for(i = 0; i < k; i++)
        f >> stari_finale[i];
    for(x = 0; x < 1000; x++)
        for(y = 0; y < 256; y++)
            tranzitie[x][y] = -1;
    f >> l;
    for(i = 0; i < l; i++)
    {
        f >> x >> c >> y;
        tranzitie[x][int(c)] = y;
    }

    f.close();
}

bool DFA::evaluate(char word[])
{
    int i, lg, nod;

    nod = q0;
    lg = strlen(word);

    for(i = 0; i < lg; i++)
    {
        nod = tranzitie[nod][int(word[i])];
        if(nod == -1)
            return false;
    }
    for(i = 0; i < k; i++)
        if(stari_finale[i] == nod)
            return true;
    return false;
}

int main()
{
    ifstream g("cuvinte.in");
    ofstream h("evaluare.out");

    DFA aut;
    int i, N, nrcuv;
    char cuv[10000];

    g >> nrcuv;
    g.get();
    g.get();
    for(i = 0; i < nrcuv; i++)
    {
        g.getline(cuv, 10000);
        N = strlen(cuv);
        cuv[N - 1] = '\0';  ///cuvantul are la final caracterele '\n' si '\0', iar instructiunea inlocuieste '\n' cu '\0'
        if(aut.evaluate(cuv))
            h << "Cuvantul '" << cuv << "' este acceptat de automat\n";
        else
            h << "Cuvantul '" << cuv << "' nu este acceptat de automat\n";
    }

    g.close();
    h.close();

    return 0;
}
