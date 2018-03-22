#include "descbc.h"

DESCBC::DESCBC(ui64 key, ui64 iv) :
    iv(iv),
    last_block(iv),
    DES(key)
{
}

ui64 DESCBC::encrypt(ui64 block)
{
    last_block = DES::encrypt(block ^ last_block);
    return last_block;
}

ui64 DESCBC::decrypt(ui64 block)
{
    ui64 result = DES::decrypt(block) ^ last_block;
    last_block = block;
    return result;
}
