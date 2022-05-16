# MPTS
Mobile Phone Tracking System 

This project implements a hierarchical data structure `Routing Map Tree` which is used to store data of base station and mobilephones on the network efficiently.
The objective is to solve the fundamental problem of cellular networks: When a phone is called, find where it is located so that a connection may be established.

`MPTS.pdf` contains full description of this project along with queries it needs to respond to.

`action1.txt` and `action2.txt` contains a list of test queries, with expected outputs given in corresponding `answer().txt`.

`checker.cpp` can be used to test the working of MPTS.

This implementation uses `bloom filters` for space efficiency and fast computation of `isMember()`. An alternate implementation using `std::set` is given in `MPTS_set`.
