#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
// this a video tutorial by jacob sorber

size_t got_data(char *buff, size_t itemsize, size_t nitems, void* ptr)
{
    size_t bytes = itemsize * nitems;

    int line = 1;
    printf("New chunk(%zu bytes)\n", bytes);
    printf("%d: \t", line);
    for (int i = 0; i < bytes; i++)
    {
        printf("%c", buff[i]);
        if (buff[i] == '\n')
        {
            line++;
            printf("%d:\t", line);
        }
    }
    printf("\n\n");
    return bytes;
}

int main(void)
{
    CURL* curl = curl_easy_init();

    if (!curl)
    {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }

    // set options
    curl_easy_setopt(curl, CURLOPT_URL, "https://jacobsorber.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);

    // perform actions
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));
    }


    curl_easy_cleanup(curl);
    return EXIT_SUCCESS;
}