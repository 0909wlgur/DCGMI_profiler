#ifndef PROFILER_H
#define PROFILER_H

// Debug print enable
#define DEBUG
#ifndef DEBUG
#define dp(fmt,args...) 
#define dlp(fmt,args...) 
#else
#define dp(fmt,args...) printf( fmt, ## args )
#define dlp(fmt,args...) printf( "[%s: line%d] " fmt, __func__,__LINE__, ## args )
#endif

#endif