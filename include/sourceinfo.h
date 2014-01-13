/*
 * Copyright (C) 2006 Atheme Development Group
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Data structures for sourceinfo
 *
 */

#ifndef SOURCEINFO_H
#define SOURCEINFO_H

/* structure describing data about a protocol message or service command */
struct sourceinfo_
{
	object_t parent;

	/* fields describing the source of the message */
	/* for protocol modules, the following applies to su and s:
	 * at most one of these two can be non-NULL
	 * before server registration, both are NULL, otherwise exactly
	 * one is NULL.
	 * for services commands, s is always NULL and su is non-NULL if
	 * and only if the command was received via IRC.
	 */
	user_t *su; /* source, if it's a user */
	server_t *s; /* source, if it's a server */

	connection_t *connection; /* physical connection cmd received from */
	const char *sourcedesc; /* additional information (e.g. IP address) */

	void *callerdata; /* opaque data pointer for caller */

	unsigned int output_limit; /* if not 0, limit lines of output */
	unsigned int output_count; /* lines of output upto now */

	//command_t *command; [> The command being executed. Needed when one function handles
				//more than one command. */
};

extern sourceinfo_t *sourceinfo_create(void);

#endif

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
