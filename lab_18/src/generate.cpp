#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <random>

int main (int argc, const char** argv) {
    int     numVerts  = 200;
    int     numGroups = 5;
    double  connectionsPerVertex = 3.0;

    // int numVerts = 20;
    int numEdges = 100;
    int min      = 0;
    int max      = 0;

    // Read args
    bool ok = true;
    for (int i = 1; i < argc; ++i) {
        if (i < argc && (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verts"))) {
            numVerts = atoi(argv[++i]);
            if (numVerts <= 0) {
                fprintf(stderr, "num verts must be > 0 (got %d)\n", numVerts);
                exit(-1);
            }
        } else if (i < argc && (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--edges"))) {
            numEdges = atoi(argv[++i]);
            if (numEdges <= 0) {
                fprintf(stderr, "num edges must be > 0 (got %d)\n", numEdges);
                exit(-1);
            }
        } else if (i < argc && !strcmp(argv[i], "--min")) {
            min = atoi(argv[++i]);
        } else if (i < argc && !strcmp(argv[i], "--max")) {
            max = atoi(argv[++i]);
        } else {
            fprintf(stderr, "unexpected argument: '%s'\n", argv[i]);
            ok = false;
        }
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
        fprintf(stderr, "usage: %s -v <num_verts> -e <num_edges> [--min <min> --max <max>]", argv[0]);
        exit(-1);
    }
    // Generate random vertices
    srand(time(nullptr));
    std::set<int> uniqueVerts;

    assert(max > min + numVerts);
    while (uniqueVerts.size() < numVerts) {
        uniqueVerts.insert(min + rand() % (max - min));
    }
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
    }
    fprintf(stderr, "Running generator\n");
    for (int i = 0; i < groupVerts.size(); ++i) {
        fprintf(stderr, "  generated group %d: ", i + 1);
        for (auto v : groupVerts[i]) {
            fprintf(stderr, "%d ", v);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");


    std::vector<std::pair<int, int>> edges;
    for (auto& group : groupVerts) {
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(edges.begin(), edges.end(), std::default_random_engine(seed));

    // Output edges
    for (auto& edge : edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}
