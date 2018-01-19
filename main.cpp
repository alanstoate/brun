#include "node.h"
#include "menu.h"
#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <utility>
#include <sys/types.h>
#include <unistd.h>

#include <ncurses.h>

namespace fs = std::experimental::filesystem;
namespace dr = directory;

using model = std::vector<std::pair<std::string, dr::Node*>>;

void generate_model(dr::Node& root, int depth, model& m) {
    for (auto& c : root.get_children()) {
        std::string entry;

        for (int i = 0; i < depth; ++i) entry += "  ";

        entry += c->get_path().stem().string();
        entry += "\n";
        m.push_back(std::make_pair(entry, c.get()));
        if (c->is_expanded() && c->is_directory()) 
            generate_model(*c, depth + 1, m);
    }
} 

void print_dir(model m) {
    for (auto& e : m) {
        printw(e.first.c_str());
    }
}

dr::Node& get_node_at_row(int& row, dr::Node& root) {
    for (auto& c : root.get_children()) {
        row--;
        if (row < 0) {
            return *c;
        }
        else if (c->is_expanded() && root.is_directory()) {
            auto& n = get_node_at_row(row, *c); 
            if (&n != &root) return n;
        }
    }
    return root;
}

void init() {
    initscr();
    noecho();
}

void end() {
    endwin();
}

void refresh_screen(dr::Node& n, model& m) {
    clear();
    m.clear();
    generate_model(n, 0, m);
    print_dir(m);
    refresh();
}

enum Mv {LEFT, RIGHT, UP, DOWN};
void mv_curs(Mv m) {
    int x, y;
    getyx(stdscr, y, x);
    switch (m) {
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        case LEFT:
            x++;
            break;
        case RIGHT:
            x--;
            break;
    }
    move(y,x);
}

bool input_loop(dr::Node& root, model& m) {
    int ch = getch();
    switch (ch) {
        case 'q':
            return false;
        case 'g':
            move(0,0);
            return true;
        case 'j':
            mv_curs(UP);
            break;
        case 'k':
            mv_curs(DOWN);
            break;
        case 'l':
            int y, x;
            getyx(stdscr,y,x);
            auto& node = m.at(y).second;

            if (node->is_directory())
                node->set_expanded(!node->is_expanded());
            else {
                end();
                system(node->get_path().string().c_str());
                exit(0);
            }
            refresh_screen(root, m);
            move(y,0);
            break;
    }
    refresh();
    return true;
}


int main(int argc, char *argv[]) {
    std::cerr << getpid() << std::endl;
    auto n = std::make_unique<dr::Node>(fs::current_path(), true);

    // set the highest level to expanded
    n->set_expanded(true);
    dr::scan_dir(fs::current_path(), n.get());

    model m;
    menu::menu me(stdscr);

    init();
    refresh_screen(*n, m);
    while(input_loop(*n, m)){}
    end();

    return 0;
}
