#include <linux/spinlock.h>

rwlock m;
read_lock(m);
    //critical section
read_unlock(m);


write_lock(m);
    // critical section
write_unlock(m);