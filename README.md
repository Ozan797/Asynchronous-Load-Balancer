# Asynchronous Network Load Balancer

An efficient and scalable asynchronous network load balancer implemented in C++ using Boost.Asio. This load balancer distributes incoming TCP connections to a pool of backend servers using a round-robin strategy, ensuring high performance and low latency.

## Features

- **Asynchronous I/O:** Utilizes Boost.Asio for non-blocking, asynchronous network operations.
- **Round-Robin Distribution:** Evenly distributes incoming connections across backend servers.
- **Scalability:** Designed to handle numerous simultaneous connections efficiently.
- **Configurable Backend Servers:** Easily specify backend servers and ports.

## Requirements

- C++17 or later
- Boost.Asio library

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/Ozan797/Asynchronous-Load-Balancer.git
cd async_load_balancer
```

### 2. Build the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

### 1. Configure Backend Servers
Edit the main.cpp file to specify your backend servers:

