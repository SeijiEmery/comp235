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
    ./generator --debug -v <num_vertices> -g <num_groups> [-cf <avg_connections_per_vertex>] | make run
    ./generator --debug -v 20 -g 10 -cf 3.5 | make run
    ./generator --debug -v 200 -g 15 -cf 10 | make run
    ./generator --debug -v 10000 -g 2000 -cf 2 | make run

## To benchmark (testcase 1: 100k verts, 2k groups, ~1M edges):
    time ./generator --ndebug -v 100000 -g 2000 -e 100000 > /dev/null
    time ./generator --ndebug -v 100000 -g 2000 -e 100000 | make run > /dev/null
    time ./generator --ndebug -v 100000 -g 2000 -e 100000 > data.txt
    ls -l data.txt
    time cat data.txt > /dev/null
    time cat data.txt | make run > /dev/null

## To benchmark (testcase 2: 1M verts, 2k groups, ~1M edges)
    time ./generator --ndebug -v 100000 -g 2000 -c 22 > /dev/null
    time ./generator --ndebug -v 100000 -g 2000 -c 22 | make run > /dev/null
    time ./generator --ndebug -v 100000 -g 2000 -c 22 > data.txt
    ls -l data.txt
    time cat data.txt > /dev/null
    time cat data.txt | make run > /dev/null


## Generator args:
    -v, --vertices    <num_vertices>   (# vertices total to generate)
    -g, --groups      <num_groups>     (# groups to generate - verts split between groups)
    -e, --edges       <num_edges>      (# edges to generate (total lines, low values will reduce groups))
    -cf, --connections <connections>   (edge factor: # edges / vertex)
    --min <min_vertex_id>              (min vertex #)
    --max <max_vertex_id>              (max vertex #)
    --debug                            (turns debugging on: displays all groups / vertices to stderr)
    --ndebug                           (turns debugging off)

## Do NOT run:
    make run

# Build instructions (windows):
Install the linux subsystem and use bash.

Or, idk, cmd.exe might work since it apparently supports piping, but this hasn't been tested.
