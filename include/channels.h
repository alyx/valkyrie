/*
 * Copyright (C) 2005 William Pitcock, et al.
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Data structures for channel information.
 *
 */

#ifndef CHANNELS_H
#define CHANNELS_H

struct channel_
{
  char *name;

  unsigned int modes;
  char *key;
  unsigned int limit;
  char **extmodes; /* non-standard simple modes with param eg +j */

  unsigned int nummembers;

  time_t ts;

  char *topic;
  char *topic_setter;
  time_t topicts;

  mowgli_list_t members;
  mowgli_list_t bans;

  unsigned int flags;
};

/* struct for channel memberships */
struct chanuser_
{
  channel_t *chan;
  user_t *user;
  unsigned int modes;
  mowgli_node_t unode;
  mowgli_node_t cnode;
};

struct chanban_
{
  channel_t *chan;
  char *mask;
  int type; /* 'b', 'e', 'I', etc -- jilles */
  mowgli_node_t node; /* for channel_t.bans */
  unsigned int flags;
};

/* channel_t.modes */
#define CMODE_INVITE    0x00000001
#define CMODE_KEY       0x00000002
#define CMODE_LIMIT     0x00000004
#define CMODE_MOD       0x00000008
#define CMODE_NOEXT     0x00000010
#define CMODE_PRIV      0x00000040      /* AKA PARA */
#define CMODE_SEC       0x00000080
#define CMODE_TOPIC     0x00000100
#define CMODE_CHANREG	0x00000200

/* channel_t.flags */
#define CHAN_LOG        0x00000001 /* logs sent to here */

/* chanuser_t.modes */
#define CSTATUS_OP      0x00000001
#define CSTATUS_VOICE   0x00000002
#define CSTATUS_OWNER   0x00000004      /* unreal/inspircd +q */
#define CSTATUS_PROTECT 0x00000008      /* unreal/inspircd +a */
#define CSTATUS_HALFOP  0x00000010      /* unreal/inspircd +h */

/* Extended channel modes will eventually go here. */
#define CMODE_NOCOLOR   0x00001000  /* hyperion +c */
#define CMODE_REGONLY   0x00002000  /* hyperion +r */
#define CMODE_OPMOD 0x00004000  /* hyperion +z */
#define CMODE_FINVITE   0x00008000  /* hyperion +g */
#define CMODE_EXLIMIT   0x00010000      /* charybdis +L */
#define CMODE_PERM      0x00020000      /* charybdis +P */
#define CMODE_FTARGET   0x00040000      /* charybdis +F */
#define CMODE_DISFWD    0x00080000      /* charybdis +Q */
#define CMODE_NOCTCP    0x00100000      /* charybdis +C */

#define CMODE_NPC   0x00200000  /* charybdis extensions/m_roleplay.c +N */
#define CMODE_SSLONLY   0x00400000  /* charybdis extensions/chm_sslonly.c +S */
#define CMODE_OPERONLY  0x00800000  /* charybdis extensions/chm_operonly.c +O */
#define CMODE_ADMINONLY 0x01000000  /* charybdis extensions/chm_adminonly.c +A */

/* chanban_t.flags */
#define CBAN_ANTIFLOOD  0x00000001	/* chanserv/antiflood set this */

#define MTYPE_NUL 0
#define MTYPE_ADD 1
#define MTYPE_DEL 2

struct cmode_
{
        char mode;
        unsigned int value;
};

//struct extmode
//{
	//char mode;
	//bool (*check)(const char *, channel_t *, mychan_t *, user_t *, myuser_t *);
//};

/* channel related hooks */
typedef struct {
	chanuser_t *cu; /* Write NULL here if you kicked the user.
			   When kicking the last user, you must join a
			   service first, otherwise the channel may be
			   destroyed and crashes may occur. The service may
			   not part until you return; chanserv provides
			   MC_INHABIT to help with this.
			   This also prevents kick/rejoin floods.
			   If this is NULL, a previous function kicked
			   the user */
} hook_channel_joinpart_t;

typedef struct {
	user_t *u;
        channel_t *c;
        char *msg;
} hook_cmessage_data_t;

typedef struct {
	user_t *u; /* Online user that changed the topic */
	server_t *s; /* Server that restored a topic */
        channel_t *c; /* Channel still has old topic */
        const char *setter; /* Stored setter string, can be nick, nick!user@host
			       or server */
	time_t ts; /* Time the topic was changed */
	const char *topic; /* New topic */
	int approved; /* Write non-zero here to cancel the change */
} hook_channel_topic_check_t;

typedef struct {
	user_t *u;
	channel_t *c;
} hook_channel_mode_t;

/* cmode.c */
extern char *flags_to_string(unsigned int flags);
extern int mode_to_flag(char c);
extern void channel_mode(user_t *source, channel_t *chan, int parc, char *parv[]);
extern void channel_mode_va(user_t *source, channel_t *chan, int parc, char *parv0, ...);
extern void clear_simple_modes(channel_t *c);
extern char *channel_modes(channel_t *c, bool doparams);
extern void modestack_flush_channel(channel_t *channel);
extern void modestack_forget_channel(channel_t *channel);
extern void modestack_finalize_channel(channel_t *channel);
//extern void check_modes(mychan_t *mychan, bool sendnow);

extern void modestack_mode_simple_real(const char *source, channel_t *channel, int dir, int flags);
extern void modestack_mode_limit_real(const char *source, channel_t *channel, int dir, unsigned int limit);
extern void modestack_mode_ext_real(const char *source, channel_t *channel, int dir, unsigned int i, const char *value);
extern void modestack_mode_param_real(const char *source, channel_t *channel, int dir, char type, const char *value);

extern void (*modestack_mode_simple)(const char *source, channel_t *channel, int dir, int flags);
extern void (*modestack_mode_limit)(const char *source, channel_t *channel, int dir, unsigned int limit);
extern void (*modestack_mode_ext)(const char *source, channel_t *channel, int dir, unsigned int i, const char *value);
extern void (*modestack_mode_param)(const char *source, channel_t *channel, int dir, char type, const char *value);

extern void modestack_flush_now(void);

/* channels.c */
extern mowgli_patricia_t *chanlist;

extern void init_channels(void);

extern channel_t *channel_add(const char *name, time_t ts, server_t *creator);
extern void channel_delete(channel_t *c);
//inline channel_t *channel_find(const char *name);

extern chanuser_t *chanuser_add(channel_t *chan, const char *user);
extern void chanuser_delete(channel_t *chan, user_t *user);
extern chanuser_t *chanuser_find(channel_t *chan, user_t *user);

extern chanban_t *chanban_add(channel_t *chan, const char *mask, int type);
extern void chanban_delete(chanban_t *c);
extern chanban_t *chanban_find(channel_t *chan, const char *mask, int type);
//inline void chanban_clear(channel_t *chan);

#endif

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
