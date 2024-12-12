![banner](https://github.com/user-attachments/assets/a86e5611-a3ed-41e3-8d54-f591e593bc5d)

---

## ✨ Introduction

Memory management is a fundamental aspect of operating systems, crucial for optimizing performance and resource
utilization. This project, **Dynamic-Memory-Allocator-Simulator**, is a C++ application designed to simulate and compare
different memory allocation techniques: **First-Fit**, **Best-Fit**, and **Worst-Fit**. By visualizing how these
algorithms allocate and deallocate memory, users can gain a deeper understanding of their memory usage and fragmentation efficiency.

---

## 🚀 Features

- **Dynamic Technique Selection**: Choose between First-Fit, Best-Fit, and Worst-Fit allocation techniques at runtime.
- **Customizable Memory Partitions**: Enter and modify memory partition sizes dynamically during execution.
- **Visual Representation**: View memory blocks and their allocation status through tables and color-coded indicators.
- **Performance Metrics**: Measure and compare the efficiency of each allocation technique regarding memory usage and
  fragmentation.
- **Deallocation Support**: Simulate real-world scenarios by freeing up allocated memory blocks.

---

## 🖥️ Project Demo

https://github.com/user-attachments/assets/2acf91f3-b76e-4730-af27-742d35908895

---

## 📚 Installation

### Prerequisites

- **C++ Compiler**: Ensure you have a C++17 compatible compiler installed (e.g., `g++`, `clang++`).
- **CMake**: Recommended for building the project.
- **Windows OS**: The current implementation utilizes Windows-specific libraries for console handling.

### Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/3bbaas/Dynamic-Memory-Allocator-Simulator.git
   ```
2. **Configure Cmake file**
   ```cmake
   cmake_minimum_required(VERSION 3.30)
   project(Dynamic_Memory_Allocator_Simulator)
   
   set(CMAKE_CXX_STANDARD 23)
   
   include_directories(include)
   include_directories(include/Allocation)
   
   add_executable(Dynamic_Memory_Allocator_Simulator
   src/Allocation/BestFit.cpp
   src/Allocation/FirstFit.cpp
   src/Allocation/WorstFit.cpp
   src/Application.cpp
   src/ConsoleHandler.cpp
   src/UI.cpp
   main.cpp)
   ```
3. **Navigate to the Project Directory**
   ```bash
   cd Dynamic-Memory-Allocator-Simulator
   ```

4. **Build the Project**
    - Using Cmake
       ```bash
       mkdir build
       cd build
       cmake ..
       make
       ```
    - Alternatively, compile manually:
      ```bash
      g++ main.cpp src/*.cpp src/Allocation/*.cpp -o MemoryAllocatorSimulator 
      ```
5. **Run the Application**
   ```bash
   ./MemoryAllocatorSimulator
   ```

---

## Usage

Upon running the application, you will be greeted with a dynamic console interface where you can:

1. Update Partition Values (Admins Only)

   - Requires admin credentials to modify memory partition sizes.

2. Use Default Partitions

   - Proceed with predefined memory partitions or enter custom ones.

3. Choose Allocation Technique

   - Select between First-Fit, Best-Fit, and Worst-Fit to allocate memory for processes.

4. Allocate and Deallocate Processes

   - Add new processes with specific memory requirements.
   - Free up memory by deallocating existing processes.

5. Visualize Memory Allocation

   - View memory blocks as tables with color-coded statuses indicating allocated or free spaces.

---

## 📂 Project Structure

```text
    Dynamic-Memory-Allocator-Simulator/
    ├── data/
    │   └── partitions
    ├── include/
    │   ├── Allocation/
    │   │   ├── AllocationTechnique.h
    │   │   ├── BestFit.h
    │   │   ├── FirstFit.h
    │   │   └── WorstFit.h
    │   ├── Application.h
    │   ├── ColorCode.h
    │   ├── ConsoleHandler.h
    │   └── UI.h
    ├── src/
    │   ├── Allocation/
    │   │   ├── BestFit.cpp
    │   │   ├── FirstFit.cpp
    │   │   └── WorstFit.cpp
    │   ├── Application.cpp
    │   ├── ConsoleHandler.cpp
    │   └── UI.cpp
    ├── main.cpp
    ├── README.md
    └── LICENSE
```
- `main.cpp`: Initializes the application.
- `include/`: Header files containing class declarations.
- `Allocation/`: Contains different allocation technique classes.
- `src/`: Source files containing class definitions and implementations.
- `data/`: Directory for storing memory partition data.

---

## 🖥️ Demo

---

## 🛠️ Requirements

1. **C++ Compiler**: Ensure you have a compatible C++ compiler (e.g., GCC or Clang).
2. **Development Environment**: Any IDE or text editor (e.g., CLion, Code::Blocks, VS Code).
3. **Terminal with Color Support**: To enhance the visual representation.

---

## 💡 Contributions

Contributions are welcome! Please create an issue or submit a pull request if you want to add a feature or improve the
code.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---
