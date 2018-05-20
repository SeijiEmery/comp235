// generate.cpp
// copyright (c) Seiji Emery, 5/15/18
// https://github.com/SeijiEmery/comp235/tree/master/lab_17e
//
// Generates graph data to be used by graph_groups.cpp (ie. 'make run', or ./graph_groups)
// Output is sent to stdout and can be piped into ./graph_groups and/or local files.
// stderr is used to display optional debug messages, ie. all groups / verts generated.
//
// Specifically, this program generates:
//      N random, unique vertices
//      divided into M groups, with at least 2 vertices per group
//      connected by an average of C connections (edges) per vertex, clamped >= 1.0
//      all vertices, and all edges are shuffled, and emitted as N * C lines of the form:
//          <vert1> <vert2>
//      eg.
//          2 4
//          4 6
//          11 4
//
// invoke as:
//      ./generate <args...> > some_file.txt
// or   ./generate <args...> | make run
// or   time ./generate <args...> --debug > /dev/null
//
// Arguments:
//      -v, --vertices    <num_vertices>   (# vertices total to generate)
//      -g, --groups      <num_groups>     (# groups to generate - verts split between groups)
//      -e, --edges       <num_edges>      (# edges to generate (total lines, low values will reduce groups))
//      -cf, --connections <connections>   (edge factor: # edges / vertex)
//      --min <min_vertex_id>              (min vertex #)
//      --max <max_vertex_id>              (max vertex #)
//      --debug                            (turns debugging on: displays all groups / vertices to stderr)
//      --ndebug                           (turns debugging off)
//
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <random>
#include "utility/util/parse_args.hpp"  // parseArgs()

int main (int argc, const char** argv) {
    int     numVerts  = 200;
    int     numGroups = 5;
    int     numEdges  = 0;
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
        .parse({ "-e", "--edges" }, numEdges)
        .parse({ "-g", "--groups" }, numGroups)
        .parse({ "-cf", "--connections" }, connectionsPerVertex)
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
    if (numEdges <= 0) {
        numEdges = static_cast<int>(numVerts * connectionsPerVertex);
    }
    if (numEdges < numVerts + numVerts / 2) {
        fprintf(stderr, "Warning: low #edges = %d (#verts = %d, #groups = %d), data may be truncated\n",
            numEdges, numVerts, numGroups);
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

    // Generate crappy MST edges so all vertices are spanned by each group
    for (auto& group : groupVerts) {
        for (size_t i = 1; i < group.size(); ++i) {
            if (rand() & 1) {
                edges.emplace_back(group[i], group[i - 1]);
            } else {
                edges.emplace_back(group[i - 1], group[i]);
            }
        }
    }

    // Generate additional random edges (iff necessary)
    for (int n = numEdges - edges.size(); n --> 0; ) {
        int group = rand() % groupVerts.size();
        int i = rand() % groupVerts[group].size(), j;
        do {
            j = rand() % groupVerts[group].size();
        } while (j == i);
        edges.emplace_back(groupVerts[group][i], groupVerts[group][j]);
    }

    // Shuffle edges
    std::shuffle(edges.begin(), edges.end(), rng);

    // Trim edges down to generated #
    if (edges.size() > numEdges) {
        edges.resize(numEdges);
    }

    // Output edges
    for (auto& edge : edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}
