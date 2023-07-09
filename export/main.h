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

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/server.hpp"
#include "websocketpp/client.hpp"

extern "C" {

struct wspp_server;
struct wspp_client;

typedef unsigned long long wspp_connection;

typedef void (*on_open)(wspp_server*, wspp_connection);
typedef void (*on_close)(wspp_server*, wspp_connection);
typedef void (*on_message_server)(wspp_server*, wspp_connection, char*, long long);

struct wspp_server {
    websocketpp::server<websocketpp::config::asio> server;
};

typedef void (*on_message_client)(wspp_client*, char*, long long);

struct wspp_client {
    websocketpp::client<websocketpp::config::asio_client> client;
    wspp_connection connection;
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

EXPORT void wspp_server_free(wspp_server*);

EXPORT void wspp_server_set_open_handler(wspp_server*, on_open);

EXPORT void wspp_server_set_close_handler(wspp_server*, on_close);

EXPORT void wspp_server_set_message_handler(wspp_server*, on_message_server);

// begin listening and accepting connections on a port
EXPORT void wspp_server_listen(wspp_server*, long long);

EXPORT void wspp_server_stop_listening(wspp_server*);

EXPORT bool wspp_server_is_listening(wspp_server*);

// makes the server continuously synchronously listen
EXPORT void wspp_server_run(wspp_server*);

// makes the server synchronously listen for a single io event
EXPORT void wspp_server_run_one(wspp_server*);

// makes the server process all currently queued io events and then returns
EXPORT void wspp_server_poll(wspp_server*);

// makes the server process a single currently queued io event and then returns
EXPORT void wspp_server_poll_one(wspp_server*);

EXPORT void wspp_server_stop(wspp_server*);

EXPORT bool wspp_server_is_stopped(wspp_server*);

EXPORT void wspp_server_start_perpetual(wspp_server*);

// stops the server once all connections have been dropped
EXPORT void wspp_server_stop_perpetual(wspp_server*);

// send to all?

EXPORT bool wspp_server_send(wspp_connection, char*, long long, wspp_message_type);

EXPORT bool wspp_server_close(wspp_connection, wspp_close_type, char*, long long);



EXPORT wspp_client* wspp_client_create();

EXPORT void wspp_client_free(wspp_client*);

EXPORT void wspp_client_set_message_handler(wspp_client*, on_message_client);

EXPORT bool wspp_client_connect(wspp_client*, char*, long long);

EXPORT void wspp_client_stop_listening(wspp_client*);

EXPORT bool wspp_client_is_listening(wspp_client*);

EXPORT void wspp_client_run(wspp_client*);

EXPORT void wspp_client_run_one(wspp_client*);

EXPORT void wspp_client_poll(wspp_client*);

EXPORT void wspp_client_poll_one(wspp_client*);

EXPORT void wspp_client_stop(wspp_client*);

EXPORT bool wspp_client_is_stopped(wspp_client*);

EXPORT void wspp_client_start_perpetual(wspp_client*);

EXPORT void wspp_client_stop_perpetual(wspp_client*);

EXPORT bool wspp_client_send(wspp_client*, char*, long long, wspp_message_type);

EXPORT bool wspp_client_close(wspp_client*, wspp_close_type, char*, long long);

}

#endif //WEBSOCKETPP_MAIN_H
