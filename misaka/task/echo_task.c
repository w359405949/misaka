#include "link.h"
#include "task.h"
#include <sys/time.h>
#include <math.h>

static int peerid = 100;

//echo unpack
int echo_unpack(struct stream *s, struct peer *peer)
{
    //new peer, mark peer when first packet come 
    if(NULL == s){
        zlog_debug("register new tcp peer as %d\n", peerid);
        peer->drole = peerid++;
        peer_register(peer);
    }else{
    
    }
    return IO_PACKET;
}

//echo pack
int  echo_pack(struct stream *s, struct peer *peer)
{
    return IO_PACKET;
}

//echo event, send this  packet back
void echo_event(struct stream *s)
{
    stream_dir_exchange(s);
    //mark route into net queue
    s->type = EVENT_NET;
    misaka_packet_usr_route(s);
}

int echo_register(void){
    misaka_register_evnet(echo_event, EVENT_ECHO);
    return 0;
}
