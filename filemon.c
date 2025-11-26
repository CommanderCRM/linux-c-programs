#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main() {
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, ".", IN_MODIFY | IN_CREATE | IN_DELETE);
    
    char buffer[BUF_LEN];
    printf("Monitoring current directory... (Ctrl+C to stop)\n");
    
    while(1) {
        int length = read(fd, buffer, BUF_LEN);
        for(int i = 0; i < length;) {
            struct inotify_event *event = (struct inotify_event*)&buffer[i];
            if(event->len) {
                if(event->mask & IN_CREATE) printf("File created: %s\n", event->name);
                if(event->mask & IN_MODIFY) printf("File modified: %s\n", event->name);
                if(event->mask & IN_DELETE) printf("File deleted: %s\n", event->name);
            }
            i += EVENT_SIZE + event->len;
        }
    }
    
    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}
