#include <iostream>
#include <vector>
#include <array>

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
    IMPLEMENT_CTORS(Organism)
    Organism (size_t position) : position(position) {}
    virtual ~Organism () {}

    virtual bool isAnt () const = 0;
    virtual void move (Simulation&) = 0;

    void setPos (size_t pos) { position = pos; }
};

class Ant : public Organism {
public:
    IMPLEMENT_CTORS(Ant)
    Ant (size_t position) : Organism(position) {}
    ~Ant () {}

    bool isAnt () const override { return true; }
    void move (Simulation&) override;
};

class Doodlebug : public Organism {
    size_t timeSinceLastMeal = 0;
public:
    IMPLEMENT_CTORS(Doodlebug)
    Doodlebug (size_t position) : Organism(position) {}
    ~Doodlebug () {}

    bool isAnt () const override { return false; }
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
        cells((width) * (height), nullptr),
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
            Organism*& from = cell(pos);
            Organism*& to   = cell(target);

            assert(from != nullptr && to == nullptr);
            from->setPos(pos);
            std::swap(from, to);
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

    bool move (size_t pos) {
        for (int dir : randomizedDirections()) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            // std::cout << pos / height << ", " << target / height << '\n';
            if (bounded(target) 
                && (pos / height) == (target / height)
                && cell(target) == nullptr && move(pos, target)) {
                return true;
            }
        }
        return false;
    }
    bool kill (size_t pos) {
        assert(bounded(pos));
        if (Organism*& organism = cell(pos)) {
            if (organism->isAnt()) {
                assert(antPopulation > 0);
                --antPopulation;
            } else {
                assert(doodlebugPopulation > 0);
                --doodlebugPopulation;
            }
            delete organism;
            organism = nullptr;
            return true;
        } else return false;
    }
    bool eat (size_t pos) {
        assert(bounded(pos));
        for (int dir : randomizedDirections()) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            if (!bounded(target)) {
                continue;
            }
            Organism*& organism = cell(target);
            if (organism && organism->isAnt()) {
                bool ok = kill(target) && move(pos, target);
                assert(ok);
                return true;
            }
        }
        return false;
    }
    size_t findSpawnLocation (size_t pos) {
        assert(bounded(pos));
        for (auto dir : directions) {
            size_t target = static_cast<size_t>(static_cast<int>(pos) + dir);
            if (cell(target) == nullptr) {
                return target;
            }
        }
        return size();
    }
    bool spawnAnt (size_t pos) {
        pos = findSpawnLocation(pos);
        if (bounded(pos)) {
            assert(cell(pos) == nullptr);
            cell(pos) = new Ant(pos);
            ++antPopulation;
            return true;
        } else return false;
    }
    bool spawnDoodlebug (size_t pos) {
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
    void spawnAnt       () { spawn<Ant>();       ++antPopulation; }
    void spawnDoodlebug () { spawn<Doodlebug>(); ++doodlebugPopulation; }

    void spawnAnts       (size_t n) { while (n --> 0) { spawnAnt(); } }
    void spawnDoodlebugs (size_t n) { while (n --> 0) { spawnDoodlebug(); } }

    void simulate () {
        organisms.clear();
        for (auto& organism : cells) {
            if (organism != nullptr) {
                organisms.push_back(organism);
            }
        }
        for (auto& organism : organisms) {
            organism->move(*this);
        }
    }
    void display (std::ostream& os) {
        for (size_t i = 0; i < size(); ++i) {
            assert(bounded(i));
            auto& organism = cell(i);
            os << (organism == nullptr ? ' ' : 
                organism->isAnt() ? 'X' : 'O');
            if ((i % width) == 0) {
                os << '\n';
            }
        }
    }
};

void Ant::move (Simulation& simulation) {
    simulation.move(position);
    if ((++lifetime % 3) == 0) {
        simulation.spawnAnt(position);
    }
}

void Doodlebug::move (Simulation& simulation) {
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

void clearScreen () {}

int main () {
    Simulation simulation { 20, 20 };
    simulation.spawnDoodlebugs(5);
    simulation.spawnAnts(100);

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
    assert(simulation.size() == 400);



    size_t step  = 0;
    while (true) {
        clearScreen();
        std::cout << "Running simulation: "
            << "step = " << step++ << ", "
            << simulation.numAnts() << " ant(s), "
            << simulation.numBugs() << " bug(s), "
            << "pop load = " << simulation.popLoad() << '\n';
        simulation.display(std::cout);

        // Early exit conditions
        if (simulation.popLoad() == 0) {
            std::cout << "Ending simulation, no life remaining\n";
            return 1;
        } 
        if (simulation.numBugs() == 0 && simulation.popLoad() > 0.7) {
            std::cout << "Ending simulation, no doodlebugs left\n";
            return 2;
        }

        // std::cout << "[ waiting for input, enter to continue, 'q' to exit ]\n";
        // char input = getchar();
        // if (input == 'q' || input == 'Q') {
        //     return 0;
        // } else {
            simulation.simulate();
        // }
    }
    return -1;
}
