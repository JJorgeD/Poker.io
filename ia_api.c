#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    strcat((char *)userp, contents);
    return size * nmemb;
}

const char* get_bot_action_from_ia(const char *game_state_json) {
    CURL *curl;
    CURLcode res;
    static char response[1024] = "";

    response[0] = '\0'; // Limpa a resposta anterior
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://sua-api-de-ia.com/analisar"); // Altere para sua API
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, game_state_json);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na requisição: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    return response;
}