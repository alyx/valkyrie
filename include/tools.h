#include "object.h"

typedef enum {
    LOG_ANY = 0,
    LOG_INTERACTIVE = 1, /* IRC channels */
    LOG_NONINTERACTIVE = 2 /* files */
} log_type_t;

typedef struct logfile_ logfile_t;

/* logstreams API --nenolod */
typedef void (*log_write_func_t)(logfile_t *lf, const char *buf);


/* logger.c */
struct logfile_ {
    object_t parent;
    mowgli_node_t node;

    void *log_file;		/* opaque: can either be mychan_t or FILextern --nenolod */
    char *log_path;
    unsigned int log_mask;

    log_write_func_t write_func;
    log_type_t log_type;
};

char *log_path; /* contains path to default log. */
extern int log_force;

extern logfile_t *logfile_new(const char *log_path_, unsigned int log_mask);
extern void logfile_register(logfile_t *lf);
extern void logfile_unregister(logfile_t *lf);

/* general */
#define LG_NONextern         0x00000001      /* don't log                */
#define LG_INFO         0x00000002      /* log general info         */
#define LG_ERROR        0x00000004      /* log real important stuff */
#define LG_IOERROR      0x00000008      /* log I/O errors. */
#define LG_DEBUG        0x00000010      /* log debugging stuff      */
#define LG_VERBOSE	0x00000020	/* log a bit more verbosely than INFO or REGISTER, but not as much as DEBUG */
/* commands */
#define LG_CMD_ADMIN    0x00000100 /* oper-only commands */
#define LG_CMD_REGISTER 0x00000200 /* register/drop */
#define LG_CMD_SET      0x00000400 /* change properties of static data */
#define LG_CMD_DO       0x00000800 /* change properties of dynamic data */
#define LG_CMD_LOGIN    0x00001000 /* login/logout */
#define LG_CMD_GET      0x00002000 /* query information */
#define LG_CMD_REQUEST	0x00004000 /* requests made by users */
/* other */
#define LG_NETWORK      0x00010000 /* netsplit/netjoin */
#define LG_WALLOPS      0x00020000 /* NOTYET wallops from opers/other servers */
#define LG_RAWDATA      0x00040000 /* all data sent/received */
#define LG_REGISTER     0x00080000 /* all registration related messages */
#define LG_WARN1        0x00100000 /* NOTYET messages formerly walloped */
#define LG_WARN2        0x00200000 /* NOTYET messages formerly snooped */
#define LG_DENYCMD	0x00400000 /* commands denied by security policy */

#define LG_CMD_ALL      0x0000FF00
#define LG_ALL          0x7FFFFFFF /* XXX cannot use bit 31 as it would then be equal to TOKEN_UNMATCHED */

/* aliases for use with logcommand() */
#define CMDLOG_ADMIN    LG_CMD_ADMIN
#define CMDLOG_REGISTER (LG_CMD_REGISTER | LG_REGISTER)
#define CMDLOG_SET      LG_CMD_SET
#define CMDLOG_SET      LG_CMD_SET
#define CMDLOG_REQUEST	LG_CMD_REQUEST
#define CMDLOG_DO       LG_CMD_DO
#define CMDLOG_LOGIN    LG_CMD_LOGIN
#define CMDLOG_GET      LG_CMD_GET

extern void log_open(void);
extern void log_shutdown(void);
extern bool log_debug_enabled(void);
extern void log_master_set_mask(unsigned int mask);
extern logfile_t *logfile_find_mask(unsigned int log_mask);
extern void slog(unsigned int level, const char *fmt, ...) PRINTFLIKE(2, 3);

/* sharedheap.c */
extern mowgli_heap_t *sharedheap_get(size_t size);
extern void sharedheap_unref(mowgli_heap_t *heap);
extern char *combine_path(const char *parent, const char *child);
