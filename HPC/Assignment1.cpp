#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

class Graph{
    public:
    int n;
    vector<vector<int>>adjList;
    bool directed;

    Graph(int n, bool directed = false){
        this->n = n;
        this->directed = directed;
        this->adjList.resize(n);
    }

    void insertEdge(int v1, int v2){
        adjList[v1].push_back(v2);
        if(!this->directed)adjList[v2].push_back(v1);
    }

    vector<int> bfs_linear(int start = 0){
        vector<bool>visited(this->n, 0);
        vector<int>res;
        queue<int>q;
        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            int top = q.front(); q.pop();
            res.push_back(top);

            for (auto &&nbr : this->adjList[top]){
                if(!visited[nbr]){
                    visited[nbr] = true;
                    q.push(nbr);
                }
            } 
        }
        return res;
    }

    vector<int> bfs_parallel(int start=0){
        vector<bool>visited(this->n, 0);
        vector<int>res, prev_lvl;
        prev_lvl.push_back(start);
        visited[start] = true;
        int num_nodes_visited = 0;

        while(num_nodes_visited < this->n){
            vector<int>current_lvl;
            
            #pragma omp parallel for shared(adjList, visited, res, prev_lvl, current_lvl, num_nodes_visited) default(none)
            for (int top_idx=0; top_idx<prev_lvl.size(); top_idx++){
                int top = prev_lvl[top_idx];
                #pragma omp atomic
                num_nodes_visited++;
                //do job on node at this level
                res.push_back(top);

                for(auto nbr: this->adjList[top])
                    if(!visited[nbr]){
                        #pragma omp critical
                        {
                        visited[nbr] = true;
                        current_lvl.push_back(nbr);
                        }
                    }
            }

            prev_lvl = current_lvl;
            res.push_back(-1);
        }

        return res;
    }

    void display(){
        for(int i=0; i<n; i++){
            cout<<i<<" : [";
            for (auto &&j : this->adjList[i]){
                cout<<j<<", ";
            }
            cout<<"] \n";
        }
        cout<<"==============================\n";
    }
};

int main(){
    Graph g(6, false);
    g.insertEdge(0, 1);
    g.insertEdge(0, 2);
    g.insertEdge(1, 3);
    g.insertEdge(1, 4);
    g.insertEdge(2, 3);
    g.insertEdge(3, 5);
    g.insertEdge(5, 4);
    // g.insertEdge(4, 0);
    g.display();

//------------ sequential ----------------------
    double t1 = omp_get_wtime();
    vector<int>dfs = g.bfs_linear();
    double t2 = omp_get_wtime();
    for (auto &&i : dfs)cout<<i<<", ";
    printf("\n EXECUTED in %f seconds \n", t2-t1);
    printf("==================================\n");

//------------ parallel  -------------------------
    double t3 = omp_get_wtime();
    dfs = g.bfs_parallel();
    double t4 = omp_get_wtime();
    for (auto &&i : dfs)cout<<i<<", ";
    printf("\n EXECUTED in %f seconds \n", t4-t3);
    printf("==================================\n");
}