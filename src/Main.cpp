#include "Cards/Cards.h"

int main(int argc, char const *argv[]) {
  Cards cards;

  cards.load_file("config.yaml");

  printf("Name: %s \n", cards.items[0].name.c_str());
  printf("Icon Type: %s \n", cards.items[0].icon.type.c_str());

  return 0;
}
