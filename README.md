# Simple Network File Transfer Application

## Overview
The **Simple Network File Transfer Application** is an open-source project that facilitates file transfers between two machines over a network using TCP sockets. This application serves both educational and practical purposes, enabling users to share files seamlessly while enhancing their understanding of network programming in C.

## Goals
- Develop a client-server application for file transfer.
- Implement robust error handling and user feedback mechanisms.
- Create a clean, user-friendly command-line interface.
- Ensure cross-platform compatibility (Windows and Linux).

## Key Features

### 1. File Transfer Functionality
- **Single File Transfer:** Send a single file from the client to the server.
- **Multi-File Transfer:** Support batch transfers of multiple files in a single session.

### 2. Progress Tracking
- Display a progress indicator showing the percentage of the file currently being transferred.

### 3. Error Handling
- Manage common issues with comprehensive error handling:
  - File not found errors.
  - Network connection failures.
  - Permission denied issues during file access.

### 4. Basic User Interface
- Command-line interface for:
  - Starting the server.
  - Connecting to the server as a client.
  - Selecting files for transfer.
  - Viewing transfer progress and receiving confirmation upon completion.

### 5. Cross-Platform Compatibility
- Runs on both Windows and Linux systems.

### 6. Documentation
- Includes installation instructions, a user guide, and contribution guidelines.

## Development Plan
The project will be developed over three days by a team of five members, each contributing approximately 3-5 hours per day:
- **Day 1:** Set up the TCP socket environment, implement basic server functionality, and establish a client connection.
- **Day 2:** Enhance features, including progress tracking and multi-file transfer capabilities, while improving error handling.
- **Day 3:** Conduct thorough testing, finalize the user interface, and prepare documentation.

## Open Source Commitment
This project is hosted on a public repository (e.g., GitHub) to promote collaboration and welcome contributions from the community. Feedback and suggestions are highly encouraged.

## Getting Started

### Prerequisites
- C compiler (e.g., GCC, Clang)
- Make (for building the project)
- Basic knowledge of networking concepts

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simple-network-file-transfer.git
   cd simple-network-file-transfer
   ```

2. Compile the application:
   ```bash
   make
   ```

### Usage
1. Start the server:
   ```bash
   ./server
   ```

2. In a separate terminal, connect the client to the server:
   ```bash
   ./client <server_ip> <port>
   ```

3. Follow the prompts to select files for transfer.

## Conclusion
The Simple Network File Transfer Application not only serves a practical purpose but also provides an opportunity for developers to learn and collaborate. By participating in this open-source project, contributors will gain valuable experience in networking, file I/O, and collaborative software development.
