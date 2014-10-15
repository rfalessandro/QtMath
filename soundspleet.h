#ifndef SOUNDSPLEET_H
#define SOUNDSPLEET_H

class SoundSpleet
{


protected:
    unsigned char **buf;//array with buffer splits.
    unsigned int *szBuff;//array with split size
    int count;

    void clear();
public:
    SoundSpleet();
    ~SoundSpleet();
    void split(unsigned char *buffer, unsigned int n, int nChannel, int bitDepth);
    int getCount() const;//get count of splits
    unsigned char *getBuffer(int pos, int *sz);//get buffer at pos and return size of it.

};

#endif // SOUNDSPLEET_H
