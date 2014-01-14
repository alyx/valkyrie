#ifndef VALKYRIE_ME_H
#define VALKYRIE_ME_H
#include <libmowgli-2/mowgli.h>

#define RF_LIVE         0x00000001      /* don't fork  */
#define RF_SHUTDOWN     0x00000002      /* shut down   */
#define RF_STARTING     0x00000004      /* starting up */
#define RF_RESTART      0x00000008      /* restart     */
#define RF_REHASHING    0x00000010      /* rehashing   */

#define CURRTIME time(NULL)

struct me
{
    mowgli_eventloop_t *base_eventloop;
    int runflags;
    struct {
        unsigned int node;
        unsigned int event;
        time_t currtime;
        int maxfd;
    } state;
    struct {
        int server;
        int tld;
    } cnt;
    server_t *me;
} me;
#endif
