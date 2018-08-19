#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#include <functional>
#include <iostream>
#include <numeric>

template<typename Key>
using ordered_set = __gnu_pbds::tree<
    Key, __gnu_pbds::null_type, std::less<Key>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;
using __gnu_pbds::gp_hash_table;  // implements unordered_map
using __gnu_cxx::rope;

int main() {
    ordered_set<int> X;
    for (auto i : {1, 2, 4, 8, 16}) {
        X.insert(i);
    }

    for (auto i : {1, 2, 4}) {
        std::cout << *X.find_by_order(i) << '\n'; // 2 4 16
    }
    std::cout << (X.end()==X.find_by_order(10)) << '\n'; // 1

    for (auto key : {-5, 1, 3, 4, 400}) {
        std::cout << X.order_of_key(key) << '\n'; // 0 0 2 2 5
    }

    rope<int> rp;
    rp.push_back(23);
    rp += rope<int>(5, 42);
    for (auto x : rp) {
        std::cout << x << ' ';
    }
    std::cout << '\n';  // 23 42 42 42 42 42

    rp.erase(3, 2);
    rp.mutable_reference_at(1) = 24;  // 2 substrs + 2 concats
    for (auto x : rp) {
        std::cout << x << ' ';
    }
    std::cout << '\n';  // 23 24 42 42

    rope<int> rp2 = rp;  // said to be fast
    std::iota(rp.mutable_begin(), rp.mutable_end(), 0); // slow
    rp.replace(2, 1, rp2);  // said to be fast
    for (auto x : rp) {
        std::cout << x << ' ';
    }
    std::cout << '\n';  // 0 1 23 24 42 42 3
    std::cout << rp.substr(2).size() << '\n';  // 1!
    std::cout << rope<char>(5, '!') + '\n';  // !!!!!
}
