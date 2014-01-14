/*
 * atheme-services: A collection of minimalist IRC services   
 * function.c: Miscillaneous functions.
 *
 * Copyright (c) 2005-2007 Atheme Project (http://www.atheme.org)           
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "valkyrie.h"

/*char ch[] = "abcdefghijklmnopqrstuvwxyz";*/

/* This function uses mowgli_alloc() to allocate memory.
 * You MUST mowgli_free the result when you are done with it!
 */
/*char *random_string(int sz)*/
/*{*/
	/*int i;*/
	/*char *buf = mowgli_alloc(sz + 1); [> padding <]*/

	/*for (i = 0; i < sz; i++)*/
	/*{*/
		/*buf[i] = ch[arc4random() % 26];*/
	/*}*/

	/*buf[sz] = 0;*/

	/*return buf;*/
/*}*/

#ifdef HAVE_GETTIMEOFDAY
/* starts a timer */
void s_time(struct timeval *sttime)
{
	gettimeofday(sttime, NULL);
}
#endif

#ifdef HAVE_GETTIMEOFDAY
/* ends a timer */
void e_time(struct timeval sttime, struct timeval *ttime)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	timersub(&now, &sttime, ttime);
}
#endif

#ifdef HAVE_GETTIMEOFDAY
/* translates microseconds into miliseconds */
int tv2ms(struct timeval *tv)
{
	return (tv->tv_sec * 1000) + (int) (tv->tv_usec / 1000);
}
#endif

/* replaces tabs with a single ASCII 32 */
void tb2sp(char *line)
{
	char *c;

	while ((c = strchr(line, '\t')))
		*c = ' ';
}

/* replace all occurances of 'old' with 'new' */
char *replace(char *s, int size, const char *old, const char *new)
{
	char *ptr = s;
	int left = strlen(s);
	int avail = size - (left + 1);
	int oldlen = strlen(old);
	int newlen = strlen(new);
	int diff = newlen - oldlen;

	while (left >= oldlen)
	{
		if (strncmp(ptr, old, oldlen))
		{
			left--;
			ptr++;
			continue;
		}

		if (diff > avail)
			break;

		if (diff != 0)
			memmove(ptr + oldlen + diff, ptr + oldlen, left + 1 - oldlen);

		memcpy(ptr, new, newlen);
		ptr += newlen;
		left -= oldlen;
	}

	return s;
}

/* reverse of atoi() */
const char *number_to_string(int num)
{
	static char ret[32];
	snprintf(ret, 32, "%d", num);
	return ret;
}

/* return the time elapsed since an event */
char *time_ago(time_t event)
{
	static char ret[128];
	int years, weeks, days, hours, minutes, seconds;

	event = CURRTIME - event;
	years = weeks = days = hours = minutes = 0;

	while (event >= 60 * 60 * 24 * 365)
	{
		event -= 60 * 60 * 24 * 365;
		years++;
	}
	while (event >= 60 * 60 * 24 * 7)
	{
		event -= 60 * 60 * 24 * 7;
		weeks++;
	}
	while (event >= 60 * 60 * 24)
	{
		event -= 60 * 60 * 24;
		days++;
	}
	while (event >= 60 * 60)
	{
		event -= 60 * 60;
		hours++;
	}
	while (event >= 60)
	{
		event -= 60;
		minutes++;
	}

	seconds = event;

	if (years)
		snprintf(ret, sizeof(ret),
			 "%d year%s, %d week%s, %d day%s, %02d:%02d:%02d", years, years == 1 ? "" : "s", weeks, weeks == 1 ? "" : "s", days, days == 1 ? "" : "s", hours, minutes, seconds);
	else if (weeks)
		snprintf(ret, sizeof(ret), "%d week%s, %d day%s, %02d:%02d:%02d", weeks, weeks == 1 ? "" : "s", days, days == 1 ? "" : "s", hours, minutes, seconds);
	else if (days)
		snprintf(ret, sizeof(ret), "%d day%s, %02d:%02d:%02d", days, days == 1 ? "" : "s", hours, minutes, seconds);
	else if (hours)
		snprintf(ret, sizeof(ret), "%d hour%s, %d minute%s, %d second%s", hours, hours == 1 ? "" : "s", minutes, minutes == 1 ? "" : "s", seconds, seconds == 1 ? "" : "s");
	else if (minutes)
		snprintf(ret, sizeof(ret), "%d minute%s, %d second%s", minutes, minutes == 1 ? "" : "s", seconds, seconds == 1 ? "" : "s");
	else
		snprintf(ret, sizeof(ret), "%d second%s", seconds, seconds == 1 ? "" : "s");

	return ret;
}

char *timediff(time_t seconds)
{
	static char buf[BUFSIZE];
	long unsigned days, hours, minutes;

	days = seconds / 86400;
	seconds %= 86400;
	hours = seconds / 3600;
	hours %= 3600;
	minutes = seconds / 60;
	minutes %= 60;
	seconds %= 60;

	snprintf(buf, sizeof(buf), "%lu day%s, %lu:%02lu:%02lu", days, (days == 1) ? "" : "s", hours, minutes, (long unsigned) seconds);

	return buf;
}

/* generate a random number, for use as a key */
/*unsigned long makekey(void)*/
/*{*/
	/*unsigned long k;*/

	/*k = arc4random() & 0x7FFFFFFF;*/

	/*[> shorten or pad it to 9 digits <]*/
	/*if (k > 1000000000)*/
		/*k = k - 1000000000;*/
	/*if (k < 100000000)*/
		/*k = k + 100000000;*/

	/*return k;*/
/*}*/

bool is_internal_client(user_t *u)
{
	return (u && (!u->server || u->server == me.me));
}

bool validhostmask(const char *host)
{
	char *p, *q;

	if (strchr(host, ' '))
		return false;

	/* make sure it has ! and @ in that order and only once */
	p = strchr(host, '!');
	q = strchr(host, '@');
	if (p == NULL || q == NULL || p > q || strchr(p + 1, '!') ||
			strchr(q + 1, '@'))
		return false;

	/* XXX this NICKLEN is too long */
	if (strlen(host) > NICKLEN + USERLEN + HOSTLEN + 1)
		return false;

	if (host[0] == ',' || host[0] == '-' || host[0] == '#' ||
			host[0] == '@' || host[0] == '!' || host[0] == ':')
		return false;

	return true;
}

/* char *
 * pretty_mask(char *mask);
 *
 * Input: A mask.
 * Output: A "user-friendly" version of the mask, in mask_buf.
 * Side-effects: mask_buf is appended to. mask_pos is incremented.
 * Notes: The following transitions are made:
 *  x!y@z =>  x!y@z
 *  y@z   =>  *!y@z
 *  x!y   =>  x!y@*
 *  x     =>  x!*@*
 *  z.d   =>  *!*@z.d
 *
 * If either nick/user/host are > than their respective limits, they are
 * chopped
 */
char *pretty_mask(char *mask)
{
	static char mask_buf[BUFSIZE];
        int old_mask_pos;
        char star[] = "*";
        char *nick = star, *user = star, *host = star;
	int mask_pos = 0;

        char *t, *at, *ex;
        char ne = 0, ue = 0, he = 0;    /* save values at nick[NICKLEN], et all */

	/* No point wasting CPU time if the mask is already valid */
	if (validhostmask(mask))
		return mask;

        if((size_t) (BUFSIZE - mask_pos) < strlen(mask) + 5)
                return (NULL);

        old_mask_pos = mask_pos;

        at = ex = NULL;
        if((t = strchr(mask, '@')) != NULL)
	{
                at = t;
                *t++ = '\0';
                if(*t != '\0')
                        host = t;

                if((t = strchr(mask, '!')) != NULL)
                {
                        ex = t;
                        *t++ = '\0';
                        if(*t != '\0')
                                user = t;
                        if(*mask != '\0')
                                nick = mask;
                }
                else
                {
                        if(*mask != '\0')
                                user = mask;
                }
        }
        else if((t = strchr(mask, '!')) != NULL)
        {
                ex = t;
                *t++ = '\0';
                if(*mask != '\0')
                        nick = mask;
                if(*t != '\0')
                        user = t;
        }
        else if(strchr(mask, '.') != NULL && strchr(mask, ':') != NULL)
        {
                if(*mask != '\0')
                        host = mask;
        }
        else
        {
                if(*mask != '\0')
                        nick = mask;
        }

        /* truncate values to max lengths */
        if(strlen(nick) > NICKLEN - 1)
        {
                ne = nick[NICKLEN - 1];
                nick[NICKLEN - 1] = '\0';
        }
        if(strlen(user) > USERLEN)
        {
                ue = user[USERLEN];
                user[USERLEN] = '\0';
        }
        if(strlen(host) > HOSTLEN)
        {
                he = host[HOSTLEN];
                host[HOSTLEN] = '\0';
        }

	snprintf(mask_buf, sizeof mask_buf, "%s!%s@%s", nick, user, host);

        /* restore mask, since we may need to use it again later */
        if(at)
                *at = '@';
        if(ex)
                *ex = '!';
        if(ne)
                nick[NICKLEN - 1] = ne;
        if(ue)
                user[USERLEN] = ue;
        if(he)
                host[HOSTLEN] = he;

	return mask_buf;
}

bool validtopic(const char *topic)
{
	int i;

	/* Most server protocols support less than this (depending on
	 * the lengths of the identifiers), but this should catch the
	 * ludicrous stuff.
	 */
	if (strlen(topic) > 450)
		return false;
	for (i = 0; topic[i] != '\0'; i++)
	{
		switch (topic[i])
		{
			case '\r':
			case '\n':
				return false;
		}
	}
	return true;
}

bool has_ctrl_chars(const char *text)
{
	int i;

	for (i = 0; text[i] != '\0'; i++)
	{
		if (text[i] > 0 && text[i] < 32)
			return true;
	}
	return false;
}

bool is_ircop(user_t *user)
{
	if (UF_IRCOP & user->flags)
		return true;

	return false;
}

bool is_admin(user_t *user)
{
	if (UF_ADMIN & user->flags)
		return true;

	return false;
}

/*bool is_autokline_exempt(user_t *user)*/
/*{*/
	/*mowgli_node_t *n;*/
	/*char buf[BUFSIZE];*/

	/*snprintf(buf, sizeof(buf), "%s@%s", user->user, user->host);*/
	/*MOWGLI_ITER_FOREACH(n, config_options.exempts.head)*/
	/*{*/
		/*if (0 == match(n->data, buf))*/
			/*return true;*/
	/*}*/
	/*return false;*/
/*}*/

char *sbytes(float x)
{
	if (x > 1073741824.0)
		return "GB";

	else if (x > 1048576.0)
		return "MB";

	else if (x > 1024.0)
		return "KB";

	return "B";
}

float bytes(float x)
{
	if (x > 1073741824.0)
		return (x / 1073741824.0);

	if (x > 1048576.0)
		return (x / 1048576.0);

	if (x > 1024.0)
		return (x / 1024.0);

	return x;
}

int srename(const char *old_fn, const char *new_fn)
{
#ifdef MOWGLI_OS_WIN
	unlink(new_fn);
#endif

	return rename(old_fn, new_fn);
}

char *combine_path(const char *parent, const char *child)
{
	char buf[BUFSIZE];

	return_val_if_fail(parent != NULL, NULL);
	return_val_if_fail(child != NULL, NULL);

	mowgli_strlcpy(buf, parent, sizeof buf);
	mowgli_strlcat(buf, "/", sizeof buf);
	mowgli_strlcat(buf, child, sizeof buf);

	return mowgli_strdup(buf);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */
