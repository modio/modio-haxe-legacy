#include "modioWrapperCallbacks.h"

u32 current_function = 0;
std::map<int, value*> functions_stored;
value* download_listener = NULL;
value* upload_listener = NULL;
value* event_listener = NULL;

void onEmailRequest(void *object, ModioResponse response)
{
  int function_number = *((int*)object);
  value ret = val_call1(*(functions_stored[function_number]), getResponseObject(response));
}

void onExchange(void *object, ModioResponse response)
{
  int function_number = *((int*)object);        
  value ret = val_call1(*(functions_stored[function_number]), getResponseObject(response));
}

void onGetAllMods(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  int function_number = *((int*)object);

  value mods_haxe = alloc_array (mods_size);
  for (int i = 0; i < mods_size; i++)
  {
    ModioMod modio_mod = mods[i];
    value mod = getModObject(modio_mod);
    val_array_set_i (mods_haxe, i, mod);
  }
  value ret = val_call2(*(functions_stored[function_number]), getResponseObject(response), mods_haxe);
}

void onModSubscribed(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call1(*(functions_stored[function_number]), getResponseObject(response));
}

void onModUnsubscribed(void* object, ModioResponse response)
{
  int function_number = *((int*)object);
  value ret = val_call1(*(functions_stored[function_number]), getResponseObject(response));
}

void onModDownload(u32 response_code, u32 mod_id)
{
  modioWrapperWriteLogLine("wrapper onDownload called", MODIO_DEBUGLEVEL_LOG);
  if(download_listener != NULL)
  {
    modioWrapperWriteLogLine("listener found! calling now...", MODIO_DEBUGLEVEL_LOG);
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

void onEvent(ModioResponse response, ModioEvent* events_array, u32 events_array_size)
{
  if(event_listener != NULL)
  {
    val_check_function(*event_listener, 2);

    value events = alloc_array(events_array_size);
    for (int i = 0; i < events_array_size; i++)
    {
      val_array_set_i(events, i, getEventObject(events_array[i]));
    }

    value ret = val_call2(*event_listener, getResponseObject(response), events);
  }
}

void onModAdded(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), getResponseObject(response), getModObject(mod));
}

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), getResponseObject(response), getModObject(mod));
}

void onGetAuthenticatedUser(void* object, ModioResponse response, ModioUser user)
{
  int function_number = *((int*)object);
  value ret = val_call2(*(functions_stored[function_number]), getResponseObject(response), getUserObject(user));
}

void onGetUserSubscriptions(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  int function_number = *((int*)object);
  
  value mods_haxe = alloc_array (mods_size);
  for (int i = 0; i < mods_size; i++)
  {
    ModioMod modio_mod = mods[i];
    value mod = getModObject(modio_mod);
    val_array_set_i (mods_haxe, i, mod);
  }
  
  value ret = val_call2(*(functions_stored[function_number]), getResponseObject(response), mods_haxe);
}