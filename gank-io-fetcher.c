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
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <tchar.h>

// Forward declaration
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int _tmain (int argc, _TCHAR **argv)
{
    char *buffer = malloc (40960);
    // CURLcode ret;
    json_object *json = NULL;

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

    // puts (buffer);

    // 2st step: parse JSON
    if ((json = json_tokener_parse (buffer)) && (json != NULL)) {
        json_object_object_foreach (json, key, val) {
            printf ("%s :=> %s\n", key, json_object_to_json_string (val));
        }
    } else {
        _fputts (_T("[ERROR] JSON parsing error. Abort."), stderr);
        free (buffer);
        curl_easy_cleanup (curl);
        return 1;
    }


    free (buffer);
    return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    strcat (userdata, ptr);
    return (size*nmemb);
}
