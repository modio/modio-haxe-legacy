#include <hx/CFFI.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <map>
#include <modio.h>

value getErrorObject(ModioError modio_error);
value getEventObject(ModioEvent modio_event);
value getResponseObject(ModioResponse modio_response);
value getTagObject(ModioTag modio_tag);
value getMediaObject(ModioMedia modio_media);
value getStatsObject(ModioStats modio_stats);
value getDownloadObject(ModioDownload modio_download);
value getFilehashObject(ModioFilehash modio_filehash);
value getModfileObject(ModioModfile modio_modfile);
value getAvatarObject(ModioAvatar modio_avatar);
value getUserObject(ModioUser modio_user);
value getImageObject(ModioImage modio_image);
value getLogoObject(ModioLogo modio_logo);
value getModObject(ModioMod modio_mod);
void modioWrapperWriteLogLine(const std::string &text, u32 debug_level);