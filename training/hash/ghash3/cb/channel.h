#pragma once
#include "mediasoup.h"
struct channel;

typedef void(*on_channel_send)(struct channel*, char*);
struct channel{
ee_t*ee;
on_channel_send request;
};
struct channel * channel_new(void);
