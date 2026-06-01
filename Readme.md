# X-INSPECT // System Intelligence Suite
### Quantum Performance & Diagnostics Documentation
**Version:** 1.2.0 (Flagship Edition)  
**Developer:** Skeler Labs (Research & Development Division)  
**Project Lead:** SkelerSecurity R&D  

---

## 1. Project Overview
**X-INSPECT** is a high-tier system optimization and diagnostic engine. It transitions from traditional cleanup utilities into a proactive performance suite. Designed with a "Stark-Industrial" aesthetic, it utilizes native Windows hooks to provide real-time optimization scoring, visual execution proof, and deep-kernel security scans.

## 2. Technical Architecture
The software is built on a high-speed, zero-dependency C++ framework:
- **Core Engine:** Native Win32 API (C++ ISO 14).
- **UI Architecture:** **Owner-Drawn GDI Engine** (Bypasses standard Windows themes for custom Slate-Panel rendering).
- **Graphics:** Alpha-blended Layered Windows (`WS_EX_LAYERED`) with high-fidelity GDI ClearType rendering.
- **Analytics:** Integrated **Quantum Dashboard** with real-time `OPT-SCORE` calculation and circular HUD.

![SkelerSecurity Windows Optimizer Banner](windows-optimizer-banner.png)

---

## 3. Neural Engine Protocols

### 3.1 System Scrub (Digital Incineration)
- **Logic:** Merges custom temporary file incineration with the native Windows Disk Cleanup Utility.
- **Process:** Triggers `cleanmgr.exe` for driver-level cleanup and executes recursive deletion of `%temp%` and `C:\Windows\Temp`.
- **Proof:** Spawns a visible terminal showing real-time file incineration.

### 3.2 Neural Overdrive (Kinetic Performance)
- **Logic:** Synchronous recalibration of power and graphics planes.
- **Process:** 
  - Forces the **High-Performance Power Plan** (GUID: 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c).
  - Deep-links to `Advanced Graphics Settings` for hardware-accelerated GPU scheduling.

### 3.3 Aegis Stealth (Privacy & Network)
- **Logic:** Hardens the OS by severing diagnostic telemetry and refreshing network pathways.
- **Process:** 
  - Physically terminates and disables the `DiagTrack` (Connected User Experiences and Telemetry) service.
  - Flushes the DNS resolver cache to eliminate routing lag.

### 3.4 Sentinel Scan (Kernel Integrity)
- **Logic:** Validates the cryptographic signatures of every core Windows binary.
- **Process:** Spawns an elevated terminal instance to execute the **System File Checker** (`sfc /scannow`).

---

## 4. Quantum Analytics (OPT-SCORE)
The **OPT-SCORE** is a real-time system health metric ranging from 35 (Base/Dirty) to 100 (Optimized/Safe).
- **Tracking:** The HUD gauge redraws dynamically as protocols are executed.
- **Weightage:** 
  - Sentinel Scan: +20%
  - Aegis Stealth: +20%
  - System Scrub: +15%
  - Neural Overdrive: +10%

---

## 5. Deployment & Build Specs

### 5.1 Prerequisites
- **Compiler:** MinGW-w64 (TDM-GCC recommended for Dev-C++ users).
- **Branding:** Requires `icon.ico` and `resources.rc` for proper binary identity.

### 5.2 Linker Dependencies
To successfully build the **X-INSPECT** binary, the following libraries must be linked:
- `-lcomctl32` (UI Controls)
- `-lgdi32` (Dashboard Rendering)
- `-lshell32` (Process Execution)
- `-lshlwapi` (System Stats/Trash Sensor)

### 5.3 Execution Requirements
- **Privilege Level:** Must be executed as **Administrator**.
- **Pathing:** Ensure the build directory contains no spaces to avoid Dev-C++ `Makefile` errors.

---

## 6. Visual Identity (Stark Design)
- **Primary Palette:** Midnight Void (`RGB 10, 10, 15`), Slate Panel (`RGB 25, 25, 35`).
- **Accent:** Electric Cyan (`RGB 0, 210, 255`).
- **Typography:** Segoe UI (Bold) for UI; Consolas for the Neural Link Console.

---
**© 2026 SkelerSecurity. All Rights Reserved.**  
*X-INSPECT is a trademark of Skeler Labs. Built for those who demand peak performance.*
