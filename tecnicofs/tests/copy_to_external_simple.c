#include "fs/operations.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main() {

    char *str = "AAA! AAA! AAA! ";
    char *path = "/f1";
    char *path2 = "external_file.txt";
    char to_read[40];
    int file;
    assert(tfs_init() != -1);

    tfs_open_paramts paramts;
    paramts.pth = path;
    paramts.flg = TFS_O_CREAT;

    tfs_open((void*)&paramts);
    file = paramts.rtn_value;
    assert(file != -1);

    assert(tfs_write(file, str, strlen(str)) != -1);

    assert(tfs_close(file) != -1);

    assert(tfs_copy_to_external_fs(path, path2) != -1);

    FILE *fp = fopen(path2, "r");

    assert(fp != NULL);

    assert(fread(to_read, sizeof(char), strlen(str), fp) == strlen(str));
    
    assert(strcmp(str, to_read) == 0);

    assert(fclose(fp) != -1);
    assert(tfs_destroy() != -1);
    unlink(path2);

    printf("Successful test.\n");

    return 0;
}
