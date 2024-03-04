# SPAM Viewer
## Installation
In order to run the tree viewer, you must configure a local python environment 
and install networkx and matplotlib.


## Usage
Run the spam_view script in command line indicating the expected parameters:
- An input json file containing a MCTS tree
- the id of the node we want to start the visualization from
- the depth we expect
- the ouput png file

```shell
python spam_view.py takuzu_2.json 1 2 tree.png 
```