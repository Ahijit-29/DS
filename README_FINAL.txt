================================================================================
SMART FLOOD RELIEF DISTRIBUTION AND RESOURCE ALLOCATION SYSTEM
Disaster Operations Command & Micro-Project Final Defense Edition
Alliance School of Advanced Computing | Department of Computer Science
================================================================================

PROJECT SUMMARY
--------------------------------------------------------------------------------
An end-to-end mission control disaster management system combining modern C++14
algorithms and a real-world Web Operations Dashboard. Solves real-time resource
allocation, dynamic flood routing, emergency SOS prioritization, and flood island
detection during catastrophic river flooding across Karnataka basins.

COURSE OUTCOMES (CO) ALIGNMENT MATRIX
--------------------------------------------------------------------------------
CO-1: Data Abstraction & Complexity
      - Modular C++ structs: Camp, SOSRequest, Vehicle, SupplyBundle.
      - Rigorous time complexity bounds: O((V+E) log V), O(log N), O(1).
CO-2: Linked-List Queues
      - Singly Linked-List Emergency SOS Request Queue (FIFO order).
      - O(1) enqueue and dequeue operations with leak-free pointer destructors.
CO-3: Heaps, Searching & Sorting
      - Binary Max-Heap from scratch for Humanitarian Triage prioritization.
      - Binary Search on sorted Camp IDs (O(log N)).
      - Case-insensitive Linear Search on Camp names (O(N)).
      - Multi-criteria humanitarian sorting.
CO-4: Trees, Sets & Graphs (DSU)
      - Disjoint Set Union (DSU / Kruskal structure) with path compression
        and union-by-rank to discover isolated flood islands.
CO-5: Graph Representation & Dijkstra Shortest Paths
      - Road network modeled as weighted adjacency list.
      - Dijkstra's algorithm for shortest open road route selection with
        real-time detour recalculation upon road submersion.

FILES IN THE PROJECT
--------------------------------------------------------------------------------
1. main.cpp                 Comprehensive C++ implementation with ANSI CLI
2. flood.exe                Pre-compiled executable (Windows x64)
3. flood_relief_demo.html   Real-World Mission Control Web Dashboard
4. index.html               Standard Web Entrypoint (Mirror of demo)
5. TEST_REPORT.txt          Full automated assertion & benchmark report
6. demo_output.txt          Raw output log from ./flood.exe --demo
7. README_FINAL.txt         Project overview and quickstart guide
8. README.md                Repository documentation

HOW TO BUILD AND RUN
--------------------------------------------------------------------------------
1. Build C++ Core:
     g++ -std=c++14 -Wall -Wextra -o flood.exe main.cpp

2. Run Automated Algorithm Verification Tests (7/7 Assertions):
     .\flood.exe --test

3. Run Benchmark Disaster Scenarios:
     .\flood.exe --demo

4. Run Interactive Terminal Mission Control:
     .\flood.exe

5. Open Web Mission Control Dashboard:
     Double-click 'flood_relief_demo.html' or 'index.html' in any browser.
     No server or external downloads required!

FEATURES FOR MAXIMUM EXAM / VIVA MARKS
--------------------------------------------------------------------------------
- Interactive GIS Road Network Map with clickable flood toggles.
- Real-time vehicle route animation along Dijkstra paths.
- Custom Test Case Builder: Load 5 academic scenarios or create custom JSON test cases.
- Live Algorithm Inspectors for Dijkstra, DSU, and Max-Heap.
- Oral Exam / Viva Defense Cheatsheet built directly into the UI.
- 1-Click Printable Executive Disaster Relief Dossier for viva submission.
================================================================================
