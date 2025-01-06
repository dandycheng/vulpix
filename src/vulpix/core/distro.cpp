#include "distro.h"
#include "file.h"
#include "logs.h"

distro_t getDistro(void)
{
    string distro { findTextInFile(OS_RELEASE_PATH, std::regex("^ID", std::regex_constants::ECMAScript)) };

    if (distro.length() > 0)
    {
        distro = distro.substr(3, distro.length());    // Trim off the "ID="
        std::transform(distro.begin(), distro.end(), distro.begin(), ::tolower);
        if (distro == "ubuntu") return UBUNTU;
        if (distro == "opensuse") return OPEN_SUSE;
        if (distro == "redhat") return REDHAT;
    }

    DEBUG_LOG(LOG_ERROR, "Unable to open file: %s", OS_RELEASE_PATH);

    return UNKNOWN_DISTRO;
}