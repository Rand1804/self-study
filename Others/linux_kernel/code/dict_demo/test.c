#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time_info = localtime(&current_time);

    if (local_time_info == NULL) {
        fprintf(stderr, "Failed to get local time\n");
        return 1;
    }

    printf("The current local time is: %02d:%02d:%02d\n", 
        local_time_info->tm_hour, 
        local_time_info->tm_min, 
        local_time_info->tm_sec
    );

    return 0;
}
