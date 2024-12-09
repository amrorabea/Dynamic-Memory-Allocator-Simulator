#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include <bits/stdc++.h>

namespace my_lib {
    class Node {
    public:
        int value, min, max;

        Node() : value(0), min{INT_MAX}, max{INT_MIN} {
        }

        explicit Node(int _value) : value(_value), min(_value), max(_value) {
        }
    };

    template<typename VAL_TYPE = int>
    class Segment_Tree {
    private:
#define L (2*node+1)
#define R (2*node+2)
#define mid ((l+r)/2)
        VAL_TYPE NEUTRAL_VALUE = 0;
        int seg_size;
        std::vector<Node> seg;

        Node merge(const Node &a, const Node &b) {
            Node ret;
            ret.max = std::max(a.max, b.max);
            ret.min = std::min(a.min, b.min);
            return ret;
        }

        Node query(const int lq, const int rq, int node, int l, int r) {
            if (lq > r || rq < l) return {};
            if (lq <= l && r <= rq) return seg[node];
            return merge(query(lq, rq, L, l, mid),
                         query(lq, rq, R, mid + 1, r));
        }

        void update(const int idx, const VAL_TYPE value, int node, int l, int r) {
            if (l == r) {
                seg[node] = Node(value);
                return;
            }
            if (idx <= mid) update(idx, value, L, l, mid);
            else update(idx, value, R, mid + 1, r);

            seg[node] = merge(seg[L], seg[R]);
        }

    public:
        explicit Segment_Tree(const int _size) : seg_size(_size) {
            seg.assign(4 * seg_size, Node());
        }

        void update(const int idx, const VAL_TYPE value) {
            update(idx, value, 0, 0, seg_size - 1);
        }

        Node query(const int lq, const int rq) {
            return query(lq, rq, 0, 0, seg_size - 1);
        }
    };
} // namespace my_lib

#endif // SEGMENT_TREE_H
