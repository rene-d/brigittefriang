//  _____       _
// | ____|_ __ (_) __ _ _ __ ___   __ _
// |  _| | '_ \| |/ _` | '_ ` _ \ / _` |
// | |___| | | | | (_| | | | | | | (_| |
// |_____|_| |_|_|\__, |_| |_| |_|\__,_|
//                |___/

// rene-d 2020

// https://www.root-me.org/fr/Challenges/Cryptanalyse/Machine-Enigma

// ./enigma B MDC III IV I "DE BK JX MU LV" < secret.txt
// ./enigma B MQT-ANR III IV I "DE BK JX MU LV" < secret.txt
// flag: LEMISANTHROPE

// https://en.wikipedia.org/wiki/Enigma_machine
// http://users.telenet.be/d.rijmenants/en/enigmatech.htm
// https://en.wikipedia.org/wiki/Enigma_rotor_details
// https://military.wikia.org/wiki/Enigma_machine
// https://www.amazon.com/Enigma-Achilles-Heel-Hugh-Skillen/dp/0951519018

// http://www.irem.unilim.fr/fileadmin/user_upload/Convergences/tpe_enigma.pdf
// Juli 1941: dans la video https://www.youtube.com/watch?v=JiCvNPkkPmU (2'10)
// https://summersidemakerspace.ca/projects/enigma-machine/
// https://www.infsec.cs.uni-saarland.de/teaching/SS07/Proseminar/slides/maurer-Enigma.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include <time.h>
#include <errno.h>

//
// implémentation Enigma M3
//

typedef unsigned char byte;
typedef unsigned short position;

#define INVALID_BYTE (0xff)
#define INVALID_POS (0xffff)

#define KEY_AAA (0)
#define KEY_MAX (26 * 26 * 26)

struct Rotor
{
    byte forward_wiring[26];
    byte backward_wiring[26];
    byte notches[2];
    const char *name;
};

struct Reflector
{
    byte wiring[26];
    const char *name;
};

struct Enigma
{
    const struct Rotor *rotor1;        // Walze, right (i.e. entry)
    const struct Rotor *rotor2;        // middle
    const struct Rotor *rotor3;        // left
    const struct Reflector *reflector; // Umkehrwalze
    byte plugboard[26];                // Stecker
    byte ring1;                        // Ringstellung (right)
    byte ring2;                        //
    byte ring3;                        //
    byte rotor1_position;              // Spruchschlussel (right)
    byte rotor2_position;              //
    byte rotor3_position;              //
};

// Enigma components
//
struct Reflector ROTOR_Reflector_A;
struct Reflector ROTOR_Reflector_B;
struct Reflector ROTOR_Reflector_C;

struct Reflector ROTOR_Reflector_B_thin;
struct Reflector ROTOR_Reflector_C_thin;

struct Rotor ROTOR_I;
struct Rotor ROTOR_II;
struct Rotor ROTOR_III;
struct Rotor ROTOR_IV;
struct Rotor ROTOR_V;
struct Rotor ROTOR_VI;
struct Rotor ROTOR_VII;
struct Rotor ROTOR_VIII;

struct Rotor *ROTORS[] = {
    &ROTOR_I,
    &ROTOR_II,
    &ROTOR_III,
    &ROTOR_IV,
    &ROTOR_V,
    &ROTOR_VI,
    &ROTOR_VII,
    &ROTOR_VIII,
    NULL,
};

static inline byte to_byte(char c)
{
    if (isupper(c))
        return c - 'A';
    if (islower(c))
        return c - 'a';
    return INVALID_BYTE;
}

bool reflector_init(struct Reflector *r, const char *wiring, const char *name)
{
    for (size_t i = 0; i < 26; ++i)
    {
        byte e = to_byte(wiring[i]);
        if (e == INVALID_BYTE)
            return false;
        r->wiring[i] = e;
    }
    r->name = name;

    return true;
}

bool rotor_init(struct Rotor *r, const char *wiring, const char *notches, const char *name)
{
    for (size_t i = 0; i < 26; ++i)
    {
        byte e = to_byte(wiring[i]);
        if (e == INVALID_BYTE)
            return false;

        r->forward_wiring[i] = e;
        r->backward_wiring[e] = i;
    }

    assert(isupper(notches[0]));
    assert(isupper(notches[1]) || notches[1] == 0);

    r->notches[0] = notches[0] - 'A';
    r->notches[1] = (notches[1] != 0) ? (notches[1] - 'A') : INVALID_BYTE;
    r->name = name;

    return true;
}

bool enigma_plugboard(struct Enigma *e, const char *plugboard)
{
    for (size_t i = 0; i < 26; ++i)
    {
        e->plugboard[i] = i;
    }

    for (const char *p = plugboard; *p; ++p)
    {
        byte a = to_byte(p[0]);
        byte b = to_byte(p[1]);

        if (a != INVALID_BYTE && b != INVALID_BYTE)
        {
            if (e->plugboard[a] != a || e->plugboard[b] != b)
            {
                //printf("Invalid plugboard (%s)\n", plugboard);
                return false;
            }

            e->plugboard[a] = b;
            e->plugboard[b] = a;

            p += 1;
        }
    }

    return true;
}

void enigma_set_position(struct Enigma *e, position key)
{
    e->rotor3_position = (key / 676) % 26;
    e->rotor2_position = (key / 26) % 26;
    e->rotor1_position = key % 26;
}

bool enigma_init(struct Enigma *e,
                 position key,
                 position ringstellung,
                 const struct Rotor *rotors[3],
                 const struct Reflector *reflector,
                 const char *plugboard)
{
    e->reflector = reflector;

    e->rotor3 = rotors[0];
    e->rotor2 = rotors[1];
    e->rotor1 = rotors[2];

    e->ring3 = (ringstellung / 676) % 26;
    e->ring2 = (ringstellung / 26) % 26;
    e->ring1 = ringstellung % 26;

    enigma_set_position(e, key);

    return enigma_plugboard(e, plugboard);
}

position enigma_key(const char *key)
{
    if (strlen(key) >= 3)
    {
        byte b3 = to_byte(key[0]);
        byte b2 = to_byte(key[1]);
        byte b1 = to_byte(key[2]);

        if (b1 == INVALID_BYTE || b2 == INVALID_BYTE || b3 == INVALID_BYTE)
            return INVALID_POS;

        return (b3 * 26 + b2) * 26 + b1;
    }

    return INVALID_POS;
}

static inline bool rotor_will_notch(const struct Rotor *r, byte position)
{
    return (r->notches[0] == position) || (r->notches[1] == position);
}

static inline byte rotor_encipher(const struct Rotor *r, bool forward, byte position, byte ring, byte c)
{
    position = (position + 26 - ring) % 26;
    c = (position + c) % 26;
    if (forward)
    {
        c = r->forward_wiring[c];
    }
    else
    {
        c = r->backward_wiring[c];
    }
    return (c + 26 - position) % 26;
}

static inline byte reflector_encipher(const struct Reflector *r, byte c)
{
    return r->wiring[c];
}

static byte enigma_encipher(struct Enigma *e, byte c)
{
    // plugboard
    c = e->plugboard[c];

    // rotor movement
    if (rotor_will_notch(e->rotor2, e->rotor2_position))
    {
        e->rotor2_position = (e->rotor2_position + 1) % 26;
        e->rotor3_position = (e->rotor3_position + 1) % 26;
    }
    if (rotor_will_notch(e->rotor1, e->rotor1_position))
    {
        e->rotor2_position = (e->rotor2_position + 1) % 26;
    }
    e->rotor1_position = (e->rotor1_position + 1) % 26;

    // forward
    c = rotor_encipher(e->rotor1, true, e->rotor1_position, e->ring1, c);
    c = rotor_encipher(e->rotor2, true, e->rotor2_position, e->ring2, c);
    c = rotor_encipher(e->rotor3, true, e->rotor3_position, e->ring3, c);

    // reflection
    c = reflector_encipher(e->reflector, c);

    // backward
    c = rotor_encipher(e->rotor3, false, e->rotor3_position, e->ring3, c);
    c = rotor_encipher(e->rotor2, false, e->rotor2_position, e->ring2, c);
    c = rotor_encipher(e->rotor1, false, e->rotor1_position, e->ring1, c);

    // plugboard
    c = e->plugboard[c];

    return c;
}

char encipher_char(struct Enigma *e, char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        c = enigma_encipher(e, c - 'A') + 'A';
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        c = enigma_encipher(e, c - 'a') + 'a';
    }

    return c;
}

void encipher_text(struct Enigma *e, const char *input, char *output)
{
    while (*input != '\0')
    {
        *(output++) = encipher_char(e, *(input++));
    }
    *(output++) = '\0';
}

void encipher_print(struct Enigma *e, const char *text)
{
    for (const char *p = text; *p; ++p)
    {
        printf("%c", encipher_char(e, *p));
    }
}

void enigma_components_init()
{
    // https://www.cryptomuseum.com/crypto/enigma/wiring.htm#10
    reflector_init(&ROTOR_Reflector_A, "EJMZALYXVBWFCRQUONTSPIKHGD", "UKW A");
    reflector_init(&ROTOR_Reflector_B, "YRUHQSLDPXNGOKMIEBFZCWVJAT", "UKW B");
    reflector_init(&ROTOR_Reflector_C, "FVPJIAOYEDRZXWGCTKUQSBNMHL", "UKW C");

    reflector_init(&ROTOR_Reflector_B_thin, "ENKQAUYWJICOPBLMDXZVFTHRGS", "UKW B thin");
    reflector_init(&ROTOR_Reflector_C_thin, "RDOBJNTKVEHMLFCWZAXGYIPSUQ", "UKW C thin");

    rotor_init(&ROTOR_I, "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Q", "I");
    rotor_init(&ROTOR_II, "AJDKSIRUXBLHWTMCQGZNPYFVOE", "E", "II");
    rotor_init(&ROTOR_III, "BDFHJLCPRTXVZNYEIWGAKMUSQO", "V", "III");
    rotor_init(&ROTOR_IV, "ESOVPZJAYQUIRHXLNFTGKDCMWB", "J", "IV");
    rotor_init(&ROTOR_V, "VZBRGITYUPSDNHLXAWMJQOFECK", "Z", "V");

    // Kriegsmarine
    rotor_init(&ROTOR_VI, "JPGVOUMFYQBENHZRDKASXLICTW", "ZM", "VI");
    rotor_init(&ROTOR_VII, "NZJHGRCXMYSWBOUFAIVLPEKQDT", "ZM", "VII");
    rotor_init(&ROTOR_VIII, "FKQHTLXOCBJSPDZRAMEWNIUYGV", "ZM", "VIII");
}

void enigma_dump(const struct Enigma *e)
{
    char plugboard[96];

    size_t k = 0;
    for (byte i = 0; i < 26; ++i)
    {
        if (i < e->plugboard[i])
        {
            plugboard[k++] = 'a' + i;
            plugboard[k++] = 'a' + e->plugboard[i];
            plugboard[k++] = ' ';
        }
    }
    plugboard[k] = 0;

    printf("%s | %3s %3s %3s | %c%c%c-%c%c%c | %s",
           e->reflector->name,
           e->rotor3->name,
           e->rotor2->name,
           e->rotor1->name,
           e->rotor3_position + 'A',
           e->rotor2_position + 'A',
           e->rotor1_position + 'A',
           e->ring3 + 'A',
           e->ring2 + 'A',
           e->ring1 + 'A',
           plugboard);
}

void benchmark()
{
    struct Enigma e;
    const struct Rotor *r[3] = {&ROTOR_I, &ROTOR_II, &ROTOR_III};

    enigma_init(&e, enigma_key("ENI"), enigma_key("GMA"), r, &ROTOR_Reflector_B, "bq cr di ej kw mt os px uz gh");

    printf("\033[2mEnigma: ");
    enigma_dump(&e);
    printf("\n\033[0m");

    srand(time(NULL));
    byte b = rand() % 26;
    byte out;

    struct timespec start, end;
    size_t iterations = 1000 * 26 * 26 * 26 * 60;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    for (size_t i = 0; i < iterations; ++i)
    {
        out = enigma_encipher(&e, b);
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    if (end.tv_nsec < start.tv_nsec)
    {
        end.tv_nsec += 1000000000;
        start.tv_sec += 1;
    }

    printf("%ld.%06ld s for %zu iterations (out: %d)\n", end.tv_sec - start.tv_sec, (end.tv_nsec - start.tv_nsec) / 1000, iterations, out);
}

void selftest()
{
    struct Enigma e1, e2;
    const struct Rotor *r[3] = {&ROTOR_I, &ROTOR_II, &ROTOR_III};

    enigma_init(&e1, enigma_key("ENI"), enigma_key("GMA"), r, &ROTOR_Reflector_B, "bq cr di ej kw mt os px uz gh");
    enigma_init(&e2, enigma_key("ENI"), enigma_key("GMA"), r, &ROTOR_Reflector_B, "bq cr di ej kw mt os px uz gh");

    printf("\033[2mEnigma: ");
    enigma_dump(&e1);
    printf("\n\033[0m");

    char secret[32];
    char clair[32];
    int i;

    for (i = 0; i < 10; ++i)
    {
        encipher_text(&e1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", secret);
        encipher_text(&e2, secret, clair);

        if (strcmp(clair, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 0)
        {
            printf("\nerror iteration %d %s", i, clair);
            break;
        }
        printf("%s", secret);
    }
    printf("\n");

    if (i == 10)
    {
        printf("\033[92mSUCCESS\033[0m\n");
    }
    else
    {
        printf("\033[31mFAIL\033[0m\n");
    }
}

bool enigma_init2(struct Enigma *e, const char *args[])
{
    const struct Rotor *rotors[3];
    struct Reflector *refl;
    position key, ring;

    if (strcmp(args[0], "B") == 0)
    {
        refl = &ROTOR_Reflector_B;
    }
    else if (strcmp(args[0], "C") == 0)
    {
        refl = &ROTOR_Reflector_C;
    }
    else
    {
        printf("Invalid reflector (%s)\n", args[0]);
        return false;
    }

    key = enigma_key(args[1]);
    if (key == INVALID_POS)
    {
        printf("Invalid key (%.3s)\n", args[1]);
        return false;
    }

    if (strlen(args[1]) == 7 && args[1][3] == '-')
    {
        ring = enigma_key(args[1] + 4);
        if (ring == INVALID_POS)
        {
            printf("Invalid ring (%s)\n", args[1] + 4);
            return false;
        }
    }
    else
    {
        ring = KEY_AAA;
    }

    for (int i = 0; i < 3; ++i)
    {
        struct Rotor *const *r;
        for (r = ROTORS; *r != NULL; ++r)
        {
            if (strcmp(args[2 + i], (*r)->name) == 0)
            {
                rotors[i] = *r;
                break;
            }
        }
        if (*r == NULL)
        {
            printf("Invalid rotor%d (%s)\n", 1 + i, args[2 + i]);
            return false;
        }
    }

    return enigma_init(e, key, ring, rotors, refl, args[5]);
}

void ctf2();
void ctf();

int main(int argc, const char *argv[])
{
    enigma_components_init();

    if (argc == 1)
    {
        ctf2();
        return 0;
    }

    if (argc < 7)
    {
        if ((argc == 2) && (strcmp(argv[1], "bench") == 0))
        {
            benchmark();
        }
        else if ((argc == 2) && (strcmp(argv[1], "test") == 0))
        {
            selftest();
        }

        exit(0);
    }

    if ((argc != 7) && (argc != 8))
    {
        printf("Usage: enigma REFL KEY[-RING] R1 R2 R3 PLUGS [TEXT]\n");
        exit(2);
    }

    struct Enigma e;
    if (!enigma_init2(&e, argv + 1))
    {
        exit(2);
    }

    if (argc == 8)
    {
        encipher_print(&e, argv[7]);
        printf("\n");
    }
    else
    {
        size_t read;
        char buffer[32];
        do
        {
            read = fread(buffer, 1, sizeof(buffer), stdin);
            for (size_t i = 0; i < read; ++i)
                putchar(encipher_char(&e, buffer[i]));
        } while (read == sizeof(buffer));
    }

    return 0;
}

void ctf()
{
    struct Enigma e1;
    const struct Rotor *rotors[3] = {&ROTOR_I, &ROTOR_III, &ROTOR_V};
    char clair[64];

    // indice: "b a:e z"

    char secret[] = "IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD";

    char stecker[] = "xx xx";

    for (int i = 0; i < 26 * 26 * 26 * 26; ++i)
    {
        stecker[0] = 'A' + i % 26;
        stecker[1] = 'A' + (i / 26) % 26;
        stecker[3] = 'A' + (i / 676) % 26;
        stecker[4] = 'A' + (i / 17576) % 26;

        if (stecker[0] == stecker[1])
            continue;
        if (stecker[0] == stecker[3])
            continue;
        if (stecker[0] == stecker[4])
            continue;

        if (stecker[1] == stecker[3])
            continue;
        if (stecker[1] == stecker[4])
            continue;
        if (stecker[3] == stecker[4])
            continue;

        const int RM = 5;

        for (int j = 0; j < RM * RM * RM; ++j)
        {
            rotors[0] = ROTORS[j % RM];
            rotors[1] = ROTORS[(j / RM) % RM];
            rotors[2] = ROTORS[(j / (RM * RM)) % RM];

            if (rotors[1] == rotors[0])
                continue;
            if (rotors[2] == rotors[0] || rotors[2] == rotors[1])
                continue;

            //enigma_init(&e1, enigma_key("MER"), enigma_key("REJ"), rotors, &ROTOR_Reflector_B, "ba ez");
            enigma_init(&e1, enigma_key("MER"), enigma_key("REJ"), rotors, &ROTOR_Reflector_B, stecker);

            enigma_dump(&e1);

            printf("\033[2mEnigma: ");
            enigma_dump(&e1);
            printf("\033[0m  ");
            encipher_text(&e1, secret, clair);
            printf("%s\n", clair);
        }
    }
}

// print(str(list(itertools.permutations(list(range(8)),3))).translate(str.maketrans("[()]", "{{}}")))
int permutations3of8[8 * 7 * 6][3] =
    {{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 1, 6}, {0, 1, 7}, {0, 2, 1}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 2, 6}, {0, 2, 7}, {0, 3, 1}, {0, 3, 2}, {0, 3, 4}, {0, 3, 5}, {0, 3, 6}, {0, 3, 7}, {0, 4, 1}, {0, 4, 2}, {0, 4, 3}, {0, 4, 5}, {0, 4, 6}, {0, 4, 7}, {0, 5, 1}, {0, 5, 2}, {0, 5, 3}, {0, 5, 4}, {0, 5, 6}, {0, 5, 7}, {0, 6, 1}, {0, 6, 2}, {0, 6, 3}, {0, 6, 4}, {0, 6, 5}, {0, 6, 7}, {0, 7, 1}, {0, 7, 2}, {0, 7, 3}, {0, 7, 4}, {0, 7, 5}, {0, 7, 6}, {1, 0, 2}, {1, 0, 3}, {1, 0, 4}, {1, 0, 5}, {1, 0, 6}, {1, 0, 7}, {1, 2, 0}, {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6}, {1, 2, 7}, {1, 3, 0}, {1, 3, 2}, {1, 3, 4}, {1, 3, 5}, {1, 3, 6}, {1, 3, 7}, {1, 4, 0}, {1, 4, 2}, {1, 4, 3}, {1, 4, 5}, {1, 4, 6}, {1, 4, 7}, {1, 5, 0}, {1, 5, 2}, {1, 5, 3}, {1, 5, 4}, {1, 5, 6}, {1, 5, 7}, {1, 6, 0}, {1, 6, 2}, {1, 6, 3}, {1, 6, 4}, {1, 6, 5}, {1, 6, 7}, {1, 7, 0}, {1, 7, 2}, {1, 7, 3}, {1, 7, 4}, {1, 7, 5}, {1, 7, 6}, {2, 0, 1}, {2, 0, 3}, {2, 0, 4}, {2, 0, 5}, {2, 0, 6}, {2, 0, 7}, {2, 1, 0}, {2, 1, 3}, {2, 1, 4}, {2, 1, 5}, {2, 1, 6}, {2, 1, 7}, {2, 3, 0}, {2, 3, 1}, {2, 3, 4}, {2, 3, 5}, {2, 3, 6}, {2, 3, 7}, {2, 4, 0}, {2, 4, 1}, {2, 4, 3}, {2, 4, 5}, {2, 4, 6}, {2, 4, 7}, {2, 5, 0}, {2, 5, 1}, {2, 5, 3}, {2, 5, 4}, {2, 5, 6}, {2, 5, 7}, {2, 6, 0}, {2, 6, 1}, {2, 6, 3}, {2, 6, 4}, {2, 6, 5}, {2, 6, 7}, {2, 7, 0}, {2, 7, 1}, {2, 7, 3}, {2, 7, 4}, {2, 7, 5}, {2, 7, 6}, {3, 0, 1}, {3, 0, 2}, {3, 0, 4}, {3, 0, 5}, {3, 0, 6}, {3, 0, 7}, {3, 1, 0}, {3, 1, 2}, {3, 1, 4}, {3, 1, 5}, {3, 1, 6}, {3, 1, 7}, {3, 2, 0}, {3, 2, 1}, {3, 2, 4}, {3, 2, 5}, {3, 2, 6}, {3, 2, 7}, {3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {3, 4, 5}, {3, 4, 6}, {3, 4, 7}, {3, 5, 0}, {3, 5, 1}, {3, 5, 2}, {3, 5, 4}, {3, 5, 6}, {3, 5, 7}, {3, 6, 0}, {3, 6, 1}, {3, 6, 2}, {3, 6, 4}, {3, 6, 5}, {3, 6, 7}, {3, 7, 0}, {3, 7, 1}, {3, 7, 2}, {3, 7, 4}, {3, 7, 5}, {3, 7, 6}, {4, 0, 1}, {4, 0, 2}, {4, 0, 3}, {4, 0, 5}, {4, 0, 6}, {4, 0, 7}, {4, 1, 0}, {4, 1, 2}, {4, 1, 3}, {4, 1, 5}, {4, 1, 6}, {4, 1, 7}, {4, 2, 0}, {4, 2, 1}, {4, 2, 3}, {4, 2, 5}, {4, 2, 6}, {4, 2, 7}, {4, 3, 0}, {4, 3, 1}, {4, 3, 2}, {4, 3, 5}, {4, 3, 6}, {4, 3, 7}, {4, 5, 0}, {4, 5, 1}, {4, 5, 2}, {4, 5, 3}, {4, 5, 6}, {4, 5, 7}, {4, 6, 0}, {4, 6, 1}, {4, 6, 2}, {4, 6, 3}, {4, 6, 5}, {4, 6, 7}, {4, 7, 0}, {4, 7, 1}, {4, 7, 2}, {4, 7, 3}, {4, 7, 5}, {4, 7, 6}, {5, 0, 1}, {5, 0, 2}, {5, 0, 3}, {5, 0, 4}, {5, 0, 6}, {5, 0, 7}, {5, 1, 0}, {5, 1, 2}, {5, 1, 3}, {5, 1, 4}, {5, 1, 6}, {5, 1, 7}, {5, 2, 0}, {5, 2, 1}, {5, 2, 3}, {5, 2, 4}, {5, 2, 6}, {5, 2, 7}, {5, 3, 0}, {5, 3, 1}, {5, 3, 2}, {5, 3, 4}, {5, 3, 6}, {5, 3, 7}, {5, 4, 0}, {5, 4, 1}, {5, 4, 2}, {5, 4, 3}, {5, 4, 6}, {5, 4, 7}, {5, 6, 0}, {5, 6, 1}, {5, 6, 2}, {5, 6, 3}, {5, 6, 4}, {5, 6, 7}, {5, 7, 0}, {5, 7, 1}, {5, 7, 2}, {5, 7, 3}, {5, 7, 4}, {5, 7, 6}, {6, 0, 1}, {6, 0, 2}, {6, 0, 3}, {6, 0, 4}, {6, 0, 5}, {6, 0, 7}, {6, 1, 0}, {6, 1, 2}, {6, 1, 3}, {6, 1, 4}, {6, 1, 5}, {6, 1, 7}, {6, 2, 0}, {6, 2, 1}, {6, 2, 3}, {6, 2, 4}, {6, 2, 5}, {6, 2, 7}, {6, 3, 0}, {6, 3, 1}, {6, 3, 2}, {6, 3, 4}, {6, 3, 5}, {6, 3, 7}, {6, 4, 0}, {6, 4, 1}, {6, 4, 2}, {6, 4, 3}, {6, 4, 5}, {6, 4, 7}, {6, 5, 0}, {6, 5, 1}, {6, 5, 2}, {6, 5, 3}, {6, 5, 4}, {6, 5, 7}, {6, 7, 0}, {6, 7, 1}, {6, 7, 2}, {6, 7, 3}, {6, 7, 4}, {6, 7, 5}, {7, 0, 1}, {7, 0, 2}, {7, 0, 3}, {7, 0, 4}, {7, 0, 5}, {7, 0, 6}, {7, 1, 0}, {7, 1, 2}, {7, 1, 3}, {7, 1, 4}, {7, 1, 5}, {7, 1, 6}, {7, 2, 0}, {7, 2, 1}, {7, 2, 3}, {7, 2, 4}, {7, 2, 5}, {7, 2, 6}, {7, 3, 0}, {7, 3, 1}, {7, 3, 2}, {7, 3, 4}, {7, 3, 5}, {7, 3, 6}, {7, 4, 0}, {7, 4, 1}, {7, 4, 2}, {7, 4, 3}, {7, 4, 5}, {7, 4, 6}, {7, 5, 0}, {7, 5, 1}, {7, 5, 2}, {7, 5, 3}, {7, 5, 4}, {7, 5, 6}, {7, 6, 0}, {7, 6, 1}, {7, 6, 2}, {7, 6, 3}, {7, 6, 4}, {7, 6, 5}};

void ctf2()
{
    struct Enigma e1;
    const struct Rotor *rotors[3];
    const struct Reflector *reflectors[5];
    char clair[64];

    //char secret[] = "IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD";
    //char secret[] = "IVQDQT NHABMPSVBYYUCJIYMJBRDWXAXP  THYVCROD";
    //char secret[] = "THYVCROD";
    //char secret[] = "DORCVYHT";

    reflectors[0] = &ROTOR_Reflector_B;
    reflectors[1] = &ROTOR_Reflector_C;
    reflectors[2] = &ROTOR_Reflector_B_thin;
    reflectors[3] = &ROTOR_Reflector_C_thin;
    reflectors[4] = &ROTOR_Reflector_A;

    for (int refl = 0; refl < 5; ++refl)
    {
        for (int perm = 0; perm < 8 * 7 * 6; ++perm)
        {
            //printf("refl %d perm %3d\n", refl, perm);

            rotors[0] = ROTORS[permutations3of8[perm][0]];
            rotors[1] = ROTORS[permutations3of8[perm][1]];
            rotors[2] = ROTORS[permutations3of8[perm][2]];

            for (position key = KEY_AAA; key < KEY_MAX; ++key)
            {
                //for (position ring = KEY_AAA; ring < KEY_MAX; ++ring)
                position ring = enigma_key("REJ");
//                position ring = enigma_key("JER");
                {
                    // indice: "b a:e z"
                    enigma_init(&e1, key, ring, rotors, reflectors[refl], "BA EZ");

                    encipher_text(&e1, secret, clair);

                    if (strstr(clair, "REJEW") != NULL)
                    {
                        printf("\033[2mEnigma: ");
                        enigma_dump(&e1);
                        printf("\033[0m  ");
                        printf("%s\n", clair);
                    }
                }
            }
        }
    }
}
