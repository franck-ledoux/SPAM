# SPAM Viewer
## Installation
In order to run the tree viewer, you must configure a local python environment 
and install networkx and matplotlib.


## Usage
Run the ``spam_view`` script in command line with the expected parameters, which are:
- An input json file containing a MCTS tree
- the id of the node we want to start the visualization from
- the depth we expect
- the ouput png file

All those parameters must be provided in a parameter file. For instance, 
the file `parameters.json`: 
```json 
{
    "tree_file":"takuzu_2.json",
    "image_file": "tree.png",
    "source-node":1,
    "depth":2
}
```
And you run
```shell
python spam_view.py parameters.json
```