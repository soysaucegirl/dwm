/* See LICENSE file for copyright and license details. */ /* This is bloated as shit and needs to have a patch in particular removed. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */

/* bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* gaps */
static const int gappih             = 12;
static const int gappiv             = 12;
static const int gappoh             = 12;
static const int gappov             = 12;
static const int smartgaps          = 0;

/* fonts */
static const char *fonts[]          = { "mononoki:size=10",
                                        "Font Awesome 5 Free Solid:size=8:antialias=true:autohint=true",
                                        "Font Awesome 5 Brands Regular:size=8:antialias=true:autohint=true",
                                        "JoyPixels:pixelsize=12:antialias=true:autohint=true"
};
static const char dmenufont[]       = "mononoki:size=10";

/* colours */
static const char normbgcolor[]     = "#222222";
static const char normbordercolor[] = "#444444";
static const char normfgcolor[]     = "#bbbbbb";
static const char selfgcolor[]      = "#eeeeee";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const unsigned int baralpha  = OPAQUE; 
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { baralpha, baralpha, borderalpha },
	[SchemeSel]  = { baralpha, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* rules */
static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class     instance    title       tags mask     isfloating   monitor */
        { NULL,      NULL,       NULL,       0,            1,           -1 },
        { NULL,      "st",       NULL,       0,            0,           -1 },
        { NULL,      NULL,       "ncmpcpp",  1 << 8                        },
        { NULL,      NULL,       "neomutt",  1 << 7                        },
        { "Chromium", NULL,      "Chromium", 1,            1,           -1 },
        { "discord", NULL,       NULL,       2,            1,           -1 },
        { NULL,      NULL,       "Spotify",  1 << 8,       1               },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include <X11/XF86keysym.h>
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "TTT",      bstack },
	{ "[M]",      monocle },
	{ "[D]",      deck },
 	{ "[@]",      spiral },  
 	{ "[\\]",     dwindle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "HHH",      grid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* keyboard */

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

    /* window manager */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_BackSpace, killclient,  {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
    { MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_equal,  defaultgaps,    {0} },
    { MODKEY|ShiftMask,             XK_minus,  togglegaps,     {0} },
	{ MODKEY,                       XK_w,      togglefloating, {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
    { MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[6]} },
    { MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[7]} },
    { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[8]} },
    { MODKEY,                       XK_p,      setlayout,      {.v = &layouts[9]} },
    { MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },

    /* tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    /* audio */
    { 0, XF86XK_AudioMute,          spawn,     SHCMD("pactl set-sink-mute 0 toggle") }, 
    { 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("pactl set-sink-volume 0 +5%") },
    { 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("pactl set-sink-volume 0 -5%") },

    /* brightness */
    { 0, XF86XK_MonBrightnessUp,    spawn,     SHCMD("xbacklight -inc 15") },
    { 0, XF86XK_MonBrightnessDown,  spawn,     SHCMD("xbacklight -dec 15") },

    /* essentials */
    { MODKEY,                       XK_Return, spawn,          SHCMD("$TERMINAL -T 'wow a terminal'") },
    { MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_semicolon, spawn,       SHCMD("slock") },
    { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("import /tmp/shot.png") },
    { MODKEY,                       XK_space,  spawn,          SHCMD("keymash") },
    /* music controls */
    { MODKEY,                       XK_backslash, spawn,       SHCMD("mpc toggle") },   
    { MODKEY|ShiftMask,             XK_bracketright, spawn,    SHCMD("mpc next") },
    { MODKEY|ShiftMask,             XK_bracketleft, spawn,     SHCMD("mpc prev") },
    { MODKEY,                       XK_bracketright, spawn,    SHCMD("mpc seekthrough +5") },
    { MODKEY,                       XK_bracketleft, spawn,     SHCMD("mpc seekthrough -5") },

    /* application shortcuts */
    { MODKEY|ControlMask,           XK_w,      spawn,          SHCMD("$TERMINAL -e nmtui") },
    { MODKEY,                       XK_m,      spawn,          SHCMD("$TERMINAL -e ncmpcpp") },
    { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("spotify") },
    { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("$TERMINAL -e neomutt") },
    { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("$TERMINAL -e nnn -d -H -r") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERMINAL") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
