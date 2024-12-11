# Dynamic Memory Allocator Simulator

A C++ project to simulate and compare memory allocation techniques in operating systems, including First-Fit, Best-Fit, and Worst-Fit. This simulator allows users to visualize how these algorithms work and evaluate their efficiency in terms of memory usage and fragmentation.

---

## 🚀 Features
1. **Dynamic Memory Partitioning:**  
   - Users can input memory partition sizes and allocation requests at runtime.
2. **Multiple Allocation Techniques:**  
   - First-Fit  
   - Best-Fit  
   - Worst-Fit
3. **Dynamic Algorithm Selection:**  
   - Users can switch between allocation techniques during runtime.
4. **Graphical Representation:**  
   - Memory blocks are displayed in a visual format (e.g., tables or colored bars) showing their allocation status.
5. **Deallocation Support:**  
   - Frees up allocatedPartitions memory to simulate real-world usage scenarios.
6. **Comparison and Evaluation:**  
   - Automatically evaluates and suggests the most efficient algorithm based on memory usage and fragmentation.

---

## 🖥️ Project Demo
*Coming Soon!*  

---

## 📂 Project Structure
- **`main.cpp`**: Contains the entry point and high-level logic.  
- **`allocator.cpp` and `allocator.h`**: Implements memory allocation algorithms.  
- **`visualizer.cpp` and `visualizer.h`**: Manages graphical/console representation.  
- **`utils.cpp` and `utils.h`**: Helper functions for memory operations and user input.  

---

## 📊 Algorithms & Data Structures
*To be added*  
(Include details about the algorithms used and their time complexity.)

---

## 🛠️ Requirements
1. **C++ Compiler**: Ensure you have a compatible C++ compiler (e.g., GCC or Clang).  
2. **Development Environment**: Any IDE or text editor (e.g., Visual Studio, Code::Blocks, VS Code).  
3. **Terminal with Color Support**: To enhance the visual representation.

---

## 📚 Usage Instructions
1. Clone the repository:  
   ```bash
   git clone https://github.com/yourusername/Dynamic-Memory-Allocator-Simulator.git
   ```
2. Customize CMAKE file 
    ```cmake
   cmake_minimum_required(VERSION 3.30)
   project(Dynamic_Memory_Allocator_Simulator)
   
   set(CMAKE_CXX_STANDARD 23)
   
   include_directories(include)
   include_directories(include/Allocation)
   
   add_executable(Dynamic_Memory_Allocator_Simulator
      main.cpp
      src/UI.cpp
      src/Application.cpp
      src/ConsoleHandler.cpp
      src/Allocation/FirstFit.cpp
      src/Allocation/BestFit.cpp
      src/Allocation/WorstFit.cpp
   )
   
   add_definitions(-D %USER_ENV_DEFINITION%)
   ```
3. Navigate to the project directory and compile:  
   ```bash
   cd Dynamic-Memory-Allocator-Simulator
   g++ main.cpp allocator.cpp visualizer.cpp utils.cpp -o memory_simulator
   ```
4. Run the program:  
   ```bash
   ./memory_simulator
   ```

---

## ✨ Future Improvements
- Add support for more allocation techniques (e.g., Next-Fit).  
- Integrate GUI-based visualization.  
- Include benchmarking for larger memory sets.

---

## 💡 Contributions
Contributions are welcome! Please create an issue or submit a pull request if you want to add a feature or improve the code.

---

## 📜 License
This project is licensed under the [MIT License](LICENSE).

---
