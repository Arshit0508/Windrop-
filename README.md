# WinDrop 🚀

> High-performance, cross-platform P2P file sharing over LAN — no internet required.

WinDrop lets you instantly share files between devices on the same local network with zero setup and no cloud dependency. Built with a C++ backend for raw speed and a Vite.js frontend for a clean, modern UI.

---

## Features

- ⚡ **Blazing fast transfers** — C++ powered backend handles large files with high throughput
- 🌐 **LAN-based P2P** — Direct device-to-device transfer, no internet or server needed
- 🖥️ **Cross-platform** — Works across Windows, macOS, and Linux
- 🎨 **Modern UI** — Lightweight and responsive frontend built with Vite.js
- 🔍 **Device discovery** — Automatically find other WinDrop devices on your network

---

## Tech Stack

| Layer | Technology |
|-------|-----------|
| Backend | C++ |
| Frontend | Vite.js |
| Protocol | P2P over LAN |

---

## Getting Started

### Prerequisites

- A C++ compiler (GCC / MSVC / Clang)
- Node.js (v18+)
- npm or yarn

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Arshit0508/Windrop-.git
   cd Windrop-
   ```

2. **Build the C++ backend**
   ```bash
   # Example using g++
   g++ -o windrop src/main.cpp -std=c++17
   ```

3. **Install frontend dependencies**
   ```bash
   cd frontend
   npm install
   ```

4. **Run the frontend**
   ```bash
   npm run dev
   ```

5. **Start the backend**
   ```bash
   ./windrop
   ```

---

## Usage

1. Launch WinDrop on two or more devices connected to the same Wi-Fi or LAN network.
2. Devices will automatically discover each other.
3. Select a file and choose the target device to begin the transfer.

---

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -m 'Add some feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Open a Pull Request

---

## License

This project is open source. See [LICENSE](LICENSE) for details.

---

## Acknowledgements

Originally inspired by [thedevsumit/WinDrop](https://github.com/thedevsumit/WinDrop).
