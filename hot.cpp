//Michał Guzek
//hot.cpp

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

///////////////////////////////////////////////////////////////////////
struct Edge
{
    int v, w;

    Edge(int v = -1, int w = -1) : v(v), w(w) { }
};
///////////////////////////////////////////////////////////////////////
class SparseGraph   //adjacency-list (vector of vectors), fixed number of vertices
{
    int Vcnt;

public:

    vector<vector<int> > adj; //no extra information about edges, except for their existence

    SparseGraph(int V)
                : Vcnt(V), adj(V)
    {
        adj.resize(V);
    }

    int V() const { return Vcnt; }

    void insert(Edge e) //allows multiple edges and self-loops
    {
        int v = e.v, w = e.w;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    friend class adjIterator;

    class adjIterator
    {
        const SparseGraph& G;
        int v;
        vector<int>::size_type it;

    public:
        adjIterator(const SparseGraph& G, int v) : G(G), v(v), it(0) { }

        int beg()
        {
            if(G.adj[v].empty()) return -1;
            return G.adj[v][it=0];
        }

        int nxt()
        {
            if(it != G.adj[v].size())
                return G.adj[v][++it];
            else
                return -1;
        }

        bool end()
        {
            return it == G.adj[v].size();
        }
    };
};
///////////////////////////////////////////////////////////////////////
unsigned long long BinCoeff(unsigned int n, unsigned int k)
{
    double result = 1;

    for(unsigned int i = 1; i <= k; ++i)
    {
        result = (result * ((n - i + 1))) / i;
    }

    return static_cast<unsigned long long>(result);
}
///////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    scanf("%d", &n);

    SparseGraph my_graph(n);

    for(int i = 0 ; i < n-1 ; ++i)
    {
        Edge ed;
        scanf("%d%d", &ed.v, &ed.w);

        --ed.v;
        --ed.w;

        my_graph.insert(ed);
    }

    unsigned long long combinations = 0;

    bool* already_processed = new bool[n];

    for(int i = 0 ; i < n ; ++i)
    {
        int adjacent_to_i = my_graph.adj[i].size();

        if(adjacent_to_i < 3)
            continue;

        combinations += BinCoeff(adjacent_to_i, 3);

        memset(already_processed, 0, sizeof(bool)*n);

        already_processed[i] = true;

        vector<queue<int>> queues(adjacent_to_i);
        for(int neighb = 0 ; neighb < adjacent_to_i ; ++neighb)
        {
            queues[neighb].push(my_graph.adj[i][neighb]);
            already_processed[my_graph.adj[i][neighb]] = true;
        }

        while(true)
        {
            vector<unsigned long long> numbers;

            for(int neighb = 0 ; neighb < adjacent_to_i ; ++neighb)
            {
                if(!queues[neighb].empty())
                {
                    unsigned long long sum = 0;

                    for(int cnt = queues[neighb].size() ; cnt > 0 ; --cnt)
                    {
                        int curr = queues[neighb].front();
                        queues[neighb].pop();

                        sum += (my_graph.adj[curr].size()-1);

                        typename SparseGraph::adjIterator A(my_graph, curr);
                        for(int t = A.beg() ; !A.end() ; t = A.nxt())
                        {
                            if(already_processed[t] == 0)
                            {
                                queues[neighb].push(t);
                                already_processed[t] = true;
                            }
                        }
                    }

                    if(sum > 0)
                        numbers.push_back(sum);
                }
            }

            if(numbers.size() >= 3)
            {
                unsigned long long sum = 0;

                for(int it = 0 ; it < numbers.size() ; ++it)
                    sum += numbers[it];

                unsigned long long initial_com = BinCoeff(sum, 3);

                for(int it = 0 ; it < numbers.size() ; ++it)
                {
                    if(numbers[it] >= 3)
                        initial_com -= BinCoeff(numbers[it], 3);
                    if(numbers[it] >= 2)
                        initial_com -= (BinCoeff(numbers[it], 2) * (sum-numbers[it]));
                }

                combinations += initial_com;
            }
            else
            {
                break;
            }
        }
    }

    printf("%llu", combinations);

    delete [] already_processed;

    return 0;
}
