# ✨ Enlightenment DPPCN: 🔒 Decentralized Privacy-Preserving Chat Network 

A decentralized, peer-to-peer (P2P) chat app focused on privacy and scalability. Built in **C23**, this project uses modular design for flexibility and extensibility. The initial implementation targets **Linux** and **Windows** (GTK-based UI), with future plans for Android.

The core goal is to provide a secure chat experience without central servers, ensuring privacy and eliminating third-party interference.

## ✨ Features

- **🔒 End-to-End Encryption**: Secure messaging with modern cryptographic standards and forward secrecy.
- **🌐 Decentralized Communication**: P2P message routing with no central control or surveillance.
- **📤 Offline Messaging**: Store and forward messages for offline peers.
- **🤝 Trust-Based Networking**: Node reliability and trust scores for secure interactions.

---

## 🏗️ Project Structure

The project is divided into modular layers for easier maintainability and scalability:

1. **🖼️ Application Layer**:

   - Manages user interface, settings, and interactions.
   - Provides a smooth user experience with chat windows and notifications.

2. **🔒 Encryption Layer**:

   - Implements encryption, hashing, and key management.
   - Manages key pairs and secure communication.

3. **🌐 P2P Layer**:

   - Handles peer discovery, message routing, and node trust scores.
   - Supports NAT traversal for better connectivity.

4. **💾 Storage Layer** (Planned):

   - Manages persistent storage for configurations and logs.
   - Supports platform-specific storage and encryption at rest.

---

## 🚀 Getting Started

### 📋 Prerequisites

- **C23-compatible Compiler**: 🖥️ GCC 14+, 🛠️ Clang 16+
- **GTK Development Libraries**: 📚 GTK 3
- **CMake**: ⚙️ For build configuration and management

### 🔨 Build Instructions

1. 🌀 Clone the repository:

   ```bash
   git clone https://github.com/laomb/Enlightenment.git
   cd Enlightenment
   ```

2. 📁 Create a build directory and configure the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. 🛠️ Compile the project:

   ```bash
   make   
   ```

4. ▶️ Run the app to start the GTK-based UI.

---

This project aims to bring secure, private communications to everyone. By removing centralized control, Enlightenment DPPCN empowers users to manage their privacy and data. We are looking for contributors passionate about privacy-focused technologies. Future plans include platform support expansion, routing optimization, and UI enhancements.

---

## 📄 License

This project is licensed under the **Apache 2.0 License**. Potential contributors are encouraged to read [Contribution Guidelines](CONTRIB.md) for guidelines on how to get involved.
