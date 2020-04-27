#include "modioWrapperObjects.h"

extern u32 current_function;
extern std::map<int, value*> functions_stored;
extern value* download_listener;
extern value* upload_listener;
extern value* event_listener;

void onGenericCallback(void* object, ModioResponse response);
void onModsCallback(void* object, ModioResponse response, ModioMod* mods, u32 mods_size);
void onModCallback(void* object, ModioResponse response, ModioMod mod);
void onModDownload(u32 response_code, u32 mod_id);
void onModUpload(u32 response_code, u32 mod_id);
void onEventCallback(ModioResponse response, ModioModEvent* events_array, u32 events_array_size);
void onUserCallback(void* object, ModioResponse response, ModioUser user);