#ifndef LOAD_BALANCER_HPP
#define LOAD_BALANCER_HPP

#include <boost/asio.hpp>
#include <vector>
#include <string>

class LoadBalancer {
public:
    LoadBalancer(boost::asio::io_context& io_context, const std::vector<std::string>& backend_servers, unsigned short port);
    void start_accept();

private:
    void handle_accept(const boost::system::error_code& error);
    std::string get_next_server();

    boost::asio::ip::tcp::acceptor acceptor_;
    std::vector<std::string> backend_servers_;
    size_t current_server_index_;
};

#endif
