# OS Memory Management Simulator

A modular **C++ simulation of an Operating System’s Memory Management Unit (MMU)**.  
This project models how logical memory requests are translated and managed under real hardware constraints using **dynamic allocation strategies, virtual memory paging, and cache hierarchies**.

The simulator focuses on **clarity, correctness, and OS-level realism**, making it suitable for academic evaluation, demonstrations, and systems learning.

---

## Project Demonstration

Watch the complete 3-minute walkthrough covering all implemented features:

[![Memory Simulator Demo](https://img.youtube.com/vi/AKx8AxRXyiI/0.jpg)](https://youtu.be/AKx8AxRXyiI)

**Note:**  
The video demonstrates:
- Physical memory allocation strategies  
- Buddy System split and merge logic  
- Virtual to physical address translation  
- Cache behavior including Modified (Dirty) bit handling  

---

## Key Features

### 1. Physical Memory Allocation

Implements multiple dynamic partitioning strategies to handle fragmentation:

- **First Fit**  
  Allocates the first available memory block large enough for the request.

- **Best Fit**  
  Allocates the smallest available block that satisfies the request to reduce wastage.

- **Worst Fit**  
  Allocates from the largest available block to preserve medium-sized free spaces.

- **Buddy System**  
  - Power-of-two memory allocation  
  - Recursive block splitting  
  - Efficient block merging using XOR-based buddy identification  

---

### 2. Virtual Memory and Paging

Simulates a paged virtual memory system:

- Virtual address decomposition into:
  - Virtual Page Number (VPN)
  - Offset
- Page table mapping:
  - VPN to Physical Frame Number (PFN)
  - Valid bit tracking
- Page fault detection for:
  - Invalid pages
  - Out-of-bounds accesses

---

### 3. Cache Subsystem

Models a realistic L1 cache:

- Set-associative cache architecture
- LRU (Least Recently Used) replacement policy
- Modified (Dirty) bit per cache line to track write operations

---

## Build and Usage

### Prerequisites

- G++ compiler (C++11 or higher)
- Make

---

### Compilation

```bash
make
---

### Execution

```bash
./memsim
```

---

## Testing and Verification

To allow evaluation without inspecting source code, predefined test artifacts are provided:

* **Sample Input**
  `tests/sample_input.txt`
  Contains command sequences testing:

  * Allocation strategies
  * Buddy System operations
  * Paging and cache accesses

* **Expected Output**
  `tests/expected_output.txt`
  Contains reference logs and traces for correctness verification.

---

## Project Structure

```
.
├── src/        # Core implementation files (.cpp)
├── include/    # Header files (.h)
├── docs/       # Design documentation
├── tests/      # Sample inputs and expected outputs
├── Makefile
└── README.md
```

---

## Design Highlights

* Modular architecture with clear separation between:

  * Physical memory management
  * Virtual memory management
  * Cache subsystem
* Traceable execution using logs
* Designed to closely reflect real OS memory management behavior

---

## Learning Outcomes

This project demonstrates understanding of:

* Memory allocation strategies in operating systems
* Virtual memory and paging mechanisms
* Cache organization and replacement policies
* Trade-offs between performance, fragmentation, and memory utilization

---

## Author

**Jay Jain**
Department of Chemical Engineering
Indian Institute of Technology Roorkee
Roll Number: 23112045
