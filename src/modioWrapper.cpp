#define IMPLEMENT_API
#include <hx/CFFI.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "modioWrapperCallbacks.h"
#include "modioWrapperObjects.h"

void storeFunction(value callback, int current_function)
{
    value *new_function = alloc_root();
    *new_function = callback;
    functions_stored[current_function] = new_function;
}

u32 valueToU32(value val)
{
    if (val_is_int(val))
        return val_int(val);
    return 0;
}

std::string valueToString(value val)
{
    if (val_is_string(val))
        return val_string(val);
    return 0;
}

std::string getStringFromObject(value object, std::string value_name)
{
    value value_haxe = val_field(object, val_id((char*)value_name.c_str()));
    return valueToString(value_haxe);
}

extern "C"
{
    // General purpose
    value modioWrapperInit(value modio_environment, value game_id, value api_key)
    {
        u32 modio_environment_cpp = valueToU32(modio_environment);
        u32 game_id_cpp = valueToU32(game_id);
        std::string api_key_cpp = valueToString(api_key);

        download_listener = alloc_root();
        upload_listener = alloc_root();
        modioSetDownloadListener(&onModDownload);
        modioSetUploadListener(&onModUpload);

        modioInit(modio_environment_cpp, game_id_cpp, (char *)api_key_cpp.c_str());

        return 0;
    }

    value modioWrapperProcess()
    {
        modioProcess();
        return 0;
    }

    // Authentication

    value modioWrapperIsLoggedIn()
    {
        return alloc_bool(modioIsLoggedIn());
    }

    value modioWrapperLogout()
    {
        modioLogout();
        return 0;
    }

    value modioWrapperEmailRequest(value email, value callback)
    {
        val_check_function(callback, 1);
        storeFunction(callback, current_function);

        std::string email_cpp = valueToString(email);

        modioEmailRequest(new int(current_function), (char *)email_cpp.c_str(), &onEmailRequest);

        current_function++;
        return 0;
    }

    value modioWrapperEmailExchange(value security_code, value callback)
    {
        val_check_function(callback, 1);
        storeFunction(callback, current_function);

        std::string security_code_cpp = valueToString(security_code);

        modioEmailExchange(new int(current_function), (char *)security_code_cpp.c_str(), &onExchange);

        current_function++;
        return 0;
    }

    // Mod browsing

    value modioWrapperGetMods(value filter_type, value limit, value offset, value callback)
    {
        val_check_function(callback, 2);
        storeFunction(callback, current_function);

        u32 filter_type_cpp = valueToU32(filter_type);
        u32 limit_cpp = valueToU32(limit);
        u32 offset_cpp = valueToU32(offset);

        ModioFilterCreator modio_filter;
        modioInitFilter(&modio_filter);
        modioSetFilterLimit(&modio_filter, limit_cpp);
        modioSetFilterOffset(&modio_filter, offset_cpp);

        switch (filter_type_cpp)
        {
        case 0:/*MODIO_SORT_BY_ID*/
            break;
        case 1:/*MODIO_SORT_BY_RATING*/
            modioSetFilterSort(&modio_filter, (char*)"rating", false);
            break;
        case 2: /*MODIO_SORT_BY_DATE_LIVE*/
            modioSetFilterSort(&modio_filter, (char*)"date_live", false);
            break;
        case 3: /*MODIO_SORT_BY_DATE_UPDATED*/
            modioSetFilterSort(&modio_filter, (char*)"date_updated", false);
            break;
        default:
            // Error
            break;
        }

        modioGetMods(new int(current_function), modio_filter, &onModsGet);

        current_function++;
        return 0;
    }

    // Subscriptions

    value modioWrapperSubscribeToMod(value mod_id, value callback)
    {
        val_check_function(callback, 1);
        storeFunction(callback, current_function);

        u32 mod_id_cpp = valueToU32(mod_id);

        modioSubscribeToMod(new int(current_function), mod_id_cpp, &onModSubscribed);

        current_function++;
        return 0;
    }

    value modioWrapperUnsubscribeFromMod(value mod_id, value callback)
    {
        val_check_function(callback, 1);
        storeFunction(callback, current_function);

        u32 mod_id_cpp = valueToU32(mod_id);

        modioUnsubscribeFromMod(new int(current_function), mod_id_cpp, &onModUnsubscribed);

        current_function++;
        return 0;
    }

    // Download Methods

    value modioWrapperInstallMod(value mod_id)
    {
        u32 mod_id_cpp = valueToU32(mod_id);
        modioInstallMod(mod_id_cpp);
        return 0;
    }

    value modioWrapperUninstallMod(value mod_id)
    {
        u32 mod_id_cpp = valueToU32(mod_id);
        modioUninstallMod(mod_id_cpp);
        return 0;
    }

    value modioWrapperPauseDownloads()
    {
        modioPauseDownloads();
        return 0;
    }

    value modioWrapperResumeDownloads()
    {
        modioResumeDownloads();
        return 0;
    }

    value modioWrapperPrioritizeDownload(value mod_id)
    {
        modioPauseDownloads();
        return 0;
    }

    value modioWrapperSetDownloadListener(value callback)
    {
        val_check_function(callback, 2);
        *download_listener = callback;
        return 0;
    }

    value modioWrapperGetModDownloadQueue()
    {
        u32 queue_size = modioGetModDownloadQueueCount();
        ModioQueuedModDownload *download_queue = (ModioQueuedModDownload *)malloc(queue_size * sizeof(*download_queue));
        modioGetModDownloadQueue(download_queue);

        value download_queue_haxe = alloc_array(queue_size);
        for (int i = 0; i < queue_size; i++)
        {
            value queued_mod = alloc_empty_object();
            alloc_field(queued_mod, val_id("state"), alloc_int(download_queue[i].state));
            alloc_field(queued_mod, val_id("current_progress"), alloc_int(download_queue[i].current_progress));
            alloc_field(queued_mod, val_id("total_size"), alloc_int(download_queue[i].total_size));
            alloc_field(queued_mod, val_id("url"), alloc_string(download_queue[i].url));
            alloc_field(queued_mod, val_id("path"), alloc_string(download_queue[i].path));

            alloc_field(queued_mod, val_id("mod"), getModObject(download_queue[i].mod));
            val_array_set_i(download_queue_haxe, i, queued_mod);
        }

        free(download_queue);

        return download_queue_haxe;
    }

    value modioWrapperSetUploadListener(value callback)
    {
        val_check_function(callback, 2);
        *upload_listener = callback;
        return 0;
    }

    value modioWrapperGetModfileUploadQueue()
    {
        u32 queue_size = modioGetModfileUploadQueueCount();
        ModioQueuedModfileUpload *upload_queue = (ModioQueuedModfileUpload *)malloc(queue_size * sizeof(*upload_queue));
        modioGetModfileUploadQueue(upload_queue);

        value upload_queue_haxe = alloc_array(queue_size);
        for (int i = 0; i < queue_size; i++)
        {
            value queued_mod = alloc_empty_object();
            alloc_field(queued_mod, val_id("mod_id"), alloc_int(upload_queue[i].mod_id));

            val_array_set_i(upload_queue_haxe, i, queued_mod);
        }

        free(upload_queue);

        return upload_queue_haxe;
    }

    value modioWrapperGetInstalledMods()
    {
        u32 installed_mods_size = modioGetInstalledModsCount();
        ModioInstalledMod *installed_mods = (ModioInstalledMod *)malloc(installed_mods_size * sizeof(*installed_mods));
        modioGetInstalledMods(installed_mods);

        value installed_mods_haxe = alloc_array(installed_mods_size);
        for (int i = 0; i < installed_mods_size; i++)
        {
            value installed_mod = alloc_empty_object();
            alloc_field(installed_mod, val_id("mod_id"), alloc_int(installed_mods[i].mod_id));
            alloc_field(installed_mod, val_id("modfile_id"), alloc_int(installed_mods[i].modfile_id));
            alloc_field(installed_mod, val_id("updated_at"), alloc_int(installed_mods[i].updated_at));
            alloc_field(installed_mod, val_id("path"), alloc_string(installed_mods[i].path));
            alloc_field(installed_mod, val_id("mod"), getModObject(installed_mods[i].mod));

            val_array_set_i(installed_mods_haxe, i, installed_mod);
        }

        free(installed_mods);

        return installed_mods_haxe;
    }

    value modioWrapperGetModState(value mod_id)
    {
        u32 mod_id_cpp = valueToU32(mod_id);
        value mod_state = alloc_int(modioGetModState(mod_id_cpp));
        return mod_state;
    }

    // Add mod

    value modioWrapperAddMod(value mod_creator, value callback)
    {
        if (val_is_object(mod_creator))
        {
            val_check_function(callback, 1);
            storeFunction(callback, current_function);

            std::string logo_path_cpp = getStringFromObject(mod_creator, "logo_path");
            std::string name_cpp = getStringFromObject(mod_creator, "name");
            std::string summary_cpp = getStringFromObject(mod_creator, "summary");

            ModioModCreator mod_creator;
            modioInitModCreator(&mod_creator);
            modioSetModCreatorLogoPath(&mod_creator, (char*)logo_path_cpp.c_str());
            modioSetModCreatorName(&mod_creator, (char*)name_cpp.c_str());
            modioSetModCreatorSummary(&mod_creator, (char*)summary_cpp.c_str());
            modioAddMod(new int(current_function), mod_creator, &onModAdded);

            current_function++;
        }
        else
        {
            printf("No object found\n");
        }
        return 0;
    }

    // Edit mod

    value modioWrapperEditMod(value mod_id, value mod_editor, value callback)
    {
        if (val_is_object(mod_editor))
        {
            val_check_function(callback, 1);
            storeFunction(callback, current_function);

            u32 mod_id_cpp = valueToU32(mod_id);

            std::string logo_path_cpp = getStringFromObject(mod_editor, "logo_path");
            std::string name_cpp = getStringFromObject(mod_editor, "name");
            std::string summary_cpp = getStringFromObject(mod_editor, "summary");
            
            ModioModEditor mod_editor;
            modioInitModEditor(&mod_editor);
            modioSetModEditorName(&mod_editor, (char*)name_cpp.c_str());
            modioSetModEditorSummary(&mod_editor, (char*)summary_cpp.c_str());
            modioEditMod(new int(current_function), mod_id_cpp, mod_editor, &onModEdited);

            current_function++;
        }
        else
        {
            printf("No object found\n");
        }
        return 0;
    }

    // Uploads

    value modioWrapperAddModfile(value mod_id, value modfile_creator)
    {
        if (val_is_object(modfile_creator))
        {
            u32 mod_id_cpp = valueToU32(mod_id);

            std::string path_cpp = getStringFromObject(modfile_creator, "path");
            
            ModioModfileCreator modfile_creator;
            modioInitModfileCreator(&modfile_creator);
            modioSetModfileCreatorPath(&modfile_creator, (char*)path_cpp.c_str());
            modioAddModfile(mod_id_cpp, modfile_creator);
        }
        else
        {
            printf("No object found\n");
        }
        return 0;
    }
}

DEFINE_PRIM(modioWrapperInit, 3);
DEFINE_PRIM(modioWrapperProcess, 0);
DEFINE_PRIM(modioWrapperEmailRequest, 2);
DEFINE_PRIM(modioWrapperEmailExchange, 2);
DEFINE_PRIM(modioWrapperIsLoggedIn, 0);
DEFINE_PRIM(modioWrapperLogout, 0);
DEFINE_PRIM(modioWrapperGetMods, 4);
DEFINE_PRIM(modioWrapperSubscribeToMod, 2);
DEFINE_PRIM(modioWrapperUnsubscribeFromMod, 2);
DEFINE_PRIM(modioWrapperInstallMod, 1);
DEFINE_PRIM(modioWrapperUninstallMod, 1);
DEFINE_PRIM(modioWrapperPauseDownloads, 0);
DEFINE_PRIM(modioWrapperResumeDownloads, 0);
DEFINE_PRIM(modioWrapperPrioritizeDownload, 1);
DEFINE_PRIM(modioWrapperSetDownloadListener, 1);
DEFINE_PRIM(modioWrapperGetModDownloadQueue, 0);
DEFINE_PRIM(modioWrapperSetUploadListener, 1);
DEFINE_PRIM(modioWrapperGetModfileUploadQueue, 0);
DEFINE_PRIM(modioWrapperGetInstalledMods, 0);
DEFINE_PRIM(modioWrapperGetModState, 1);
DEFINE_PRIM(modioWrapperAddMod, 2);
DEFINE_PRIM(modioWrapperEditMod, 3);
DEFINE_PRIM(modioWrapperAddModfile, 2);
