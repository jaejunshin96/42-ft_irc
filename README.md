# ft_irc - Internet Relay Chat Server

## Project Overview

**ft_irc** is a network programming project focused on building a custom Internet Relay Chat (IRC) server using the C++98 standard. IRC is a text-based communication protocol that enables real-time messaging over the Internet. This project involves implementing an IRC server that handles multiple clients, manages channels, supports basic IRC commands, and facilitates communication between users.

The server communicates using TCP/IP, allowing clients to join channels, exchange messages, and perform operations like kicking users, setting topics, and moderating channels. This project provided a practical introduction to real-time network communication and socket programming in C++.

---

## Key Features

- **Program Name**: `ircserv`
- **Core Features**:
  - **User Authentication**: Clients must connect using a password for authentication.
  - **Nicknames**: Clients can set and change their nicknames.
  - **Channels**: Clients can join channels, send messages, and receive messages from other users in the same channel.
  - **Channel Operators**: Operators have the ability to manage the channel with commands like kicking users, inviting users, setting topics, and modifying channel modes.
  - **Private Messaging**: Clients can send direct messages to other users.
  
- **Command-Line Arguments**:
  - `port`: The port number the server listens on for incoming connections.
  - `password`: The connection password required for clients to access the server.

---

## Technical Details

- **Network Communication**:
  - The server communicates over TCP/IP (v4 or v6), handling multiple clients concurrently.
  - I/O operations (read, write, listen) are handled non-blocking using system calls like `poll()`, `select()`, or `epoll()` to ensure efficient resource usage.
  
- **Client Management**:
  - Clients must authenticate using a password.
  - Users can set nicknames and usernames and join or create channels for group discussions.
  - Messages sent to a channel are broadcast to all participants, while private messages can be exchanged between individual users.
  
- **Channel Operators**:
  - Operators can moderate channels with commands like:
    - `KICK`: Eject a user from the channel.
    - `INVITE`: Invite a user to the channel.
    - `TOPIC`: Set or view the channel topic.
    - `MODE`: Change the channel's mode (invite-only, topic restrictions, setting passwords, etc.).

---

## Skills Demonstrated

- **Network Programming**: Gained experience in socket programming, handling multiple client connections over TCP/IP.
- **Non-blocking I/O**: Implemented non-blocking I/O to ensure the server can manage multiple concurrent connections without stalling.
- **IRC Protocol**: Developed a working knowledge of the IRC protocol, including how clients and servers communicate and how channels are managed.
- **C++ 98**: Applied C++98 features to build a robust IRC server, adhering to a specific C++ standard while ensuring efficient, modular code.

---

## Conclusion

The **ft_irc** project provided a comprehensive introduction to network programming and the implementation of real-time communication protocols. By building an IRC server from the ground up, I gained valuable experience in handling multiple client connections, managing communication channels, and implementing non-blocking I/O operations. This project helped solidify my understanding of network protocols, socket programming, and real-time messaging systems.
