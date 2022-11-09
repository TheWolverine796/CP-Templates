struct Edge{
    int index;
    int src, dest;
    long long val;
    int residualIndex;
};
struct Flow{
    int n;
    int src, dest;
    int iteration = 0;
    vector<Edge> edgesT;
    vector<vector<int>> edges;
    vector<int> visited;
    bool solved;
    long long flow;
    Flow(vector<pair<int, long long>>* edges1, int n1, int s, int d){
        n = n1, src = s, dest = d;
        solved = false;
        flow = 0, iteration = 1;
        visited.resize(n);
        fill(all(visited), 0);
        edges.resize(n);
        for(int i = 0; i < n; i++){
            for(auto j : edges1[i]){
                Edge e1 = {sz(edgesT), i, j.first, j.second, sz(edgesT) + 1};
                Edge e2 = {sz(edgesT) + 1, j.first, i, 0, sz(edgesT)};
                edgesT.pb(e1);
                edgesT.pb(e2);
                edges[i].pb(e1.index);
                edges[j.first].pb(e2.index);
            }
        }
    }
    long long bfs(int root){
        queue<int> qu;
        qu.push(root);
        visited[root] = iteration;
        vector<int> prev(n, -1);
        while(!qu.empty()){
            int node = qu.front();
            qu.pop();
            if(node == dest)
                break;
            for(auto i : edges[node]){
                Edge e1 = edgesT[i];
                if(visited[e1.dest] != iteration && e1.val > 0){
                    visited[e1.dest] = iteration;
                    prev[e1.dest] = e1.index;
                    qu.push(e1.dest); 
                }
            }
        }
        int currNode = dest;
        if(prev[currNode] == -1)
            return 0;
        long long finalValue = INF;
        while(prev[currNode] != -1){
            Edge e1 = edgesT[prev[currNode]];
            finalValue = min(finalValue, e1.val);
            currNode = e1.src;
        }
        currNode = dest;
        while(prev[currNode] != -1){
            Edge e1 = edgesT[prev[currNode]];
            e1.val -= finalValue;
            edgesT[e1.index] = e1;
            edgesT[e1.residualIndex].val += finalValue;
            currNode = e1.src;
        }
        return finalValue;
    }
    void EdmondsKarp(){
        while(true){
            long long f = bfs(src);
            if(f == 0)
                return;
            flow += f;
            iteration++;
        }
    }
    long long maxFlow(){
        if(!solved){
            solved = true;
            EdmondsKarp();
        }
        return flow;
    }
};