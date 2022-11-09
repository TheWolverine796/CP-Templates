void BellmanFord(int n, int src, vector<pair<int, long long>> *edges,
                 vector<long long> &dist, set<int> &negCycle) {
  fill(all(dist), INF);
  dist[src] = 0;
  vector<pair<long long, pair<int, int>>> e;
  for (int i = 0; i < n; i++) {
    for (auto j : edges[i]) {
      e.pb({j.second, {i, j.first}});
    }
  }
  for (int i = 0; i < n - 1; i++) {
    for (auto j : e) {
      dist[j.second.second] =
          min(dist[j.second.second], dist[j.second.first] + j.first);
    }
  }
  // checking negative cycle
  for (int i = 0; i < n; i++) {
    for (auto j : e) {
      if (dist[j.second.second] > dist[j.second.first] + j.first) {
        dist[j.second.second] = dist[j.second.first] + j.first;
        negCycle.insert(j.second.second);
      }
    }
  }
}