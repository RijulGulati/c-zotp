#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zotp/andotp.h>
#include <zotp/zotp.h>

void process_otp(char *file) {

  cJSON *entry = NULL;
  uint8_t *otp = NULL;

  cJSON *json = cJSON_Parse(file);
  if (json == NULL) {
    const char *json_error = cJSON_GetErrorPtr();
    if (json_error != NULL) {
      fprintf(stderr, "Error parsing JSON: %s\n", json_error);
    }
    exit(EXIT_FAILURE);
  }

  cJSON_ArrayForEach(entry, json) {
    cJSON *secret = cJSON_GetObjectItemCaseSensitive(entry, "secret");
    cJSON *digits = cJSON_GetObjectItemCaseSensitive(entry, "digits");
    cJSON *algorithm = cJSON_GetObjectItemCaseSensitive(entry, "algorithm");
    cJSON *period = cJSON_GetObjectItemCaseSensitive(entry, "period");
    cJSON *issuer = cJSON_GetObjectItemCaseSensitive(entry, "issuer");
    cJSON *type = cJSON_GetObjectItemCaseSensitive(entry, "type");
    cJSON *label = cJSON_GetObjectItemCaseSensitive(entry, "label");

    int validity = 0;

    if (!cJSON_IsString(secret) || !cJSON_IsNumber(digits) ||
        !cJSON_IsString(algorithm) || !cJSON_IsNumber(period) ||
        !cJSON_IsString(issuer) || !cJSON_IsString(type)) {

      fprintf(stderr,
              "Error: Erroneous JSON entry. Please check and try again!");
      exit(EXIT_FAILURE);
    }

    otp = malloc(sizeof(uint8_t *) * (digits->valueint + 1));

    time_t current_time = time(NULL);

    zotp_compute_otp(algorithm->valuestring, (uint8_t *)secret->valuestring,
                     current_time, period->valueint, digits->valueint,
                     (char *)otp);

    validity = period->valueint - (current_time % period->valueint);

    printf("\nOTP: %s [Valid for: %d seconds]\n", otp, validity);
    printf("Issuer: %s\n", issuer->valuestring);
    printf("Label: %s\n", label->valuestring);
    printf("Type: %s\n", type->valuestring);
    printf("\n===============\n");

    free(otp);
    otp = NULL;
  }

  cJSON_Delete(json);
}

void zotp_cli(int is_encrypted_file, char *filename) {

  uint8_t *decrypted_file;
  long decrypted_file_len = 0;
  char *password = NULL;

  if (is_encrypted_file == 1) {
    const char prompt[] = "File Password: ";
    password = getpass(prompt);

    andotp_decrypt((uint8_t *)filename, (uint8_t *)password, &decrypted_file,
                   &decrypted_file_len);

    if (decrypted_file_len > 0) {

      process_otp((char *)decrypted_file);

    } else {
      fprintf(stderr, "Incorrect Password!\n");
      exit(EXIT_FAILURE);
    }
  } else {
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
      fseek(fp, 0, SEEK_END);
      decrypted_file_len = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      decrypted_file = malloc(sizeof(uint8_t *) * (decrypted_file_len + 1));
      fread(decrypted_file, 1, decrypted_file_len, fp);
      fclose(fp);
      decrypted_file[decrypted_file_len] = '\0';
      process_otp((char *)decrypted_file);
    }
  }

  free(decrypted_file);
  if (is_encrypted_file == 1) {
    free(password);
  }
}
