#define _GNU_SOURCE

#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN    (16 * (EVENT_SIZE + 16))

int main(int argc,char** argv)
{
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init()");
    }
    if (argc<2) {
        perror("Need path(s) to watch");
    }
    for (int i=1; i<argc; i++) {

        int wd = inotify_add_watch(fd, argv[i], IN_ALL_EVENTS);
        if (wd < 0) {
            perror("inotify_add_watch");
        }
    }

    setbuf(stdout, 0);

    /* a dummy name, zero filled */
    char* last_name=calloc(1,1);

    while (1) {
        char buf[BUF_LEN];
        int i = 0;
        int len = read(fd, buf, BUF_LEN);

        while (i < len) {
            struct inotify_event* event;
            event = (struct inotify_event*) &buf[i];

            i += EVENT_SIZE + event->len;

            if (event->len==0) {
                continue;
            }
            if (strcmp(event->name,last_name)!=0) {
                printf("\n");
                /* drop old name */
                free(last_name);
                /* save new name */
                last_name=strdup(event->name);
                printf("%s: ", last_name);
            }
            if (event->mask & IN_ACCESS)  { putchar('R'); }
            if (event->mask & IN_MODIFY)  { putchar('W'); }
            if (event->mask & IN_ATTRIB)  { putchar('A'); }
            if (event->mask & IN_CLOSE)   { putchar('C'); }
            if (event->mask & IN_OPEN)    { putchar('O'); }
            if (event->mask & IN_MOVE)    { putchar('M'); }
            if (event->mask & IN_CREATE)  { putchar('N'); }
            if (event->mask & IN_DELETE)  { putchar('D'); }
            if (event->mask & IN_IGNORED) { putchar('I'); }
        }
    }
    return 0;
}
