/* data.h: Standard data structures used by libGankIo to process and provide information fetched.
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

#ifndef _GANK_IO_DATA_H
#define _GANK_IO_DATA_H

/* GankIoResourceType: Indicates the resource type of the item.
 */
enum GankIoResourceType {
    Goods,          // 福利
    Android,
    Ios,
    RelaxingMovies,
    ExtendRes,
    Frontend,
    All,
};

/* GankIoItem: Single item for every item fetched from gank.io.
 * If there's no description, the names are all the same as those in JSON.
 */
struct _GankIoItem {
    char   *id;                      // "_id" section in JSON
    char   *createdAt;               // Item create time
    char   *desc;                    // Description of the item
    char   *publishedAt;             // Item publish time
    char   *source;                  // Indicates where the item comes from
    enum   GankIoResourceType type;  // Resource type of this item
    char   *url;                     // URL
    int    used;                     // Indicates if it is used (?)
    char   *who;                     // The man who published this item
};
typedef struct _GankIoItem GankIoItem;

/* GankIoDailyFeed: All-in-one daily feed containing several sections of the day
 */
struct _GankIoDailyFeed {
    GankIoItem *picToday;
    GankIoItem *movToday;
    GankIoItem *android;
    GankIoItem *iOS;
    GankIoItem *extendRes;
    GankIoItem *frontEnd;

    int nPicToday;
    int nMovToday;
    int nAndroid;
    int nIos;
    int nExtendRes;
    int nFrontEnd;
};
typedef struct _GankIoDailyFeed GankIoDailyFeed;

#endif /* end of include guard: _GANK_IO_DATA_H */
