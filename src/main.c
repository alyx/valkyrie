#include "valkyrie.h"

char *log_path;

static void handle_recv(connection_t *cptr)
{
    char buf[BUFSIZE];
    mowgli_node_t *n, *tn;
    connection_t *target;
    int i;

    i = recvq_getline(cptr, buf, sizeof buf - 1);
    buf[i] = '\0';
    MOWGLI_LIST_FOREACH_SAFE(n, tn, connection_list.head)
    {
        target = (connection_t *)n->data;
        if (target == NULL)
            continue;
        sendq_add(target, buf, i);
    }
    irc_parse(buf);
}


static void do_listen(connection_t *cptr)
{
    connection_t *newptr;
    newptr = connection_accept_tcp(cptr, recvq_put, NULL);
    newptr->recvq_handler = handle_recv;
}

void init_valkyrie(void)
{
    log_open();
    init_servers();
}

int main(int argc, char *argv[])
{
    log_path = "valkyrie.log";

    init_valkyrie();
	me.base_eventloop = mowgli_eventloop_create();
    me.me = server_add("valkyrie.plexbox.co.uk", 0, NULL, "42X", "Valkyrie Test Server");

    connection_open_listener_tcp("0.0.0.0", 1337, do_listen);

	mowgli_eventloop_run(me.base_eventloop);

	mowgli_eventloop_destroy(me.base_eventloop);

	return EXIT_SUCCESS;
}
