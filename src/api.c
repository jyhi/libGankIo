/* api.c: Functions to directly convert APIs and inner data structures, usually used by the library itself but men.
 * Copyright (C) 2016 Junde Yhi <lmy441900@gmail.com>
 * This file is part of libGankIo.
 *
 * libGankIo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * libGankIo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU lesser General Public
 * License along with libGankIo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"
#define BUFFER_SIZE 4096

static const char *BaseUrl = "http://gank.io/api";

int _gank_io_api_daily_url_form (char **url, unsigned int year, unsigned int month, unsigned int day)
{
    char *buf = gank_io_xmalloc (BUFFER_SIZE);
    int retVal = 0;

    retVal = snprintf (buf, BUFFER_SIZE, "%s/day/%d/%d/%d", BaseUrl, year, month, day);
    if (retVal <= BUFFER_SIZE) {
        *url = buf;
        return EXIT_SUCCESS;
    } else {
        // Overflowed. (It seems impossible)
        gank_io_error ("%s:%d String overflowed!", __FILE__, __LINE__);
    }

    // Whatever.
    return EXIT_FAILURE;
}





int _gank_io_api_sorted_url_form (char **url, GankIoResType resType, unsigned int nRequest, unsigned int nPage)
{
    char *buf = gank_io_xmalloc (BUFFER_SIZE);
    char strResType = gank_io_xmalloc (BUFFER_SIZE);
    int retVal = 0;

    switch (resType) {
        case Goods:
            strncpy (strResType, "福利", BUFFER_SIZE);
            break;
        case Android:
            strncpy (strResType, "Android", BUFFER_SIZE);
            break;
        case Ios:
            strncpy (strResType, "iOS", BUFFER_SIZE);
            break;
        case RelaxingMovies:
            strncpy (strResType, "休息视频", BUFFER_SIZE);
            break;
        case ExtendRes:
            strncpy (strResType, "拓展资源", BUFFER_SIZE);
            break;
        case Frontend:
            strncpy (strResType, "前端", BUFFER_SIZE);
            break;
        default:
            // WTF
            gank_io_error ("%s:%d Unexpected: Wrong resType", __FILE__, __LINE__);
            break;
    }

    retVal = snprintf (BUFFER_SIZE, "%s/%s/%d/%d", BaseUrl, strResType, nRequest, nPage);
    if (retVal <= BUFFER_SIZE) {
        *url = buf;
        return;
    } else {
        gank_io_error ("%s:%d String overflowed!", __FILE__, __LINE__);
    }
}





int _gank_io_api_get (char **json, const char *url)
{

}





int _gank_io_api_parse (const char *json, GankIoItem **item, unsigned int nItem)
{

}
