#include <hx/CFFI.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <map>
#include <modio/modio.h>

extern u32 current_function;
extern std::map<int, value*> functions_stored;
extern value* download_listener;
extern value* upload_listener;

void onEmailRequest(void *object, ModioResponse response);
void onExchange(void *object, ModioResponse response);
void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size);
void onModSubscribed(void* object, ModioResponse response, ModioMod mod);
void onModUnsubscribed(void* object, ModioResponse response);
void onModDownload(u32 response_code, u32 mod_id);
void onModUpload(u32 response_code, u32 mod_id);
void onModAdded(void* object, ModioResponse response, ModioMod mod);
void onModEdited(void* object, ModioResponse response, ModioMod mod);