//
// Created by Kuju on 7/7/2023.
//

#ifndef WEBSOCKETPP_MAIN_H
#define WEBSOCKETPP_MAIN_H

#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// #include "websocketpp/config/asio_no_tls.hpp"
// #include "websocketpp/config/asio_no_tls_client.hpp"
// #include "websocketpp/server.hpp"
// #include "websocketpp/client.hpp"

extern "C" {

struct wspp_server;
struct wspp_client;

typedef unsigned long long wspp_connection;

typedef void (*on_open_server)(wspp_server* server, wspp_connection connection);
typedef void (*on_close_server)(wspp_server* server, wspp_connection connection);
typedef void (*on_message_server)(wspp_server* server, wspp_connection connection, char* data, long long length);

struct wspp_server {
    void* data;
    // websocketpp::server<websocketpp::config::asio> server;
};

typedef void (*on_open_client)(wspp_client* server, wspp_connection connection);
typedef void (*on_close_client)(wspp_client* server, wspp_connection connection);
typedef void (*on_message_client)(wspp_client* client, char* data, long long length);

struct wspp_client {
    void* data;
    // websocketpp::client<websocketpp::config::asio_client> client;
    // wspp_connection connection;
};

enum wspp_message_type {
    continuation = 0x0,
    text = 0x1,
    binary = 0x2,
};

enum wspp_close_type {
    blank = 0,
    omit_handshake = 1,
    force_tcp_drop = 2,
    normal = 1000,
    going_away = 1001,
    protocol_error = 1002,
    unsupported_data = 1003,
    no_status = 1005,
    abnormal_close = 1006,
    invalid_payload = 1007,
    policy_violation = 1008,
    message_too_big = 1009,
    extension_required = 1010,
    internal_endpoint_error = 1011,
    service_restart = 1012,
    try_again_later = 1013,
    bad_gateway = 1014,
    tls_handshake = 1015,
    subprotocol_error = 3000,
    invalid_subprotocol_data = 3001,
};



EXPORT wspp_server* wspp_server_create();

EXPORT void wspp_server_free(wspp_server* server);

EXPORT void wspp_server_set_open_handler(wspp_server* server, on_open_server handler);

EXPORT void wspp_server_set_close_handler(wspp_server* server, on_close_server handler);

EXPORT void wspp_server_set_message_handler(wspp_server* server, on_message_server handler);

// begin listening and accepting connections on a port
EXPORT void wspp_server_listen(wspp_server* server, long long port);

EXPORT void wspp_server_stop_listening(wspp_server* server);

EXPORT bool wspp_server_is_listening(wspp_server* server);

// makes the server continuously synchronously listen
EXPORT void wspp_server_run(wspp_server* server);

// makes the server synchronously listen for a single io event
EXPORT void wspp_server_run_one(wspp_server* server);

// makes the server process all currently queued io events and then returns
EXPORT void wspp_server_poll(wspp_server* server);

// makes the server process a single currently queued io event and then returns
EXPORT void wspp_server_poll_one(wspp_server* server);

EXPORT void wspp_server_stop(wspp_server* server);

EXPORT bool wspp_server_is_stopped(wspp_server* server);

EXPORT void wspp_server_start_perpetual(wspp_server* server);

// stops the server once all connections have been dropped
EXPORT void wspp_server_stop_perpetual(wspp_server* server);

// send to all?

EXPORT bool wspp_server_send(wspp_connection connection, char* data, long long length, wspp_message_type op);

EXPORT bool wspp_server_close(wspp_connection connection, wspp_close_type code, char* reason_data, long long reason_length);



EXPORT wspp_client* wspp_client_create();

EXPORT void wspp_client_free(wspp_client* client);

EXPORT void wspp_client_set_open_handler(wspp_client* client, on_open_client handler);

EXPORT void wspp_client_set_close_handler(wspp_client* client, on_close_client handler);

EXPORT void wspp_client_set_message_handler(wspp_client* client, on_message_client handler);

EXPORT bool wspp_client_connect(wspp_client* client, char* data, long long length);

EXPORT void wspp_client_run(wspp_client* client);

EXPORT void wspp_client_run_one(wspp_client* client);

EXPORT void wspp_client_poll(wspp_client* client);

EXPORT void wspp_client_poll_one(wspp_client* client);

EXPORT void wspp_client_stop(wspp_client* client);

EXPORT bool wspp_client_is_stopped(wspp_client* client);

EXPORT void wspp_client_start_perpetual(wspp_client* client);

EXPORT void wspp_client_stop_perpetual(wspp_client* client);

EXPORT bool wspp_client_send(wspp_client* client, char* data, long long length, wspp_message_type op);

EXPORT bool wspp_client_close(wspp_client* client, wspp_close_type code, char* reason_data, long long reason_length);

}

#endif //WEBSOCKETPP_MAIN_H
