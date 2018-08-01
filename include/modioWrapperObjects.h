#include <hx/CFFI.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <map>
#include <modio.h>

value getTagObject(ModioTag modio_Tag);
value getMediaObject(ModioMedia modio_media);
value getRatingSummaryObject(ModioRatingSummary modio_rating_summary);
value getDownloadObject(ModioDownload modio_download);
value getFilehashObject(ModioFilehash modio_filehash);
value getModfileObject(ModioModfile modio_modfile);
value getAvatarObject(ModioAvatar modio_avatar);
value getUserObject(ModioUser modio_user);
value getImageObject(ModioImage modio_image);
value getLogoObject(ModioLogo modio_logo);
value getModObject(ModioMod modio_mod);