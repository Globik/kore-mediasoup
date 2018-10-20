#pragma once
#include <ee.h>
#include "channel.h"
#include <stdio.h>

struct server;

typedef void(*on_emit)(struct server*, const char*, void*);
typedef void(*on_close)(struct server*);

typedef int(*on_funny)(void*);
typedef int(*on_create_something)(struct server*, int, on_funny);

//void ersti_cb(struct channel*,char*);

struct server{
	ee_t*ee;
	struct channel*ch;
	on_emit emit;
	on_close close;
	on_create_something create_something;
};

struct out_data{
const char*str;	
};
struct server*server_new(ee_t*,struct channel*);
