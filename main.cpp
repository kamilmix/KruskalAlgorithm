#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

typedef  pair<int, int> iPair;


struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;

    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int waga)
    {
        edges.push_back({waga, {u, v}});
    }

    int kruskalMST();
};

struct ZbioryRozlaczne
{
    int *ojciec, *h;

    ZbioryRozlaczne(int n)
    {
        ojciec = new int[n+1];
        h = new int[n+1];

        // Poczatkowo wszystkie wierzcholki sa rozlacznymi zbiorami i maja wysokosc h = 0
        for (int i = 0; i <= n; i++)
        {
            h[i] = 0;

            ojciec[i] = i;  //kazdy element jest wlasnym ojcem
        }
    }


    // Kompresja drogi
    int findSet(int x)
    {
        if (x != ojciec[x])
            ojciec[x] = findSet(ojciec[x]);
        return ojciec[x];
    }

    void merge(int x, int y)
    {
        x = findSet(x), y = findSet(y);

        if (h[x] > h[y])
        {
            ojciec[y] = x;
        }
        else
        {
           ojciec[x] = y;
        }

        if (h[x] == h[y])
        {
            h[y]++;
        }

    }
};


int Graph::kruskalMST()
{
    int mst_waga = 0;

    sort(edges.begin(), edges.end());

    // Tworzymy zbiory rozlaczne
    ZbioryRozlaczne zbiory(V);

    // Iterujemy przez wszytskie posortowane krawêdzie
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int zbior_u = zbiory.findSet(u);
        int zbior_v = zbiory.findSet(v);

        //Sprawdzamy czy wybrana krawedz tworzy cykl
        if (zbior_u != zbior_v)
        {
            cout << u << " - " << v << endl;

            mst_waga += it->first;

            zbiory.merge(zbior_u, zbior_v);
        }
    }

    return mst_waga;
}

int main()
{
    int V = 9, E = 14;
    Graph g(V, E);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    cout << "Krawedzie nalezace do MST";
    int mst_waga = g.kruskalMST();

    cout << "\nWaga MST = " << mst_waga;
    return 0;
}
