#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "cJSON.h"

/*-----------------Function to create directories-----------------------------*/
void create_directory(const char *path)
{
    if (mkdir(path, 0777) == -1)
    {
        perror("Error creating directory");
    }
    else
    {
        printf("Directory created: %s\n", path);
    }
}
/*------------------------Function to create files-------------------------*/

void create_file(const char *path)
{
    FILE *file = fopen(path, "w");
    if (file)
    {
        printf("File created: %s\n", path);
        fclose(file);
    }
    else
    {
        perror("Error creating file");
    }
}

/*-----------------------Recursive function to handle the structure-------------------------*/
void create_structure(cJSON *folder, const char *base_path)
{
    cJSON *item = NULL;

    cJSON_ArrayForEach(item, folder)
    {
        const char *name = item->string;

        if (strcmp(name, "files") == 0)
        {
            cJSON *files = item;
            if (cJSON_IsArray(files))
            {
                int file_count = cJSON_GetArraySize(files);
                for (int i = 0; i < file_count; ++i)
                {
                    cJSON *file = cJSON_GetArrayItem(files, i);
                    if (cJSON_IsString(file))
                    {
                        char file_path[256];
                        snprintf(file_path, sizeof(file_path), "%s/%s", base_path, file->valuestring);
                        create_file(file_path);
                    }
                }
            }
        }
        else
        {

            if (cJSON_IsObject(item))
            {
                char folder_path[256];
                snprintf(folder_path, sizeof(folder_path), "%s/%s", base_path, name);
                create_directory(folder_path);

                create_structure(item, folder_path);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <json_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Could not open JSON file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

/*------------------------------Read Json file------------------------------------*/ 
    char *json_string = (char *)malloc(length + 1);
    fread(json_string, 1, length, file);
    json_string[length] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(json_string);
    free(json_string);
    if (json == NULL)
    {
        printf("Error parsing JSON\n");
        return 1;
    }

    /*------------Detect and use the first key as the root folder--------------------------*/
    cJSON *root = json->child;
    if (!root)
    {
        printf("No root object found\n");
        cJSON_Delete(json);
        return 1;
    }

    const char *root_name = root->string;
    create_directory(root_name);
    create_structure(root, root_name);
    cJSON_Delete(json);

    return 0;
}
