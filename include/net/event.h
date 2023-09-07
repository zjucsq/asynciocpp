#pragma once

#include <sys/epoll.h>

#include "../handle.h"

using Flags_t = uint32_t;

struct Event {
  enum Flags : Flags_t { EVENT_READ = EPOLLIN, EVENT_WRITE = EPOLLOUT };
  int fd;
  Flags flags;
  HandleInfo handle_info;
};