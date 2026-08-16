# Smart Bank Management System (Qt / C++, OOP)

A desktop banking application built with Qt Widgets, demonstrating
object-oriented design in C++: login, dashboard, and file-based
persistence of account data.

## Problem it solves
A self-contained, GUI-based bank account management demo — login,
view/manage account data, persisted to a local data file.

## Key features
- Login screen with credential check
- Dashboard view after login (`showDashboard()`)
- Account data persisted to `bankdata.txt`
- Built with Qt Widgets (`QMainWindow`, `QTableWidget`, dialogs, etc.)

## Tech stack
C++, Qt 6 (Widgets), CMake

## How it works
`mainwindow.cpp` defines the `BankSystem` widget: a login form wired via
Qt's signal/slot system (`connect(loginBtn, &QPushButton::clicked, ...)`),
which on success opens a dashboard for account operations. Data is loaded
from and written to a flat file (`loadData()` / `bankdata.txt`).

## Project structure
```
main.cpp
mainwindow.cpp / mainwindow.h
CMakeLists.txt
```
> The `build/` directory (compiled binaries, CMake cache, Qt Creator
> metadata) is no longer tracked — see `.gitignore` below. If you're
> pulling a version of this repo from before this cleanup, run the `git rm
> -r --cached build/` command in the setup section once to stop tracking
> it (your local build folder is not deleted).

## Installation & setup
Requires Qt 6 and CMake.

```bash
git clone https://github.com/Javeriaa367/gui-based-bank-management-system-using-oop.git
cd gui-based-bank-management-system-using-oop/smartbankmanagementsystemm
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage
Run the built `BankSystem` executable. Demo login credentials are set in
`mainwindow.cpp` — replace with real auth before using this as anything
beyond a demo.

## Future improvements
*[Add your own roadmap — e.g. real authentication/hashing instead of a
hardcoded demo login, a proper database instead of a flat file.]*

## Author
**Javeria** — GitHub: [@Javeriaa367](https://github.com/Javeriaa367)
