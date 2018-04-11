#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <chrono>
#include <fstream>
#include "utility/util/mem_bench.hpp"

#if 0
struct ScopeDebugger {
    const char* msg;
    static int  indent;

    static std::ostream& writeln (std::ostream& os = std::cout) {
        os << '\n';
        for (int i = indent; i --> 0; ) {
            os << "| ";
        }
        return os;
    }

    ScopeDebugger (const char* msg) : msg(msg) {
        writeln() << msg << " begin"; ++indent;
    }
    ~ScopeDebugger () { 
        --indent;
        writeln() << msg << " end";
    }
};
int ScopeDebugger::indent = 0;
#define DEBUG_SCOPE(msg) ScopeDebugger debug ## __COUNTER__ (msg);
#define DEBUG_ONE(msg)   ScopeDebugger::writeln() << msg;
#else
#define DEBUG_SCOPE(msg)
#define DEBUG_ONE(msg)
#endif

class Simulation;

template <typename T>
struct Bitfield {
    T value = 0;
public:
    typedef T value_t;

    void clear () { value = 0; }

    template <typename U, size_t offset, size_t size>
    U getChannel () const {
        constexpr value_t mask = (1 << size) - 1;
        return static_cast<U>((value >> offset) & mask);
    }
    template <typename U, size_t offset, size_t size>
    void setChannel (U v) {
        constexpr value_t mask = (1 << size) - 1;
        value &= ~(mask << offset);
        value |= (static_cast<value_t>(v) & mask) << offset;
    }
};
#define DECL_BIT_PROPERTY(name, type, offset, size) \
    type name () const { return getChannel<type, offset, size>(); } \
    void name (type v) { setChannel<type, offset, size>(v); }

typedef unsigned char byte_t;

enum class CellId {
    BORDER = 0, EMPTY, PREDATOR, PREY
};
struct BitfieldCell : public Bitfield<byte_t> {
    DECL_BIT_PROPERTY(id,       CellId, 0, 2)
    DECL_BIT_PROPERTY(hunger,   size_t, 2, 2)
    DECL_BIT_PROPERTY(age,      size_t, 4, 4)
};

struct Cell : public BitfieldCell {
    Cell () {}
    Cell (Cell&& other) 


    Cell (const Cell& other) : value(other.value) {}
    Cell& operator= (const Cell& other) { value = other.value; }


    bool isEmpty    () { return id() == CellId::EMPTY; }
    bool isPredator () { return id() == CellId::PREDATOR; }
    bool isPrey     () { return id() == CellId::PREY; }

    void create (CellId cellId) { 
        clear(); id(cellId); 
    }
    void kill () { 
        id(CellId::EMPTY); 
    }
    bool breedCycle (size_t breedingAge) {
        auto nextAge = age() + 1;
        if (nextAge >= breedingAge) {
            return age(0), true;
        } else {
            return age(nextAge), false;
        }
    }
    void   resetHunger () { hunger(0); }
    size_t tickHunger  () {
        auto next = hunger() + 1;
        return hunger(next), next;
    }
    friend std::ostream& operator<< (std::ostream& os, const Cell& cell) {
        switch (cell.id()) {
            case CellId::BORDER: return os << 'b';
            case CellId::EMPTY:  return os << ' ';
            case CellId::PREDATOR: return os << 'X';
            case CellId::PREY: return os << '0';
            default: assert(0);
        }
    }
};

#define IS_EMPTY [](const Cell& cell) { return cell.isEmpty(); }
#define IS_PREY  [](const Cell& cell) { return cell.isPrey(); }

struct PreyActor {
    size_t breedingAge = 3;
    void simulate (Simulation& simulation, size_t cell, Cell* state);
};
struct PredatorActor {
    size_t breedingAge = 3;
    size_t starvation  = 7;

    void simulate (Simulation& simulation, size_t cell, Cell* state);
};

#define DISABLE_DEFAULT_CTOR(T) \
    T () = delete;
#define DISABLE_COPY_CTOR(T) \
    T (const T&) = delete; \
    T& operator= (const T&) = delete;
#define ENABLE_MOVE_CTOR(T) \
    T (T&&) = default; \
    T& operator= (T&&) = default;
#define IMPLEMENT_CTORS(T) \
    DISABLE_DEFAULT_CTOR(T) \
    DISABLE_COPY_CTOR(T) \
    ENABLE_MOVE_CTOR(T)


class Simulation {
    size_t                  width;
    size_t                  height;
    std::vector<Cell>       cells;
    std::vector<Cell*>      temp;
    size_t                  antPopulation = 0;
    size_t                  doodlebugPopulation = 0;

    PredatorActor           predatorActor;
    PreyActor               preyActor;
public:
    IMPLEMENT_CTORS(Simulation)
    Simulation (size_t width, size_t height) 
        : width(width + 2), height(height + 2),
        cells((width + 2) * (height + 2))
    {
        for (size_t j = 1; j < width - 1; ++j) {
            for (size_t i = 1; i < width - 1; ++i) {
                cells[j * width + i].create(CellId::EMPTY);
            }
        }
    }
    size_t size () const { return width * height; }
    // bool bounded (size_t pos) const { return pos < size(); }

    size_t population () const { return antPopulation + doodlebugPopulation; }
    double popLoad () const { return static_cast<double>(population()) / static_cast<double>(size()); }

    size_t numAnts () const { return antPopulation; }
    size_t numBugs () const { return doodlebugPopulation; }

    // Returns a random adjacent cell that matches pred (and is bounded),
    // or cell if no such cell exists 
    template <typename Pred>
    size_t findAdjacent (size_t cell, Cell* state, const Pred& pred) {
        size_t positions [4];
        size_t n = 0;

        #define TRY_MOVE(cell, borderCheck) \
        if (cell < size() && (borderCheck) && pred(state[cell])) { positions[n++] = cell; }

        TRY_MOVE(cell + 1, (cell + 1) % width != 0)
        TRY_MOVE(cell - 1, cell % width != 0)
        TRY_MOVE(cell + width, true)
        TRY_MOVE(cell - width, true)
        
        return n ?
            positions[rand() % n] :
            cell;
    }

    template <typename Pred>
    bool move (size_t& cell, Cell* state, const Pred& pred) {
        size_t adj = findAdjacent(cell, state, pred);
        if (cell != adj) {
            std::move(state[cell], state[adj]);
            cell = adj;
            return true;
        } else return false;
    }
    template <typename Pred>
    bool eat (size_t& cell, Cell* state, const Pred& pred) {
        size_t adj = findAdjacent(cell, state, pred);
        if (cell != adj) {
            state[adj].kill();
            std::move(state[cell], state[adj]);
            cell = adj;
            return true;
        } else return false;
    }
    bool spawnAdjacent (size_t cell, Cell* state) {
        size_t adj = findAdjacent(cell, state, IS_EMPTY);
        if (cell != adj) {
            state[adj].create(state[cell].id());
            return true;
        } else return false;
    }

    void spawn (CellId id) {
        assert(popLoad() < 0.7);
        while (1) {
            size_t pos = static_cast<size_t>(rand()) % size();
            if (cells[pos].isEmpty()) {
                cells[pos].create(id);
                return;
            }
        }
    }
    void spawnAnts (size_t n) { 
        DEBUG_SCOPE("Simulation::spawnAnts()")
        while (n --> 0) { 
            spawn(CellId::PREY);
        } 
    }
    void spawnDoodlebugs (size_t n) { 
        DEBUG_SCOPE("Simulation::spawnDoodlebugs()")
        while (n --> 0) { 
            spawn(CellId::PREDATOR);
        } 
    }
    template <typename Actor>
    void simulate (Actor& actor) {
        temp.clear();
        for (size_t i = 0; i < cells.size(); ++i) {
            if (cells[i].id() == actor.id()) {
                temp.push_back(i);
            }
        }
        Cell* state = &cells[0];
        for (auto& cell : temp) {
            if (cells[cell].id() == actor.id()) {
                actor.simulate(*self, cell, state);
            }
        }
    }
    void simulate () {
        simulate(predatorActor);
        simulate(PreyActor);
    }
    void display (std::ostream& os) {
        DEBUG_SCOPE("Simulation::display()")
        for (size_t i = 0; i < size(); ++i) {
            os << cells[i];
            if (((i + 1) % width) == 0) {
                os << '\n';
            }
        }
    }
};

void PreyActor::simulate (Simulation& simulation, size_t cell, Cell* state) {
    assert(state[cell].isPrey());
    simulation.move(cell, state, IS_EMPTY);
    if (state[cell].breedCycle(breedingAge)) {
        simulation.spawnAdjacent(cell, state);
    }
}

void PredatorActor::simulate (Simulation& simulation, size_t cell, Cell* state) {
    assert(state[cell].isPredator());
    if (simulation.eat(cell, state, IS_PREY)) {
        state[cell].resetHunger();
    } else {
        simulation.move(cell, state, IS_EMPTY);
    }
    if (state[cell].breedCycle(breedingAge)) {
        simulation.spawnAdjacent(cell, state);
    }
    if (state[cell].tickHunger() >= starvation) {
        state[cell].kill();
    }
}

struct Bytes {
    size_t value;
    Bytes (size_t value) : value(value) {}
    friend std::ostream& operator<< (std::ostream& os, const Bytes& bytes) {
        if (bytes.value <= 1000)                    { return os << bytes.value << "byte(s)"; }
        else if (bytes.value <= 1000 * 1000)        { return os << static_cast<double>(bytes.value) * 1e-3 << " kb"; }
        else if (bytes.value <= 1000 * 1000 * 1000) { return os << static_cast<double>(bytes.value) * 1e-6 << " mb"; }
        else                                        { return os << static_cast<double>(bytes.value) * 1e-9 << " gb"; }
    }
};
Bytes bytes (size_t value) { return { value }; }


struct Seconds {
    double value;
    Seconds (double value = 0.0) : value(value) {}
    friend std::ostream& operator<< (std::ostream& os, const Seconds& seconds) {
        if (seconds.value >= 1.0) { return os << seconds.value << "sec"; }
        else if (seconds.value >= 1e-3) { return os << seconds.value * 1e3 << " ms"; }
        else if (seconds.value >= 1e-6) { return os << seconds.value * 1e6 << " µs"; }
        else                            { return os << seconds.value * 1e9 << " ns"; }
    }
};

struct Timer {
    double& value;
    std::chrono::high_resolution_clock::time_point t0;

    Timer  (double& value) 
        : value(value), 
        t0(std::chrono::high_resolution_clock::now()) 
    {}
    ~Timer () { 
        using namespace std::chrono;
        auto t1 = high_resolution_clock::now();
        value = duration_cast<duration<double>>(t1 - t0).count();
    }
};

void clearScreen () {
    std::cout << "\033[J";
}

int main () {
    DEBUG_SCOPE("int main()")
    srand(time(nullptr));
    size_t width = 204, height = 63;
    Simulation simulation { width, height };
    // simulation.spawnDoodlebugs(5);
    // simulation.spawnAnts(100);
    simulation.spawnAnts(500);
    simulation.spawnDoodlebugs(250);

    std::cout << "Random direction iterator samples:\n";
    for (auto i = 10; i --> 0; ) {
        for (int dir : simulation.randomizedDirections()) {
            std::cout << dir << ", ";
        }
        std::cout << "\b\b\n";
    }
    std::cout << '\n';

    assert(simulation.bounded(0));
    assert(simulation.bounded(simulation.size() - 1));
    assert(!simulation.bounded(simulation.size()));
    assert(simulation.size() == width * height);

    std::chrono::high_resolution_clock::time_point t0, t1;

    using namespace std::chrono;
    Seconds simulationTime;
    Seconds displayTime;
    Seconds ioTime;

    std::ofstream summary { "log.csv" };
    summary
        << "step, "
        << "%% ants, "
        << "%% bugs, "
        << "simulation time (s), "
        << "display time (s), "
        << "user input time (s)\n";

    size_t step  = 0;
    while (true) {
        {
            Timer t (displayTime.value);
            clearScreen();
            std::cout << "Running simulation: "
                << "step = " << step++ << ", "
                << simulation.numAnts() << " ant(s), "
                << simulation.numBugs() << " bug(s), "
                << "pop load = " << simulation.popLoad() << '\n'
                << "simulation: " << simulationTime << ", " 
                << "display: " << displayTime << ", "
                << "i/o: " << ioTime << ", "
                << "\nmemory alloc / freed: " 
                    << bytes(g_memTracer.memAllocated()) << " / " << bytes(g_memTracer.memDeallocated())
                    << " (" << g_memTracer.allocCount() << " / " << g_memTracer.deallocCount() << ")\n";

            simulation.display(std::cout);
        }
        {
            summary 
                << step << ", "
                << ((double)simulation.numAnts() / (double)simulation.size()) << ", "
                << ((double)simulation.numBugs() / (double)simulation.size()) << ", "
                << simulationTime.value << ", "
                << displayTime.value << ", "
                << ioTime.value << '\n';
        }

        char input;
        {
            Timer t (ioTime.value);
            std::cout << "[ waiting for input, enter to continue, 'q' to exit ]\n";
            input = getchar(); 
        }
        
        if (input == 'q' || input == 'Q') {
            return 0;
        } else {
            Timer t (simulationTime.value);
            simulation.simulate();
        }
    }
    return -1;
}
