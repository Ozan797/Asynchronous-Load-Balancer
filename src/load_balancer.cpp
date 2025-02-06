#include "load_balancer.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <utility>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket client_socket, const std::string& backend_server)
        : client_socket_(std::move(client_socket)),
          server_socket_(client_socket_.get_executor()),
          backend_server_(backend_server) {}

    void start() {
        do_resolve();
    }

private:
    void do_resolve() {
        auto self(shared_from_this());
        auto pos = backend_server_.find(':');
        std::string host = backend_server_.substr(0, pos);
        std::string port = backend_server_.substr(pos + 1);

        tcp::resolver resolver(client_socket_.get_executor());
        resolver.async_resolve(
            host, port,
            [this, self](const boost::system::error_code& ec, tcp::resolver::results_type endpoints) {
                if (!ec) {
                    do_connect(endpoints);
                }
            });
    }

    void do_connect(const tcp::resolver::results_type& endpoints) {
        auto self(shared_from_this());
        boost::asio::async_connect(
            server_socket_, endpoints,
            [this, self](const boost::system::error_code& ec, const tcp::endpoint&) {
                if (!ec) {
                    do_read_client();
                    do_read_server();
                }
            });
    }

    void do_read_client() {
        auto self(shared_from_this());
        client_socket_.async_read_some(
            boost::asio::buffer(client_data_),
            [this, self](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    do_write_server(length);
                }
            });
    }

    void do_write_server(std::size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(
            server_socket_, boost::asio::buffer(client_data_, length),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    do_read_client();
                }
            });
    }

    void do_read_server() {
        auto self(shared_from_this());
        server_socket_.async_read_some(
            boost::asio::buffer(server_data_),
            [this, self](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    do_write_client(length);
                }
            });
    }

    void do_write_client(std::size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(
            client_socket_, boost::asio::buffer(server_data_, length),
            [this, self](const boost::system::error_code& ec, std::size_t) {
                if (!ec) {
                    do_read_server();
                }
            });
    }

    tcp::socket client_socket_;
    tcp::socket server_socket_;
    std::string backend_server_;
    std::array<char, 8192> client_data_;
    std::array<char, 8192> server_data_;
};

LoadBalancer::LoadBalancer(boost::asio::io_context& io_context,
                           const std::string& listen_address,
                           unsigned short listen_port,
                           const std::vector<std::string>& backend_servers)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(boost::asio::ip::make_address(listen_address), listen_port)),
      backend_servers_(backend_servers),
      next_server_index_(0) {}

void LoadBalancer::start_accept() {
    acceptor_.async_accept(
        [this](const boost::system::error_code& ec, tcp::socket client_socket) {
            if (!ec) {
                std::string backend_server = backend_servers_[next_server_index_];
                next_server_index_ = (next_server_index_ + 1) % backend_servers_.size();
                std::make_shared<Session>(std::move(client_socket), backend_server)->start();
            }
            start_accept();
        });
}
