/* api.h: Functions to directly convert APIs and inner data structures, usually used by the library itself but men.
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

#include "data.h"

#ifndef _GANK_IO_API_H
#define _GANK_IO_API_H

/* _gank_io_api_daily_url_form: Generate the RESTFul API according to the daily arguments
 */
int _gank_io_api_daily_url_form (char **url, unsigned int year, unsigned int month, unsigned int day);

/* _gank_io_api_sorted_url_form: Generate the RESTFul API according to the sorted arguments
 */
int _gank_io_api_sorted_url_form (char **url, GankIoResType resType, unsigned int nRequest, unsigned int nPage);

/* _gank_io_apt_get: Perform network connection to fetch JSON from gank.io
 */
int _gank_io_api_get (const char *url, char **json);

/* _gank_io_api_parse: Parse JSON to convert it into inner data structures
 */
int _gank_io_api_parse (const char *json, GankIoItem **item, unsigned int nItem);

#endif /* end of include guard: _GANK_IO_API_H */
