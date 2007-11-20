#include "mysql.h"
#include "mysql_storage.h"


unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char** argv) {

        MYSQL* conn1 = open_mysql_conn("localhost","root","moosaysthecow",
                                        "ssh");
        MYSQL* conn2 = open_mysql_conn("localhost","root","moosaysthecow",
                                        "ssh");
        char *query_buf = "SELECT sid,kid,time from observations order by time";

	if(mysql_real_query(conn1, query_buf, strlen(query_buf)) != 0) {
		fprintf(stderr, "Error on query '%s' accessing observations: %s \n",
			query_buf, mysql_error(conn1));
		return 0;
        }
  
	
	MYSQL_RES *result = mysql_store_result(conn1);
	if(!result) {
		fprintf(stderr, "no observations found: %s \n",
			mysql_error(conn1));
		return 0;
        }

	// loop once for each unique key that we have seen for this
	// service identifier
	while(1) {
		MYSQL_ROW row = mysql_fetch_row(result);
		if(row == NULL) break;
		if(row[0] == NULL) break;
    
                int sid = atoi(row[0]);
		int kid = atoi(row[1]);
                unsigned int time = atoi(row[2]);
	
                update_timespan(conn2,sid,kid,time);
	}

        return 0;
}
