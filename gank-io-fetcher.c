/**
 * Gank.io Fetcher
 * Copyright (C) 2016 Junde Yi <lmy441900@gmail.com>
 */
#define VERSION "0.0"

// Standard header files
#include <stdio.h>
#include <stdlib.h>

// Libraries
#include <curl/curl.h>
#include <json-c/json.h>

// Enable Unicode
// Comment these lines to disable Unicode.

#include <tchar.h>

// Forward declaration
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int _tmain (int argc, _TCHAR **argv)
{
    char *buffer = malloc (40960);
    // CURLcode ret;
    json_object *jReceived = NULL;
    json_object *jResArray   = NULL;

    // _tprintf (_T("Gank.io Fetcher Version %s\nCopyright (C) 2016 Junde Yi\n\n"), _T(VERSION));

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
                free (buffer);
                return 1;
            }
        } else {
            _fputts (_T("[ERROR] Server responds an error. Abort."), stderr);
            free (buffer);
            return 1;
        }
    } else {
        _fputts (_T("[ERROR]Cannot get jReceived."), stderr);
        free (buffer);
        return 1;
    }

    free (buffer);
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
