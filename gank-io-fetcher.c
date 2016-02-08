/**
 * Gank.io Fetcher
 * Copyright (C) 2016 Junde Yi <lmy441900@gmail.com>
 */
#define VERSION "0.0"

// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

// Libraries
#include <curl/curl.h>
#include <json-c/json.h>

// Enable Unicode
// FIXME: Wait for my finishing the coordination with ANSI functions...

#include <tchar.h>

#include "data.h"
// Forward declaration
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
void parse_arguments (const int *argc, _TCHAR ***argv, enum Type *resType, enum DataType *dataType,
                      uint32_t *nRequest, uint32_t *page,
                      uint32_t *year, uint32_t *month, uint32_t *day);

int _tmain (int argc, _TCHAR **argv)
{
    static char buffer[40960] = {0};  // Buffer for the data received. FIXME: Flexible capacity
    uint32_t nRequest = 0;
    uint32_t page     = 0;
    uint32_t year = 0, month = 0, day = 0;
    json_object *jReceived = NULL;
    json_object *jResArray = NULL;
    enum DataType dataType = NotSet;
    enum Type     resType  = TNotSet;

    // Parse arguments
    parse_arguments (&argc, &argv, &resType, &dataType,
                     &nRequest, &page,
                     &year, &month, &day);

    // cURL Initialize
    CURL *curl = curl_easy_init ();

    // 1st step: cURL get JSON
    if (curl) {
        // Setup cURL
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt (curl, CURLOPT_URL, "http://gank.avosapps.com/api/data/%E7%A6%8F%E5%88%A9/1/1");
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, buffer);

        // Go you!
        curl_easy_perform (curl);
        // Cleanup
        curl_easy_cleanup (curl);
    } else {
        _fputts (_T("[ERROR] cURL initialization failed. Abort."), stderr);
        curl_easy_cleanup (curl);
        return 1;
    } // if (curl)

    // 2st step: parse JSON
    jReceived = json_tokener_parse (buffer);
    if (jReceived != NULL) {
        int ret = 0;
        json_object *jError = NULL;

        ret = json_object_object_get_ex (jReceived, "error", &jError);
        if ((ret == TRUE) && (strcmp (json_object_to_json_string (jError), "false") == 0)) {
            ret = json_object_object_get_ex (jReceived, "results", &jResArray);
            if ((ret == TRUE) && (json_object_is_type (jResArray, json_type_array) == TRUE)) {
                json_object *jResult = json_object_array_get_idx (jResArray, 0); // jResult is finally a type_json_object
                json_object_object_foreach (jResult, key, val) {
                    printf ("%s => %s\n", key, json_object_to_json_string (val));
                }
            } else {
                _fputts (_T("[ERROR] Cannot get jResArray."), stderr);
                return 1;
            }
        } else {
            _fputts (_T("[ERROR] Server responds an error. Abort."), stderr);
            return 1;
        }
    } else {
        _fputts (_T("[ERROR]Cannot get jReceived."), stderr);
        return 1;
    }

    return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realSize = size*nmemb;
    if (ptr) {
        memcpy ((char *)userdata, ptr, realSize);
    }
    return (size*nmemb);
}

void parse_arguments (const int *argc, _TCHAR ***argv, enum Type *resType, enum DataType *dataType,
                      uint32_t *nRequest, uint32_t *page,
                      uint32_t *year, uint32_t *month, uint32_t *day)
{
    static int optFlag = 0;
    static struct option options[] = {
        {"restype",  required_argument, &optFlag, 'r'},
        {"datatype", required_argument, &optFlag, 't'},
        {"number",   required_argument, &optFlag, 'n'},
        {"page",     required_argument, &optFlag, 'p'},
        {"year",     required_argument, &optFlag, 'y'},
        {"month",    required_argument, &optFlag, 'm'},
        {"day",      required_argument, &optFlag, 'd'}
    };

    // FIXME: *argc and the following many `optarg`s will be wchat_t types if Unicode is enabled,
    //        but getopt_long and wcsicmp won't receive them.
    //        (iconv? (Oh I think applying Unicode is a wrong decision))
    while (getopt_long (*argc, *argv, "rtnpymd", options, NULL) != -1) {
        switch (optFlag) {
            case 'r': // type (分类数据/每日数据/随机数据)
                if (_tcsicmp (optarg, _T("Sorted")) == 0) {
                    *resType = Sorted;
                } else if (_tcsicmp (optarg, _T("Daily")) == 0) {
                    *resType = Daily;
                } else if (_tcsicmp (optarg, _T("Random")) == 0) {
                    *resType = Random;
                } else {
                    // Nothing matches
                    _fputts (_T("[ERROR] You've set a wrong type of resource."), stderr);
                    exit (2);
                }
                break;

            case 't': // Data Type (福利 | Android | iOS | 休息视频 | 拓展资源 | 前端 | all)
                if (_tcsicmp (optarg, _T("Goods")) == 0) {
                    *dataType = Goods;
                } else if (_tcsicmp (optarg, _T("Android")) == 0) {
                    *dataType = Android;
                } else if (_tcsicmp (optarg, _T("iOS")) == 0) {
                    *dataType = iOS;
                } else if (_tcsicmp (optarg, _T("RelaxingMovies")) == 0) {
                    *dataType = RelaxingMovies;
                } else if (_tcsicmp (optarg, _T("ExpandingRes")) == 0) {
                    *dataType = ExpandingRes;
                } else if (_tcsicmp (optarg, _T("FrontEnd")) == 0) {
                    *dataType = FrontEnd;
                } else if (_tcsicmp (optarg, _T("all")) == 0) {
                    *dataType = All;
                } else {
                    // Nothing matches
                    _fputts (_T("[ERROR] You've set a wrong type of data."), stderr);
                    exit (2);
                }
                break;

            case 'n': // Request number
                *nRequest = _tcstoul (optarg, NULL, 10);
                break;
            case 'p': // Pages
                *page = _tcstoul (optarg, NULL, 10);
                break;
            case 'y': // Year
                *year = _tcstoul (optarg, NULL, 10);
                break;
            case 'm': // Month
                *month = _tcstoul (optarg, NULL, 10);
                break;
            case 'd': // Day
                *day = _tcstoul (optarg, NULL, 10);
                break;
            default:  // ???
                break;
        } // switch (optFlag)
    } // while (getopt_long (*argc, *argv, "tDnpymd", options, NULL) != -1)

    // Check if variables are set.
    if (*resType == Sorted) {
        if (*dataType != NotSet) {
            if (*nRequest != 0) {
                if (*page != 0) {
                    return;
                } else {
                    _fputts (_T("[ERROR] Please set page..."), stderr);
                    exit (2);
                }
            } else {
                _fputts (_T("[ERROR] Please set request number..."), stderr);
                exit (2);
            }
        } else {
            _fputts (_T("[ERROR] Please set Data Type..."), stderr);
            exit (2);
        }
    } else if (*resType == Daily) {
        if (*year != 0) {
            if (*month != 0) {
                if (*day != 0) {
                    return;
                } else {
                    _fputts (_T("[ERROR]Please set day..."), stderr);
                    exit (2);
                }
            } else {
                _fputts (_T("[ERROR]Please set month..."), stderr);
                exit (2);
            }
        } else {
            _fputts (_T("[ERROR] Please set year..."), stderr);
            exit (2);
        }
    } else if (*resType == Random) {
        if (*dataType != NotSet) {
            if (*nRequest != 0) {
                return;
            } else {
                _fputts (_T("[ERROR] Please set request number..."), stderr);
                exit (2);
            }
        } else {
            _fputts (_T("[ERROR] Please set Data Type..."), stderr);
            exit (2);
        }
    } else {
        _fputts (_T("[ERROR] Please set resource type..."), stderr);
        exit (2);
    }
}
