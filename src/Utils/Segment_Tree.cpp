#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include <bits/stdc++.h>

namespace Segment_Tree {

    class Node {
    public:
        int value;
        Node() : value(0) {}
        explicit Node(int _value) : value(_value) {}
    };

    template<typename VAL_TYPE = int, VAL_TYPE NEUTRAL_VALUE = 0, class MRG = std::function<VAL_TYPE(const VAL_TYPE &, const VAL_TYPE &)> >
    class Segment_Tree {
    private:
#define L (2*node+1)
#define R (2*node+2)
#define mid ((l+r)/2)

        int seg_size;
        std::vector<Node> seg;
        MRG merge;

        Node query(const int lq, const int rq, int node, int l, int r) {
            if (lq > r || rq < l) return Node(NEUTRAL_VALUE);
            if (lq <= l && r <= rq) return seg[node];
            return Node(merge(query(lq, rq, L, l, mid).value,
                              query(lq, rq, R, mid + 1, r).value));
        }

        void update(const int idx, const VAL_TYPE value, int node, int l, int r) {
            if (l == r) {
                seg[node] = Node(value);
                return;
            }
            if (idx <= mid) update(idx, value, L, l, mid);
            else update(idx, value, R, mid + 1, r);

            seg[node] = Node(merge(seg[L].value, seg[R].value));
        }

    public:
        explicit Segment_Tree(const int _size, const MRG &_mrg) : seg_size(_size), merge(_mrg) {
            seg.assign(4 * seg_size, Node(NEUTRAL_VALUE));
        }

        void update(const int idx, const VAL_TYPE value) {
            update(idx, value, 0, 0, seg_size - 1);
        }

        Node query(const int lq, const int rq) {
            return query(lq, rq, 0, 0, seg_size - 1);
        }
    };

} // namespace Segment_Tree

#endif // SEGMENT_TREE_H
