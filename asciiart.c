#include "asciiart.h"
#include "math.h"
#include "random.h"
#include "term_control.h"

#pragma region boats

void art_print_sloop() {
  term_println("   o");
  term_println("  /|            \" Up with the Jolly Roger boys,");
  term_println("*|-+--*              And off we go to sea.");
  term_println("  \\|                 There's heaps of fun");
  term_println("   \\              When the Jolly Roger's hung,");
  term_println("\\  |> /           And the wind is on the lee. \"");
  term_println(" ~~~~~");
  term_println("                              - C.F. Chudleigh Candish");
}

void art_print_sub() {
  term_println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~oo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  term_println("                                 o o");
  term_println("                                 o ooo");
  term_println("                                   o oo");
  term_println("                                      o o      |   #)");
  term_println("                                       oo     _|_|_#_    -Scott Mason-");
  term_println("                                         o   | 751   |");
  term_println("    __                    ___________________|       |_________________");
  term_println("   |   -_______-----------                                              \\");
  term_println("  >|    _____                                                   --->     )");
  term_println("   |__ -     ---------_________________________________________________ /");
}

void art_print_boat() {
  term_println("                                     |__");
  term_println("                                     |\\/");
  term_println("                                     ---");
  term_println("                                     / | [");
  term_println("                              !      | |||");
  term_println("                            _/|     _/|-++'");
  term_println("                        +  +--|    |--|--|_ |-");
  term_println("                     { /|__|  |/\\__|  |--- |||__/");
  term_println("                    +---------------___[}-_===_.'____               /\\");
  term_println("                ____`-' ||___-{]_| _[}-  |     |_[___\\==--          \\/   _");
  term_println(" __..._____--==/___]_|__|_____________________________[___\\==--___,-----' .7");
  term_println("|                                                                   BB-61/");
  term_println(" \\_______________________________________________________________________|");
  term_println("  Matthew Bace");
}

#pragma endregion

void art_print_main() {
  switch (math_mod(rng_getRandomValue_waiting(), 3)) {
  case 0:
    art_print_sloop();
    break;
  case 1:
    art_print_sub();
    break;
  case 2:
    art_print_boat();
    break;
  }
}

void art_print_victory() {
  term_println("\e[33m");
  term_println("                            .                   s                                            ..");
  term_println("                       @88>                :8                               ..          888B.");
  term_println("     ...     ..        %%8P                .88           u.      .u    .    @L          48888E");
  term_println("  :~\"\"888h.:^\"888:      .          .     :888ooo  ...ue888b   .d88B :@8c  9888i   .dL  '8888'");
  term_println(" 8X   `8888X  8888>   .@88u   .udR88N  -*8888888  888R Y888r =\"8888f8888r `Y888k:*888.  Y88F");
  term_println("X888n. 8888X  ?888>  ''888E` <888'888k   8888     888R I888>   4888>'88\"    888E  888I  '88");
  term_println("'88888 8888X   ?**h.   888E  9888 'Y\"    8888     888R I888>   4888> '      888E  888I   8F");
  term_println("  `*88 8888~ x88x.     888E  9888        8888     888R I888>   4888>        888E  888I   4");
  term_println(" ..<\"  88*`  88888X    888E  9888       .8888Lu= u8888cJ888   .d888L .+     888E  888I   .");
  term_println("    ..XC.    `*8888k   888&  ?8888u../  ^%%888*    \"*888*P\"    ^\"8888*\"     x888N><888'  u8N.");
  term_println("  :888888H.    `%%88>   R888\"  \"8888P'     'Y\"       'Y\"          \"Y\"        \"88\"  888  \"*88%%");
  term_println(" <  `\"888888:    X\"     \"\"      \"P'                                               88F    \"\"");
  term_println("       %%888888x.-`                                                               98\"");
  term_println("         \"\"**\"\"                                                                ./\"");
  term_println("                                                                               ~`");
  term_print("\e[0m");
}

void art_print_loss() {
  term_println("\e[31m");
  term_println("  ▓██   ██▓ ▒█████   █    ██      ██████  █    ██  ███▄    █  ██ ▄█▀ ▐██▌");
  term_println("   ▒██  ██▒▒██▒  ██▒ ██  ▓██▒   ▒██    ▒  ██  ▓██▒ ██ ▀█   █  ██▄█▒  ▐██▌");
  term_println("    ▒██ ██░▒██░  ██▒▓██  ▒██░   ░ ▓██▄   ▓██  ▒██░▓██  ▀█ ██▒▓███▄░  ▐██▌");
  term_println("    ░ ▐██▓░▒██   ██░▓▓█  ░██░     ▒   ██▒▓▓█  ░██░▓██▒  ▐▌██▒▓██ █▄  ▓██▒");
  term_println("    ░ ██▒▓░░ ████▓▒░▒▒█████▓    ▒██████▒▒▒▒█████▓ ▒██░   ▓██░▒██▒ █▄ ▒▄▄");
  term_println("     ██▒▒▒ ░ ▒░▒░▒░ ░▒▓▒ ▒ ▒    ▒ ▒▓▒ ▒ ░░▒▓▒ ▒ ▒ ░ ▒░   ▒ ▒ ▒ ▒▒ ▓▒ ░▀▀▒");
  term_println("   ▓██ ░▒░   ░ ▒ ▒░ ░░▒░ ░ ░    ░ ░▒  ░ ░░░▒░ ░ ░ ░ ░░   ░ ▒░░ ░▒ ▒░ ░  ░");
  term_println("   ▒ ▒ ░░  ░ ░ ░ ▒   ░░░ ░ ░    ░  ░  ░   ░░░ ░ ░    ░   ░ ░ ░ ░░ ░     ░");
  term_println("   ░ ░         ░ ░     ░              ░     ░              ░ ░  ░    ░");
  term_println("   ░ ░");
  term_print("\e[0m");
}

void art_print_bargraph(int hits, int misses) {
  term_print("\e[41m");
  for (int i = 0; i < hits; i++) {
    term_printc(' ');
  }
  term_print("\e[44m");
  for (int i = 0; i < hits; i++) {
    term_printc(' ');
  }
  term_println("\e[0m");
}
