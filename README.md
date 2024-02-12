# C-project-type-game
This is the final project of NTU PD 112. We design a fun game which user can practice typing ability.
#### Team Members
- **Zheng Ruiyu (R12723030)**
- **Yang Yide (R12722043)**
- **Shi Yating (B11204016)**
- **Chen Weilin (B12208033)**

#### 1. Overview
We developed a dynamic typing game aimed at improving players' typing speed and accuracy. The game interface is inspired by traditional shooting games, requiring players to complete levels of increasing difficulty. Players must quickly and accurately type words falling from the top of the screen to eliminate them before they reach the bottom, with the game's difficulty progressively increasing.

#### 2. Game Process
- **Game Instructions:** Displayed using `showinstruction()` to show game rules.
- **Game Phases:** Words drop from the top at random intervals, and players must type them to eliminate them. As the game progresses, the speed of falling words increases, and the criteria to pass levels become stricter.
- **Game Modes:** Standard, Multiple Vocabulary, and Random Speed modes, with a hidden level unlocking after passing the initial stages, offering the highest difficulty or replaying previous modes.

#### 3. System Design and Architecture
- **Programming Language:** C++ with object-oriented programming principles such as Encapsulation, Inheritance, Polymorphism, and Abstraction.
- **Key Components:** `WordManager` for managing word behaviors, `ConsoleUtility` for console interactions, and `Stage` class with subclasses for different game modes.

#### 4. Application of Skills
- Utilization of File I/O, Inheritance for game mode hierarchies, Polymorphism for stage-specific behaviors, Exception Handling for robust game performance, and templates for word management.

