# Roadmap to 1.0.0

This document aims to demonstrate the direction of Breezy. 

**Note:** This roadmap is in its early stages and is subject to change.

## 0.1.0 - CLI Tool & Interpreter

**Components**

- **breezy.exe** - CLI tool
- **zephyr.dll** - Core runtime/interpreter

**Goals**

- CLI can:
    - Display version info (`--version`)
    - Run a `.brz` script via the runtime
- Runtime can:
    - Parse source code into AST
    - Execute basic scripts
