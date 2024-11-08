/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const char *fonts[]          = { "SauceCodeProNF:size=11:antialias=true:autohint=true", "Noto Color Emoji:size=11" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
/*                             firefox  terminal    folder  code gaming video   mail discord music*/
static const char *tags[] = { "",      "",        "",    "", "",   "",    "󰇮", "󰙯",   "" };

#define TAG_BROWSER_MASK 	1 << 0
#define TAG_TERM_MASK 		1 << 1
#define TAG_FILE_MASK 		1 << 2
#define TAG_CODE_MASK 		1 << 3
#define TAG_GAME_MASK 		1 << 4
#define TAG_VIDEO_MASK 		1 << 5
#define TAG_MAIL_MASK 		1 << 6
#define TAG_DISCORD_MASK 	1 << 7
#define TAG_MUSIC_MASK 		1 << 8

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class            	instance        title       tags mask   		switchtotag	isfloating	monitor */
    {"Pavucontrol",     	NULL,           NULL,       0,          		0,			1,          -1 },
    {"vorta",           	NULL,           NULL,       0,          		0,			1,          -1 },
    {"Galculator",      	NULL,           NULL,       0,          		0,			1,          -1 },
    {"Thunderbird",     	"Msgcompose",   NULL,       0,          		0,			1,          -1 },
    {"fehfloat",            NULL,           NULL,       0,                  0,          1,          -1 },

    {"zoom",            	NULL,           NULL,       TAG_VIDEO_MASK, 	0,			0,          -1 },
    {"zoom",            	NULL,           "Polls",    TAG_VIDEO_MASK, 	0,			1,          -1 },
	{"vlc",					NULL,			NULL,		TAG_VIDEO_MASK,		1,			0,			-1 },
	{"mpv",					NULL,			NULL,		TAG_VIDEO_MASK,		1,			0,			-1 },

    {NULL,              	"discord",      NULL,       TAG_DISCORD_MASK, 	0,			0,          -1 },

    {"Thunderbird",     	NULL,         	NULL,       TAG_MAIL_MASK, 		0,			0,           1 },
    {"mail",				NULL,			NULL,		TAG_MAIL_MASK,		1,			0,			-1 },

    {"Spotify",         	NULL,           NULL,       TAG_MUSIC_MASK, 	0,			0,          -1 },

	{ "St",      			"st",     		NULL,       TAG_TERM_MASK,      1,			0,          -1 },
    { "com.mitchellh.ghostty", "ghostty", NULL, TAG_TERM_MASK, 1, 0, -1 },

	{"firefox",				NULL,			NULL,		TAG_BROWSER_MASK,	1,			0,			-1 },

	{"VSCodium",			NULL,			NULL,		TAG_CODE_MASK,		1,			0,			-1 },
	{"Code",    			NULL,			NULL,		TAG_CODE_MASK,		1,			0,			-1 },
	{"jetbrains-idea",		NULL,			NULL,		TAG_CODE_MASK,		1,			0,			-1 },
	{"jetbrains-phpstorm",	NULL,			NULL,		TAG_CODE_MASK,		1,			0,			-1 },

	{"ranger",				NULL,	    	NULL,   	TAG_FILE_MASK,		1,			0,			-1 },
	{"Thunar",				NULL,			NULL,		TAG_FILE_MASK,		1,			0,			-1 },
    {"Filezilla",           NULL,           NULL,       TAG_FILE_MASK,      1,          0,          -1 },

	{"Lutris",				NULL,			NULL,		TAG_GAME_MASK,		1,			0,			-1 },
    {"Steam",               NULL,           NULL,       TAG_GAME_MASK,      0,          0,          -1 },
    {NULL,                  NULL,           "Event Tester", 0,              0,          0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

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
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL};
static const char *termcmd[]  = { "default-terminal", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", "-c", "scratchpad", NULL };

static const Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_c,      togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
    { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_e,      quit,           {1} },
    { MODKEY|ControlMask|ShiftMask, XK_e,      quit,           {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
    { "xrdb",           xrdb },
};
