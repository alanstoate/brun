all:
	g++ -std=c++17 main.cpp file_tree_item.cpp file_tree_view.cpp -lstdc++fs -lncurses -g
