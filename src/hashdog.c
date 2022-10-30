#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#include "arg_utils.h"
#include "input.h"
#include "tree.h"
#include "colors.h"


#define PASSWORD_MAX_SIZE   100
#define HASH_MAX_SIZE       2*EVP_MAX_MD_SIZE
#define T3C_LINE_MAX_SIZE   HASH_MAX_SIZE + 1 + PASSWORD_MAX_SIZE
#define QUIT                "quit please"


void get_hash(const char* cleartext, int cleartext_len, char* hash, const char* digest)
{
    unsigned char md_value[EVP_MAX_MD_SIZE];
    size_t md_len;
    EVP_Q_digest(NULL, digest, NULL, cleartext, cleartext_len, md_value, &md_len);
    for (size_t i = 0; i < md_len; i++)
        sprintf(&hash[2*i], "%02x", md_value[i]);
}


void generate(const char* input_filename, const char* output_filename, const char* digest)
{
    FILE* input = stdin;
    FILE* output = stdout;
    char cleartext[PASSWORD_MAX_SIZE+1] = {0};
    char hash[HASH_MAX_SIZE+1] = {0};
    int ret = -1;

    if(EVP_get_digestbyname(digest) == NULL)
    {
        fprintf(stderr, ""RED"ERROR: Unknown digest %s\n"COLOR_RESET"", digest);
        exit(EXIT_FAILURE);
    }

    if(input_filename != NULL)
    {
        input = fopen(input_filename, "r");
        if(input == NULL)
        {
            fprintf(stderr, ""RED"ERROR: Could not open file %s\n"COLOR_RESET"", input_filename);
            exit(EXIT_FAILURE);
        }
    }

    if(output_filename != NULL)
    {
        output = fopen(output_filename, "w");
        if(output == NULL)
        {
            fprintf(stderr, ""RED"ERROR: Could not open file %s\n"COLOR_RESET"", output_filename);
            fclose(input);
            exit(EXIT_FAILURE);
        }
    }

    while((ret = read_string_and_check_size(cleartext, sizeof(cleartext), input)) != -1)
    {
        if(ret == 0)
        {
            if(cleartext[0] == '\0')
                continue;
            if(strcmp(cleartext, QUIT) == 0)
                break;
            get_hash(cleartext, strlen(cleartext), hash, digest);
            if(output == stdout)
                fprintf(output, ""GRN"%s"COLOR_RESET":%s\n", hash, cleartext);
            else
                fprintf(output, "%s:%s\n", hash, cleartext);

        }
        else
            fprintf(stderr, ""YEL"WARNING: Password must be at most %d characters"COLOR_RESET"\n", PASSWORD_MAX_SIZE);
    }

    fclose(input);
    fclose(output);
}


void load_t3c(Node** tree_ptr, const char* input_filename)
{
    FILE* file = NULL;
    char t3c_line[T3C_LINE_MAX_SIZE+1] = {0};
    char* hash = NULL;
	char* cleartext = NULL;
    int ret = -1;
    int loaded = 0;

    if(input_filename == NULL)
    {
        fprintf(stderr, ""RED"ERROR: You must provide a file from where to load t3c\n"COLOR_RESET"");
        exit(EXIT_FAILURE);
    }

    file = fopen(input_filename, "r");
    if(file == NULL)
    {
        fprintf(stderr, ""RED"ERROR: Could not open file %s\n"COLOR_RESET"", input_filename);
        exit(EXIT_FAILURE);
    }

	printf(""BLU"INFO: Loading file...\n"COLOR_RESET"");
    
    while((ret = read_string_and_check_size(t3c_line, sizeof(t3c_line), file)) != -1)
    {
        if(ret == 0)
        {
            hash = strtok(t3c_line, ":");
            cleartext = strtok(NULL, "");
            if(hash != NULL && cleartext != NULL)
            {
                insert_node(tree_ptr, cleartext, hash);
                loaded++;
            }
            else
                fprintf(stderr, ""YEL"WARNING: Detected a line with incorrect format"COLOR_RESET"\n");
        }
        else
            fprintf(stderr, ""YEL"WARNING: Detected a line too long"COLOR_RESET"\n");
    }

    printf(""BLU"INFO: Loaded %d hashes\n"COLOR_RESET"", loaded);
    fclose(file);
}


void lookup(const char* input_filename)
{
    Node* tree = new_tree();
    load_t3c(&tree, input_filename);

    char hash[HASH_MAX_SIZE+1];
    char* cleartext = NULL;
    int ret = -1;

    while((ret = read_string_and_check_size(hash, sizeof(hash), stdin)) != -1)
    {
        if(ret == 0)
        {
                if(hash[0] == '\0')
                    continue;
                else if(strcmp(hash, QUIT) == 0)
                    break;
                else
                {
                    if((cleartext = find_node(tree, hash)) == NULL)
                        printf(""RED"No password corresponding to hash %s\n"COLOR_RESET"", hash);
                    else
                        printf("%s:"GRN"%s\n"COLOR_RESET"", hash, cleartext);
                }
        }
        else
            fprintf(stderr, ""YEL"WARNING: Hash must be at most %d characters"COLOR_RESET"\n", HASH_MAX_SIZE);
    }
    free_tree(tree);
}



int main(int argc, char** argv)
{
    char* mode = NULL;
    char* digest = NULL;
    char* input_filename;
    char* output_filename;
    parse_args(argc, argv, &mode, &digest, &input_filename, &output_filename);

    if(strcmp(mode, "generate") == 0)
        generate(input_filename, output_filename, digest);
    if(strcmp(mode, "lookup") == 0)
        lookup(input_filename);

    exit(EXIT_SUCCESS);
}