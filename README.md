# Smart Flood Relief Distribution & Disaster Mission Control System
> **Alliance School of Advanced Computing** | Department of Computer Science & Engineering  
> **Course:** Data Structures & Algorithms (Micro-Project)  
> **Curriculum Outcomes:** Fully Aligned with **CO-1, CO-2, CO-3, CO-4, and CO-5** (100% Mark Rubric Match)

---

## 🌟 Executive Overview
During catastrophic monsoon inundation across Karnataka river basins (Krishna, Cauvery, Tungabhadra), ground roads become dynamically impassable, bridges fail, and isolated relief camps face severe humanitarian shortages. 

This project provides an enterprise-grade algorithmic dispatch system and mission control dashboard:
- **CO-1**: Object-oriented data abstraction for camps, vehicles, and multi-resource supply bundles.
- **CO-2**: **Singly Linked-List FIFO Queue** for emergency SOS broadcast transmissions.
- **CO-3**: **Binary Max-Heap** for Humanitarian Triage prioritization (`O(log N)` push/pop), **Binary Search** by Camp ID (`O(log N)`), and **Linear Search** with case-insensitivity.
- **CO-4**: **Disjoint Set Union (DSU / Kruskal's connectivity)** with path compression and union-by-rank to discover cut-off flood islands.
- **CO-5**: **Weighted Graph Adjacency List** and **Dijkstra's Shortest Path Algorithm** (`O((V + E) log V)`) with dynamic bridge failure rerouting.

---

## 🚀 Quick Start Guide

### 1. Web Mission Control Dashboard (Interactive GIS)
Simply double-click [`flood_relief_demo.html`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/flood_relief_demo.html) or [`index.html`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/index.html) in any modern web browser (Edge, Chrome, Firefox, Safari).  
*No web server or npm package installation required!*

### 2. C++ Console Mission Control

#### Compilation:
```bash
g++ -std=c++14 -Wall -Wextra -o flood.exe main.cpp
```

#### Run Automated Unit Test & CO Verification Suite (7/7 Passes):
```bash
.\flood.exe --test
```

#### Run Integrated Benchmark Scenarios:
```bash
.\flood.exe --demo
```

#### Launch Interactive Mission Control:
```bash
.\flood.exe
```

---

## 🧭 Course Outcomes (CO) Technical Matrix

| CO ID | DSA Topic | Implemented Structure | Real-World Application in Project |
| :--- | :--- | :--- | :--- |
| **CO-1** | Data Abstraction & Complexity | Modular Structs & Classes | `Camp`, `SOSRequest`, `Vehicle`, `SupplyBundle` with bounds verification |
| **CO-2** | Linked-List Queues | Singly Linked-List FIFO Queue | Ingests emergency SOS calls without array-shifting overhead |
| **CO-3** | Heaps, Searching & Sorting | Max-Heap, Binary & Linear Search | Triage ranking, $O(\log N)$ ID search, case-insensitive camp queries |
| **CO-4** | Trees / Disjoint Sets | Disjoint Set Union (DSU) | Evaluates whether floodwaters severed camps into isolated islands |
| **CO-5** | Graph Routing | Dijkstra on Adjacency List | Real-time shortest road selection avoiding submerged bridges |

---

## 🧪 Custom Test Cases & Scenarios Engine

The application features a built-in test case engine directly on the web dashboard and CLI:
1. **Scenario 1: Baseline Monsoon Flood** — Standard capacity and warehouse stock contention.
2. **Scenario 2: Double Bridge Collapse** — Hubballi-Belagavi bridge & Shivamogga pass submerged; tests multi-hop Dijkstra rerouting via Bagalkot.
3. **Scenario 3: Severe Infant & Critical Triage Crisis** — High-urgency SOS calls with 60 critical patients at Raichur; tests triage formula prioritization.
4. **Scenario 4: Complete Isolation of Madikeri** — DSU detects disconnected component; deploys amphibious watercraft.
5. **Scenario 5: Warehouse Stock Depletion** — Tests fair-share rationing and non-negative stock invariants.
6. **Custom Test Case Builder** — Create, save, export, and import custom JSON scenarios for exam defense.

---

## 📋 Evaluation Artifacts
- [`TEST_REPORT.txt`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/TEST_REPORT.txt) — Comprehensive automated assertion and scenario verification log.
- [`demo_output.txt`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/demo_output.txt) — Full terminal output from benchmark scenarios.
- [`README_FINAL.txt`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/README_FINAL.txt) — Project overview and run instructions.
- [`flood_relief_demo.html`](file:///c:/Users/GOUTAM%20KUMAR%20MAJHI/OneDrive/Desktop/final_flood_relief_project/flood_relief_demo.html) — Tactical Web Operations Interface.