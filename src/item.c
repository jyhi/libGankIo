/* item.h: Functions for operating single items (GankIoItem)
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

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "api.h"
#include "utils.h"

int gank_io_item_info_fetch (GankIoItem **items, enum GankIoResourceType resType, unsigned int nItem, unsigned int nPage)
{
    GankIoItem *itemsTmp = (GankIoItem *)gank_io_xmalloc (sizeof (GankIoItem) * nItem);
    int retVal = 0;
    char *url  = NULL;
    char *json = NULL;

    retVal = _gank_io_api_sorted_url_form (&url, resType, nItem, nPage);
    if (retVal == EXIT_SUCCESS) {
        if (retVal = EXIT_SUCCESS) {
        retVal = _gank_io_api_get (&json, url);
            retVal = _gank_io_api_sorted_parse (&itemsTmp, json, nItem);
            if (retVal = EXIT_SUCCESS) {
                *items = itemsTmp;
            } else {
                gank_io_warn ("JSON parsing error.");
            }
        } else {
            gank_io_warn ("Failed to fetch data information!");
        }
    } else {
        gank_io_warn ("Unexpected error: URL forming error.");
    }

    return EXIT_SUCCESS;
}





int gank_io_item_content_fetch (GankIoItem *item)
{

}





int gank_io_item_free (GankIoItem *item)
{
    gank_io_xfree (item->id);
    gank_io_xfree (item->createdAt);
    gank_io_xfree (item->desc);
    gank_io_xfree (item->publishedAt);
    gank_io_xfree (item->source);
    gank_io_xfree (item->url);
    gank_io_xfree (item->who);
    gank_io_xfree (item->content);
    item->type = Unknown;
    item->used = 0;
    return EXIT_SUCCESS;
}
