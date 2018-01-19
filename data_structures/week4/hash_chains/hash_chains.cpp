#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::list;
using std::cin;

struct Query
{
    string type, s;
    size_t ind;
};

class QueryProcessor
{
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<list<string>> hash_table;
    size_t hash_func(const string& s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

    public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        hash_table.resize(bucket_count);
    }

    Query readQuery() const
    {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const
    {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQueryChains(const Query& query)
    {
        if (query.type == "check")
        {
            list<string> *current_list = &hash_table[query.ind];
            list<string>::iterator i;
            for (i = current_list->begin(); i != current_list->end(); ++i)
            {
                std::cout << *i << " ";
            }
            std::cout << "\n";
        }
        else
        {
            int hash_val = hash_func(query.s);
            list<string> *current_list = &hash_table[hash_val];
            list<string>::iterator i = std::find(current_list->begin(),
                    current_list->end(), query.s);
            if (query.type == "find")
            {
                writeSearchResult(i != current_list->end());
            }
            else if (query.type == "add")
            {
                if (i == current_list->end())
                {
                    current_list->push_front(query.s);
                    list<string>::iterator printer;
                }
            }
            else if (query.type == "del")
            {
                if (i != current_list->end())
                {
                    current_list->erase(i);
                }
            }
        }
    }

    //void processQuery(const Query& query)
    //{
    //    if (query.type == "check")
    //    {
    //        // use reverse order, because we append strings to the end
    //        for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
    //            if (hash_func(elems[i]) == query.ind)
    //                std::cout << elems[i] << " ";
    //        std::cout << "\n";
    //    }
    //    else
    //    {
    //        vector<string>::iterator it =
    //            std::find(elems.begin(), elems.end(), query.s);
    //        if (query.type == "find")
    //        {
    //            writeSearchResult(it != elems.end());
    //        }
    //        else if (query.type == "add")
    //        {
    //            if (it == elems.end())
    //                elems.push_back(query.s);
    //        }
    //        else if (query.type == "del")
    //        {
    //            if (it != elems.end())
    //                elems.erase(it);
    //        }
    //    }
    //}

    void processQueries()
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQueryChains(readQuery());
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
