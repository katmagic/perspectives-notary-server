/**
 * The following functions are for parsing of request lines containing urls
 * with parameters in the form <ignored>?param=value<&><...>.  They
 * destructively modify the request string.  Parse begin initializes the
 * parsing while parse_next gets the parameters.  They return -1 if the
 * string cannot be parsed or if there are no more parameter value pairs.
 * Note the state string should not be notified by the calling functions.
 **/

/* Begins the parsing.
 * returns -1 if the request cannot be parsed 
 **/
int parse_begin(char **state, char *request);

/** 
 * Sets param and value to the next param-value pair.  If there are no more
 * pairs returns -1.  Otherwise returns 0
 **/
int parse_next(char **state, char **param, char **value);
