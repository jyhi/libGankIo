/* utils.h: Utilities used by libGankIo
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

void *gank_io_xmalloc (const size_t size)
{
    void *ptr = malloc (size);
    if (size) {
        return ptr;
    } else {
        fprintf (stderr, " ** libGankIo: FATAL: memory allocation failed!");
        abort ();
    }
}

void gank_io_output (enum GankIoOutputType, char *fmt, ...)
{
    va_list args;
    static const char *head = " ** libGankIo:";
    char yn = 'N';
    va_start (args, fmt);

    switch (GankIoOutputType) {
        case Info:
            printf ("%s INFO: ", head);
            vprintf (fmt, args);
            break;
        case Warn_NoAck:
            printf ("%s WARN: ", head);
            vprintf (fmt, args);
            break;
        case Warn_Ack:
            printf ("%s WARN: ", head);
            vprintf (fmt, args);
            // Enquire for acknowledge
            while (1) {
                printf (" -> Continue? [y/N]");
                yn = getc (stdin);
                switch (yn) {
                    case 'Y': // fall through
                    case 'y':
                        while (getc(stdin) != EOF) {} // Clean stdin
                        return;
                    case 'N': // fall through
                    case 'n': // fall through
                    case '\r':
                        exit (255); // User terminated
                    default:
                        printf ("    Please answer [y]es or [N]o.");
                        break; // Repeat
                }
            }
            break;
        case Error:
            fprintf (stderr, "%s FAIL: ", head);
            vfprintf (args, fmt);
            abort ();
            break;
    }
}
