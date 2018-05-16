#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

int main (int argc, const char** argv) {
    int numVerts = 20;
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
    std::vector<int> verts (numVerts);
    std::generate(verts.begin(), verts.end(), [&](){ return rand() % (numVerts * 12); });

    // Generate + output random edges (to stdout, can pipe to file if desired)
    while (numEdges --> 0) {
        int a, b;
        do {
            a = verts[rand() % verts.size()];
            b = verts[rand() % verts.size()];
        } while (a == b);
        printf("%d %d \n", a, b);
    }
    return 0;
}
