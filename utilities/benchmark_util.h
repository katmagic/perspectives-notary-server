#ifndef _BENCHMARK_UTIL_H_
#define _BENCHMARK_UTIL_H_

// gets an approximate number of random service-ids from the DB
char ** get_random_serviceids(int num, DB* db, int *actual) {

    char **all_hosts = (char**)malloc(sizeof(char*) * num);

    DBC *cursorp;
    DBT key,data;
    int ret; 

    // first time, loop through just to count
    int count = 0;
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        printf("error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        ++count;
    }

    if(ret != DB_NOTFOUND) {
        printf("some error warming the cache: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB warming ");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);
    
    double ratio = (double) (count / num);
    int index = 0;
    // now take some random sample...
    
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        printf("error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    int r;
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        if(index < num) {
          // still think about add this one
          while(ratio <= (r = rand() / (RAND_MAX / ratio)));
          if(r == 1) 
             all_hosts[index] = strdup(key.data);
        }
    }

    if(ret != DB_NOTFOUND) {
        printf("some error warming the cache: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB warming ");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);


    *actual = index + 1;
    return all_hosts;
}



#endif
