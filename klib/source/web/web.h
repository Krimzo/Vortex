#pragma once


// Socket
#include "web/socket/socket.h"


namespace kl {
    std::string download_website(const std::string& url, int buffer_size = 65536);
}
