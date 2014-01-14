#ifndef VALKYRIE_MODE_H
#define VALKYRIE_MODE_H

static struct cmode_ mode_list[] = {
  { 'i', CMODE_INVITE },
  { 'm', CMODE_MOD    },
  { 'n', CMODE_NOEXT  },
  { 'p', CMODE_PRIV   },
  { 's', CMODE_SEC    },
  { 't', CMODE_TOPIC  },
  { 'r', CMODE_REGONLY},
  { 'z', CMODE_OPMOD  },
  { 'g', CMODE_FINVITE},
  { 'L', CMODE_EXLIMIT},
  { 'P', CMODE_PERM   },
  { 'F', CMODE_FTARGET},
  { 'Q', CMODE_DISFWD },

  /* following modes are added as extensions */
  { 'N', CMODE_NPC       },
  { 'S', CMODE_SSLONLY   },
  { 'O', CMODE_OPERONLY  },
  { 'A', CMODE_ADMINONLY },
  { 'c', CMODE_NOCOLOR   },
  { 'C', CMODE_NOCTCP    },

  { '\0', 0 }
};

//static struct extmode ignore_mode_list[] = {
  //{ 'f', check_forward },
  //{ 'j', check_jointhrottle },
  //{ '\0', 0 }
//};

static struct cmode_ status_mode_list[] = {
  { 'o', CSTATUS_OP    },
  { 'v', CSTATUS_VOICE },
  { '\0', 0 }
};

static struct cmode_ prefix_mode_list[] = {
  { '@', CSTATUS_OP    },
  { '+', CSTATUS_VOICE },
  { '\0', 0 }
};

static struct cmode_ user_mode_list[] = {
  { 'p', UF_IMMUNE   },
  { 'a', UF_ADMIN    },
  { 'i', UF_INVIS    },
  { 'o', UF_IRCOP    },
  { 'D', UF_DEAF     },
  { '\0', 0 }
};

#endif
