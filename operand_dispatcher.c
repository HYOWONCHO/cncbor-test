#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "cn-cbor/cn-cbor.h"
#include "whcbor_types.h"

void dump(const char *,const void*, int , bool);
int whcbor_cmd_dispatch(uint8_t *payload, uint32_t len);

void obtain_random_bytes(int lowers, int upper, int count, uint8_t *_out)
{
    int random_val; // = (rand() % (upper - lowers +1)) + lowers;
    srand(time(0));

    for ( int  i = 0L; i < count; i++ ) {
        random_val = (rand() % (upper - lowers +1)) + lowers;
        _out[i] = random_val;
        //printf("random value : 0x%02x \n", random_val);
    }

    return;
}


int operand_scp_operand_encode(int subcommand, uint8_t  *encbuf)
{
    int ret = 0L;
    cn_cbor *map = NULL;
    cn_cbor *key = NULL;
    uint8_t pubkey[65] = { [0] = 0x04, 0x00, };
    uint8_t nonce[32] = {0, };

    map = cn_cbor_map_create(CBOR_CONTEXT_COMMA NULL);

    // Create the SCP command
    key = cn_cbor_int_create(1, NULL);
    cn_cbor_mapput_int(map, 1, key, NULL);


    // Create the SCP connect subcommand
    key = cn_cbor_int_create(2, NULL);
    cn_cbor_mapput_int(map, subcommand, key, NULL);


    // Create the Public-key credential 
    obtain_random_bytes(0, 255, 64, &pubkey[1]);
    dump("Encoded Public key", pubkey, 65, true);
    key = cn_cbor_data_create((const uint8_t *)pubkey, 65 CBOR_CONTEXT,NULL);
    cn_cbor_mapput_string(map, (const char *)WHCBOR_SCP_PUBKEY_ID, key, NULL);


    obtain_random_bytes(0, 255, 32, nonce);
    dump("Encoded Nonce ", nonce, 32, true);
    key = cn_cbor_data_create((const uint8_t *)nonce, 32 CBOR_CONTEXT,NULL);
    cn_cbor_mapput_string(map, (const char *)WHCBOR_SCP_NONCE_ID, key, NULL);

    ret = cn_cbor_encoder_write(encbuf, 0, 512, map);
    if(ret < 0) {
        printf(" cbor encode failed \n");
        ret = -1;
        goto err;
    }

err:

   return ret; 



}


void operand_dispatcher(int mode, void *opbuf)
{
    int ret = 0L;
    uint8_t encbuf[255] = { 0x00, };
    switch(mode) {
        case 1: // Encrypt Mode
            printf("Encrypt Disptach \n");
            ret = operand_scp_operand_encode(1, encbuf);
            //dump("SCP encode", encbuf, ret, true);

            whcbor_cmd_dispatch(encbuf, ret);


            break;
        case 2: // Decrypt Mode
            printf("Decrypt Disptach \n");
            break; 
        case 3: // Both Mode
            printf("Both Disptach \n");
            break;
        default:
            printf("Unknown Operand Mode \n");
            break;

    }
}
    
