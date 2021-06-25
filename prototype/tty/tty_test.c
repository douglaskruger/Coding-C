/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: test_msm_rdb_manager.c$";

/*==============================================================================
  Description:
    Test for the tty (Terminal)
==============================================================================*/
#include <unistd.h>   // for isatty()
#include <stdio.h>    // for fileno()

/*
    $ ./tty_test
    stdout is tty

    $ ./tty_test > tmp
    $ cat tmp
    stdout is not tty
*/
int
main()
{
    puts(isatty(fileno(stdout))
          ? "stdout is tty"
          : "stdout is not tty");
}
