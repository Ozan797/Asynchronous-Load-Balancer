#ifndef LOAD_BALANCER_HPP
#define LOAD_BALANCER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>

class LoadBalancer {
public:
    LoadBalancer(boost::asio::io_context& io_context,
                 const std::string& listen_address,
                 unsigned short listen_port,
                 const std::vector<std::string>& backend_servers);

    void start_accept();

private:
    void handle_accept(const boost::system::error_code& error);

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::vector<std::string> backend_servers_;
    std::size_t next_server_index_;
};

#endif // LOAD_BALANCER_HPP
