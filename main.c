#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

#include <getopt.h>


int main(int argc, char **argv)
{
    void operand_dispatcher(int, void*);

    int c = 0L;
    int digit_optind = 0L;

    static int active_enc = 0L;
    static int active_dec = 0L;

    static int active_enc_fname = false;
    static int active_dec_fname = false;


    uint8_t encfile[512] = {0, };
    uint8_t decfile[512] = {0, };
    
    if( argc < 2 ) {
        fprintf(stderr, "Usage: cbor_test \"mode\" ... \n");
        return -1;
    }

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;

        static struct option long_options[] = {
            {"enc", no_argument, &active_enc, 1},
            {"dec", no_argument, &active_dec, 2},
            {"encfile", required_argument, &active_enc_fname, true},
            {"decfile", required_argument, &active_dec_fname, true},
            {0,0,0,0}
        };

        c = getopt_long(argc, argv, "edef:df:", long_options, &option_index);
        if(c == -1) {
            break;
        }

        switch(c) {
            case 0:     //Long options
                printf("options %s", long_options[option_index].name);
                if(optarg) {
                    printf(" with arg %s", optarg);
                }
                printf("\n");

                if( active_enc_fname == true ) memcpy(encfile, optarg, strlen(optarg));
                if( active_dec_fname == true ) memcpy(decfile, optarg, strlen(optarg));

                break;
            case 'e':
                active_enc = 1;
                break;
            case 'f':

                if( active_enc == 1 && active_enc_fname == false ) {
                    memcpy(encfile, optarg, strlen(optarg));
                    active_enc_fname = true;
                }
                //printf("encfile: %s \n", encfile);
                if( active_dec == 2 && active_dec_fname == false )  {
                    memcpy(decfile, optarg, strlen(optarg));
                    active_dec_fname = true;
                }
                //printf("decfile: %s \n", decfile);
                break;
            case 'd':
                active_dec = 2;
                break;
            case '?':
                printf("otherwise ? \n" );
                break;
            default:
                printf("??getopt returned character code 0%o ?? \n", c);
                break;
        }
    }


    (active_enc == true) ? printf("Encmode Activate ~~~ \n") : printf("Encmode de-activate ~~~ \n");
    (active_dec == true) ? printf("Decmode Activate ~~~ \n") : printf("Decmode de-activate ~~~ \n");

    (active_enc_fname == true) ? printf("Encrypt File Name : %s \n", encfile) : printf("Encfname NILL \n");
    (active_dec_fname == true) ? printf("Decrypt File Name : %s \n", decfile) : printf("Decfname NILL \n");

    operand_dispatcher(active_enc + active_dec , NULL);



    return true;
}
