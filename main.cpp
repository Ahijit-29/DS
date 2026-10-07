// Data Structures Based Smart Flood Relief Distribution and Resource Allocation System
// Micro-project | Alliance School of Advanced Computing
// CO-2: linked-list queue (pending requests)   CO-3: heap priority queue, searching, sorting
// CO-5: graph (road network) + Dijkstra route selection
// Build: g++ -std=c++17 -Wall -o flood main.cpp    Run: ./flood   (or ./flood --demo)

#include <algorithm>
#include <climits>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

const int INF = INT_MAX;
const char* SUPPLY[3] = {"Medicine", "Water", "Food"};  // allocation order = essential first

// ===================== Module 1: records =====================
struct Camp    { int id; string name; int families; int urgency; int need[3]; };
struct Request { int campId; int urgency; int families; int need[3]; };
struct Vehicle { string name; int cap; int left; };
struct Result  { string camp; int km; string status; int given[3]; string vehicles; string route; };

// ===================== Module 2: linked-list queue (CO-2) =====================
struct Node { Request r; Node* next; };
class RequestQueue {
    Node *head = nullptr, *tail = nullptr;
    int n = 0;
public:
    void enqueue(const Request& r) {
        Node* p = new Node{r, nullptr};
        if (tail) tail->next = p; else head = p;
        tail = p; n++;
    }
    bool dequeue(Request& out) {
        if (!head) return false;
        Node* p = head; out = p->r; head = p->next;
        if (!head) tail = nullptr;
        delete p; n--; return true;
    }
    int size() const { return n; }
    ~RequestQueue() { Request t; while (dequeue(t)); }
};

// ===================== Module 3: max-heap priority queue (CO-3) =====================
struct HeapItem { int score; int campId; };
class CampHeap {
    vector<HeapItem> a;
public:
    bool empty() const { return a.empty(); }
    void push(HeapItem x) {
        a.push_back(x);
        int i = (int)a.size() - 1;
        while (i > 0 && a[(i - 1) / 2].score < a[i].score) { swap(a[i], a[(i - 1) / 2]); i = (i - 1) / 2; }
    }
    HeapItem pop() {
        HeapItem top = a[0];
        a[0] = a.back(); a.pop_back();
        int i = 0, n = (int)a.size();
        while (true) {
            int l = 2 * i + 1, r = l + 1, m = i;
            if (l < n && a[l].score > a[m].score) m = l;
            if (r < n && a[r].score > a[m].score) m = r;
            if (m == i) break;
            swap(a[i], a[m]); i = m;
        }
        return top;
    }
};

// ===================== Module 4: road graph + Dijkstra (CO-5) =====================
struct Edge { int to, km; bool blocked; };
class RoadGraph {
    vector<vector<Edge>> adj;
public:
    explicit RoadGraph(int n) : adj(n) {}
    void addRoad(int u, int v, int km) { adj[u].push_back({v, km, false}); adj[v].push_back({u, km, false}); }
    bool setBlocked(int u, int v, bool b) {
        bool found = false;
        for (auto& e : adj[u]) if (e.to == v) { e.blocked = b; found = true; }
        for (auto& e : adj[v]) if (e.to == u) e.blocked = b;
        return found;
    }
    void shortest(int src, vector<int>& dist, vector<int>& prev) const {
        dist.assign(adj.size(), INF); prev.assign(adj.size(), -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[src] = 0; pq.push({0, src});
        while (!pq.empty()) {
            pair<int,int> top = pq.top(); pq.pop();
            int d = top.first, u = top.second;
            if (d > dist[u]) continue;
            for (const Edge& e : adj[u]) {
                if (e.blocked) continue;                       // flooded road/bridge is skipped
                if (d + e.km < dist[e.to]) { dist[e.to] = d + e.km; prev[e.to] = u; pq.push({dist[e.to], e.to}); }
            }
        }
    }
    void print(const vector<string>& names) const {
        for (size_t u = 0; u < adj.size(); u++)
            for (const Edge& e : adj[u]) if ((int)u < e.to)
                cout << "  " << names[u] << " <-> " << names[e.to] << " (" << e.km << " km) "
                     << (e.blocked ? "[BLOCKED]" : "[open]") << "\n";
    }
};

// ===================== Module 5: relief system (allocation + display) =====================
class ReliefSystem {
    vector<string> names;     // node 0 = depot, 1..N = camps
    vector<Camp> camps;       // kept sorted by id -> binary search works
    vector<Vehicle> fleet;
    int stock[3];
    RoadGraph roads;
    RequestQueue pending;

    int totalNeed(const Camp& c) const { return c.need[0] + c.need[1] + c.need[2]; }
    int capLeft() const { int s = 0; for (auto& v : fleet) s += v.left; return s; }
    int score(const Camp& c) const { return c.urgency * 1000 + c.families; }  // urgency first, then families

    void load(int units, string& log) {                       // fill the vehicle with most free space first
        while (units > 0) {
            Vehicle* best = &fleet[0];
            for (auto& v : fleet) if (v.left > best->left) best = &v;
            int take = min(units, best->left);
            if (take <= 0) break;
            best->left -= take; units -= take;
            log += best->name + "(" + to_string(take) + ") ";
        }
    }
    string routeText(int dst, const vector<int>& prev) const {
        vector<int> p;
        for (int v = dst; v != -1; v = prev[v]) p.push_back(v);
        reverse(p.begin(), p.end());
        string s;
        for (size_t i = 0; i < p.size(); i++) s += (i ? " -> " : "") + names[p[i]];
        return s;
    }
public:
    ReliefSystem() : roads(7) {
        names = {"Hubballi Depot", "Belagavi", "Bagalkot", "Raichur", "Madikeri", "Karwar", "Shivamogga"};
        camps = {{1, "Belagavi",   450, 5, {20, 50, 40}}, {2, "Bagalkot",   300, 4, {10, 40, 30}},
                 {3, "Raichur",    200, 2, {5, 25, 20}},  {4, "Madikeri",   350, 5, {25, 30, 35}},
                 {5, "Karwar",     150, 3, {8, 20, 15}},  {6, "Shivamogga", 250, 1, {5, 15, 15}}};
        fleet = {{"V1", 80, 80}, {"V2", 60, 60}, {"V3", 40, 40}};
        stock[0] = 50; stock[1] = 120; stock[2] = 100;
        int r[][3] = {{0,1,100},{0,2,110},{0,3,190},{0,5,150},{0,6,140},{1,2,120},{1,5,130},{2,3,150},{6,4,170},{5,6,200}};
        for (auto& e : r) roads.addRoad(e[0], e[1], e[2]);
    }

    int findCamp(int id) const {                              // binary search on sorted ids (CO-3)
        int lo = 0, hi = (int)camps.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (camps[mid].id == id) return mid;
            if (camps[mid].id < id) lo = mid + 1; else hi = mid - 1;
        }
        return -1;
    }
    int findByName(string key) const {                        // linear search by name
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        for (size_t i = 0; i < camps.size(); i++) {
            string n = camps[i].name; transform(n.begin(), n.end(), n.begin(), ::tolower);
            if (n == key) return (int)i;
        }
        return -1;
    }
    void showCamp(const Camp& c) const {
        cout << " [" << c.id << "] " << left << setw(11) << c.name << " families=" << setw(4) << c.families
             << " urgency=" << c.urgency << " score=" << score(c)
             << " need(Med/Water/Food)=" << c.need[0] << "/" << c.need[1] << "/" << c.need[2] << "\n";
    }
    void showCampAt(int i) const { showCamp(camps[i]); }
    void showCamps() const {                                  // sort by priority, highest first (CO-3)
        vector<Camp> v = camps;
        sort(v.begin(), v.end(), [&](const Camp& a, const Camp& b) { return score(a) > score(b); });
        cout << "Camps by priority:\n";
        for (auto& c : v) showCamp(c);
    }
    void showStatus() const {
        cout << "Stock -> Medicine:" << stock[0] << " Water:" << stock[1] << " Food:" << stock[2] << "\n";
        cout << "Fleet -> "; for (auto& v : fleet) cout << v.name << "(cap " << v.cap << ") ";
        cout << "\nPending emergency requests: " << pending.size() << "\nRoads:\n";
        roads.print(names);
    }
    void addRequest(int campId, int urgency, int families, int med, int water, int food) {
        if (findCamp(campId) < 0) { cout << "No such camp id.\n"; return; }
        pending.enqueue({campId, urgency, families, {med, water, food}});
        cout << "Emergency request queued for " << camps[findCamp(campId)].name << ".\n";
    }
    void blockRoad(int u, int v, bool b) {
        if (!roads.setBlocked(u, v, b)) { cout << "No direct road between those nodes.\n"; return; }
        cout << names[u] << " <-> " << names[v] << (b ? " marked BLOCKED.\n" : " reopened.\n");
    }
    void restock(int med, int water, int food) { stock[0] += med; stock[1] += water; stock[2] += food; }

    void dispatch() {
        Request q; int applied = 0;                           // 1. apply queued emergency requests (FIFO)
        while (pending.dequeue(q)) {
            Camp& c = camps[findCamp(q.campId)];
            c.urgency = max(c.urgency, q.urgency); c.families += q.families;
            for (int t = 0; t < 3; t++) c.need[t] += q.need[t];
            applied++;
        }
        CampHeap heap;                                        // 2. rank camps that still need supplies
        for (auto& c : camps) if (totalNeed(c) > 0) heap.push({score(c), c.id});
        vector<int> dist, prev; roads.shortest(0, dist, prev); // 3. routes from depot on current road status
        for (auto& v : fleet) v.left = v.cap;                 // vehicles are back at the depot
        cout << "\n=== Dispatch round (" << applied << " queued request(s) applied) ===\n";
        if (heap.empty()) { cout << "All camps are fully supplied.\n"; return; }

        vector<Result> out;
        while (!heap.empty()) {                               // 4. serve in priority order
            Camp& c = camps[findCamp(heap.pop().campId)];
            Result r{c.name, dist[c.id], "", {0, 0, 0}, "", ""};
            if (dist[c.id] == INF) {
                r.status = "UNREACHABLE - deferred";
            } else {
                r.route = routeText(c.id, prev);
                for (int t = 0; t < 3; t++) {
                    int give = min({c.need[t], stock[t], capLeft()});
                    if (give > 0) { load(give, r.vehicles); c.need[t] -= give; stock[t] -= give; r.given[t] = give; }
                }
                int got = r.given[0] + r.given[1] + r.given[2];
                r.status = totalNeed(c) == 0 ? "SERVED" : (got > 0 ? "PARTIAL" : "NOT SERVED (no capacity/stock)");
            }
            out.push_back(r);
        }
        for (size_t i = 0; i < out.size(); i++) {
            const Result& r = out[i];
            cout << i + 1 << ". " << r.camp << " - " << r.status << "\n";
            if (r.km != INF) cout << "   route: " << r.route << " (" << r.km << " km)\n"
                                  << "   delivered Med/Water/Food: " << r.given[0] << "/" << r.given[1] << "/" << r.given[2]
                                  << "  vehicles: " << (r.vehicles.empty() ? "-" : r.vehicles) << "\n";
        }
        cout << "Remaining stock -> Medicine:" << stock[0] << " Water:" << stock[1] << " Food:" << stock[2] << "\n";
    }
    int nodeCount() const { return (int)names.size(); }
    const vector<string>& nodeNames() const { return names; }
};

// ===================== Test scenario (covers the proposal's test cases) =====================
void demo() {
    ReliefSystem s;
    cout << "--- TEST 1: high-priority camps, limited vehicle capacity, insufficient supplies ---";
    s.showCamps(); s.dispatch();
    cout << "\n--- TEST 2: Hubballi-Belagavi bridge and Shivamogga-Madikeri road blocked; new emergency at Raichur ---\n";
    s.blockRoad(0, 1, true); s.blockRoad(6, 4, true);
    s.addRequest(3, 5, 100, 10, 10, 10); s.addRequest(1, 4, 50, 5, 5, 5); s.restock(40, 60, 60);
    s.dispatch();
    cout << "\n--- TEST 3: Madikeri road reopened ---\n";
    s.blockRoad(6, 4, false); s.dispatch();
}

// ===================== Menu (data input + display) =====================
int main(int argc, char** argv) {
    if (argc > 1 && string(argv[1]) == "--demo") { demo(); return 0; }
    ReliefSystem s;
    int ch = -1;
    while (ch != 0) {
        cout << "\n1 Show camps by priority   2 Search camp   3 Add emergency request\n"
                "4 Block/unblock road       5 Run dispatch   6 Status & roads\n"
                "7 Add stock                8 Run test scenario   0 Exit\nChoice: ";
        if (!(cin >> ch)) { if (cin.eof()) break; cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (ch == 1) s.showCamps();
        else if (ch == 2) {
            string key;
            cout << "Camp id or name: ";
            cin >> ws;
            getline(cin, key);
            if (key.empty()) {
                cout << "Search value cannot be empty.\n";
                continue;
            }
            bool numeric = true;
            for (unsigned char ch2 : key) {
                if (!isdigit(ch2)) { numeric = false; break; }
            }
            int i = -1;
            if (numeric) {
                try { i = s.findCamp(stoi(key)); }
                catch (...) { i = -1; }
            } else {
                i = s.findByName(key);
            }
            if (i < 0) cout << "Camp not found.\n";
            else { cout << "Found:\n"; s.showCampAt(i); }
        }
        else if (ch == 3) {
            int id, u, f, m, w, fo;
            cout << "Camp id, urgency(1-5), extra families, medicine, water, food: ";
            if (cin >> id >> u >> f >> m >> w >> fo) s.addRequest(id, u, f, m, w, fo);
        }
        else if (ch == 4) {
            int u, v, b; cout << "Node a, node b (0=Depot,1-6=camps), 1=block 0=open: ";
            if (cin >> u >> v >> b && u >= 0 && v >= 0 && u < s.nodeCount() && v < s.nodeCount()) s.blockRoad(u, v, b == 1);
        }
        else if (ch == 5) s.dispatch();
        else if (ch == 6) s.showStatus();
        else if (ch == 7) { int m, w, f; cout << "Medicine, water, food to add: "; if (cin >> m >> w >> f) s.restock(m, w, f); }
        else if (ch == 8) demo();
    }
    return 0;
}
