#define IMPLEMENT_API
#include <hx/CFFI.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <map>
#include <modio/modio.h>

u32 current_function = 0;
std::map<int, value*> functions_stored;

void onEmailRequest(void *object, ModioResponse response)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onExchange(void *object, ModioResponse response)
{
    int function_number = *((int*)object);        
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

extern "C"
{
    value modioWrapperInit(value modio_environment, value game_id, value api_key)
    {
        u32 modio_environment_cpp;
        u32 game_id_cpp;
        std::string api_key_cpp;

        if (val_is_int(modio_environment))
            modio_environment_cpp = val_int(modio_environment);
        if (val_is_int(game_id))
            game_id_cpp = val_int(game_id);
        if (val_is_string(api_key))
            api_key_cpp = val_string(api_key);

        modioInit(modio_environment_cpp, game_id_cpp, (char *)api_key_cpp.c_str());

        return 0;
    }

    value modioWrapperProcess()
    {
        modioProcess();
    }

    value modioWrapperIsLoggedIn()
    {
        return alloc_bool(modioIsLoggedIn());
    }

    value modioWrapperLogout()
    {
        modioLogout();
    }

    value modioWrapperEmailRequest(value email, value callback)
    {
        val_check_function(callback, 1);
        value *new_function = alloc_root();
        *new_function = callback;
        functions_stored[current_function] = new_function;

        std::string email_cpp;

        if (val_is_string(email))
            email_cpp = val_string(email);
        
        modioEmailRequest(new int(current_function), (char *)email_cpp.c_str(), &onEmailRequest);

        current_function++;
    }

    value modioWrapperEmailExchange(value security_code, value callback)
    {
        val_check_function(callback, 1);
        value *new_function = alloc_root();
        *new_function = callback;
        functions_stored[current_function] = new_function;

        std::string security_code_cpp;

        if (val_is_string(security_code))
            security_code_cpp = val_string(security_code);

        modioEmailExchange(new int(current_function), (char *)security_code_cpp.c_str(), &onExchange);

        current_function++;        
    }
}

DEFINE_PRIM(modioWrapperInit, 3);
DEFINE_PRIM(modioWrapperProcess, 0);
DEFINE_PRIM(modioWrapperEmailRequest, 2);
DEFINE_PRIM(modioWrapperEmailExchange, 2);
DEFINE_PRIM(modioWrapperIsLoggedIn, 0);
DEFINE_PRIM(modioWrapperLogout, 0);