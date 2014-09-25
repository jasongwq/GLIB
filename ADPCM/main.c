/* realize the adpcm code and decode, bandwidth needed is 32kbps,
   is half of the ulaw coded, 64kbps
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <linux/soundcard.h>

#include "adpcm.h"
  
#define RATE     8000 
#define SIZE     AFMT_S16_LE 
#define CHANNELS 2
#define FRAME_SIZE  1000

int main(int argc, char *argv[])
{
    int fd,mid;
    int arg;
    int status;
    int i;
    // for encode use
    unsigned char inbuf[FRAME_SIZE*4];  // 2 channels , 16bit data , so *4
    short         inenc[FRAME_SIZE];    // 1 channel, 16bit data, but short type, so *1
    unsigned char encbuf[FRAME_SIZE/2];
    // for decode use
    short         decbuf[FRAME_SIZE];   // decode restore inenc
    unsigned char outbuf[FRAME_SIZE*4]; // restore inbuf 
    // adpcm
    struct adpcm_state enc_state, dec_state;
    //----------------------------------------------------------------------
    fd = open("/dev/dsp", O_RDWR);
    arg = SIZE;
    printf("SIZE:=%d\n",arg);
    if (fd < 0)
    {
        perror("Open /dev/dsp fail");
        exit(1);
    }

    arg = SIZE;
    status = ioctl(fd, SNDCTL_DSP_SETFMT, &arg);
    if (status == -1)
    {
        perror("SNDCTL_DSP_SETFMT ioctl failed");
        exit(1);
    }

    arg    = CHANNELS;
    status = ioctl(fd, SNDCTL_DSP_CHANNELS, &arg);
    if (status == -1)
    {
        perror("SNDCTL_DSP_CHANNELS ioctl failed");
        exit(1);
    }

    ioctl(fd, SOUND_PCM_READ_CHANNELS, &arg);
    if (arg != CHANNELS)
    {
        perror("unable to set channels");
        exit(1);
    }

    arg = RATE;
    status = ioctl(fd, SNDCTL_DSP_SPEED, &arg);
    if (status == -1)
    {
        perror("SNDCTL_DSP_SPEED ioctl failed");
        exit(1);
    }

    if (arg != RATE)
    {
        perror("unable to set rate");
        exit(1);
    }

    mid = open("/dev/mixer",O_RDWR);
    arg = SOUND_MASK_MIC;
    ioctl(mid,SOUND_MIXER_READ_VOLUME,(char *)&arg);
    printf("volume is:%d\n",arg);
    arg = 55000;
    ioctl(mid,SOUND_MIXER_WRITE_VOLUME,(char *)&arg);
    //----------------------------------------------------------------------
    // encode
    enc_state.valprev = 0;
    enc_state.index = 0;
    //----------------------------------------------------------------------
    // decode
    dec_state.valprev = 0;
    dec_state.index = 0;
    //----------------------------------------------------------------------
    while(1)
    {
        // encode
        printf("encode\n");
        read(fd, inbuf, sizeof(inbuf));
        for(i=0;i<FRAME_SIZE*4;i+=4) inenc[i/4] = inbuf[i] + inbuf[i+1]*256;  
        adpcm_coder(inenc, encbuf, FRAME_SIZE, &enc_state);

        // decode
        printf("decode\n");
        adpcm_decoder(encbuf, decbuf, FRAME_SIZE/2, &dec_state); 
        for(i=0;i<FRAME_SIZE;i++)
        {
            outbuf[i*4] = decbuf[i] & 0xff;
            outbuf[i*4+1] = decbuf[i] >> 8;
            outbuf[i*4+2] = decbuf[i] & 0xff;
            outbuf[i*4+3] = decbuf[i] >> 8;
        }
        write(fd, outbuf, sizeof(outbuf)); 
    }
    //----------------------------------------------------------------------

    printf("finished\n");
    return 0;
}  
