#include "modioWrapperCallbacks.h"

u32 current_function = 0;
std::map<int, value*> functions_stored;
value* download_listener = NULL;
value* upload_listener = NULL;

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

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  int function_number = *((int*)object);

  value mods_haxe = alloc_array (mods_size);
  for (int i = 0; i < mods_size; i++)
  {
    ModioMod modio_mod = mods[i];
    value mod = getModObject(modio_mod);
    val_array_set_i (mods_haxe, i, mod);
  }
  value ret = val_call2(*(functions_stored[function_number]), mods_haxe, alloc_int(response.code));
}

void onModSubscribed(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModUnsubscribed(void* object, ModioResponse response)
{
  int function_number = *((int*)object);
  value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModDownload(u32 response_code, u32 mod_id)
{
  if(download_listener != NULL)
  {
    val_check_function(*download_listener, 2);
    value ret = val_call2(*download_listener, alloc_int(response_code), alloc_int(mod_id));
  }
}

void onModUpload(u32 response_code, u32 mod_id)
{
  if(upload_listener != NULL)
  {
    val_check_function(*upload_listener, 2);
    value ret = val_call2(*upload_listener, alloc_int(response_code), alloc_int(mod_id));
  }
}

void onModAdded(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), alloc_int(response.code), getModObject(mod));
}

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), alloc_int(response.code), getModObject(mod));
}

void onGetAuthenticatedUser(void* object, ModioResponse response, ModioUser user)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), alloc_int(response.code), getUserObject(user));
}