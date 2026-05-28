#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *path = "/sys/bus/w1/devices/28-012036415ce5/w1_slave";
    FILE *fp;
    char buffer[256];
    int temp_milli = 0;
    int valid = 0;

    //printf("Starting DS18B20 read...\n");

    fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open DS18B20 device");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        // Debug: näytä luettu rivi
        //printf("LINE: %s", buffer);

        // Tarkista CRC (pitää olla YES)
        if (strstr(buffer, "YES")) {
            valid = 1;
        }

        // Etsi lämpötila
        char *t_ptr = strstr(buffer, "t=");
        if (t_ptr && valid) {
            temp_milli = atoi(t_ptr + 2);
            printf("DS18B20 Temperature: %.2f °C\n", temp_milli / 1000.0);
        }
    }

    fclose(fp);
    return 0;
}
