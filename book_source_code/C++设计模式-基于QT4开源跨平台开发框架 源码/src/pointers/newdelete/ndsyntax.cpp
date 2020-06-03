{
 int* ip = 0;   /* null pointer */
 ip = new int;  /* allocate space for an int */
 int* jp = new int(13);     /* allocate and initialize */
 [...]      
 delete ip;    /* Without this, we have a memory leak. */
 delete jp;
}
