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

#ifndef _GANK_IO_ITEM_H
#define _GANK_IO_ITEM_H

/* gank_io_item_info_fetch: Fetch items of specific numbers, and write information into the specific 'GankIoItem' items.
 * NOTE: Unlike gank_io_item_content_fetch, this function only fetches summaries.
 */
int gank_io_item_info_fetch (GankIoItem **items, enum GankIoResourceType resType, unsigned int nItem, unsigned int nPage);

/* gank_io_item_content_fetch: Fetch the content of the specific item, which contains information fetched by
 *   gank_io_item_info_fetch.
 */
int gank_io_item_content_fetch (GankIoItem *item);

/* gank_io_item_free: Free the specific item.
 * NOTE: If the item is already NULL, this function does nothing.
 */
int gank_io_item_free (GankIoItem *item);

#endif /* end of include guard: _GANK_IO_ITEM_H */
