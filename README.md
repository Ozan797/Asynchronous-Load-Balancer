# Asynchronous Network Load Balancer

An efficient and scalable asynchronous network load balancer implemented in C++ using Boost.Asio. This load balancer distributes incoming TCP connections to a pool of backend servers using a round-robin strategy, ensuring high performance and low latency.

## Features

- **Asynchronous I/O:** Utilises Boost.Asio for non-blocking, asynchronous network operations.
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
```bash
std::vector<std::string> backend_servers = {
    "127.0.0.1:3000", // Backend Server 1
    "127.0.0.1:3001", // Backend Server 2
    // Add more servers as needed
};
```

### 2. Run the Load Balancer
```bash
./async_load_balancer
```

### 3. Test with curl:
```bash
curl http://127.0.0.1:8080/
```

## Benchmarking
```bash
ab -n 10000 -c 100 http://127.0.0.1:8080/
wrk -t12 -c400 -d30s http://127.0.0.1:8080/
```
