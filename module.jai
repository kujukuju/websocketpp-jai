//
// This file was auto-generated using the following command:
//
// jai ./generate.jai
//



wspp_connection :: u64;

on_open_server :: #type (server: *wspp_server, connection: wspp_connection) -> void #c_call;
on_close_server :: #type (server: *wspp_server, connection: wspp_connection) -> void #c_call;
on_message_server :: #type (server: *wspp_server, connection: wspp_connection, data: *u8, length: s64) -> void #c_call;

wspp_server :: struct {
    data: *void;
}

on_open_client :: #type (server: *wspp_client, connection: wspp_connection) -> void #c_call;
on_close_client :: #type (server: *wspp_client, connection: wspp_connection) -> void #c_call;
on_message_client :: #type (client: *wspp_client, data: *u8, length: s64) -> void #c_call;

wspp_client :: struct {
    data: *void;
}

wspp_message_type :: enum s32 {
    continuation :: 0;
    text         :: 1;
    binary       :: 2;
}

wspp_close_type :: enum s32 {
    blank                    :: 0;
    omit_handshake           :: 1;
    force_tcp_drop           :: 2;
    normal                   :: 1000;
    going_away               :: 1001;
    protocol_error           :: 1002;
    unsupported_data         :: 1003;
    no_status                :: 1005;
    abnormal_close           :: 1006;
    invalid_payload          :: 1007;
    policy_violation         :: 1008;
    message_too_big          :: 1009;
    extension_required       :: 1010;
    internal_endpoint_error  :: 1011;
    service_restart          :: 1012;
    try_again_later          :: 1013;
    bad_gateway              :: 1014;
    tls_handshake            :: 1015;
    subprotocol_error        :: 3000;
    invalid_subprotocol_data :: 3001;
}

wspp_server_create :: () -> *wspp_server #foreign websocketpp;

wspp_server_free :: (server: *wspp_server) -> void #foreign websocketpp;

wspp_server_set_open_handler :: (server: *wspp_server, handler: on_open_server) -> void #foreign websocketpp;

wspp_server_set_close_handler :: (server: *wspp_server, handler: on_close_server) -> void #foreign websocketpp;

wspp_server_set_message_handler :: (server: *wspp_server, handler: on_message_server) -> void #foreign websocketpp;

// begin listening and accepting connections on a port
wspp_server_listen :: (server: *wspp_server, port: s64) -> void #foreign websocketpp;

wspp_server_stop_listening :: (server: *wspp_server) -> void #foreign websocketpp;

wspp_server_is_listening :: (server: *wspp_server) -> bool #foreign websocketpp;

// makes the server continuously synchronously listen
wspp_server_run :: (server: *wspp_server) -> void #foreign websocketpp;

// makes the server synchronously listen for a single io event
wspp_server_run_one :: (server: *wspp_server) -> void #foreign websocketpp;

// makes the server process all currently queued io events and then returns
wspp_server_poll :: (server: *wspp_server) -> void #foreign websocketpp;

// makes the server process a single currently queued io event and then returns
wspp_server_poll_one :: (server: *wspp_server) -> void #foreign websocketpp;

wspp_server_stop :: (server: *wspp_server) -> void #foreign websocketpp;

wspp_server_is_stopped :: (server: *wspp_server) -> bool #foreign websocketpp;

wspp_server_start_perpetual :: (server: *wspp_server) -> void #foreign websocketpp;

// stops the server once all connections have been dropped
wspp_server_stop_perpetual :: (server: *wspp_server) -> void #foreign websocketpp;

// send to all?
wspp_server_send :: (connection: wspp_connection, data: *u8, length: s64, op: wspp_message_type) -> bool #foreign websocketpp;

wspp_server_close :: (connection: wspp_connection, code: wspp_close_type, reason_data: *u8, reason_length: s64) -> bool #foreign websocketpp;

wspp_client_create :: () -> *wspp_client #foreign websocketpp;

wspp_client_free :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_set_open_handler :: (client: *wspp_client, handler: on_open_client) -> void #foreign websocketpp;

wspp_client_set_close_handler :: (client: *wspp_client, handler: on_close_client) -> void #foreign websocketpp;

wspp_client_set_message_handler :: (client: *wspp_client, handler: on_message_client) -> void #foreign websocketpp;

wspp_client_connect :: (client: *wspp_client, data: *u8, length: s64) -> bool #foreign websocketpp;

wspp_client_run :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_run_one :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_poll :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_poll_one :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_stop :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_is_stopped :: (client: *wspp_client) -> bool #foreign websocketpp;

wspp_client_start_perpetual :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_stop_perpetual :: (client: *wspp_client) -> void #foreign websocketpp;

wspp_client_send :: (client: *wspp_client, data: *u8, length: s64, op: wspp_message_type) -> bool #foreign websocketpp;

wspp_client_close :: (client: *wspp_client, code: wspp_close_type, reason_data: *u8, reason_length: s64) -> bool #foreign websocketpp;

#scope_file

websocketpp :: #library "bin/win/websocketpp";
