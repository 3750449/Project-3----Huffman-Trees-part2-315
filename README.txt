## Student Information

**Name:** Desmond Farley-Williams
**Student ID:** 008508702
**Repository:** https://github.com/3750449/Project-3----Huffman-Trees-part2-315.git

---

## Collaboration & Sources

- **cppreference.com** — consulted for `std::fstream`, `std::tolower`, `std::filesystem`
- **geeksforgeeks.org** — cross-checked C++ I/O examples and syntax

---

## Implementation Details — **Project 3, Part 2**

- This implements **Scanner → BST → PriorityQueue (vector+sort)
- It produces two files (`.tokens`, `.freq`) and prints five BST measures to `stdout`

### Files Implemented

- `Scanner.hpp` / `Scanner.cpp` — tokenization (file writer)
- `BinSearchTree.hpp` / `BinSearchTree.cpp` — word frequency for BST
- `PriorityQueue.hpp` / `PriorityQueue.cpp` — vector + sort (simulated PQ)
- `utils.hpp` / `utils.cpp` — error codes, filesystem checks, error reporting
- `main.cpp` — driver wiring modules and writing outputs
- `CMakeLists.txt` — build configuration

### Scanner

- **Normalization rules**

  - Lowercase ASCII only.
  - Tokens match: `[a–z]+` **or** `[a–z]+'[a–z]+` (apostrophes only **inside**)
  - Separators: digits, whitespace, punctuation/symbols, all hyphens/dashes, any non-ASCII byte
  - Drop leading/trailing apostrophes (e.g., `'tis` → `tis`, `rock-n-roll` → `rock`, `n`, `roll`)
  - `tokenize(vector<string>&)` → in-memory tokens
  - `tokenize(vector<string>&, path outputFile)` → calls in-memory version, writes one token per line
  - file ends with a single trailing newline (even when empty)
  - `readWord(istream&)` → scanner primitive implementing the rules

### BST (word → count)

- **Node:** `word`, `count`, `left`, `right`.
- **Insert:** `insert`, `bulkInsert` (duplicates increment count)
- **Traversal:** `inorderCollect` → `vector<pair<string,int>>` in ascending order
- **Metrics:** `height()` (empty = 0), `size()`

### PriorityQueue (vector+sort stand-in)

- Builds from BST’s `(word,count)` vector
- Sorted invariant `.freq`:
- **Primary:** count **descending** (alphabetical)

---

## Outputs

- **`<base>.tokens`**
- One token per line
- **Ends with exactly one trailing newline** (even if the input is empty)

- **`<base>.freq`**
- Each line: `std::setw(10) << count << ' ' << word << '\n'`
- Sorted by count desc, tie by word asc
- Ends with newline, including the empty case (file is a single `\n`)

### Required stdout (exact labels/order)

BST height: H
BST unique words: U
Total tokens: T
Min frequency: MIN
Max frequency: MAX

Empty input defines:

H = 0, U = 0, T = 0, MIN = 0, MAX = 0

---

## Testing & Status

### Sample run (The Bells)

BST height: 12
BST unique words: 49
Total tokens: 83
Min frequency: 1
Max frequency: 11

**Excerpt of `<base>.freq` (format + ordering):**

    11 bells
    11 the
     4 of
     3 a
     3 time
     3 tinkle
     2 from
     2 in
     2 that
     2 to
     2 with
     1 air
     1 all
     1 allan
     1 and
     1 crystalline
     1 delight
     1 edgar
     1 foretells
     1 hear
     1 heavens
     1 how
     1 icy
     1 jingling
     1 keeping
     1 melody
     1 merriment
     1 musically
     1 night
     1 oversprinkle
     1 poe
     1 rhyme
     1 runic
     1 s
     1 seem
     1 silver
     1 sledges
     1 so
     1 sort
     1 stars
     1 their
     1 they
     1 tinkling
     1 tintinnabulation
     1 twinkle
     1 wells
     1 what
     1 while
     1 world

### Empty-input test

Create `input_output/empty.txt` (0 bytes), then run. Expect:

- Stdout:

BST height: 0
BST unique words: 0
Total tokens: 0
Min frequency: 0
Max frequency: 0

- Files:

- `empty.tokens` → **exactly one newline**
- `empty.freq` → **exactly one newline**

---

## How to Compile & Run

### Plain g++

g++ -std=c++20 -Wall *.cpp -o huff_phase2
./huff_phase2 input_output/<file>.txt

mkdir build && cd build
cmake ..
make
./huff_phase2 ../input_output/<file>.txt

