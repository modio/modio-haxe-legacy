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

std::string valueToString(value val)
{
  if (val_is_string(val))
    return val_string(val);
  return "";
}

int valueToInt(value val)
{
  if (val_is_int(val))
    return val_int(val);
  return -1;
}

bool valueToBool(value val)
{
  if (val_is_bool(val))
    return val_bool(val);
  return false;
}

std::string getStringFromObject(value object, std::string value_name)
{
  value value_haxe = val_field(object, val_id((char *)value_name.c_str()));
  return valueToString(value_haxe);
}

int getIntFromObject(value object, std::string value_name)
{
  value value_haxe = val_field(object, val_id((char *)value_name.c_str()));
  return valueToInt(value_haxe);
}

bool getBoolFromObject(value object, std::string value_name)
{
  value value_haxe = val_field(object, val_id((char *)value_name.c_str()));
  return valueToBool(value_haxe);
}

std::vector<std::string> getStringVectorFromObject(value object, std::string array_name, int array_size)
{
  std::vector<std::string> result;
  value array = val_field(object, val_id((char *)array_name.c_str()));
  for (int i = 0; i < array_size; i++)
  {
    value array_object = val_array_i(array, i);
    result.push_back(valueToString(array_object));
  }
  return result;
}

extern "C"
{
  // General purpose
  value modioWrapperInit(value modio_environment, value game_id, value api_key)
  {
    int modio_environment_cpp = valueToInt(modio_environment);
    int game_id_cpp = valueToInt(game_id);
    std::string api_key_cpp = valueToString(api_key);

    download_listener = NULL;
    upload_listener = NULL;
    event_listener = NULL;
    modioSetDownloadListener(&onModDownload);
    modioSetUploadListener(&onModUpload);
    modioSetEventListener(&onEvent);

    modioInit(modio_environment_cpp, game_id_cpp, (char *)api_key_cpp.c_str(), NULL);

    modioWrapperWriteLogLine("wrapper initialized", MODIO_DEBUGLEVEL_LOG);    

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
    current_function++;

    val_check_function(callback, 1);
    storeFunction(callback, current_function);

    std::string email_cpp = valueToString(email);


    modioEmailRequest(new int(current_function), (char *)email_cpp.c_str(), &onEmailRequest);

    return 0;
  }

  value modioWrapperEmailExchange(value security_code, value callback)
  {
    current_function++;

    val_check_function(callback, 1);
    storeFunction(callback, current_function);

    std::string security_code_cpp = valueToString(security_code);


    modioEmailExchange(new int(current_function), (char *)security_code_cpp.c_str(), &onExchange);

    return 0;
  }

  // Mod browsing

  value modioWrapperGetAllMods(value filter_type, value limit, value offset, value callback)
  {
    current_function++;

    val_check_function(callback, 2);
    storeFunction(callback, current_function);

    int filter_type_cpp = valueToInt(filter_type);
    int limit_cpp = valueToInt(limit);
    int offset_cpp = valueToInt(offset);

    ModioFilterCreator modio_filter;
    modioInitFilter(&modio_filter);
    modioSetFilterLimit(&modio_filter, limit_cpp);
    modioSetFilterOffset(&modio_filter, offset_cpp);

    switch (filter_type_cpp)
    {
    case 0: /*MODIO_SORT_BY_ID*/
      break;
    case 1: /*MODIO_SORT_BY_RATING*/
      modioSetFilterSort(&modio_filter, (char *)"rating", false);
      break;
    case 2: /*MODIO_SORT_BY_DATE_LIVE*/
      modioSetFilterSort(&modio_filter, (char *)"date_live", false);
      break;
    case 3: /*MODIO_SORT_BY_DATE_UPDATED*/
      modioSetFilterSort(&modio_filter, (char *)"date_updated", false);
      break;
    default:
      // Error
      break;
    }

    modioGetAllMods(new int(current_function), modio_filter, &onGetAllMods);

    return 0;
  }

  // Subscriptions

  value modioWrapperSubscribeToMod(value mod_id, value callback)
  {
    current_function++;

    val_check_function(callback, 1);
    storeFunction(callback, current_function);

    int mod_id_cpp = valueToInt(mod_id);

    modioSubscribeToMod(new int(current_function), mod_id_cpp, &onModSubscribed);

    return 0;
  }

  value modioWrapperUnsubscribeFromMod(value mod_id, value callback)
  {
    current_function++;

    val_check_function(callback, 1);
    storeFunction(callback, current_function);

    int mod_id_cpp = valueToInt(mod_id);

    modioUnsubscribeFromMod(new int(current_function), mod_id_cpp, &onModUnsubscribed);

    return 0;
  }

  // Download Methods

  value modioWrapperInstallDownloadedMods()
  {
    modioWrapperWriteLogLine("installing downloaded mods", MODIO_DEBUGLEVEL_LOG);    
    modioInstallDownloadedMods();
    return 0;
  }

  value modioWrapperDownloadMod(value mod_id)
  {
    int mod_id_cpp = valueToInt(mod_id);
    modioDownloadMod(mod_id_cpp);
    return 0;
  }

  value modioWrapperUninstallMod(value mod_id)
  {
    int mod_id_cpp = valueToInt(mod_id);
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
    if (!download_listener)
      download_listener = alloc_root();

    val_check_function(callback, 2);
    *download_listener = callback;
    return 0;
  }

  value modioWrapperGetModDownloadQueue()
  {
    int queue_size = modioGetModDownloadQueueCount();
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
    if (!upload_listener)
      upload_listener = alloc_root();

    val_check_function(callback, 2);
    *upload_listener = callback;
    return 0;
  }

  value modioWrapperSetEventListener(value callback)
  {
    if (!event_listener)
      event_listener = alloc_root();

    val_check_function(callback, 2);
    *event_listener = callback;
    printf("Event listener set\n");
    return 0;
  }

  value modioWrapperGetModfileUploadQueue()
  {
    int queue_size = modioGetModfileUploadQueueCount();
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
    int installed_mods_size = modioGetAllInstalledModsCount();
    ModioInstalledMod *installed_mods = (ModioInstalledMod *)malloc(installed_mods_size * sizeof(*installed_mods));
    modioGetAllInstalledMods(installed_mods);

    value installed_mods_haxe = alloc_array(installed_mods_size);
    for (int i = 0; i < installed_mods_size; i++)
    {
      value installed_mod = alloc_empty_object();
      alloc_field(installed_mod, val_id("mod_id"), alloc_int(installed_mods[i].mod_id));
      alloc_field(installed_mod, val_id("modfile_id"), alloc_int(installed_mods[i].modfile_id));
      //alloc_field(installed_mod, val_id("updated_at"), alloc_int(installed_mods[i].date_updated));
      alloc_field(installed_mod, val_id("path"), alloc_string(installed_mods[i].path));
      alloc_field(installed_mod, val_id("mod"), getModObject(installed_mods[i].mod));

      val_array_set_i(installed_mods_haxe, i, installed_mod);
    }

    free(installed_mods);

    return installed_mods_haxe;
  }

  value modioWrapperGetModState(value mod_id)
  {
    int mod_id_cpp = valueToInt(mod_id);
    value mod_state = alloc_int(modioGetModState(mod_id_cpp));
    return mod_state;
  }

  // Add mod

  value modioWrapperAddMod(value mod_creator, value callback)
  {
    if (val_is_object(mod_creator))
    {
      current_function++;

      val_check_function(callback, 2);
      storeFunction(callback, current_function);

      // Required fields
      std::string logo_path_cpp = getStringFromObject(mod_creator, "logo_path");
      std::string name_cpp = getStringFromObject(mod_creator, "name");
      std::string summary_cpp = getStringFromObject(mod_creator, "summary");
      // Optional fields
      int visible_cpp = getIntFromObject(mod_creator, "visible");
      int maturity_option_cpp = getIntFromObject(mod_creator, "maturity_option");
      std::string name_id_cpp = getStringFromObject(mod_creator, "name_id");
      std::string description_cpp = getStringFromObject(mod_creator, "description");
      std::string homepage_cpp = getStringFromObject(mod_creator, "homepage");
      std::string metadata_cpp = getStringFromObject(mod_creator, "metadata");
      int tags_size_cpp = getIntFromObject(mod_creator, "tags_size");
      std::vector<std::string> tags_cpp = getStringVectorFromObject(mod_creator, "tags", tags_size_cpp);

      ModioModCreator mod_creator;
      modioInitModCreator(&mod_creator);
      // Required fields
      if (logo_path_cpp != "")
        modioSetModCreatorLogoPath(&mod_creator, (char *)logo_path_cpp.c_str());
      if (name_cpp != "")
        modioSetModCreatorName(&mod_creator, (char *)name_cpp.c_str());
      if (summary_cpp != "")
        modioSetModCreatorSummary(&mod_creator, (char *)summary_cpp.c_str());
      // Optional fields
      if (visible_cpp != -1)
        modioSetModCreatorVisible(&mod_creator, visible_cpp);
      if (maturity_option_cpp != -1)
        modioSetModCreatorMaturityOption(&mod_creator, maturity_option_cpp);
      if (name_id_cpp != "")
        modioSetModCreatorNameid(&mod_creator, (char *)name_id_cpp.c_str());
      if (description_cpp != "")
        modioSetModCreatorDescription(&mod_creator, (char *)description_cpp.c_str());
      if (homepage_cpp != "")
        modioSetModCreatorHomepageURL(&mod_creator, (char *)homepage_cpp.c_str());
      if (metadata_cpp != "")
        modioSetModCreatorMetadataBlob(&mod_creator, (char *)metadata_cpp.c_str());
      for (auto tag : tags_cpp)
      {
        modioAddModCreatorTag(&mod_creator, (char *)tag.c_str());
      }

      modioAddMod(new int(current_function), mod_creator, &onModAdded);

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
      current_function++;

      val_check_function(callback, 2);
      storeFunction(callback, current_function);

      int mod_id_cpp = valueToInt(mod_id);

      int visible_cpp = getIntFromObject(mod_editor, "visible");
      int maturity_option_cpp = getIntFromObject(mod_editor, "maturity_option");
      int status_cpp = getIntFromObject(mod_editor, "status");
      int modfile_id_cpp = getIntFromObject(mod_editor, "modfile_id");
      std::string name_cpp = getStringFromObject(mod_editor, "name");
      std::string name_id_cpp = getStringFromObject(mod_editor, "name_id");
      std::string summary_cpp = getStringFromObject(mod_editor, "summary");
      std::string description_cpp = getStringFromObject(mod_editor, "description");
      std::string homepage_cpp = getStringFromObject(mod_editor, "homepage");
      std::string metadata_cpp = getStringFromObject(mod_editor, "metadata");

      ModioModEditor mod_editor;
      modioInitModEditor(&mod_editor);
      if (visible_cpp != -1)
        modioSetModEditorVisible(&mod_editor, visible_cpp);
      if (maturity_option_cpp != -1)
        modioSetModEditorMaturityOption(&mod_editor, maturity_option_cpp);
      if (status_cpp != -1)
        modioSetModEditorMaturityOption(&mod_editor, status_cpp);
      if (modfile_id_cpp != -1)
        modioSetModEditorMaturityOption(&mod_editor, modfile_id_cpp);
      if (name_cpp != "")
        modioSetModEditorName(&mod_editor, (char *)name_cpp.c_str());
      if (name_id_cpp != "")
        modioSetModEditorNameid(&mod_editor, (char *)name_id_cpp.c_str());
      if (summary_cpp != "")
        modioSetModEditorSummary(&mod_editor, (char *)summary_cpp.c_str());
      if (description_cpp != "")
        modioSetModEditorDescription(&mod_editor, (char *)description_cpp.c_str());
      if (homepage_cpp != "")
        modioSetModEditorHomepageURL(&mod_editor, (char *)homepage_cpp.c_str());
      if (metadata_cpp != "")
        modioSetModEditorMetadataBlob(&mod_editor, (char *)metadata_cpp.c_str());

      modioEditMod(new int(current_function), mod_id_cpp, mod_editor, &onModEdited);

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
      int mod_id_cpp = valueToInt(mod_id);

      std::string path_cpp = getStringFromObject(modfile_creator, "path");
      std::string version_cpp = getStringFromObject(modfile_creator, "version");
      std::string changelog_cpp = getStringFromObject(modfile_creator, "changelog");
      bool active_cpp = getBoolFromObject(modfile_creator, "active");
      std::string filehash_cpp = getStringFromObject(modfile_creator, "filehash");

      ModioModfileCreator modfile_creator;
      modioInitModfileCreator(&modfile_creator);
      if (path_cpp != "")
        modioSetModfileCreatorPath(&modfile_creator, (char *)path_cpp.c_str());
      if (version_cpp != "")
        modioSetModfileCreatorVersion(&modfile_creator, (char *)version_cpp.c_str());
      if (changelog_cpp != "")
        modioSetModfileCreatorChangelog(&modfile_creator, (char *)changelog_cpp.c_str());
      modioSetModfileCreatorActive(&modfile_creator, active_cpp);
      if (filehash_cpp != "")
        modioSetModfileCreatorFilehash(&modfile_creator, (char *)filehash_cpp.c_str());

      modioAddModfile(mod_id_cpp, modfile_creator);
    }
    else
    {
      printf("No object found\n");
    }
    return 0;
  }

  // Me
  value modioWrapperGetAuthenticatedUser(value callback)
  {
    current_function++;

    val_check_function(callback, 2);
    storeFunction(callback, current_function);

    modioGetAuthenticatedUser(new int(current_function), &onGetAuthenticatedUser);

    return 0;
  }

  value modioWrapperGetUserSubscriptions(value callback)
  {
    current_function++;
    
    val_check_function(callback, 2);
    storeFunction(callback, current_function);

    ModioFilterCreator filter;
    modioInitFilter(&filter);

    modioGetUserSubscriptions(new int(current_function), filter, &onGetUserSubscriptions);

    return 0;
  }
}

DEFINE_PRIM(modioWrapperInit, 3);
DEFINE_PRIM(modioWrapperProcess, 0);
DEFINE_PRIM(modioWrapperEmailRequest, 2);
DEFINE_PRIM(modioWrapperEmailExchange, 2);
DEFINE_PRIM(modioWrapperIsLoggedIn, 0);
DEFINE_PRIM(modioWrapperLogout, 0);
DEFINE_PRIM(modioWrapperGetAllMods, 4);
DEFINE_PRIM(modioWrapperSubscribeToMod, 2);
DEFINE_PRIM(modioWrapperUnsubscribeFromMod, 2);
DEFINE_PRIM(modioWrapperInstallDownloadedMods, 0);
DEFINE_PRIM(modioWrapperDownloadMod, 1);
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
DEFINE_PRIM(modioWrapperGetAuthenticatedUser, 1);
DEFINE_PRIM(modioWrapperGetUserSubscriptions, 1);
DEFINE_PRIM(modioWrapperSetEventListener, 1);