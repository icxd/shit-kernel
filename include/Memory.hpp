#pragma once

#include <LibBase/Common.hpp>
#include <LibBase/Debug.hpp>
#include <LibBase/Logger.hpp>
#include <LibC/stddef.h>
#include <LibC/stdint.h>
#include <Multiboot.h>

namespace Memory {

void init(multiboot_info_t *mbi);

} // namespace Memory