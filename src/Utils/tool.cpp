#include "Segment_Tree.cpp"
using namespace std;
using namespace my_lib;
#include <bits/stdc++.h>


class Min_Tree {
  public:
    Min_Tree(int _n) {
      Segment_Tree tree(_n, INT_MAX, [&](const Node &l, const Node &r){
            return Node(min(l.value, r.value));
        });
    }
};

class Max_Tree {
public:
    Max_Tree(int _n) {
        Segment_Tree tree(_n, INT_MIN, [&](const Node &l, const Node &r){
              return Node(max(l.value, r.value));
          });
    }
};