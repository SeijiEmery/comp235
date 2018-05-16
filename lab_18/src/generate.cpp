#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <random>


template <typename T> struct Reader;
template <> struct Reader<int> { static int read (const char* arg) { return atoi(arg); }};
template <> struct Reader<double> { static double read (const char* arg) { return atof(arg); }};
template <> struct Reader<std::string> { static std::string read (const char* arg) { return { arg }; }};

template <typename T>
static T read (const char* arg) { return Reader<T>::read(arg); }

class ArgParser {
    int          argc;
    const char** argv;
    int          i = 1;
    std::vector<std::function<bool()>> parseCases;
    std::function<void(const char*)> defaultCase;
public:
    typedef ArgParser This;
    
    ArgParser (int argc, const char** argv)
        : argc(argc), argv(argv) {}
    ~ArgParser () { parseAll(); }

    void parseAll () {
        while (i < argc) {
            // fprintf(stderr, "parsing argument %d '%s'\n", i, argv[i]);
            int j = 0;
            for (const auto& parseCase : parseCases) {
                if (parseCase()) {
                    // fprintf(stderr, "handled with case %d\n", j);
                    goto continue_;       
                }
                ++j;
            }
            defaultCase(argv[i++]);
        continue_:;
        }
    }
    This& parseDefault (std::function<void(const char*)> callback) {
        defaultCase = callback;
        return *this;
    }
    template <typename... Args>
    This& parse (std::string name, std::function<void(Args...)> callback) {
        return parse({ name }, callback);
    }
    This& parse (std::initializer_list<std::string> argNames, std::function<void()> callback) {
        // fprintf(stderr, "case 1\n");
        parseCases.emplace_back([argNames, callback, this]() -> bool {
            if (argc - i >= 1 && match(argv[i], argNames)) {
                callback();
                i += 1;
                return true;
            }
            return false;
        });
        return *this;
    }
    template <typename T>
    This& parse (std::initializer_list<std::string> argNames, std::function<void(T)> callback) {
        // fprintf(stderr, "case 2\n");
        parseCases.emplace_back([argNames, callback, this]() -> bool {
            if (argc - i >= 2 && match(argv[i], argNames)) {
                callback(read<T>(argv[i + 1]));
                i += 2;
                return true;
            }
            return false;
        });
        return *this;
    }

    template <typename T>
    This& parse (const std::string& name, T& value) {
        return parse(
            std::initializer_list<std::string> { name }, 
            std::function<void(T)> { [&](T x) { 
                // fprintf(stderr, "setting value = %d\n", x); 
                return value = x; 
            } 
        });
    }
    template <typename T>
    This& parse (std::initializer_list<std::string> argNames, T& value) {
        return parse(
            argNames, 
            std::function<void(T)> { [&](T x) { 
                // fprintf(stderr, "setting value = %d\n", x); 
                return value = x; 
            } 
        });
    }
private:
    static bool match (const char* arg, const std::string& name) { return arg == name; }
    static bool match (const char* arg, const std::initializer_list<std::string>& names) {
        for (auto name : names) {
            if (arg == name) {
                return true;
            }
        }
        return false;
    }
};
ArgParser parseArgs (int argc, const char** argv) { return { argc, argv }; }


int main (int argc, const char** argv) {
    int     numVerts  = 200;
    int     numGroups = 5;
    double  connectionsPerVertex = 3.0;
    int min      = 0;
    int max      = 0;
    bool debug   = true;

    // const char* args[] = {
    //     "my-program",
    //     "-v", "1000",
    //     "--verts", "100000",
    //     "--groups", "10",
    //     "--connections", "1.256",
    //     "--min", "100",
    //     "--max", "20",
    //     "asdf",
    //     "whatever"
    // };
    // int count = sizeof(args) / sizeof(args[0]);

    // Read args
    bool ok = true;
    // parseArgs(count, &args[0])
    parseArgs(argc, argv)
        .parse({ "-v", "--verts" }, numVerts)
        .parse({ "-g", "--groups" }, numGroups)
        .parse({ "-c", "--connections" }, connectionsPerVertex)
        .parse({ "--min" }, min)
        .parse({ "--max" }, max)
        .parse({ "--debug" }, [&](){ debug = true; })
        .parse({ "--ndebug" }, [&](){ debug = false; })
        .parseDefault([](const char* arg){
            fprintf(stderr, "unexpected argument: '%s'\n", arg);
        })
    ;
    if (numVerts <= 0) {
        fprintf(stderr, "num verts must be > 0 (got %d)\n", numVerts);
        exit(-1);
    }
    if (numGroups <= 0) {
        fprintf(stderr, "num groups must be > 0 (got %d)\n", numVerts);
        exit(-1);
    }
    if (connectionsPerVertex <= 0.0) {
        fprintf(stderr, "num connections (per vertex) must be > 0 (got %lf)\n", connectionsPerVertex);
        exit(-1);
    }
    if (!min || !max) {
        if (max && !min) {
            min = max - numVerts * 4;
        } else {
            max = min + numVerts * 4;
        }
    } else {
        if (min >= max) {
            fprintf(stderr, "invalid min, max: %d, %d\n", min, max);
            exit(-1);
        }
    }
    if (!ok) {
        fprintf(stderr, "usage: %s -v <num_verts> -g <num_groups> -c <connections_per_vertex>] --min <min_vertex> --max <max_vertex>", argv[0]);
        exit(-1);
    }
    // Generate random vertices
    srand(time(nullptr));
    std::set<int> uniqueVerts;

    assert(max > min + numVerts);
    while (uniqueVerts.size() < numVerts) {
        uniqueVerts.insert(min + rand() % (max - min));
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::vector<std::vector<int>> groupVerts (numGroups);
    {   
        // Insert vertices into random groups
        auto it = uniqueVerts.begin(), end = uniqueVerts.end();

        // Ensure each group has at least 2 vertices
        for (auto& group : groupVerts) {
            assert(it != end); group.push_back(*it); ++it;
            assert(it != end); group.push_back(*it); ++it;
        }
        // Insert all remaining vertices
        for (; it != end; ++it) {
            groupVerts[rand() % numGroups].push_back(*it);
        }
        // Shuffle vertices
        for (auto& group : groupVerts) {
            std::shuffle(group.begin(), group.end(), rng);
        }
    }
    if (debug) {
        fprintf(stderr, "Running generator\n");
        for (int i = 0; i < groupVerts.size(); ++i) {
            fprintf(stderr, "  generated group %d: ", i + 1);
            for (auto v : groupVerts[i]) {
                fprintf(stderr, "%d ", v);
            }
            fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }

    //
    // Generate edges
    //
    std::vector<std::pair<int, int>> edges;

    // Generate adjacent edges
    connectionsPerVertex -= 1;
    for (auto& group : groupVerts) {
        for (size_t i = 1; i < group.size(); ++i) {
            if (rand() & 1) {
                edges.emplace_back(group[i], group[i - 1]);
            } else {
                edges.emplace_back(group[i - 1], group[i]);
            }
        }

        if (connectionsPerVertex <= 0)
            continue;
        for (size_t i = 0; i < group.size(); ++i) {
            int n = static_cast<int>(static_cast<double>(rand() % 1000) * connectionsPerVertex) / 1000;
            while (n --> 0) {
                size_t j = rand() % group.size();
                if (rand() & 1) {
                    edges.emplace_back(group[i], group[j]);
                } else {
                    edges.emplace_back(group[j], group[i]);
                }
            }
        }
    }

    // Shuffle edges
    std::shuffle(edges.begin(), edges.end(), rng);

    // Output edges
    for (auto& edge : edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}
