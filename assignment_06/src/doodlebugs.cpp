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

class Organism {
protected:
    size_t position = 0;
    size_t lifetime = 0;
public:
    bool   dead     = false;
    IMPLEMENT_CTORS(Organism)
    Organism (size_t position) : position(position) {}
    virtual ~Organism () {}

    virtual bool isAnt () const = 0;
    virtual void move (Simulation&) = 0;

    void setPos (size_t pos) { DEBUG_ONE("Organism::setPos()") position = pos; }
    size_t pos () const { return position; }
};

class Ant : public Organism {
public:
    IMPLEMENT_CTORS(Ant)
    Ant (size_t position) : Organism(position) { DEBUG_ONE("Ant()"); }
    ~Ant () { DEBUG_ONE("~Ant()");}

    bool isAnt () const override { DEBUG_ONE("Ant::isAnt()") return true; }
    void move (Simulation&) override;
};

class Doodlebug : public Organism {
    size_t timeSinceLastMeal = 0;
public:
    IMPLEMENT_CTORS(Doodlebug)
    Doodlebug (size_t position) : Organism(position) { DEBUG_ONE("Doodlebug()"); }
    ~Doodlebug () { DEBUG_ONE("~Doodlebug()"); }

    bool isAnt () const override { DEBUG_ONE("Doodlebug::isAnt()") return false; }
    void move (Simulation&) override;
};

class Simulation {
    size_t                  width;
    size_t                  height;
    std::vector<Organism*>  cells;
    std::vector<Organism*>  organisms;  // temp array
    std::array<int, 4>      directions;
    size_t                  antPopulation = 0;
    size_t                  doodlebugPopulation = 0;
public:
    IMPLEMENT_CTORS(Simulation)
    Simulation (size_t width, size_t height) 
        : width(width), height(height),
        cells(width * height, nullptr),
        directions { -1, +1, -(int)width, +(int)width }
    {}
    size_t size () const { return width * height; }
    bool bounded (size_t pos) const { return pos < size(); }

    size_t population () const { return antPopulation + doodlebugPopulation; }
    double popLoad () const { return static_cast<double>(population()) / static_cast<double>(size()); }

    size_t numAnts () const { return antPopulation; }
    size_t numBugs () const { return doodlebugPopulation; }


    Organism*& cell (size_t pos) {
        assert(bounded(pos));
        return cells[pos];
    }
    bool move (size_t pos, size_t target) {
        if (bounded(target)) {
            assert(bounded(pos));
            assert(cell(pos) != nullptr && cell(target) == nullptr);
            assert(cell(pos)->pos() == pos);

            std::swap(cell(pos), cell(target));
            cell(target)->setPos(target);

            assert(cell(pos) == nullptr);
            assert(cell(target) != nullptr);
            assert(cell(target)->pos() == target);
            return true;
        } else return false;
    }

protected:
    template <typename T, size_t N>
    class RandomArrayIterator {
        std::array<T, N>* array = nullptr;
        int               n = 0;
    public:
        typedef RandomArrayIterator<T,N> This;
        RandomArrayIterator () {}
        RandomArrayIterator (std::array<T, N>* array)
            : array(array), n(N) { std::swap((*array)[n-1], (*array)[rand() % n]); }
        RandomArrayIterator (const This&) = default;
        This& operator= (const This&) = default;

        operator bool () const { return n > 0; }
        T& operator*  () { assert(*this); return (*array)[n - 1];  }
        T* operator-> () { assert(*this); return &(*array)[n - 1]; }
        This& operator++ () {
            if (--n > 1) {
                std::swap((*array)[n - 1], (*array)[rand() % n]);
            }
            return *this;
        }
        friend bool operator== (const This& a, const This& b) {
            return (!a && !b) || (a.n == b.n);
        }
    };
    template <typename T, size_t N>
    struct RandomArrayIterable {
        std::array<T, N>& array;
    public:
        RandomArrayIterable (std::array<T,N>& array)
            : array(array) {}

        RandomArrayIterator<T, N>       begin () { return { &array }; }
        RandomArrayIterator<T, N>       end   () { return {}; }
        RandomArrayIterator<const T, N> begin () const { return { &array }; }
        RandomArrayIterator<const T, N> end   () const { return {}; }
    };
public:
    RandomArrayIterable<int, 4> randomizedDirections () { return { directions }; }

    bool canMove (size_t pos, size_t target) {
        if (!bounded(target)) return false; // must be bounded
        int dx = (pos % width) - (target % width);
        int dy = (pos / width) - (target / width);
        return (dx == 0) != (dy == 0); // can move along x axis or y axis but not both
    }

    bool move (size_t pos) {
        DEBUG_SCOPE("Simulation::move(size_t)")
        Organism* organism = cell(pos);
        assert(organism->pos() == pos);
        for (int dir : randomizedDirections()) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            // std::cout << pos / height << ", " << target / height << '\n';
            if (canMove(pos, target)
                && cell(target) == nullptr 
                && move(pos, target)
            ) {
                assert(organism->pos() == target);
                assert(cell(pos)    == nullptr);
                assert(cell(target) == organism);
                return true;
            }
        }
        assert(organism->pos() == pos);
        assert(cell(pos) == organism);
        return false;
    }
    bool kill (size_t pos) {
        DEBUG_SCOPE("Simulation::kill(size_t)")
        assert(bounded(pos));
        assert(cell(pos) != nullptr);
        assert(cell(pos)->pos() == pos);
        if (Organism*& organism = cell(pos)) {
            if (organism->isAnt()) {
                assert(antPopulation > 0);
                --antPopulation;
            } else {
                assert(doodlebugPopulation > 0);
                --doodlebugPopulation;
            }
            organism->dead = true;
            organism = nullptr;
            assert(cell(pos) == nullptr);
            return true;
        } else return false;
    }
    bool eat (size_t pos) {
        DEBUG_SCOPE("Simulation::eat(size_t)")
        assert(bounded(pos));
        for (int dir : randomizedDirections()) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            if (canMove(pos, target)
                && cell(target) != nullptr
                && cell(target)->isAnt()
            ) {
                bool ok = kill(target) 
                       && move(pos, target);
                assert(ok);
                return true;
            }
        }
        return false;
    }
    size_t findSpawnLocation (size_t pos) {
        DEBUG_SCOPE("Simulation::findSpawnLocation(size_t)")
        assert(bounded(pos));
        for (auto dir : directions) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            if (canMove(pos, target)
                && cell(target) == nullptr
            ) {
                return target;
            }
        }
        return size();
    }
    bool spawnAnt (size_t pos) {
        DEBUG_SCOPE("Simulation::spawnAnt(size_t)")

        assert(cell(pos) && cell(pos)->isAnt());
        pos = findSpawnLocation(pos);
        if (bounded(pos)) {
            assert(cell(pos) == nullptr);
            cell(pos) = new Ant(pos);
            ++antPopulation;
            return true;
        } else return false;
    }
    bool spawnDoodlebug (size_t pos) {
        DEBUG_SCOPE("Simulation::spawnDoodlebug(size_t)")
        assert(cell(pos) && !cell(pos)->isAnt());
        pos = findSpawnLocation(pos);
        if (bounded(pos)) {
            assert(cell(pos) == nullptr);
            cell(pos) = new Doodlebug(pos);
            ++doodlebugPopulation;
            return true; 
        } else return false;
    }
private:
    template <typename T>
    void spawn () {
        DEBUG_SCOPE("Simulation::spawn<T>()")
        assert(popLoad() < 0.7);
        while (1) {
            size_t pos = static_cast<size_t>(rand()) % size();
            if (cell(pos) == nullptr) {
                cell(pos) = static_cast<Organism*>(new T(pos));
                return;
            }
        }
    }
public:
    void spawnAnt () { 
        DEBUG_SCOPE("Simulation::spawnAnt()")  
        spawn<Ant>();      
        ++antPopulation; 
    }
    void spawnDoodlebug () { 
        DEBUG_SCOPE("Simulation::spawnDoodlebug()")
        spawn<Doodlebug>(); 
        ++doodlebugPopulation; 
    }

    void spawnAnts (size_t n) { 
        DEBUG_SCOPE("Simulation::spawnAnts()")
        while (n --> 0) { 
            spawnAnt(); 
        } 
    }
    void spawnDoodlebugs (size_t n) { 
        DEBUG_SCOPE("Simulation::spawnDoodlebugs()")
        while (n --> 0) { 
            spawnDoodlebug(); 
        } 
    }

    void simulate () {
        DEBUG_SCOPE("Simulation::simulate()")
        organisms.clear();
        for (auto& organism : cells) {
            if (organism != nullptr) {
                organisms.push_back(organism);
            }
        }
        for (auto& organism : organisms) {
            if (!organism->dead) {
                organism->move(*this);
            }
        }
        for (auto& organism : organisms) {
            if (organism->dead) {
                delete organism;
            }
        }
    }
    void display (std::ostream& os) {
        DEBUG_SCOPE("Simulation::display()")
        for (size_t i = 0; i < size(); ++i) {
            assert(bounded(i));
            auto& organism = cell(i);
            os << (organism == nullptr ? ' ' : 
                !organism->isAnt() ? 'X' : 'O');
            if (((i + 1) % width) == 0) {
                os << '\n';
            }
        }
    }
};

void Ant::move (Simulation& simulation) {
    DEBUG_SCOPE("Ant::move()");
    assert(simulation.cell(position) == static_cast<Organism*>(this));
    simulation.move(position);
    if ((++lifetime % 3) == 0) {
        simulation.spawnAnt(position);
    }
}

void Doodlebug::move (Simulation& simulation) {
    DEBUG_SCOPE("Doodlebug::move()");
    assert(simulation.cell(position) == static_cast<Organism*>(this));
    if (simulation.eat(position)) {
        timeSinceLastMeal = 0;
    } else {
        simulation.move(position);
    }
    if ((++lifetime % 8) == 0) {
        simulation.spawnDoodlebug(position);
    }
    if (++timeSinceLastMeal > 3) {
        simulation.kill(position);
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

void clearScreen () {}

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
