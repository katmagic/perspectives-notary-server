#ifndef _FILE_LIST_CONVERT_H_
#define _FILE_LIST_CONVERT_H_

#include <stdlib.h> 
#include "common.h"


ssh_key_info_list *read_key_info_from_file(FILE *f);

void read_key_data_from_file(FILE *f, char *buf_out, int *data_len);


#endif
