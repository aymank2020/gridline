#pragma once
#include <algorithm>
#include <cstdint>
#include <queue>
#include <stdexcept>
#include <vector>

namespace gridline {
struct Cell { int x; int y; bool operator==(const Cell& b) const { return x == b.x && y == b.y; } };
class Grid {
public:
    Grid(int width, int height) : width_(width), height_(height) {
        if (width <= 0 || height <= 0 || width > 1024 || height > 1024) throw std::invalid_argument("invalid grid dimensions");
        blocked_.resize(static_cast<std::size_t>(width * height));
    }
    bool inside(Cell p) const { return p.x >= 0 && p.y >= 0 && p.x < width_ && p.y < height_; }
    bool open(Cell p) const { return inside(p) && !blocked_[index(p)]; }
    void block(Cell p) { if (!inside(p)) throw std::out_of_range("tile outside grid"); blocked_[index(p)] = true; }
    std::vector<Cell> path(Cell start, Cell goal) const {
        if (!open(start) || !open(goal)) return {};
        std::vector<int> parent(blocked_.size(), -1);
        std::queue<Cell> frontier;
        parent[index(start)] = index(start); frontier.push(start);
        // Unit-cost Dijkstra/BFS with a fixed neighbor order for replay stability.
        const Cell directions[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (!frontier.empty() && parent[index(goal)] == -1) {
            const Cell current = frontier.front(); frontier.pop();
            for (Cell d : directions) {
                const Cell next{current.x + d.x, current.y + d.y};
                if (open(next) && parent[index(next)] == -1) {
                    parent[index(next)] = index(current); frontier.push(next);
                }
            }
        }
        if (parent[index(goal)] == -1) return {};
        std::vector<Cell> result;
        for (int n = index(goal); ; n = parent[n]) {
            result.push_back({n % width_, n / width_});
            if (n == index(start)) break;
        }
        std::reverse(result.begin(), result.end()); return result;
    }
private:
    int index(Cell p) const { return p.y * width_ + p.x; }
    int width_, height_;
    std::vector<bool> blocked_;
};
struct Battle {
    Cell position{0, 0}; int actions = 2;
    bool move(const Grid& grid, Cell target, int maxSteps) {
        if (actions <= 0 || maxSteps < 0) return false;
        const auto route = grid.path(position, target);
        if (route.size() < 2 || route.size() - 1 > static_cast<std::size_t>(maxSteps)) return false;
        position = target; --actions; return true;
    }
    std::uint64_t hash() const {
        // Explicit integer encoding, with no struct-padding or platform hash dependency.
        std::uint64_t value = 14695981039346656037ULL;
        for (std::uint32_t field : {static_cast<std::uint32_t>(position.x), static_cast<std::uint32_t>(position.y), static_cast<std::uint32_t>(actions)})
            for (int byte = 0; byte < 4; ++byte) { value ^= (field >> (byte * 8)) & 255U; value *= 1099511628211ULL; }
        return value;
    }
};
}
