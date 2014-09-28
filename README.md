Parses weechat IRC logs and builds an in-memory graph of Nicks seen.

## Usage

````
./nick_normalize <output_type> <logfile>

Where <output_type> is one of the following:

    gephi       - Outputs /tmp/nodes.csv and /tmp/edges.csv for use with the Gephi graph program.
    sigmajs     - Outputs a JSON encoded graph for use with the sigma.js graphing library.
    aliases     - Simply prints aliases and joins to STDOUT. Filters out non-aliased users.
    nodes       - Prints all nodes to stdout.
    edges       - Prints all edges to stdout.
````
