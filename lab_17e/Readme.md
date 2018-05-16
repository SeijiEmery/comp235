# Lab 17e

Lab assignment: implements a program (graph_groups.cpp) that reads in a text file of graph edges (ie. "2 4", "4 6" for the graph 2 <-> 4, 4 <-> 6), and builds up a list of all connected vertices for sub-graphs / groups 1 .. n (for some n).

In addition to the assignment, I also implemented a robust generator program (generator.cpp) that generates data for graph_groups.cpp to consume, ie. random graphs of N vertices divided into M connected groups.

Due to the above, graph_groups does NOT actually read in data from a file, but from stdin (and will stall forever if invoked without piping data into stdin)

# Build instructions (\*nix)
    cd <some-temp-dir>
    git clone https://github.com/SeijiEmery/comp235
    cd comp235/lab_17e/
    mkdir build; cd build
    cmake ..
    make generator

## To run from default data set (\*nix)
    cat ../data/connectedGraphs.txt | make run

## To run from generated data set (\*nix)
    ./generator -v <num_vertices> -g <num_groups> [-c <avg_connections_per_vertex>] | make run
eg.
    ./generator -v 20 -g 10 -c 3.5 | make run
    ./generator -v 200 -g 15 -c 10 | make run
    ./generator -v 10000 -g 2000 -c 2 | make run

## Generator args:
    -v, --vertices    <num_vertices>   (# vertices total to generate)
    -g, --groups      <num_groups>     (# groups to generate - verts split between groups)
    -c, --connections <connections>    (# edges per vertex (avg), clamped to >= 1.0)
    --min <min_vertex_id>              (min vertex #)
    --max <max_vertex_id>              (max vertex #)
    --debug                            (turns debugging on: displays all groups / vertices to stderr)
    --ndebug                           (turns debugging off)

## Do NOT run:
    make run

# Build instructions (windows):
Install the linux subsystem and use bash.

Or, idk, cmd.exe might work since it apparently supports piping, but this hasn't been tested.
