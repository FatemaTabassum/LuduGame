# 🎲 LAN-Based Multiplayer Ludu Game (C++ | OpenGL | Socket Programming)

A real-time 2-player multiplayer Ludu game built in C++ using OpenGL for graphics and
TCP socket programming for LAN-based communication.

This project demonstrates concurrent networking, graphical rendering, and 
synchronized game-state management in a distributed environment.

### Project Highlights

- Real-time multiplayer over LAN
- TCP socket-based client–server architecture
- Turn-based gameplay synchronization
- Dynamic dice roll handling
- OpenGL-powered graphical board rendering
- Custom game logic implementation in C++

### Tech Stack

| Category  | Technology             |
| ----------- | ---------------------- |
| Language    | C++                    |
| Graphics    | OpenGL                 |
| Networking  | TCP Socket Programming |
| Development | Xcode (macOS)          |

### Networking Architecture
The system follows a Client–Server model.

Player A (Client)  ----TCP---->  Game Server  <----TCP----  Player B (Client)

***Server Responsibilities***
- Accept multiple client connections
- Maintain authoritative game state
- Broadcast start-game signal
- Synchronize turn order
- Distribute move updates to all players

***Client Responsibilities***
- Connect to server via TCP
- Send play requests and moves
- Listen continuously for server updates
- Enable/disable user interaction based on turn
- Render board updates using OpenGL

### Concurrency Model
The client uses:
- pthread_create() for server listener thread
- Condition variables (pthread_cond_wait) to delay UI start
- Continuous non-blocking message parsing
This allows:
- Rendering loop and networking to run simultaneously
- Real-time updates without freezing UI

### Graphics Layer (OpenGL)
- The OpenGL module handles:
- Rendering 4-color Ludu board
- Token placement and movement
- Dice display
- Dynamic board updates after each move
Game logic updates trigger re-rendering.

### Known Limitations
- Assumes full message arrives in single read() call (TCP stream framing not robust)
- No message-length prefix handling
- No encryption
- Limited to 2 players (extendable)

### Demo
<img width="1700" height="2200" alt="ludu_page_1" src="https://github.com/user-attachments/assets/a70d7144-849a-4374-a253-bcd03d4aa677" />
<img width="1700" height="2200" alt="ludu_page_2" src="https://github.com/user-attachments/assets/04a483a4-9bfa-4b44-ac8a-e9dbf991f74c" />


***Author***
Fatema Tabassum
PhD Candidate – Computer Science
Focus: Systems, Security & Machine Learning
