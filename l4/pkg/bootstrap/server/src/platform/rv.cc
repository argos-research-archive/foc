/*!
 * \file
 * \brief  Support for the rv platform
 *
 * \date   2011
 * \author Adam Lackorzynski <adam@os.inf.tu-dresden.de>
 *
 */
/*
 * (c) 2008-2011 Author(s)
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 */

#include "support.h"

#include <l4/drivers/uart_pl011.h>

namespace {

class Platform_arm_rv : public Platform_single_region_ram
{
  bool probe() { return true; }

  /* enfore two memory regions */
  void setup_memory_map()
  {
    Region_list *ram = mem_manager->ram;
    Region_list *regions = mem_manager->regions;
    /* 2x512 MB */
    ram->add(Region::n(0x20000000, 0x40000000, ".ram", Region::Ram));
    ram->add(Region::n(0x70000000, 0x90000000, ".ram", Region::Ram));
  }

  void init()
  {
    static L4::Io_register_block_mmio r(0x10009000);
    static L4::Uart_pl011 _uart(24019200);
    _uart.startup(&r);
    set_stdio_uart(&_uart);
  }
};

}

REGISTER_PLATFORM(Platform_arm_rv);
