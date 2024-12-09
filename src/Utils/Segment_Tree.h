#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>
#include <climits>

namespace my_lib {
    class Node {
    public:
        int min;
        int max;
        Node() : min(INT_MAX), max(INT_MIN) { }
        Node(int value) : min(value), max(value) { }
    };

    class Segment_Tree {
    private:
        int seg_size;
        std::vector<Node> seg;

        Node merge(const Node &a, const Node &b) const {
            Node ret;
            ret.max = std::max(a.max, b.max);
            ret.min = std::min(a.min, b.min);
            return ret;
        }

        Node query(int lq, int rq, int node, int l, int r) const {
            if (lq > r || rq < l) return Node(); // Neutral node with min=INT_MAX and max=INT_MIN
            if (lq <= l && r <= rq) return seg[node];
            int mid = l + (r - l) / 2;
            Node left = query(lq, rq, 2 * node + 1, l, mid);
            Node right = query(lq, rq, 2 * node + 2, mid + 1, r);
            return merge(left, right);
        }

        void update(int idx, int value, int node, int l, int r) {
            if (l == r) {
                seg[node] = Node(value);
                return;
            }
            int mid = l + (r - l) / 2;
            if (idx <= mid) update(idx, value, 2 * node + 1, l, mid);
            else update(idx, value, 2 * node + 2, mid + 1, r);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }

    public:
        explicit Segment_Tree(int size) : seg_size(size), seg(4 * size, Node()) { }

        void build(const std::vector<int> &data, int node = 0, int l = 0, int r = -1) {
            if (r == -1) r = seg_size - 1;
            if (l == r) {
                seg[node] = Node(data[l]);
                return;
            }
            int mid = l + (r - l) / 2;
            build(data, 2 * node + 1, l, mid);
            build(data, 2 * node + 2, mid + 1, r);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }

        Node query(int lq, int rq) const {
            return query(lq, rq, 0, 0, seg_size - 1);
        }

        void update(int idx, int value) {
            update(idx, value, 0, 0, seg_size - 1);
        }
    };
} // namespace my_lib

#endif // SEGMENT_TREE_H
