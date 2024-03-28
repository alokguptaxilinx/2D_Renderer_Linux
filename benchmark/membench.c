#include <stdio.h> 
#include <sys/time.h>
#include <string.h>
#include <memory.h>
#include <pthread.h>

// Global variables
char str1[9999999]; // String array for data
long n = 5242880, lc, buffer_size; // Data size, loop count, buffer size
struct timeval t; // Structure for time measurement
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Mutex for thread synchronization

// Function to calculate time difference
long timediff(clock_t t1, clock_t t2) 
{
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000000 ;
    return elapsed;
}

// Function to calculate average of an array of doubles
double genavg(double a[])
{
    int s;
    double sum = 0;
    double avg;
    for(s = 0; s < 10000; s++)
    {
        sum += a[s];
    }
    avg = sum / 10000;
    return avg;
}

// Function to generate data
void mkdata(long n)
{
    printf("Constructing the file...\n");
    int i;
    for (i = 0; i < n; ++i)
    {
        str1[i] = (char)((rand() % 10) + 97);
    }
}

// Function for sequential read operation
void *seqread()
{
    char temp[n];
    long m;
    pthread_mutex_lock(&mutex1);

    for(m = 0; m < lc; m += buffer_size)
        memcpy(temp, str1, buffer_size);

    pthread_mutex_unlock(&mutex1);
}

// Function for sequential write operation
void *seqwrite()
{
    char str3[n];
    long q;
    pthread_mutex_lock(&mutex1);

    for(q = 0; q < lc; q += buffer_size)
        strncpy(str3, str1, buffer_size);

    pthread_mutex_unlock(&mutex1);
}

// Function for random read operation
void *randread()
{
    long w, v;
    char temp[n];
    pthread_mutex_lock(&mutex1);

    for (w = 0; w < lc; w += buffer_size) 
    {
        v = rand() % 200;
        memcpy(&temp[v], &str1[v], buffer_size);
    }
    pthread_mutex_unlock(&mutex1);
}

// Function for random write operation
void *randwrite()
{
    long e, g;
    char str3[n];
    pthread_mutex_lock(&mutex1);

    for (e = 0; e < lc; e += buffer_size)
    { 
        g = rand() % 200;
        strncpy(&str3[g], &str1[g], buffer_size);
    }
    pthread_mutex_unlock(&mutex1);
}

// Function to compute latency
void latency(long buffer_size1, long buffer_size)
{
    long r;
    char str5[n];
    clock_t t1, t2;
    double elapsed[10000];
    double tt;
    
    for(r = 0; r < 10000; r += 1) 
    {
        t1 = clock();
        memcpy(&str5[r], &str1[r], buffer_size); 
        t2 = clock();
        elapsed[r] = timediff(t1, t2);
    }
    tt = genavg(elapsed);
    printf("Latency: %lf ns\n", tt);
}

int main()
{
    int threadct, i, j, k, l, p, o, u, y, q;
    double s_t, e_t, t_t, tt;
    float ca1[40], ca2[40], ca3[40], ca4[40];
    pthread_t threads[threadct]; // Array of thread IDs

    // Input parameters
    printf("Enter the number of threads you want to create:");
    scanf("%d", &threadct);
    printf("\nEnter the size(1 byte/1024 bytes/1048576 bytes:");
    scanf("%ld", &buffer_size);

    // Generate data
    mkdata(n);
    lc = n / threadct;

    // Sequential Read
    gettimeofday(&t, NULL);
    s_t = t.tv_sec + (t.tv_usec / 1000000.0);
    for(i = 0; i < threadct; i++)
    {
        pthread_create(&threads[i], NULL, &seqread, NULL);
    } 
    for(p = 0; p < threadct; p++)
    {
        pthread_join(threads[p], NULL);
    }
    gettimeofday(&t, NULL);
    e_t = t.tv_sec + (t.tv_usec / 1000000.0);
    t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    printf("Throughput for seq read = %lf \n", (n / t_t) / (1024 * 1024));
    sleep(1);

    // Sequential Write
    gettimeofday(&t, NULL);
    s_t = t.tv_sec + (t.tv_usec / 1000000.0);    
    for(j = 0; j < threadct; j++)
    {
        pthread_create(&threads[j], NULL, &seqwrite, NULL);
    }
    for(o = 0; o < threadct; o++)
    {
        pthread_join(threads[o], NULL);
    }
    gettimeofday(&t, NULL);
    e_t = t.tv_sec + (t.tv_usec / 1000000.0);
    t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    printf("Throughput for seq write = %lf \n", (n / t_t) / (1024 * 1024));
    sleep(1);

    // Random Read 
    gettimeofday(&t, NULL);
    s_t = t.tv_sec + (t.tv_usec / 1000000.0);
    for(k = 0; k < threadct; k++)
    {
        pthread_create(&threads[k], NULL, &randread, NULL);
    }
    for(u = 0; u < threadct; u++)
    {
        pthread_join(threads[u], NULL);
    }
    gettimeofday(&t, NULL);
    e_t = t.tv_sec + (t.tv_usec / 1000000.0);
    t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    printf("Throughput for rand read = %lf \n", (n / t_t) / (1024 * 1024));
    sleep(1);

    // Random Write
    gettimeofday(&t, NULL);
    s_t = t.tv_sec + (t.tv_usec / 1000000.0);
    for(l = 0; l < threadct; l++)
    {
        pthread_create(&threads[l], NULL, &randwrite, NULL);
    }
    for(y = 0; y < threadct; y++)
    {
        pthread_join(threads[y], NULL);
    }
    gettimeofday(&t, NULL);
    e_t = t.tv_sec + (t.tv_usec / 1000000.0);
    t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    printf("Throughput for rand write = %lf \n", (n / t_t) / (1024 * 1024));
    sleep(1);

    printf("Ending...\n");

    // Latency calculation
    latency(buffer_size, buffer_size);

    return 0;	
}
