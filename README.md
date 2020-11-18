# Display_VD
Folder contains: TreeManager to read TTrees in root files (TreeManager.h, TreeManager.C, Header.h (for HeaderTree) and Hits.h (for HitsTree) )

usage:
root -l
.L TreeManager.C++ (only once to create shared library)
.q
...
usage of event display
root -l [xxxxx].root
.L Analysis_V2.C
GetDisplay()

