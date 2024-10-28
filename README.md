# Networking-CPP

A simple networking project implemented in C++ using the ASIO library. This project demonstrates client-server networking functionalities and includes a sample Hangman game implemented over the network.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)

## Features

- **Networking Communication**: Client-server communication using the ASIO library.
- **Sample Game - Hangman**: A classic hangman game implemented for network play.
- **Cross-Platform Compatibility**: Developed in C++ for easy cross-platform support.

## Installation

### Prerequisites

- C++ compiler (C++11 or later)
- CMake
- [ASIO](https://think-async.com/Asio/) (version 1.22.1 included in `Depends` folder)

## Usage

1. **Run the Server**:
   - Navigate to the server executable:
     ```bash
     ./build/ServerExecutable
     ```

2. **Run the Client**:
   - In a separate terminal, navigate to the client executable:
     ```bash
     ./build/ClientExecutable
     ```

3. **Play the Game**: Follow the on-screen instructions to play Hangman with the server.

## Project Structure

- **ConsoleApplication1/**: Main application folder.
- **Depends/asio-1.22.1/**: ASIO library dependencies.
- **NetworkTest/**: Test files for networking functions.
- **Networking.sln**: Solution file for IDEs like Visual Studio.

## Contribution

Contributions are welcome! Please submit a pull request or open an issue for suggestions.

## License

This project is licensed under the MIT License.
