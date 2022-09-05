#include "whcbor_types.h"


static void whcbor_cmd_map_fetch(void *decode, void *map)
{

    whcbor_map_t *m = (whcbor_map_t *)decode;

    m->command = cn_cbor_mapget_int((const cn_cbor *)decode, WHCBOR_CMD_SCP);
    if( m->command == NULL ) {
        m->command = cn_cbor_mapget_int((const cn_cbor *)decode, WHCBOR_CMD_BIO);
    }

    switch(m->command->v.uint) {
        case WHCBOR_CMD_SCP:
            for (int x = 1; x < WHCBOR_SCP_SUBCMD_RECONNECT; x++) {
                m->subcommand = cn_cbor_mapget_int((const char *)decode,x);

                if( m->subcommand != NULL ) {
                    break;
                }
            } 
            break;
        case WHCBOR_CMD_BIO:
            for( int x = 1; x < WHCBOR_BIO_SUBCMD_IDENTIFY; x++ ) {
                m->subcommand = cn_cbor_mapget_int((const char *)decode,x);

                if( m->subcommand != NULL )  {
                    break;
                }
            }
            break;
        default:
            break;
    }
    

    return;

}


int whcbor_cmd_dispatch(uint8_t *payload, uint32_t len)
{
    int ret = WHCBOR_RET_FAIL;

    uint8_t *_payload = payload;
    cn_cbor *decodemap = NULL;
    whcbor_map_t whmap;

    memset((void *)&whmap, 0x00, sizeof whmap);

    decodemap = cn_cbor_decode((const uint8_t *)_payload, len CBOR_CONTEXT_PARAM, NULL);


    whcbor_cmd_map_fetch((void *)decodemap, (void *)&whmap);


    if(whmap.command == NULL || whmap.subcommand == NULL) {
        goto err;
    }


err:
    return ret;
}
