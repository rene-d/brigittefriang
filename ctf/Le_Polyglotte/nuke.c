#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char byte;

int checkpassword(char *param_1)
{
  int i;
  uint local_78 [12];
  uint local_48 [14];

  local_78[0] = 2;
  local_78[1] = 4;
  local_78[2] = 9;
  local_78[3] = 0xc;
  local_78[4] = 1;
  local_78[5] = 2;
  local_78[6] = 9;
  local_78[7] = 3;
  local_78[8] = 2;
  local_78[9] = 1;
  local_78[10] = 0xd;
  local_48[0] = 0x54;
  local_48[1] = 0x52;
  local_48[2] = 0x4f;
  local_48[3] = 0x4c;
  local_48[4] = 0x4f;
  local_48[5] = 0x4c;
  local_48[6] = 0x4f;
  local_48[7] = 0x4c;
  local_48[8] = 0x4f;
  local_48[9] = 0x4c;
  local_48[10] = 0x4f;

  i = 0;
  while (i < 0xb) {
    local_48[i] = local_48[i] ^ local_78[i];
    i = i + 1;
  }

  return 0;
}



int main(void)
{
  size_t len;
  byte *password;
  long in_FS_OFFSET;
  char buffer [24];

  puts("Operation Soleil Atomique");
  printf("Entrez le mot de passe : ");
  fgets(buffer,0x10,stdin);
  len = strlen(buffer);
  password = (byte *)malloc(len + 1);
  strcpy((char *)password,buffer);
  checkpassword((char *)password);
  if (((((((password[1] ^ *password) == 0x69) && ((password[2] ^ password[1]) == 0x6f)) &&
        ((password[3] ^ password[2]) == 0x38)) &&
       (((password[4] ^ password[3]) == 0x56 && ((password[5] ^ password[4]) == 0x50)))) &&
      (((password[6] ^ password[5]) == 0x57 &&
       (((password[7] ^ password[6]) == 0x50 && ((password[8] ^ password[7]) == 0x56)))))) &&
     (((password[9] ^ password[8]) == 6 && (password[9] == 0x34)))) {
    puts("Bravo");
    exit(0);
  }
  puts("Mauvais mot de passe");

  return 0;
}
