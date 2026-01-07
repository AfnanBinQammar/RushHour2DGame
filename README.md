# 🚖 Rush Hour 2D (OOP Project)

![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat&logo=c%2B%2B)
![Graphics](https://img.shields.io/badge/Graphics-OpenGL%20%2F%20GLUT-red)
![Build](https://img.shields.io/badge/Build-Make-green)

**Rush Hour 2D** is an interactive city simulation game built using **C++** and **OpenGL (GLUT)**. The project demonstrates core **Object-Oriented Programming (OOP)** concepts such as inheritance, polymorphism, and encapsulation to create a functioning game ecosystem with traffic, economy, and dynamic missions.

---

## 🎮 Game Overview

In **Rush Hour 2D**, you navigate a bustling 25x20 grid-based city. You must race against the clock to complete transport missions while managing your fuel and money.

### 🌟 Key Features
* **🔄 Dual Game Modes:**
    * **Taxi Mode:** Drive a yellow cab and transport passengers[cite: 1].
    * **Pickup Mode:** Drive a red truck and transport cargo boxes[cite: 1].
    * *Dynamic Switching:* Visit the Garage to switch roles mid-game using the **'S'** key[cite: 1].
* **🚦 Smart Traffic System:** Computer-controlled cars navigate the grid randomly, requiring the player to avoid collisions to save points[cite: 1].
* **⛽ Economy & Resources:**
    * **Fuel System:** Fuel depletes as you move. [cite_start]Refill at gas stations (Red zones)[cite: 1].
    * **Money System:** Earn cash by completing drops; spend cash to buy fuel[cite: 1].
* **🏙️ Interactive Map:** Features destructible elements, buildings, trees, and a functional garage[cite: 1].
* **⏱️ Timer:** Complete as many objectives as possible before the 180-second timer runs out[cite: 1].

---

## 🕹️ Controls

| Input | Action | Context |
| :---: | :--- | :--- |
| **Arrow Keys** | Move Vehicle | Up, Down, Left, Right |
| **Spacebar** | Interact | Pick up passenger/box or Drop off at destination |
| **S** | Switch Role | Only works when the car is inside the **Garage** (Green zone) |
| **Esc** | Exit Game | Quit application |
| **Mouse** | Menu Selection | Use to click "Start Game", "Play as Taxi", etc. |

---

## 🏗️ Object-Oriented Design

This project utilizes a structured class hierarchy to manage game state[cite: 1]:

* **Inheritance:**
    * `class Game`: The parent class for most entities.
    * `class Board`, `class Menu`, `class Score`, `class Fuel`: All inherit from `Game` to share common attributes.
    * `class mainCar`: Inherits properties to interact with the grid.
* **Encapsulation:** Private data members (like `grid[][]`, `score`, `fuelbar`) are protected and accessed via public getter/setter methods[cite: 1].
* **Composition:** The `Garage` and `Dropoffs` classes hold pointers to the `Board`, allowing complex interactions between different game components[cite: 1].

---

## 🚀 Installation & Build

### Prerequisites (Linux/Ubuntu)
You need the OpenGL and FreeGLUT development libraries. You can install them using the provided script or manually:

```bash
# Using the provided script
sudo chmod +x install-libraries.sh
./install-libraries.sh

# OR Manual Install
sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev
