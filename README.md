# brun
**brun** (bash runner) is a small program that takes a single directory as an argument and creates a treeview of every bash script within that directory.

It features vi-like key bindings for navigating the directory.

### Usage
* j/k   - navigate up/down
* l - select (open/close directory or run script)
* / - enter search mode
* q - quit
* n/N - goto next/previous highlighted script 

### Installation
To test brun on a linux system:
* clone this repository with ``` git clone https://github.com/alanstoate/brun.git ```
* ``` cd brun ```
* run ``` make ```
* ```./brun ./scripts ``` to display the test scripts directory (ensure that the scripts have correct permissions)

### Requirements
* gcc with c++17 support
* ncurses library

### Todo
* Complete search functionality 
* Get a real build system going 
