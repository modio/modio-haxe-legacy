#include "modioWrapperObjects.h"

value getErrorObject(ModioError modio_error)
{
  value error = alloc_empty_object();

  alloc_field(error, val_id("code"), alloc_int(modio_error.code));
  if(modio_error.message)
    alloc_field(error, val_id("message"), alloc_string(modio_error.message));

  value errors = alloc_array(modio_error.errors_array_size);
  for (int i = 0; i < modio_error.errors_array_size; i++)
  {
    val_array_set_i(error, val_id("errors"), alloc_string(modio_error.errors_array[i]));
  }
  alloc_field(error, val_id("errors"), errors);

  return error;
}

value getEventObject(ModioModEvent modio_event)
{
  value event = alloc_empty_object();

  alloc_field(event, val_id("id"), alloc_int(modio_event.id));
  alloc_field(event, val_id("mod_id"), alloc_int(modio_event.mod_id));
  alloc_field(event, val_id("user_id"), alloc_int(modio_event.user_id));
  alloc_field(event, val_id("event_type"), alloc_int(modio_event.event_type));
  alloc_field(event, val_id("date_added"), alloc_int(modio_event.date_added));

  return event;
}

value getResponseObject(ModioResponse modio_response)
{
  value response = alloc_empty_object();

  alloc_field(response, val_id("code"), alloc_int(modio_response.code));
  alloc_field(response, val_id("result_count"), alloc_int(modio_response.result_count));
  alloc_field(response, val_id("result_limit"), alloc_int(modio_response.result_limit));
  alloc_field(response, val_id("result_offset"), alloc_int(modio_response.result_offset));
  alloc_field(response, val_id("result_total"), alloc_int(modio_response.result_total));
  alloc_field(response, val_id("error"), getErrorObject(modio_response.error));

  return response;
}

value getTagObject(ModioTag modio_tag)
{
  value tag = alloc_empty_object();

  alloc_field(tag, val_id("date_added"), alloc_int(modio_tag.date_added));
  if(modio_tag.name)
    alloc_field(tag, val_id("name"), alloc_string(modio_tag.name));

  return tag;
}

value getMediaObject(ModioMedia modio_media)
{
  value media = alloc_empty_object();

  value youtube = alloc_array(modio_media.youtube_size);
  for (int i = 0; i < modio_media.youtube_size; i++)
  {
    val_array_set_i(youtube, i, alloc_string(modio_media.youtube_array[i]));
  }
  alloc_field(media, val_id("youtube"), youtube);

  value sketchfab = alloc_array(modio_media.sketchfab_size);
  for (int i = 0; i < modio_media.sketchfab_size; i++)
  {
    val_array_set_i(sketchfab, i, alloc_string(modio_media.sketchfab_array[i]));
  }
  alloc_field(media, val_id("sketchfab"), sketchfab);

  value images = alloc_array(modio_media.images_size);
  for (int i = 0; i < modio_media.images_size; i++)
  {
    val_array_set_i(images, i, getImageObject(modio_media.images_array[i]));
  }
  alloc_field(media, val_id("tags"), images);

  return media;
}

value getStatsObject(ModioStats modio_stats)
{
  value stats = alloc_empty_object();

  alloc_field(stats, val_id("mod_id"), alloc_int(modio_stats.mod_id));
  alloc_field(stats, val_id("popularity_rank_position"), alloc_int(modio_stats.popularity_rank_position));
  alloc_field(stats, val_id("popularity_rank_total_mods"), alloc_int(modio_stats.popularity_rank_total_mods));
  alloc_field(stats, val_id("downloads_total"), alloc_int(modio_stats.downloads_total));
  alloc_field(stats, val_id("subscribers_total"), alloc_int(modio_stats.subscribers_total));
  alloc_field(stats, val_id("ratings_total"), alloc_int(modio_stats.ratings_total));
  alloc_field(stats, val_id("ratings_positive"), alloc_int(modio_stats.ratings_positive));
  alloc_field(stats, val_id("ratings_negative"), alloc_int(modio_stats.ratings_negative));
  alloc_field(stats, val_id("ratings_percentage_positive"), alloc_int(modio_stats.ratings_percentage_positive));
  alloc_field(stats, val_id("ratings_weighted_aggregate"), alloc_float(modio_stats.ratings_weighted_aggregate));
  if(modio_stats.ratings_display_text)
    alloc_field(stats, val_id("ratings_display_text"), alloc_string(modio_stats.ratings_display_text));
  alloc_field(stats, val_id("date_expires"), alloc_float(modio_stats.date_expires));

  return stats;
}

value getDownloadObject(ModioDownload modio_download)
{
  value download = alloc_empty_object();

  alloc_field(download, val_id("date_expires"), alloc_int(modio_download.date_expires));
  if(modio_download.binary_url)
    alloc_field(download, val_id("binary_url"), alloc_string(modio_download.binary_url));

  return download;
}

value getFilehashObject(ModioFilehash modio_filehash)
{
  value filehash = alloc_empty_object();

  if(modio_filehash.md5)
    alloc_field(filehash, val_id("md5"), alloc_string(modio_filehash.md5));

  return filehash;
}

value getModfileObject(ModioModfile modio_modfile)
{
  value modfile = alloc_empty_object();

  alloc_field(modfile, val_id("id"), alloc_int(modio_modfile.id));
  alloc_field(modfile, val_id("mod_id"), alloc_int(modio_modfile.mod_id));
  alloc_field(modfile, val_id("virus_status"), alloc_int(modio_modfile.virus_status));
  alloc_field(modfile, val_id("virus_positive"), alloc_int(modio_modfile.virus_positive));
  alloc_field(modfile, val_id("date_added"), alloc_int(modio_modfile.date_added));
  alloc_field(modfile, val_id("date_scanned"), alloc_int(modio_modfile.date_scanned));
  alloc_field(modfile, val_id("filesize"), alloc_int(modio_modfile.filesize));
  if(modio_modfile.filename)
    alloc_field(modfile, val_id("filename"), alloc_string(modio_modfile.filename));
  if(modio_modfile.version)
    alloc_field(modfile, val_id("version"), alloc_string(modio_modfile.version));
  if(modio_modfile.virustotal_hash)
    alloc_field(modfile, val_id("virustotal_hash"), alloc_string(modio_modfile.virustotal_hash));
  if(modio_modfile.changelog)
    alloc_field(modfile, val_id("changelog"), alloc_string(modio_modfile.changelog));
  alloc_field(modfile, val_id("download"), getDownloadObject(modio_modfile.download));
  alloc_field(modfile, val_id("filehash"), getFilehashObject(modio_modfile.filehash));        

  return modfile;
}

value getAvatarObject(ModioAvatar modio_avatar)
{
  value avatar = alloc_empty_object();

  if(modio_avatar.filename)
    alloc_field(avatar, val_id("filename"), alloc_string(modio_avatar.filename));
  if(modio_avatar.original)
    alloc_field(avatar, val_id("original"), alloc_string(modio_avatar.original));
  if(modio_avatar.thumb_50x50)
    alloc_field(avatar, val_id("thumb_50x50"), alloc_string(modio_avatar.thumb_50x50));
  if(modio_avatar.thumb_100x100)
    alloc_field(avatar, val_id("thumb_100x100"), alloc_string(modio_avatar.thumb_100x100));

  return avatar;
}

value getUserObject(ModioUser modio_user)
{
  value user = alloc_empty_object();

  alloc_field(user, val_id("id"), alloc_int(modio_user.id));
  alloc_field(user, val_id("date_online"), alloc_int(modio_user.date_online));
  if(modio_user.username)
    alloc_field(user, val_id("username"), alloc_string(modio_user.username));
  if(modio_user.name_id)
    alloc_field(user, val_id("name_id"), alloc_string(modio_user.name_id));
  if(modio_user.timezone)
    alloc_field(user, val_id("timezone"), alloc_string(modio_user.timezone));
  if(modio_user.language)
    alloc_field(user, val_id("language"), alloc_string(modio_user.language));
  if(modio_user.profile_url)
    alloc_field(user, val_id("profile_url"), alloc_string(modio_user.profile_url));
  alloc_field(user, val_id("avatar"), getAvatarObject(modio_user.avatar));

  return user;
}

value getImageObject(ModioImage modio_image)
{
  value image = alloc_empty_object();

  if(modio_image.filename)
    alloc_field(image, val_id("filename"), alloc_string(modio_image.filename));
  if(modio_image.original)
    alloc_field(image, val_id("original"), alloc_string(modio_image.original));
  if(modio_image.thumb_320x180)
    alloc_field(image, val_id("thumb_320x180"), alloc_string(modio_image.thumb_320x180));

  return image;
}

value getLogoObject(ModioLogo modio_logo)
{
  value logo = alloc_empty_object();

  if(modio_logo.filename)
    alloc_field(logo, val_id("filename"), alloc_string(modio_logo.filename));
  if(modio_logo.original)
    alloc_field(logo, val_id("original"), alloc_string(modio_logo.original));
  if(modio_logo.thumb_320x180)
    alloc_field(logo, val_id("thumb_320x180"), alloc_string(modio_logo.thumb_320x180));
  if(modio_logo.thumb_640x360)
    alloc_field(logo, val_id("thumb_640x360"), alloc_string(modio_logo.thumb_640x360));
  if(modio_logo.thumb_1280x720)
    alloc_field(logo, val_id("thumb_1280x720"), alloc_string(modio_logo.thumb_1280x720));

  return logo;
}

value getModObject(ModioMod modio_mod)
{
  value mod = alloc_empty_object();

  alloc_field(mod, val_id("id"), alloc_int(modio_mod.id));
  alloc_field(mod, val_id("game_id"), alloc_int(modio_mod.game_id));
  alloc_field(mod, val_id("status"), alloc_int(modio_mod.status));
  alloc_field(mod, val_id("visible"), alloc_int(modio_mod.visible));
  alloc_field(mod, val_id("date_added"), alloc_int(modio_mod.date_added));
  alloc_field(mod, val_id("date_updated"), alloc_int(modio_mod.date_updated));
  alloc_field(mod, val_id("date_live"), alloc_int(modio_mod.date_live));
  if(modio_mod.homepage_url)
      alloc_field(mod, val_id("homepage_url"), alloc_string(modio_mod.homepage_url));
  if(modio_mod.name)    
    alloc_field(mod, val_id("name"), alloc_string(modio_mod.name));
  if(modio_mod.name_id)    
    alloc_field(mod, val_id("name_id"), alloc_string(modio_mod.name_id));
  if(modio_mod.summary)    
    alloc_field(mod, val_id("summary"), alloc_string(modio_mod.summary));
  if(modio_mod.description)    
    alloc_field(mod, val_id("description"), alloc_string(modio_mod.description));
  if(modio_mod.description_plaintext)    
    alloc_field(mod, val_id("description_plaintext"), alloc_string(modio_mod.description_plaintext));
  if(modio_mod.metadata_blob)
    alloc_field(mod, val_id("metadata_blob"), alloc_string(modio_mod.metadata_blob));
  if(modio_mod.profile_url)
    alloc_field(mod, val_id("profile_url"), alloc_string(modio_mod.profile_url));
  alloc_field(mod, val_id("logo"), getLogoObject(modio_mod.logo));
  alloc_field(mod, val_id("submitted_by"), getUserObject(modio_mod.submitted_by));
  alloc_field(mod, val_id("modfile"), getModfileObject(modio_mod.modfile));


  value tags = alloc_array(modio_mod.tags_array_size);
  for (int i = 0; i < modio_mod.tags_array_size; i++)
  {
    val_array_set_i(tags, i, getTagObject(modio_mod.tags_array[i]));
  }
  alloc_field(mod, val_id("tags"), tags);

  return mod;
}

// ...

void modioWrapperWriteLogLine(const std::string &text, u32 debug_level)
{
  std::ofstream log_file(".modio/log", std::ios::app);
  log_file << "[wrapper] ";
  if (debug_level == MODIO_DEBUGLEVEL_ERROR)
  {
    log_file << "[Error] ";
  }
  else if (debug_level == MODIO_DEBUGLEVEL_WARNING)
  {
    log_file << "[WARNING] ";
  }
  else if (debug_level == MODIO_DEBUGLEVEL_LOG)
  {
    log_file << "[LOG] ";
  }
  log_file << text.c_str() << "\n";
  log_file.close();
}