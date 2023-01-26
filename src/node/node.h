#pragma once

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>

#include "libhirte/common/common.h"

typedef struct {
        int ref_count;

        char *name;
        char *host;
        int port;

        char *orch_addr;
        char *user_bus_service_name;

        sd_event *event;

        sd_bus *user_dbus;
        sd_bus *systemd_dbus;
        sd_bus *peer_dbus;
} Node;

Node *node_new(void);
Node *node_ref(Node *node);
void node_unref(Node *node);
void node_unrefp(Node **nodep);

bool node_set_port(Node *node, const char *port);
bool node_set_host(Node *node, const char *host);
bool node_set_name(Node *node, const char *name);
bool node_parse_config(Node *node, const char *configfile);

bool node_start(Node *node);
bool node_stop(Node *node);

#define _cleanup_node_ _cleanup_(node_unrefp)
