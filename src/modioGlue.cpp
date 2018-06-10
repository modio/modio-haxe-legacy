#define IMPLEMENT_API
#include <hx/CFFI.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <modio/modio.h>


extern "C" {
    value init(value modio_environment, value game_id, value api_key)
    {
        u32 modio_environment_cpp;
        u32 game_id_cpp;
        std::string api_key_cpp;

        if(val_is_int(modio_environment))
            modio_environment_cpp = val_int(modio_environment);
        if(val_is_int(game_id))
            game_id_cpp = val_int(game_id);
        if(val_is_string(api_key))
            api_key_cpp = val_string(api_key);
        
        modioInit(modio_environment_cpp, game_id_cpp, (char *)api_key_cpp.c_str());
    }
}
DEFINE_PRIM( init, 3 );
