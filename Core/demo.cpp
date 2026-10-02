#include "GridlineCore.h"
#include <iostream>
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
static void tests() {
    gridline::Grid grid(4, 4); grid.block({1, 0});
    auto path = grid.path({0, 0}, {2, 0});
    check(path.size() == 5 && path.front() == gridline::Cell{0, 0} && path.back() == gridline::Cell{2, 0}, "shortest detour");
    check(grid.path({-1, 0}, {2, 0}).empty(), "outside tile");
    check(grid.path({0, 0}, {1, 0}).empty(), "blocked goal");
    gridline::Battle first, replay;
    check(!first.move(grid, {2, 0}, 3) && first.actions == 2, "rejected move is atomic");
    for (auto target : {gridline::Cell{2, 0}, gridline::Cell{3, 0}}) {
        check(first.move(grid, target, 4) && replay.move(grid, target, 4), "valid movement");
    }
    check(first.hash() == replay.hash(), "replayed commands match");
    check(!first.move(grid, {3, 1}, 4) && first.actions == 0, "action budget enforced");
    gridline::Grid isolated(2, 2); isolated.block({1, 0}); isolated.block({0, 1});
    check(isolated.path({0, 0}, {1, 1}).empty(), "unreachable destination");
}
int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--self-test") { tests(); std::cout << "Gridline core checks passed\n"; return 0; }
        if (argc != 1) { std::cerr << "Usage: core-demo [--self-test]\n"; return 2; }
        gridline::Grid grid(4, 4); grid.block({1, 0}); gridline::Battle battle;
        if (!battle.move(grid, {2, 0}, 4)) return 1;
        std::cout << "position=" << battle.position.x << ',' << battle.position.y << " actions=" << battle.actions << " hash=" << battle.hash() << '\n';
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
