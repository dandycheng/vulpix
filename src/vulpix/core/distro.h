#ifndef DISTRO_H
#define DISTRO_H

#define OS_RELEASE_PATH "/etc/os-release"

typedef enum Distro
{
    UBUNTU,
    REDHAT,
    OPEN_SUSE,
    UNKNOWN_DISTRO
} distro_t;

distro_t getDistro(void);

#endif