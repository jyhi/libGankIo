/* daily_feed.h: Functions for operatingdaily feed items (GankIoDailyFeed)
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

/* gank_io_daily_feed_info_fetch: Fetch daily feed of the specific date.
 * NOTE: This function fetches only information returned as JSON.
 */
int gank_io_daily_feed_info_fetch ();

/* gank_io_daily_feed_content_fetch: Fetch contents of the specific daily feed item, which is filled by
 *  gank_io_daily_feed_info_fetch.
 */
int gank_io_daily_feed_content_fetch ();

/* gank_io_daily_feed_free: Free the specific daily feed item.
 * NOTE: If the item is already NULL, this function does nothing.
 */
int gank_io_daily_feed_free ();
