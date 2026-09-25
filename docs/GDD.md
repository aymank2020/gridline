# GRIDLINE: Game Design Document (v0.1)

## 1. Overview
- **Genre:** squad turn-based tactics
- **Engine:** Unreal Engine 5.8, gameplay in C++
- **Platform:** PC (Windows)
- **Session:** 10–15 minute missions; a 5-mission campaign
- **Inspirations:** XCOM 2 (cover and flanking), Into the Breach (readable information, short missions)

## 2. Design pillars
1. **Information is fair.** Hit chance, enemy intent and cover are always visible before you commit.
2. **Position beats luck.** Flanking, height and overwatch matter more than dice rolls.
3. **Short and sharp.** Small maps and few units, so every turn matters.

## 3. Rules
- **Action points:** each unit has 2 actions per turn. Moving is one action; shooting ends the turn.
- **Cover:** each tile edge is none, half (−20 aim) or full (−40 aim). Flanking ignores cover.
- **Hit chance** = aim − cover − distance penalty + height bonus + flanking bonus, clamped to 5–95%. The random draw is logged so every outcome can be replayed.
- **Overwatch:** spend your turn to take a reaction shot at the first enemy that moves in sight (−15 aim).
- **Statuses:** Burning (damage over time; spreads to adjacent flammable tiles) and Stunned (lose next turn).
- **Destruction:** explosives and heavy weapons remove half-cover walls.

## 4. Squad
| Class | Role | Signature ability |
|---|---|---|
| Breacher | Close range | *Cutting Torch:* destroys a wall and damages behind it |
| Marksman | Long range | *Deadeye:* high-accuracy shot, ignores half cover |
| Technician | Support | *Patch Drone:* heals or repairs |
| Grenadier | Area control | *Arc Charge:* stuns in a small area |

## 5. Enemies
Scrap Drone (fast, weak), Welder Bot (melee, sets Burning), Turret Node (static overwatch), Sentinel (elite; shielded until flanked), and the Station Core (final boss mission).

## 6. AI
Utility AI scores every legal command by expected damage, cover gained, flank risk and overwatch exposure. Each archetype has its own weights. The AI is deterministic given the state and seed, and must finish its turn in under 200 ms.

## 7. Scope of the MVP
5 missions, 4 squad classes, 5 enemy types, 1 promotion per unit per mission, and saving between missions. **Out of scope:** a base-building meta layer, procedural maps, and multiplayer.

## 8. Success criteria
- Replaying any recorded mission reproduces the same final state hash
- The AI never issues an invalid command (tested across thousands of random states)
- 60 fps at 1080p on an RTX 4050 Laptop
