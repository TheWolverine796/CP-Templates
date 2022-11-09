// O(VlogV + ElogV)
// Single Source Shortest Path

void Dijkstra(int s, int n, vector<long long> &dist, vector<int> &parent,
              vector<pair<int, long long>> *adj) {
  dist.assign(n, INF);
  parent.assign(n, -1);
  dist[s] = 0;
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                 greater<pair<long long, long long>>>
      q;
  q.push({0, s});
  while (!q.empty()) {
    pair<long long, int> here = q.top();
    q.pop();
    int v = here.second;
    long long d_v = here.first;
    if (d_v != dist[v])
      continue;
    for (auto edge : adj[v]) {
      if (dist[v] + edge.second < dist[edge.first]) {
        dist[edge.first] = dist[v] + edge.second;
        parent[edge.first] = v;
        q.push({dist[edge.first], edge.first});
      }
    }
  }
}