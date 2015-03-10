#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    if(argc != 3){
        printf(2, "Usage: move original_path new_path\n");
        exit();
    }
    if(move(argv[1], argv[2]) < 0)
        printf(2, "move %s %s: failed\n", argv[1], argv[2]);
    exit();
}