#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Node {
  public:
    Node() { return; }
    Node(unsigned int);
    unsigned int get_parent() { return parent; }
    unsigned int get_rank() { return rank; }
    unsigned int get_size() { return size; }
    unsigned int get_index() { return index; }
    void set_parent(unsigned int p) { parent = p; }
    void set_rank(unsigned int r) { rank = r; }
    void set_size(unsigned int s) { size = s; }
    void set_index(unsigned int i) { index = i; }
  private:
    unsigned int parent;
    unsigned int rank;
    unsigned int size;
    unsigned int index;
};

Node::Node(unsigned int index) {
  parent = index;
  rank = 0;
  size = 1;
  index = index;
}

void make_set(unsigned int n, vector<Node*> &f) {
  for(unsigned int i = 0; i < n; ++i) {
    f.push_back(new Node(i));
  }
}

unsigned int find(unsigned int x, vector<Node*> &f) {
  if(f[x]->get_parent() != x) {
    f[x]->set_parent(find(f[x]->get_parent(), f));
  }
  return f[x]->get_parent();
}

void union_by_rank(unsigned int x, unsigned int y, vector<Node*> &f) {
  unsigned int x_root = find(x, f);
  unsigned int y_root = find(y, f);
  if(x_root == y_root) {
    return;
  }
  if(f[x_root]->get_rank() < f[y_root]->get_rank()) {
    //swap x_root and y_root
    unsigned int tmp;
    tmp = x_root;
    x_root = y_root;
    y_root = tmp;
  }
  f[y_root]->set_parent(x_root);
  f[x_root]->set_size(f[x_root]->get_size() + f[y_root]->get_size());
  if(f[x_root]->get_rank() == f[y_root]->get_rank()) {
    f[x_root]->set_rank(f[x_root]->get_rank() + 1);
  }
}

int main() {
  unsigned int num_nodes;
  unsigned int num_edges;
  
  cin >> num_nodes >> num_edges;

  vector<Node*> forest;

  make_set(num_nodes, forest);

  vector< tuple<unsigned int, unsigned int, unsigned int> > edges;

  unsigned int u, v, w;

  for(unsigned int i = 0; i < num_edges; ++i) {
    cin >> u >> v >> w;
    edges.push_back(make_tuple(u - 1, v - 1, w));
  }

  sort(begin(edges), end(edges), [](const tuple<unsigned int, unsigned int,
    unsigned int>  a, const tuple<unsigned int, unsigned int, unsigned int> b)
    { return get<2>(a) < get<2>(b); });

  vector< tuple<unsigned int, unsigned int, unsigned int> > A;

  for(tuple<unsigned int, unsigned int, unsigned int> n: edges) {
    if(find(get<0>(n), forest) != find(get<1>(n), forest)) {
      A.push_back(n);
      union_by_rank(get<0>(n), get<1>(n), forest);
    }
  }
  
  unsigned int sum = 0;
  for_each(A.begin(), A.end(), [&sum](const tuple<unsigned int, unsigned int,
    unsigned int> a) { sum += get<2>(a); });
  cout << sum << '\n';
  
  return 0;

}

