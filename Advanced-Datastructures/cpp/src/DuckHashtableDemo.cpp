#include "DuckHashtable.h"
#include "DuckHash.h"

#include <iostream>
#include <string>
#include <utility>

int main() {
    duck::DuckHashtable<int> table(8);

    for (int i = 0; i < 100; ++i)
        table.insert(i);

    std::cout << "after inserting 0..99: size=" << table.size() << " capacity=" << table.capacity() << '\n';

    std::cout << "contains(42)=" << (table.contains(42) ? "yes" : "no") << '\n';
    std::cout << "contains(100)=" << (table.contains(100) ? "yes" : "no") << '\n';

    if (const int* p = table.get(99))
        std::cout << "get(99)=" << *p << '\n';

    int false_positives = 0;
    for (int i = 100; i < 200; ++i)
        if (table.contains(i))
            ++false_positives;
    std::cout << "false positives=" << false_positives << '\n';

    size_t before = table.size();
    for (int i = 0; i < 100; i += 2)
        table.remove(i);
    std::cout << "after removing evens: size " << before << " -> " << table.size() << '\n';

    int errors = 0;
    for (int i = 0; i < 100; i += 2)
        if (table.contains(i))
            ++errors;
    for (int i = 1; i < 100; i += 2)
        if (!table.contains(i))
            ++errors;
    std::cout << "consistency errors=" << errors << '\n';

    duck::DuckHashtable<std::string> words;
    words.insert("duck");
    words.insert("hash");
    words.insert("table");
    words.insert("duck");
    std::cout << "words size=" << words.size() << " contains(hash)=" << (words.contains("hash") ? "yes" : "no") << '\n';

    duck::DuckHashtable<int> copy(table);
    duck::DuckHashtable<int> moved(std::move(copy));
    std::cout << "copy moved; moved size=" << moved.size() << " source size=" << copy.size() << '\n';

    words.clear();
    std::cout << "after clear, words empty=" << (words.empty() ? "yes" : "no") << '\n';

    return 0;
}