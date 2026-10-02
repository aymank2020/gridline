# GRIDLINE

> A squad-based, turn-based tactics game built in **Unreal Engine 5.8 (C++)**, with a deterministic rules engine that is fully separated from presentation.

**Status:** pre-production. The design is locked; no playable build yet. See [`docs/STATUS.md`](docs/STATUS.md).

## The pitch
A four-person squad of salvage engineers fights rogue machines inside a collapsing orbital station. Missions are tight (10–15 minutes) and built around cover, overwatch and destructible walls.

## Technical goals
| Area | Approach |
|---|---|
| Rules engine | `GridlineCore`, a plain C++ module with no Actor dependency: grid, battle state, commands |
| Pathfinding | A* for paths plus Dijkstra reachable sets for movement range |
| Line of sight | Tile supercover with half/full cover, height and peeking |
| Commands | Command pattern: each command has `Validate()` and `Apply()`, and emits events |
| Determinism | A mission is `seed + command list`; a replay must reproduce the same state hash |
| AI | Utility AI scoring candidate commands; weights live in data assets |
| Quality | Target of 100+ automation tests in the core, including property tests on random maps |

## Roadmap
- [ ] M0 Repository and modules
- [ ] M1 Grid and pathfinding
- [ ] M2 Line of sight and cover
- [ ] M3 Battle state, commands, hit chance
- [ ] M4 Determinism and replay
- [ ] M5 Overwatch, statuses, destructible cover
- [ ] M6 Utility AI
- [ ] M7 Presentation and UI
- [ ] M8 Five-mission campaign and saving
- [ ] M9 Packaged build and performance report

## Documents
- [Game Design Document](docs/GDD.md)

## Development note
Development uses AI coding assistants under my direction and review. Commits carry honest co-author trailers, and the history is never rewritten.

## Executable foundation

[Portable core, commands and verification limits](docs/CORE.md). No playable build yet.
