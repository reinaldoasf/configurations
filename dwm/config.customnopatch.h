/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10:style=Regular" };
static const char dmenufont[]       = "Hack Nerd Font:size=10:style=Bold";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#dddddd";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char custom1[]         = "#0F336F";
static const char custom2[]         = "#1D2330";
static const char custom3[]         = "#6A0888";
static const char custom4[]         = "#0174DF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, custom2, col_gray2 },
	[SchemeSel]  = { col_gray4, custom1,  custom3  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "krita",    NULL,       NULL,       1 << 7,       0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]         = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", custom2, "-nf", col_gray3, "-sb", custom4, "-sf", col_gray4, NULL };
static const char *termcmd[]          = { "st", NULL };
static const char *upvol[]            = { "pactl", "set-sink-volume", "0", "+1%", NULL };
static const char *downvol[]          = { "pactl", "set-sink-volume", "0", "-1%", NULL };
static const char *upvol5[]           = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol5[]         = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[]          = { "pactl", "set-sink-mute", "0", "toggle", NULL };
//static const char *brightup[]         = { "light", "-A", "1" };
//static const char *brightdown[]       = { "light", "-U"," 1" };
//static const char *brightup5[]        = { "light", "-A", "5" };
//static const char *brightdown5[]      = { "light", "-U"," 5" };
static const char *brightup[]         = { "xbacklight", "-inc", "1" };
static const char *brightdown[]       = { "xbacklight", "-dec"," 1" };
static const char *brightup5[]        = { "xbacklight", "-inc", "5" };
static const char *brightdown5[]      = { "xbacklight", "-dec"," 5" };
static const char *slock[]            = { "slock", NULL };
//static const char *scrotcmd[]         = { "scrot", "-e", "mv $f ~/Pictures/", NULL };
//static const char *scrotfocusedcmd[]  = { "scrot", "--focused", "-e", "mv $f ~/Pictures/", NULL };
static const char *scrotcmd[]         = { "import", "print.jpg", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_n,      spawn,          {.v = slock } },
	/* modifier                     key        function        argument */
	{ 0,                            XK_Print,  spawn,          {.v = scrotcmd } },
	//{ ShiftMask,                    XK_Print,  spawn,          {.v = scrotfocusedcmd } },
	//{ ControlMask,                  XK_Print,  spawn,          SHCMD("sleep 1s;scrot --select") },
	/* multimedia keys */
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn, {.v = upvol } },  
	{ 0,                            XF86XK_AudioLowerVolume,  spawn, {.v = downvol } },
	{ ShiftMask,                    XF86XK_AudioRaiseVolume,  spawn, {.v = upvol5 } },  
	{ ShiftMask,                    XF86XK_AudioLowerVolume,  spawn, {.v = downvol5 } },
	{ 0,                            XF86XK_AudioMute,         spawn, {.v = mutevol } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn, {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v = brightdown } },
	{ ShiftMask,                    XF86XK_MonBrightnessUp,   spawn, {.v = brightup5 } },
	{ ShiftMask,                    XF86XK_MonBrightnessDown, spawn, {.v = brightdown5 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

