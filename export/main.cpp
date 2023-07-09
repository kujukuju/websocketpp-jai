#include <iostream>

#include "main.h"

extern "C" {

wspp_server* wspp_server_create() {
    wspp_server* server = new wspp_server();

    server->server.init_asio();
    server->server.clear_access_channels(websocketpp::log::alevel::all);

    return server;
}

void wspp_server_free(wspp_server* server) {
    delete server;
}

void wspp_server_set_open_handler(wspp_server* server, on_open handler) {
    server->server.set_open_handler([server, handler](websocketpp::connection_hdl handle) {
        unsigned long long identifier = reinterpret_cast<unsigned long long>(handle.lock().get());

        handler(server, identifier);
    });
}

void wspp_server_set_close_handler(wspp_server* server, on_close handler) {
    server->server.set_open_handler([server, handler](websocketpp::connection_hdl handle) {
        unsigned long long identifier = reinterpret_cast<unsigned long long>(handle.lock().get());

        handler(server, identifier);
    });
}

void wspp_server_set_message_handler(wspp_server* server, on_message_server handler) {
    server->server.set_message_handler([server, handler](websocketpp::connection_hdl handle, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
        unsigned long long identifier = reinterpret_cast<unsigned long long>(handle.lock().get());

        std::string& payload = const_cast<std::string&>(msg->get_payload());
        char* data = payload.data();
        long long length = payload.size();

        handler(server, identifier, data, length);
    });
}

void wspp_server_listen(wspp_server* server, long long port) {
    server->server.listen((int) port);
    server->server.start_accept();
}

void wspp_server_stop_listening(wspp_server* server) {
    server->server.stop_listening();
}

bool wspp_server_is_listening(wspp_server* server) {
    return server->server.is_listening();
}

void wspp_server_run(wspp_server* server) {
    server->server.run();
}

void wspp_server_run_one(wspp_server* server) {
    server->server.run_one();
}

void wspp_server_poll(wspp_server* server) {
    server->server.poll();
}

void wspp_server_poll_one(wspp_server* server) {
    server->server.poll_one();
}

void wspp_server_stop(wspp_server* server) {
    server->server.stop();
}

bool wspp_server_is_stopped(wspp_server* server) {
    return server->server.stopped();
}

void wspp_server_start_perpetual(wspp_server* server) {
    server->server.start_perpetual();
}

void wspp_server_stop_perpetual(wspp_server* server) {
    server->server.stop_perpetual();
}

bool wspp_server_send(wspp_connection connection, char* data, long long length, wspp_message_type op) {
    websocketpp::server<websocketpp::config::asio>::connection_type* connection_ptr = reinterpret_cast<websocketpp::server<websocketpp::config::asio>::connection_type*>(connection);

    if (!connection_ptr || connection_ptr->get_state() != websocketpp::session::state::open) {
        return false;
    }

    // websocketpp::frame::opcode::value
    websocketpp::lib::error_code error = connection_ptr->send(data, length, (websocketpp::frame::opcode::value) op);
    return !error;
}

bool wspp_server_close(wspp_connection connection, wspp_close_type code, char* reason_data, long long reason_length) {
    websocketpp::server<websocketpp::config::asio>::connection_type* connection_ptr = reinterpret_cast<websocketpp::server<websocketpp::config::asio>::connection_type*>(connection);

    if (!connection_ptr || connection_ptr->get_state() != websocketpp::session::state::open) {
        return false;
    }

    std::string reason_string(reason_data, reason_length);

    websocketpp::lib::error_code error;
    connection_ptr->close((websocketpp::close::status::value) code, reason_string, error);
    return !error;
}

wspp_client* wspp_client_create() {
    wspp_client* client = new wspp_client();

    client->client.init_asio();
    client->client.clear_access_channels(websocketpp::log::alevel::all);

    return client;
}

void wspp_client_free(wspp_client* client) {
    delete client;
}

void wspp_client_set_message_handler(wspp_client* client, on_message_client handler) {
    client->client.set_message_handler([client, handler](websocketpp::connection_hdl handle, websocketpp::server<websocketpp::config::asio_client>::message_ptr msg) {
        std::string& payload = const_cast<std::string&>(msg->get_payload());
        char* data = payload.data();
        long long length = payload.size();

        handler(client, data, length);
    });
}

bool wspp_client_connect(wspp_client* client, char* data, long long length) {
    std::string uri(data, length);

    websocketpp::lib::error_code error;
    websocketpp::server<websocketpp::config::asio_client>::connection_ptr connection_ptr = client->client.get_connection(uri, error);
    if (!connection_ptr || error) {
        return false;
    }

    unsigned long long identifier = reinterpret_cast<unsigned long long>(connection_ptr.get());
    client->connection = identifier;

    return true;
}

void wspp_client_stop_listening(wspp_client* client) {
    client->client.stop_listening();
}

bool wspp_client_is_listening(wspp_client* client) {
    return client->client.is_listening();
}

void wspp_client_run(wspp_client* client) {
    client->client.run();
}

void wspp_client_run_one(wspp_client* client) {
    client->client.run_one();
}

void wspp_client_poll(wspp_client* client) {
    client->client.poll();
}

void wspp_client_poll_one(wspp_client* client) {
    client->client.poll_one();
}

void wspp_client_stop(wspp_client* client) {
    client->client.stop();
}

bool wspp_client_is_stopped(wspp_client* client) {
    return client->client.stopped();
}

void wspp_client_start_perpetual(wspp_client* client) {
    client->client.start_perpetual();
}

void wspp_client_stop_perpetual(wspp_client* client) {
    client->client.stop_perpetual();
}

bool wspp_client_send(wspp_client* client, char* data, long long length, wspp_message_type op) {
    websocketpp::server<websocketpp::config::asio_client>::connection_type* connection_ptr = reinterpret_cast<websocketpp::server<websocketpp::config::asio_client>::connection_type*>(client->connection);

    if (!connection_ptr || connection_ptr->get_state() != websocketpp::session::state::open) {
        return false;
    }

    // websocketpp::frame::opcode::value
    websocketpp::lib::error_code error = connection_ptr->send(data, length, (websocketpp::frame::opcode::value) op);
    return !error;
}

bool wspp_client_close(wspp_client* client, wspp_close_type code, char* reason_data, long long reason_length) {
    websocketpp::server<websocketpp::config::asio_client>::connection_type* connection_ptr = reinterpret_cast<websocketpp::server<websocketpp::config::asio_client>::connection_type*>(client->connection);

    if (!connection_ptr || connection_ptr->get_state() != websocketpp::session::state::open) {
        return false;
    }

    std::string reason_string(reason_data, reason_length);

    websocketpp::lib::error_code error;
    connection_ptr->close((websocketpp::close::status::value) code, reason_string, error);
    return !error;
}

}