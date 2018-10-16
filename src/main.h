#ifndef _MAIN_H_
#define _MAIN_H_

// ------------------------------------------------------------------------
struct rwlock_t readings_lock;
struct read
{
    uint32_t voltage : 24;
    uint32_t energy : 24;
    uint16_t current : 16;
    uint16_t power : 16;
};
struct read readings[6];

// ------------------------------------------------------------------------
int main();

// ------------------------------------------------------------------------

#endif /* _MAIN_H_ */
