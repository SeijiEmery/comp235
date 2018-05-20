#include "linked_list.hpp"
#include "utility/util/mem_bench.hpp"
#include "utility/util/lineio.hpp"
#include <algorithm>

int main () {
    #define PRINT_EXPR(expr) \
        report() << #expr; info() << (expr) << '\n';


    LinkedList<int> list { 1, 2, 3, 4, 5 }; 
    PRINT_EXPR(list)

    LinkedList<int>::iterator it;
    PRINT_EXPR((it = list.find(27), it != list.end() ? "true" : "false"))
    PRINT_EXPR((it = list.find(2), it != list.end() ? "true" : "false"))
    PRINT_EXPR(*it)

    PRINT_EXPR(*(++it))
    PRINT_EXPR((list.insert(6, it), list))

    PRINT_EXPR((list.insert(7, list.end()), list))

    PRINT_EXPR((list.push_front(8), list))
    PRINT_EXPR((list.push_back(10), list))
    PRINT_EXPR((list.front()))
    PRINT_EXPR((list.remove(4), list))
    PRINT_EXPR((list.remove(8), list))
    PRINT_EXPR((list.pop_front(), list))
    // PRINT_EXPR((list.pop_back(), list))

    {
        report() << "Copy-constructing to new list";
        LinkedList<int> copy { list };
        PRINT_EXPR(copy)

        report() << "Removing all elements with pop_front()";
        while (copy) {
            PRINT_EXPR((copy.pop_front(), copy))
        }
        report() << "List should be unaffected";
        PRINT_EXPR(list)
    }
    {
        report() << "Constructing empty list via copy-assignment";
        LinkedList<int> copy;
        PRINT_EXPR(copy = list)

        info() << "Removing all elements with pop_back()";
        while (copy) {
            PRINT_EXPR((copy.pop_back(), copy))
        }
        report() << "List should be unaffected";
        PRINT_EXPR(list)
    }
}
