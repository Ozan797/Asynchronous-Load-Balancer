#include "load_balancer.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;

        std::vector<std::string> backend_servers = {
                "127.0.0.1:3000", // Node.js server
        };

        LoadBalancer lb(io_context, "0.0.0.0", 8080, backend_servers);
        lb.start_accept();

        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
