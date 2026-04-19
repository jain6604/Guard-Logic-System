# Guard Logic Challenge

## 📌 Problem Statement
Design a decision system for a secured facility with three doors:
- One leads to a safe exit
- One leads to a trap
- One leads back to the starting point

## 💡 Approach
I implemented a structured decision-making system using a function-based approach in C++.

- Used clear conditional logic (if-else)
- Ensured only one outcome is selected at a time
- Designed for readability and easy modification

## ⚙️ How It Works
The program takes input conditions and evaluates them to decide:
- Safe Exit
- Trap
- Back to Start

## 🚀 Features
- Clean and modular code
- Logical consistency
- Easy to understand
  --- Guard Decision ---
  Keycard : YES
  Alarm   : NO
  Motion  : NO
  → Door 1 [Green Door] — Safe Exit

--- Guard Decision ---
  Keycard : YES
  Alarm   : YES
  Motion  : NO
  → Door 2 [Red Door] — Trap

--- Guard Decision ---
  Keycard : NO
  Alarm   : NO
  Motion  : YES
  → Door 3 [Yellow Door] — Starting Point

--- Guard Decision ---
  Keycard : NO
  Alarm   : NO
  Motion  : NO
  → Door 3 [Yellow Door] — Starting Point

--- Guard Decision ---
  Keycard : NO
  Alarm   : YES
  Motion  : YES
  → Door 2 [Red Door] — Trap

## 👨‍💻 Author
Saksham Jain
