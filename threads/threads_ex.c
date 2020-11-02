#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg)                                        \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg)                               \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define STACK 1000
#define MEGSTACK 1000000
#define N_MAX 128
#define STR_MAX 256
#define DATA_MAX 12

typedef struct {
    float noise[DATA_MAX][DATA_MAX];
    char source[STR_MAX];
} data_t;

data_t SHARED_DATA;
pthread_mutex_t datamutex;

struct thread_info {    /* Used as argument to thread_start() */
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int       thread_num;       /* Application-defined thread # */
    char     *argv_string;      /* From command-line argument */
};

/* Thread start function: display address near top of our stack,
   and return upper-cased copy of argv_string */

static void *
thread_start(void *arg)
{
    struct thread_info *tinfo = arg;
    char *uargv, *p;
    pthread_attr_t attr;
    size_t t_stacksize;
    FILE * read_fd;
    read_fd = fopen("test.txt", "r");

    pthread_attr_getstacksize(&attr,&t_stacksize);
    printf("Thread %d: stacksize:%li\n",
           tinfo->thread_num, t_stacksize);
    printf("Thread %d: top of stack near %p; argv_string=%s\n",
           tinfo->thread_num, &p, tinfo->argv_string);


    int i,j;
    int rounds;
    for (rounds=0;rounds <5;rounds++)
        {
            pthread_mutex_lock(&datamutex);
            for (i =0;i < DATA_MAX;i++)
                {
                    for(j=0; j< DATA_MAX; j++)
                        {
                            SHARED_DATA.noise[i][j]=tinfo->thread_num;
                            /* fprintf(stderr, "SHARED_DATA.noise[%d][%d]=%f", */
                            /*         i,j,SHARED_DATA.noise[i][j]); */
                        }
                }
            snprintf(SHARED_DATA.source,STR_MAX,"%d",tinfo->thread_num);
            pthread_mutex_unlock(&datamutex);
        }
    char line[128];
    char str[128];
    while ((p = fgets(line,sizeof(line),read_fd)) != NULL)
        {
            pthread_mutex_lock(&datamutex);

            //fprintf(stdout,"line: %s\n",line);
            sscanf(line,"%*[^(]%[^)]",str);
            fprintf(stdout, "thread:%d str : %s\n",
                    tinfo->thread_num,str);

            if (line ==NULL || str==NULL )
                {
                    break;
                }
            pthread_mutex_unlock(&datamutex);
        }

    p=NULL;
    uargv = strdup(tinfo->argv_string);
    if (uargv == NULL)
        handle_error("strdup");

    for (p = uargv; *p != '\0'; p++)
        *p = toupper(*p);

    return uargv;
}


int
main(int argc, char *argv[])
{
    int s, tnum, opt, num_threads;
    struct thread_info *tinfo;
    pthread_attr_t attr;
    int verbose;
    void *res;
    size_t stacksize;

    /* The "-s" option specifies a stack size for our threads */

    char usage[]="Usage: %s [-v verbose] [-n numthreads] \n";
    if (argc < 2)
    {
        fprintf(stderr, usage,
                argv[0]);
        exit(EXIT_FAILURE);

    }
    verbose = -1;
    while ((opt = getopt(argc, argv, "v:n:")) != -1) {
        switch (opt) {
        case 'v':
            verbose = strtoul(optarg, NULL, 0);
            break;
        case 'n':
            num_threads = strtoul(optarg, NULL, 0);
            break;
        default:
            fprintf(stderr, usage,
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    /* Initialize thread creation attributes */

    s = pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr,&stacksize);
    printf("Default stack size = %li\n", stacksize);
    if (s != 0)
        handle_error_en(s, "pthread_attr_init");

    stacksize = sizeof(double)*STACK*STACK+MEGSTACK;
    printf("New stacksize = %li\n",stacksize);
    pthread_attr_setstacksize(&attr,stacksize);
    if (s != 0)
        handle_error_en(s, "pthread_attr_setstacksize");

    s= pthread_mutex_init(&datamutex,NULL);
    if (s != 0)
        handle_error_en(s, "pthread_mutex_init");

    /* Allocate memory for pthread_create() arguments */

    tinfo = calloc(num_threads, sizeof(struct thread_info));
    if (tinfo == NULL)
        handle_error("calloc");

    /* Create one thread for each command-line argument */

    for (tnum = 0; tnum < num_threads; tnum++) {
        tinfo[tnum].thread_num = tnum + 1;
        tinfo[tnum].argv_string = usage;
        //memcpy(tinfo[tnum].pentry.lbname,"happy",6);
        /* The pthread_create() call stores the thread ID into
           corresponding element of tinfo[] */

        s = pthread_create(&tinfo[tnum].thread_id, &attr,
                           &thread_start, &tinfo[tnum]);
        if (s != 0)
            handle_error_en(s, "pthread_create");
    }

    /* Destroy the thread attributes object, since it is no
       longer needed */

    s = pthread_attr_destroy(&attr);

    if (s != 0)
        handle_error_en(s, "pthread_attr_destroy");

    /* Now join with each thread, and display its returned value */

    for (tnum = 0; tnum < num_threads; tnum++) {
        s = pthread_join(tinfo[tnum].thread_id, &res);
        if (s != 0)
            handle_error_en(s, "pthread_join");

        printf("Joined with thread %d; returned value was %s\n",
               tinfo[tnum].thread_num, (char *) res);
        free(res);      /* Free memory allocated by thread */
    }

    free(tinfo);
    fprintf(stdout,"Final source: %s\n",
            SHARED_DATA.source);
    exit(EXIT_SUCCESS);
}
